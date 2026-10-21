---
type: permanent-note

created: 2026-07-31
updated: 2026-07-31

tags:
- electronics
- arduino

status: 🌱 seedling
excalidraw-diagram: "[[Arduino Pins - NOMDECU ESP8266.excalidraw]]"
excalidraw-open-md: true

north:
- "[[ESP8266 - GPIO Pins]]"
south:
east:
west:

---
> [!tip] status:
>	🌱 seedling (Once it is turned into a permanent note)
>	🌿 sapling (Once at least 3 links are added)
>	🌳 evergreen (Once it is indexed or Used in a Project)


> [!tip] links:
>	⬆️ North (Origin) - Where did this idea came from?
>	⬇️ South (Destiny) - Where does this idea lead to?
>	➡️ East (Agreement) - Other notes that support this idea.
>	⬅️ West (Opposition) - Ideias that opposite to this note.

> [!abstract]- Total number of links

> **Links:** `= length(this.north) + length(this.south) + length(this.east) + length(this.west)`
  
# Arduino Pins - NOMDECU ESP8266

---

> [!tip] What kind of note is this?
>	🤔Question - What are the problems the content is trying to deal with?
>	💡 Evidence - What are the examples the author uses to develop his thinking?
>	📊 Conclusion - If we follow the evidence to deal with the question in place, where will that lead to?

## Main unit of information

The NodeMCU ESP8266 board exposes several pins that can be used for different purposes. Some of the pins are labeled with names such as `CLK`, `SD0`, `CMD`, etc.

![[NOMDECU ESP8266 internal pins.png]]

These labels correspond to the ESP8266's internal SPI Flash interface. They indicate how those pins are used internally by the microcontroller to communicate with its external Flash memory, rather than how they should be used to connect external peripherals.

Although these pins physically exist on the board, they are reserved for the Flash memory and should normally not be used in user projects.

For connecting external devices, the NodeMCU provides another set of pins labeled `D0` to `D8`, `RX`, `TX`, and `A0`. Most tutorials and libraries refer to these labels or to their corresponding GPIO numbers.

![[NODEMCU ESP8266 - external pins notation.png]]

- **Internal SPI Flash pins** (`CLK`, `CMD`, `SD0`...)
- **Board pin labels** (`D0`–`D8`, `RX`, `TX`, `A0`)
- **GPIO numbers** (`GPIO0`, `GPIO2`, `GPIO14`...)
  
### Additional information

> [!note] 
> The labels `D0`–`D8` are board pin names, not GPIO numbers. 
> 
> For example: 
> 
> - D5 → GPIO14 
> - D6 → GPIO12 
> - D7 → GPIO13 
> - D8 → GPIO15

This might avoid issues since some places will use the "D" notation

````cpp
</> C++
digitalWrite(D5, HIGH);
````

Or the "GPIO" notation

````cpp
</> C++
digitalWrite(I4, HIGH);
````

#### 🎨 Visuals

![[Arduino Pins - NOMDECU ESP8266.excalidraw|100%]]

🧩 **Legendas e Convenções**

<!-- Explain colors, simbles, icons whenever necessary -->

> [!tip] Edit Diagram
>Double click on diagram to edit on Excalidraw  
>   Or use: `Ctrl/Cmd + Click` to open on a new tab

  
  

---
## 📚 Bibliography

  
