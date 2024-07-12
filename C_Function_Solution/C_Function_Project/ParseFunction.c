#include <stdint.h.>

#include "FuncA.h"
#include "FuncB.h"
#include "FuncC.h"
#include "Checksum.h"

typedef enum {
	STATE_WATING_FOR_HEADER_G = 0,
	STATE_WATING_FOR_HEADER_B = 1,
	STATE_WATING_FOR_OPCODE = 2,
	STATE_WATING_FOR_PAYOAD_1 = 3,
	STATE_WATING_FOR_PAYOAD_2 = 4,
	STATE_WAITING_FOR_CHECKSUM = 5,
} FunctionState;

void ParseFunction(char receivedByte)
{
	static FunctionState funcState = STATE_WATING_FOR_HEADER_G;
	static char header[2] = { '\0', '\0' };
	static char opcode = '\0';
	static uint8_t payload[2] = { 0, 0 };
	static uint8_t checksumByte = 0;
	static int16_t unifiedPayload = 0;

	switch (funcState)
	{
		case STATE_WATING_FOR_HEADER_G:

			if (receivedByte == 'G')
			{
				header[0] = receivedByte;
				funcState = STATE_WATING_FOR_HEADER_B;
				break;
			}
			break;

		case STATE_WATING_FOR_HEADER_B:

			if (receivedByte == 'B')
			{
				header[1] = receivedByte;
				funcState = STATE_WATING_FOR_OPCODE;
				break;
			}
			break;

		case STATE_WATING_FOR_OPCODE:

			if (receivedByte == 'A' || receivedByte == 'B' || receivedByte == 'C')
			{
				opcode = receivedByte;
				funcState = STATE_WATING_FOR_PAYOAD_1;
				break;
			}
			break;

		case STATE_WATING_FOR_PAYOAD_1:

			payload[0] = receivedByte;
			funcState = STATE_WATING_FOR_PAYOAD_2;
			break;

		case STATE_WATING_FOR_PAYOAD_2:

			payload[1] = receivedByte;
			funcState = STATE_WAITING_FOR_CHECKSUM;
			break;

		case STATE_WAITING_FOR_CHECKSUM:

			checksumByte = receivedByte;
			if (checksumByte == checksum(header, opcode, payload))
			{
				unifiedPayload = (payload[0] << 8) | payload[1];

				if (opcode == 'A') FuncA(unifiedPayload);
				else if (opcode == 'B') FuncB(unifiedPayload);
				else if (opcode == 'C') FuncC(unifiedPayload);
			}
			funcState = STATE_WATING_FOR_HEADER_G;
			break;

		default:
			funcState = STATE_WATING_FOR_HEADER_G;
			break;			
	}





}

