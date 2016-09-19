#####################################################
#
# Makefile for the MIPS Dissassembler
#
#####################################################
FLAGS	= -g -Wall -Wno-unused-variable -Wno-unused-function
LINK	= -pthread
SRC	= $(wildcard *.cpp)
OBJ	= $(SRC:.cpp=.o)
TARGET	= MIPSsim

all 	: $(TARGET)

$(TARGET): $(OBJ)
		g++ $(LINK) $(FLAGS) -o $@ $(OBJ)
			
.cpp.o	:
		g++ $(FLAGS) -c $< -o $@

.PHONY	: clean

clean 	: 
		rm *.o MIPSsim
