#include "ParseFunction.h"

int main()
{
	char message[] = { 'H', 'B', 'A', 'X', 'Y', 'Q' };

	for (int i = 0; i<6; i++)
	{
		ParseFunction(message[i]);
	}
	
	return 0;
}