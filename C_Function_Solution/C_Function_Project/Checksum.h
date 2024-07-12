#pragma once

#include <stdint.h.>

//This function calculates the received data integrity and returns an int value that summarizes the calculation. The received data used in the calculation are header, opcode and payload.
uint8_t checksum(char header[], char opcode, uint8_t payload[]);