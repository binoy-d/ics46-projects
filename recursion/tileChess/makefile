# Makefile for Tile Chessboard example
# Week 1, I&C SCI 46, Lecture B, Fall 2019

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

tilechess: tilechess.o Point.o 
	$(CXX) $(CXXFLAGS) -o tilechess tilechess.o Point.o 

# The main.o target can be written more simply

tilechess.o: tilechess.cpp Point.hpp
	$(CXX) $(CXXFLAGS) -c tilechess.cpp

Point.o: Point.hpp Point.cpp

