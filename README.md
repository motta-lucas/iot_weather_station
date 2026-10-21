---

type: project
title: IoT - Arduino Weather Station
created: 2026-09-21
updated: 2026-10-21

tags:
- arduino
- nodemcu-esp8266
---


### Problem

The actual problem was that I wanted to be a Data Engineer. So, I needed some real data (someone said). Someone else said "you can generate synthetic data", but what is the fun in that?

I also wanted to learn a bit about microcontrollers and maybe build some cool stuff in the future. So I decided to buy one of this learning kits and built a Weather Station to have some real data. The focus would be on setting up an API, build an ETL pipeline and at the end, make it possible to perform some simple analysis on the data. 

Ps.: Now I've created a monster and I'm reading about bare-metal. 


---

## 🎯 Initial Project Setup

### General idea
<!--What are the data sources and steps to be performed? 
	At first it will be just a draft, but this section should be fairly defined before any coding beggins
-->

Assemble a circuit to retrieve:
	- Temperature
	- Humidity
	- Pressure
	- Air quality


#### Deliverables

## 🏗️ Architecture


#### 🎨 Visuals

![Arduino - IoT weather station - Circuit.png](notes/Arduino%20-%20IoT%20weather%20station%20-%20Circuit.png)
> **Figure 1:** *Initial circuit.*

>[!warning]
>First load the code into ESP8266
>Then connect D0 to RST to enable ESP8266 to come back from deep sleep

![Arduino - IoT weather station - Circuit - D0 to RST.png](notes/Arduino%20-%20IoT%20weather%20station%20-%20Circuit%20-%20D0%20to%20RST.png)
> **Figure 2:** *Circuit with D0 connected to RST to enable return from deep sleep.*

![Weather Station - Real circuit.png](notes/Weather%20Station%20-%20Real%20circuit.png)
> **Figure 3:** *Real built circuit.*

🧩 **Legendas e Convenções**
<!-- Explain colors, simbles, icons whenever necessary -->
-
> [!tip] Edit Diagram
> Double click on diagram to edit on Excalidraw  
> Or use: `Ctrl/Cmd + Click` to open on a new tab

---
## 🗓️ Timeline

### Step 1: Setup ✅


- [ ] [Arduino - Setting up Arduino IDE](Arduino%20-%20Setting%20up%20Arduino%20IDE.md)
- [ ] [Arduino - Driver installation](Arduino%20-%20Driver%20installation.md)
- [ ] [Arduino Pins - NOMDECU ESP8266](notes/Arduino%20Pins%20-%20NODEMCU ESP8266.md)
- [ ] [Arduino - Set secrets.h for credentials](notes/Arduino%20-%20Set%20secrets.h%20for%20credentials.md)
- [ ] Write code - https://github.com/motta-lucas/iot_weather_station
	- [ ] Import libraries
	- [ ] Define inputs/outputs
	- [ ] Read/Write digital entries
	- [ ] Read/Write analogic entries
	- [ ] Connect Arduino to WiFi
	- [ ] Enter deep sleep
  

### Step 2: Build 🚧

- [ ] Build Circuit
- [ ] Load code
- [ ] Connect R0 to RST if deep sleep is set up
- [ ] [Weather Station API](https://github.com/motta-lucas/weather_station.git)
  

### Step 3: Testing 📅

- [ ] Check if Serial Monitor prints:

```
Connecting to WiFi
WiFi connected
Loged in successfully
========Weather Station IoT==========
[DHT] Humidity: 65.0%
[DHT] Temperature: 30.8 C
[SEND] Starting sendSensorData()
[SEND] Token available
[SEND] URL: https://192.168.0.19/event/new
[SEND] Sending POST request...
API Answer: HTTP 200
{"message":"Event created successfully"}
Reading successfully sent!
[SLEEP] Entering deep sleep for 30 minutes...
```


- [ ] Check on [Weather Station API](https://github.com/motta-lucas/weather_station.git) server if it information is being saved properly:

	```bash
	curl -k -X GET 'https://localhost/event/'   -H 'accept: application/json'
	```

- Expected output:
```bash
curl -k -X GET 'https://localhost/event/'   -H 'accept: application/json'

[{"_id":"6bb24934-a6ee-4ebb-98f1-e654eb6490e4","timestamp":"2026-10-17T00:36:01.439000","device_id":"weather_station_01","creator":"sensor@iot.com","humidity":68.0,"temperature":29.5,"relative_pressure":1008.264413,"abs_pressure":1006.71159,"ppm":0.185847,"rain_reading":1},{"_id":"45502693-81c4-407e-8b0a-93c3fb95e1f4","timestamp":"2026-10-17T00:07:30.883000","device_id":"weather_station_01","creator":"sensor@iot.com","humidity":68.0,"temperature":29.4,"relative_pressure":1008.492714,"abs_pressure":1006.93954,"ppm":0.185847,"rain_reading":1}
```
### Step 4:  Deploy 📅

- [ ] [[Weather Station - Data Pipeline]]

---
## 🕷Problems

- [Arduino - Invalid head of packet]
- On serial monitor, always check if the set baud rate on code matches the baud rate output on the serial monitor.
- Had some issues with wiring. Especially with DHT11 connections
- To power it continuously I tried a power bank first, but it would last about a day only. So I bought a simple cellphone charger that outputs 5v and connected it to the serial port.

---
## 📈 Results

- 
## 📝 Permanent Notes Created/Updated

<!-- Links to permanent notes -->

-[[ESP8266 - GPIO Pins]]
-[[ESP8266 Protocols]]


---
## 🔥 TILs Created

<!-- Links for TILs created on the main topics-->

- [[How to read the color code for resistors]]
- [[Arduino - Traffic Lights - Car_Pedestrians]]
- [[Arduino - Taking inputs from the serial monitor]]

---
## 🔗 Links Importantes

- https://app.cirkitdesigner.com/project
- https://medium.com/@punnyarthabanerjee/esp8266-handling-data-in-json-7c6f62c9062e
- https://app.cirkitdesigner.com/project/43f60b29-b361-4df2-907a-c41c36d677e4
  

- **Repos:** https://github.com/motta-lucas/iot_weather_station
- **Dashboards:** [Link quando disponível]
---
