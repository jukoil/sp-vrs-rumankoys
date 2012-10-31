#include "spi.h"

void mcp6s92_setings(unsigned char command, unsigned char regAddress, unsigned char regData)
{
	unsigned char instruction = command<<5;
	instruction = instruction | regAddress;

	device_Select();

	readWriteSPI2(instruction);
	readWriteSPI2(regData);

	device_Unselect();
}
