#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)

SOURCES := entities.cpp input.cpp button.cpp KY040.cpp weapon.cpp HCSR04.cpp game.cpp interface.cpp transceiver.cpp scoreboard.cpp RGBLed.cpp
SOURCES += display.cpp 

# header files in this project
HEADERS := entities.hpp input.hpp button.hpp KY040.hpp weapon.hpp HCSR04.hpp game.hpp interface.hpp transceiver.hpp scoreboard.hpp RGBLed.hpp
HEADERS += display.hpp applicationLogic.hpp
# other places to look for files for this project

SEARCH  := Boundary/Infrared Boundary/HCSR04 Boundary/KY040 Entity Boundary Control Boundary/Infrared Boundary/Display Boundary/buttoninterrupt 
SEARCH  += Boundary/RGBLed ApplicationLogic


# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
