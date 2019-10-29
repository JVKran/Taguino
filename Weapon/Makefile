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

SOURCES := entities.cpp input.cpp KY040.cpp weapon.cpp HCSR04.cpp game.cpp interface.cpp transceiver.cpp display.cpp scoreboard.cpp button.cpp

# header files in this project
HEADERS := entities.hpp input.hpp KY040.hpp weapon.hpp HCSR04.hpp game.hpp interface.hpp transceiver.hpp display.hpp scoreboard.hpp button.hpp

# other places to look for files for this project
SEARCH  := Boundary/Infrared Boundary/HCSR04 Boundary/KY040 Entity Boundary Control Boundary/Infrared Boundary/Display Boundary/buttoninterrupt


# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
