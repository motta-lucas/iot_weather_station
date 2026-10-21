---
type: til

created: 2026-09-21

tags:
- arduino
- driver

category: electronics

---

  

# TIL - 2026-09-21 - Arduino - Driver installation

  

## 📚 Goal
<!-- Clear and Simple description of learning -->

While working on my mini weather station, I had to install the arduino drivers to make it work
  
  

## 🔧 Procedure
<!-- Technical or Conceptual explanation -->

1. On windows "Execute" type "mmc devmgmt.msc"
2. Check if the NODEMCU ESP8266 (or the corresponding board) is being correctly read by the system. (COM3 in the image below)

![[Correct Port being located by the system.png]]
  
3. If that is not the case and you see something like:

![[Driver not found by the system.png]]

4. Download the correct driver on https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

## 💻 Hands on
<!-- Codes, commmands ou practical cases -->

```



```

  
##   ❓  Why Use it



## 🎯 When to use
<!-- Where does it apply? -->

  
  

## ⚠️ Catches
<!-- Common pitfals -->

  
  
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

 - 2026-09-21 - <!-- Insert Comment -->
