#include "eeprom.h"

char EEPROM::Memory[ 128 ];

EEPROM::EEPROM()
{
}

void EEPROM::write ( int asiAddr, char achData )
{
  EEPROM::Memory[ asiAddr ] = achData;
}

char EEPROM::read ( int asiAddr )
{
  return EEPROM::Memory[ asiAddr ];
}
