# Crazy Alarm System

## Team Members
| Name  | GitHub
| ------------- | ------------- |
| Nada Atia | nada-dev
| Mariam Fawzy | mariam606
| Mira Shanouda | mirashanouda
| Rawan Hamad | rawansameh

## Proposal
Alarms are important in our lives as they can help to make waking easier, and may help to reinforce natural circadian rhythms that strengthen the patterns of sleep and wakefulness. 

We noticed that the alarms we use today are very traditional and as our brains prefer to be in the comfort zone, sometimes it is hard to overcome the urge to sleep and we sleep instead of waking up for our important meetings. We thought to implement a smart alarm system. The main component of this system is a car that is connected to some other sensors and I/O devices. One of the components connected to the car is a buzzer that is triggered when the current time matches a previously determined time using an RTC. At the same time, the car starts to move. In addition, the car is connected to a LCD that shows a riddle. To stop the buzzer and the car movement, the user should solve the riddle and input it to the system. This will make the person be more active as starting our day with some simple movements is the best thing to help us get up easily.

## Initial Design
![Initial_Design](https://user-images.githubusercontent.com/67865802/235510986-ef036b8c-790e-4bfb-bf2e-44a2c3577abc.jpg)

## Identified components:
| Hardware Components 
| -------------
| [STM32L432KC Microcontroller](https://www.st.com/en/microcontrollers-microprocessors/stm32l432kc.html)
| [USB A-to-C](https://ram-e-shop.com/product/usb-cable-micro-copy/)
| [LCD Module Display I2C 1602 QAPASS](https://ram-e-shop.com/product/lcd-2x16-blue/)
| [Pmod KYPD: 16-button Keypad](https://www.amazon.co.uk/DIGILENT-410-195-410-195-16-Buttons-Keyboard/dp/B0792G3C45)
| [The Pololu TReX Motor Controller](https://www.pololu.com/product/777)
| [Dagu Wild Thumper 4WD Chassis](https://www.pololu.com/product/1567)
| [DS3231 High Precision Real Time Clock (RTC)](https://store.fut-electronics.com/products/ds3231-high-precision-rtc-module-ds3231)
| [Jumper Wires](https://ram-e-shop.com/product/ph60-mf-20cm/)
| [Bread Board](https://ram-e-shop.com/product/bb01-bread-board/)
| [Buzzer](https://ram-e-shop.com/product/buzzar3v/)

| Software Components 
| -------------
| Keil uVision 5
| STM32CubeMX
