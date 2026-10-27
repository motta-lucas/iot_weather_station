//Wifi information
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "secrets.h"

//Sensors libraries
#include <DHT.h> //DHT11 library
#include <SFE_BMP180.h> //BMP180 sensor library
#include <Wire.h> //I2C communication library

// Server information
const char* loginUrl = "https://192.168.0.26/user/signin";
const char* sensorUrl = "https://192.168.0.26/event/new";

// Sensor models
const char* HUMIDITY_SENSOR = "dht11";
const char* TEMPERATURE_SENSOR = "dht11";
const char* RELATIVE_PRESSURE_SENSOR = "bmp180";
const char* ABS_PRESSURE_SENSOR = "bmp180";
const char* PPM_SENSOR = "mq-135";
const char* RAIN_READING_SENSOR = "mh-rd yl-83";

BearSSL::WiFiClientSecure client;
String accessToken;

const uint64_t SLEEP_TIME_US = 1800ULL * 1000000ULL;
const unsigned long RETRY_DELAY_MS = 5000;

bool loginAPI(){
  HTTPClient http;

  client.setInsecure();

  if (!http.begin(client, loginUrl)){
    Serial.println("Failed to initalize login");
    return false;
  }

  http.addHeader(
    "Content-Type",
    "application/x-www-form-urlencoded"
  );

  String body = "username=" + String(API_USERNAME) + "&password=" + String(API_PASSWORD);

  int code = http.POST(body);
  String response = http.getString();

  if (code==200){
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, response);

    if(!error && doc["access_token"].is<const char*>()){
      accessToken = doc["access_token"].as<String>();
      http.end();
      Serial.println("Loged in successfully");
      return true;
    }
  }

  Serial.printf("Failed to login. HTTP: %d\n", code);
  Serial.println(response);
  http.end();
  return false;
}

//The public CA of nginx will load here
HTTPClient http;

//GIPOs definition

//Humidity and temperature
#define DHTPIN D3 //D3 Pin will be responsible for DHT11 readings
#define DHTTYPE DHT11 //Defines the sensor DHT11 as the sensor type to be used by library <DHT.h>

DHT dht(DHTPIN, DHTTYPE); //Initialize a dht object of type DHT passing as parameters the PIN (DHTPIN) and the sensor type (DHTTYPE)

float u = 0.0; //Defines the variable u to store humidity values
float t = 0.0; //Defines the variable t to store temperature values

//Air quality
int airSensor = A0; //Sets analogic pin A0 as the variable AirSensor
float m = -0.3376; //Slope parameter
float b = 0.7165; //Y-intercept parameter
float R0 = 23.36; //R0 resistence found at air calibration tutorial
float sensor_volt; //Defines the variable sensor_volt to store sensor voltage
float Rs; //Defines Rs variable to store air resistance
float Rs_R0_ratio; //Defines variable to store the ratio between Rs and R0
float ppm_log; //Variable to store the ppm value in log scale
float ppm = 0.0; //Variable to store the ppm value in linear scale

//Atmosferic pressure
SFE_BMP180 sensorP; //Defines the sensorP object
#define ALTITUDE 13 //Define the altitude of the place where measurement will be made
char status; //Auxiliar variable to check results
double temperature; //Variable to store temperature values
double abs_pressure; //Variable to store absolute pressure values
double relative_pressure = 0.0; //Variable to store relative pressure values

//Rain detector
int rainSensor = D5; //Sets digital pin D5 as variable for rainSensor
int rainReading = 0; //Variable to store readings from rainSensor
String rain; //Variable to store message "It is raining" or "It is not raining"

//Function - reading humidity and temperature - Sensor DHT11
void sensorDHT() {
  u = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(u) || isnan(t)) {
    Serial.println("[DHT] Failed to read sensor!");
    return;
  }

  Serial.printf("[DHT] Humidity: %.1f%%\n", u);
  Serial.printf("[DHT] Temperature: %.1f C\n", t);
}

//Function - reading air quality - Sensor MQ-135
void airQuality(){
  sensor_volt = analogRead(airSensor)*(3.3/1023.0);
  Rs = ((5.0 * 10.0) / sensor_volt) - 10.0; //Calculate the resistance Rs for the sensor
  Rs_R0_ratio = Rs / R0;
  ppm_log = (log10(Rs_R0_ratio) - b) / m;
  ppm = pow(10, ppm_log);
}

//Function - Absolute and relative pressure readings - Sensor BMP180
void Pressure(){
  status = sensorP.startTemperature(); //Initialize temperature readings
  if (status != 0){
    delay(status);
    status = sensorP.getTemperature(temperature);
    if (status != 0){
      status = sensorP.startPressure(3);
      if (status != 0){
        delay(status);
        status = sensorP.getPressure(abs_pressure, temperature);
        if (status != 0){
          relative_pressure = sensorP.sealevel(abs_pressure, ALTITUDE);
        }
      }
    }
  }
}

//Function - Rain detector - Rain sensor
void detectRain(){
  rainReading = digitalRead(rainSensor);
  if (rainReading){
    rain = "It is not raining";
  } else {
    rain = "It is raining";
  }
}

// Defining function to prepare data to be sent to my API
bool sendSensorData(
  float u,
  float t,
  double relative_pressure,
  double abs_pressure,
  float ppm,
  int rainReading
  ) {
  Serial.println("[SEND] Starting sendSensorData()");

  if (accessToken.isEmpty()) {
    Serial.println("[SEND] Token is empty; loggin in...");
    
    if(!loginAPI()){
      Serial.println("[SEND] Login failed");
      return false;
    }
    
  }

  Serial.println("[SEND] Token available");
  Serial.print("[SEND] URL: ");
  Serial.println(sensorUrl);

  HTTPClient http;

  if (!http.begin(client, sensorUrl)){
    Serial.println("Failed to initialize request");
    return false;
  }
  // JSON document with readings
  JsonDocument doc;

  // Sensor readings
  doc["humidity"] = u;
  doc["temperature"] = t;
  doc["relative_pressure"] = relative_pressure;
  doc["abs_pressure"] = abs_pressure;
  doc["ppm"] = ppm;
  doc["rain_reading"] = rainReading;

  // Sensor models
  doc["humidity_sensor"] = HUMIDITY_SENSOR;
  doc["temperature_sensor"] = TEMPERATURE_SENSOR;
  doc["relative_pressure_sensor"] = RELATIVE_PRESSURE_SENSOR;
  doc["abs_pressure_sensor"] = ABS_PRESSURE_SENSOR;
  doc["ppm_sensor"] = PPM_SENSOR;
  doc["rain_reading_sensor"] = RAIN_READING_SENSOR;

  Serial.println("[SEND] Sending POST request...");

  String payload;
  serializeJson(doc,payload);

  http.addHeader("Content-Type", "application/json");
  http.addHeader(
    "Authorization",
    "Bearer " + accessToken
  );

  int code = http.POST(payload);
  String response = http.getString();

  if (code == 401 || code == 403){
    // Token expired or rejected: try new login
    http.end();
    accessToken = "";

    if (!loginAPI()){
      return false;
    }

    Serial.println("[AUTH] Token rejected. It will try again next time.");
    return false;
  }

  Serial.printf("API Answer: HTTP %d\n", code);
  Serial.println(response);

  http.end();
  return code >= 200 && code < 300;
}

void setup(){
  Serial.begin(115200);

  dht.begin();
  sensorP.begin();
  delay(500);

  pinMode(airSensor, INPUT);
  pinMode(rainSensor, INPUT);

  Serial.println(" ");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
        millis() - startAttempt < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WIFI] Conectado!");
    Serial.print("[WIFI] IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n[WIFI] Falha na conexao");
    Serial.print("[WIFI] Status: ");
    Serial.println(WiFi.status());
  }

  Serial.println("WiFi connected");

  Serial.print("WiFi status: ");
  Serial.println(WiFi.status());

  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  if (!loginAPI()){
    Serial.println("It was not possible to connect to API");
  }
}

void loop(){
  Serial.println("========Weather Station IoT==========");
  sensorDHT();
  if (isnan(u) || isnan(t)) {
    Serial.println("[ERROR] Invalid DHT readings; skipping upload.");
    delay(15000);
    return;
  }

  airQuality();
  Pressure();
  detectRain();

  bool success = sendSensorData(
  u, t, relative_pressure,
  abs_pressure, ppm, rainReading
  );

  if (success) {
    Serial.println("Reading successfully sent!");
  } else {
    Serial.println("Failed to send readings.");
  }

  Serial.println("[SLEEP] Entering deep sleep for 30 minutes...");
  Serial.flush();

  ESP.deepSleep(SLEEP_TIME_US);
}