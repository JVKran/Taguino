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
SOURCES := transceiver.cpp

# header files in this project
HEADERS := transceiver.hpp entities.hpp

# other places to look for files for this project
SEARCH  := Boundary/Infrared Boundary/HCSR04 Entity

# Core_flags first have to be unset in bmptk/Makefile.inc
CORE_FLAGS += -O0

# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
