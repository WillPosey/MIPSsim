#####################################################
#
# Makefile for the MIPS Dissassembler
#
#####################################################
FLAGS	= -g -Wall
SRC		= $(wildcard *.cpp)
OBJ		= $(SRC:.cpp=.o)
TARGET	= MIPSsim

all 	: $(TARGET)

$(TARGET): $(OBJ)
		g++ -g -Wall -o $@ $(OBJ)
			
.cpp.o	:
		g++ $(FLAGS) -c $< -o $@

.PHONY	: clean

clean 	: 
		rm *.o MIPSsim