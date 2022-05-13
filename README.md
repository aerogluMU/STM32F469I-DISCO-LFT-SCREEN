

# STM32F469I-DISCO-LFT-SCREEN

## Content of Project

The subject of this project is to develop a software that controls led states using various functions and provides communication using various communication protocols. In addition, it is to make a design that will show these situations on the TFT screen.

- The functions to be used to change the states of the LEDs are respectively: **GPIO TOGGLE**

- The communication protocols used are respectively: **USART**, **Can BUS**
	> USART and Can BUS communication protocols are bilateral.

## The Board Used in The Project

This project used **STM32F469I-DISCO** board.

## Pinouts

- USART pinouts: **PC6**, **PC7**
	> PC6 --> USART6 **TX**
	
	> PC7 --> USART6 **RX**

## Flowchart of Project

```mermaid
graph TD
    A[Start] --> B[Initialization]
    B --> C[Main Menu]
    C --> D{Is LEDS button pressed?}
    C --> E{Is USART button pressed?}
    D --> |Yes| F(LEDS Menu)
    D --> |No| C
    F --> G{Is Main Menu button pressed?}
    F --> H{Is toggle button of LED3 status on?}
    F --> K{Is toggle button of LED4 status on?}
    G --> |Yes| C
    G --> |No| F
    H --> |Yes| HYES(LED3 on)
    H --> |No| HNO(LED3 off)
    K --> |Yes| KYES(LED4 on)
    K --> |No| KNO(LED4 off)
    E --> |Yes| U(USART Menu)
    E --> |No| C
    U --> L{Is Send ''Hello'' button pressed?}
    U --> M{Is USART6 Receive Interrupt?}
    U --> N{Is Main Menu button pressed?}
    N --> |Yes| C
    N --> |No| U
    L --> |Yes| LYES(Send ''Hello'' string using USART6)
    L --> |No| U
    M --> |Yes| MYES(Display received data)
    M --> |No| U
```
