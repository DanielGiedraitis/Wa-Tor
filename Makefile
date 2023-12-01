# Author: Daniel Giedraitis (C00260331)
# Date Created: 04/11/2023
# Purpose: It contains rules that tell the system how to compile the code and produce a working executable called wator.
# GitHub URL: https://github.com/DanielGiedraitis/Wa-Tor
# Licence: GPL-3.0

CXX = g++ -fopenmp
CPPFILES= wator.cpp
CPPFLAGS= -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lgomp -fopenmp
EXE= wator

SRCS=wator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

#This rule says that each .o file depends on a .cpp file of the same name
#This is actually built into Make but anyways...
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)  $(DEBUGFLAGS)


ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)
