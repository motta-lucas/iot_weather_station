---
type: til

created: 2026-09-21

tags:
- arduino
- nodemcu-esp8266

category: electronics

---

  

# TIL - 2026-09-21 - Arduino - Invalid head of packet

  

## 📚 Goal
<!-- Clear and Simple description of learning -->

Solving the issue "A fatal esptool.py error occurred: Invalid head of packet (0xFF)".

I was trying to load my first code into my NODEMCU ESP8266 using the "Blink" example and received the error above as an output.  

This error indicates that the computer could'nt properly communicate with the ESP8266 because the chip did not enter record mode (Flash/Download) or there is noise/interference in the serial line.

## 🔧 Procedure
<!-- Technical or Conceptual explanation -->

Solution
1. Press and **hold** the **FLASH** button (or **BOOT**) on ESP8266.
2. While doing it, press and let go the **RST** button (or **EN**).
3. Let go the **FLASH** button.
4. Try to send the code again

In my case this solved the issue.

## 💻 Hands on
<!-- Codes, commmands ou practical cases -->

![[Flash and Rst button on NODEMCU ESP8266.png]]
  
##   ❓  Why Use it

This specific solution manually forces the board to go into coding mode.

The following message appeared as an output on Arduino IDE:

```
Hard resetting via RTS pin...
```

## 🎯 When to use
<!-- Where does it apply? -->

When the board doesn't communicate properly with computer.
  
  

## ⚠️ Catches
<!-- Common pitfals -->

- Manually forcing coding mode worked for me but it might also be the case that:
1. The cable is too long, or too old and might be causing the so called interference
2. The GPIO0 is not connected to GND. For NODEMCU ESP8266 this is done by default, but in other cases it might be needed. Or the NODEMCU ESP8266 might have issue with that regard.
3. The drivers in the computer are not correctly set.
  
## 🔗 Related notes
<!-- Internal references and other notes -->

- [[Arduino - Driver installation]]
- [[Arduino - Setting up Arduino IDE]]
- [[Arduino Pins - NOMDECU ESP8266]]

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

 - 2026-09-21 - <!-- Insert Comment -->
