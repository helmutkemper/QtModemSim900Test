#ifndef EEPROM_H
#define EEPROM_H

class EEPROM
{
public:
  static char Memory[ 128 ];
  EEPROM();
  static void write ( int asiAddr, char achData );
  static char read ( int asiAddr );
};

#endif // EEPROM_H
