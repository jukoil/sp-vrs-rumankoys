/**
  ******************************************************************************
  * @file    hw/spi_devices/mcp6s92/inc/mcp6s92.h
  * @author  Jozef Rodina
  * @version V1.0.0
  * @date    30-October-2012
  * @brief   MCP6S92 PGA.
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2012 Jozef Rodina</center></h2>
  ******************************************************************************
  */

#ifndef __MCP6S92
#define __MCP6S92

#define CMD_MCP6S92_NOP				0x00
#define CMD_MCP6S92_SHUT_DOWN		0x01
#define CMD_MCP6S92_WRITE_TO_REG	0x02

#define MCP6S92_CHANNEL_REG_ADDRESS	0x01
#define MCP6S92_GAIN_REG_ADDRESS	0x00

#define GAIN_1	0x00
#define GAIN_2	0x01
#define GAIN_4	0x02
#define GAIN_5	0x03
#define GAIN_8	0x04
#define GAIN_10	0x05
#define GAIN_16	0x06
#define GAIN_32	0x07

#define CHANNEL_0	0x00
#define CHANNEL_1	0x01

void mcp6s92_setings(unsigned char command, unsigned char regAddress, unsigned char regData);

#endif
