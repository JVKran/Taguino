SOURCES := entities.cpp input.cpp button.cpp KY040.cpp weapon.cpp HCSR04.cpp game.cpp transmitter.cpp receiver.cpp scoreboard.cpp RGBLed.cpp
SOURCES += display.cpp NRF24.cpp interface.cpp grenade.cpp 

HEADERS := entities.hpp input.hpp button.hpp KY040.hpp weapon.hpp HCSR04.hpp game.hpp transmitter.hpp receiver.hpp scoreboard.hpp RGBLed.hpp
HEADERS += display.hpp applicationLogic.hpp NRF24.hpp NRF24_register.hpp interface.hpp grenade.hpp 

SEARCH  := Boundary/Infrared Boundary/HCSR04 Boundary/KY040 Entity Boundary Control Boundary/Infrared Boundary/Display Boundary/buttoninterrupt
SEARCH  += Boundary/RGBLed ApplicationLogic Boundary/NRF Boundary/433mhz/Grenade 

RELATIVE := ..
include $(RELATIVE)/Makefile.due
include ../$(relative)/rtos/makefile.inc
