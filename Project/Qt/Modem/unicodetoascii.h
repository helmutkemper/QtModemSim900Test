#ifndef UNICODETOASCII_H
#define UNICODETOASCII_H

class UnicodeToAscii
{
public:
  static int Value[];
  static char Normal[];
  static char LowerCase[];

  UnicodeToAscii();

  static void Convert ( const char * apcchInput, char * apchOutput , bool ablLowerCase );
};

#endif // UNICODETOASCII_H
