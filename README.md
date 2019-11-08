[![Showcase Video](/Deliverables/20191108_161837.jpg)](https://youtu.be/YKAxMUS9iD8)
# Taguino
Lasertag-games are great fun! So why not make one? That's what this repository is for... This project consists of two devices;
- Weapons
- Gameleader

The Gameleader has the ability to set the gametime, enable powerups, show the scoreboard and type in names. Furthermore, it also
has an MP3 player to play suitable audio; lobby music while all players are signing up and fight music when the game starts.

The weapon can select the weapontype and firemode, or to display the scoreboard. Furthermore, also the health, amount of bullets and magazines and remaining time is printed on the display.

### Gameleader
The gameleader is built with the following components:
- Keypad
- OlED (SSD1306)
- Rotary Encoder (EC11)
- NRF24L01+

The Gameleader dynamically assigns adresses to the weapons; when a weapon boots up, the Gameleader detects that and transmits an address to the weapon. After an address has been assigned the master concatenates the newly assigned address to an array. Now, when a player enters a name with the keypad, the first unoccupied weapon gets that name. That name is also used in the scoreboards. 

When the gameleader starts the game after setting the gametime, all players receive the message that define the start of a game and its duration. When a weapon disconnects, the game can just continue; the scoreboard remains.

### Weapon
The weapon has the following components:
- Ultrasonic distance sensor (HCSR04)
- RGB Led
- Infrared transmitter (TSUS5202) and receiver (VS1838B)
- OLED (SSD1306)
- Rotary Encoder (EC11)
- Microswitch
- Toggleswitch 
- NRF24L01+.

The ultrasonic distance sensor is used to determine wether or not a shotgun should kill a player. It should if the distance is shorter than 3 meters. Else it shouldn't.
The infrared transmitter and receiver are wired in such a way that the total distance is +-32 meters. That is, with pushing 525mA through a LED that's rated for 300mA and a very overthough receiver circuit.
The OLED and Rotary Encoder are used to display health, bullets, weapon, firemode, scoreboard and to switch between the several implemented windows.
The microswitch is used to fire a bullet and the toggleswitch is used to select the firemode. The NRF24L01+ is used as communication method between gameleader and weapons.

## Diagrams

## Protocol

