---
type: til

created: 2026-10-16

tags:
- security
- credentials
category: software-engineering

---

  

# TIL - 2026-10-16 - Arduino - Set secrets.h for credentials

## 📚 Goal
<!-- Clear and Simple description of learning -->

Similar to [[Set up .env for data projects | .env]] it is not a good pactice to hardcode credentials on code.

For C++ projects, the file created is a secrets.h
  
  
## 🔧 Procedure
<!-- Technical or Conceptual explanation -->

  
  
## 💻 Hands on
<!-- Codes, commmands ou practical cases -->

- secrets.h content:
```
#define WIFI_SSID "<WIFI NAME>"

#define WIFI_PASSWORD "<PASSWORD>"

#define API_USERNAME "<API USER NAME>"

#define API_PASSWORD "<API USER NAME - PASSWORD>"

```

- Calling it on your .ino file
```
#include "secrets.h"

<...>

String body = "username=" + String(API_USERNAME) + "&password=" + String(API_PASSWORD);

<...>

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
```

Check https://github.com/motta-lucas/iot_weather_station/blob/main/weather_station.ino for detailed implementation
##   ❓  Why Use it

To segregate credentials from files that go online and are exposed.

## 🎯 When to use
<!-- Where does it apply? -->
Whenever you need to have credentials logged into the circuit and want to take the safe route.
  
  
## ⚠️ Catches
<!-- Common pitfals -->
- keep secrets.h on your .gitignore and your .dockerignore and don't share it with anyone
  
  
## 🔗 Related notes
<!-- Internal references and other notes -->


## 🔗 Resources
<!-- Links, documentation, references-->
-

---


## 📝 Version control
<!-- Register any big changes in the notes 
	- If a certain snippet has changed
	- If you added a significant amount of resources
	- Or any other major changes on how to apply this knowledge
-->

 - 2026-10-16 - <!-- Insert Comment -->
