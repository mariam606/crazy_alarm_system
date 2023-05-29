# Crazy Alarm System

## Team Members
| Name  | GitHub
| ------------- | ------------- |
| Nada Atia | [nada-dev](https://github.com/nada-dev)
| Mariam Fawzy | [mariam606](https://github.com/mariam606)
| Mira Shanouda | [mirashanouda](https://github.com/mirashanouda)
| Rawan Hamad | [rawansameh](https://github.com/mirashanouda)

# First Milestone
## Proposal
Alarms are important in our lives as they can help to make waking easier, and may help to reinforce natural circadian rhythms that strengthen the patterns of sleep and wakefulness. 

We noticed that the alarms we use today are very traditional and as our brains prefer to be in our comfort zone, sometimes it is hard to overcome the urge to sleep and we sleep instead of waking up for our important meetings. We thought to implement a smart alarm system. The main component of this system is a car that is connected to some other sensors and I/O devices. One of the components connected to the car is a buzzer that is triggered when the current time matches a previously determined time using an RTC. At the same time, the car starts to move. In addition, the car is connected to an LCD that shows a riddle. To stop the buzzer and the car movement, the user should solve the riddle and input it into the system. This will make the person more active as starting our day with some simple movements is the best thing to help us get up easily.

## Updated Block Diagram
![Updated_Diagram](https://github.com/shalan/CSCE4301-WiKi/assets/67865802/1b39d7f6-5018-4d0a-83a8-e395fe46980b)

## Identified components:
| Hardware Components 
| -------------
| [STM32L432KC Microcontroller](https://www.st.com/en/microcontrollers-microprocessors/stm32l432kc.html)
| [USB A-to-C](https://ram-e-shop.com/product/usb-cable-micro-copy/)
| [LCD (Character LCD 2×16) Blue 1602 QAPASS](https://ram-e-shop.com/product/lcd-2x16-blue/)
| [I2C LCD Serial Interface Module](https://uge-one.com/i2c-lcd-serial-interface-module.html)
| [Pmod KYPD: 16-button Keypad](https://www.amazon.co.uk/DIGILENT-410-195-410-195-16-Buttons-Keyboard/dp/B0792G3C45)
| [The Pololu TReX Motor Controller](https://www.pololu.com/product/777)
| [Dagu Wild Thumper 4WD Chassis](https://www.pololu.com/product/1567)
| [Jumper Wires](https://ram-e-shop.com/product/ph60-mf-20cm/)
| [Bread Board](https://ram-e-shop.com/product/bb01-bread-board/)
| [Buzzer](https://ram-e-shop.com/product/buzzar3v/)

| Software Components 
| -------------
| Keil uVision 5
| STM32CubeMX


## How components are used
## Buzzer
A small 3V buzzer was used to sound the alarm after a specified time interval has passed. The integrated Real Time Clock (RTC) in the STM32L432KC microcontroller was used to achieve this. The positive side of the buzzer was connected to a specified GPIO PIN in the microcontroller (PA5 in our case) and its negative was connected to the microcontroller's ground.


https://github.com/mariam606/crazy_alarm_system/assets/67865802/ed08a846-97fe-4931-8bb7-291dee86afbd



## KeyPad
To be able to detect whenever a key is pressed in the keypad, 4 GPIOs output are needed to drive the columns and 4 GPIO inputs to check which row was chosen by the user. First all columns are pulled to be high and then drive one column at a time to be low. A row is low when pressed. In each column when it is low, check if row is also low which means a key has been pressed.

## LCD
The LCD Module Display I2C 1602 QAPASS is connected to a Serial I2C module which allows for a serial connection with the STM32L432KC microcontroller. Only the 4 pins of the I2C module are connected to the microcontroller.


https://github.com/mariam606/crazy_alarm_system/assets/67865802/ade83742-e399-4783-8f39-dd9d9016b0cf



# Second Milestone
The first milestone integrates all of these previous components with the Dagu Wild Thumper 4WD Chassis to implement the alarm system           

## Movement
To make sure that the movement is suitable for any space, the robot moves forward 1 meter, then rotates, then stops for a few seconds to allow the user to enter the riddle solution. 


https://github.com/mariam606/crazy_alarm_system/assets/67865802/3fb81c8d-4d69-4017-b77d-9e654d3df42a


## Riddle
The riddle displayed is a mathematical equation with random numbers generated every time. The user must write the answer then click 'A' on the keypad to indicate that he/she finished writing the answer. The LCD then displays whether answer is correct or wrong. If the answer is correct the buzzer stops ringing and car stops moving


https://github.com/mariam606/crazy_alarm_system/assets/67865802/93db8023-b4ba-4caf-84e7-59b441a3757d



# Integration 
This is the demo of the integrated embedded system. 


https://github.com/shalan/CSCE4301-WiKi/assets/67857016/2ce321ea-a9a7-4a68-8621-49c1ecf9c352

# Third Milestone
In this MS, we have done the following:
## Adjusting the workflow of the LCD
As shown in the demo video below, the LCD starts by asking the user to enter the alarm. After that, it waits till the alarm time starts, and displays the riddle.

## Enabling the user to enter the alarm from the keypad
Unlike the previous milestone, the user currently can enter the alarm time from the keypad.

## Using freeRTOS instead of Round Robin
The code is divided into 5 tasks, and each of them performs a specific task. Some parts of the project need delay such as the car movement. This makes the freeRTOS very useful because the delay, in this case, will not affect other tasks. The tasks are divided as following:
- Getting the alarm input from the user
- Adjusting the RTC to start the alarm
- Getting the riddle answer and checking if it is correct 
- Moving the car

## Demo of MS4:
https://github.com/shalan/CSCE4301-WiKi/assets/67857016/a77fdb07-c6cb-40bc-9208-12089989c376
