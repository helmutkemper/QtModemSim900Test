#include "unicodetoascii.h"

int UnicodeToAscii::Value[] = { 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0xc2a1, 0xc2a2, 0xc2a3, 0xc2a4, 0xc2a5, 0xc2a6, 0xc2a7, 0xc2a8, 0xc2a9, 0xc2aa, 0xc2ab, 0xc2ac, 0xc2ae, 0xc2af, 0xc2b0, 0xc2b1, 0xc2b2, 0xc2b3, 0xc2b4, 0xc2b5, 0xc2b6, 0xc2b7, 0xc2b8, 0xc2b9, 0xc2ba, 0xc2bb, 0xc2bc, 0xc2bd, 0xc2be, 0xc2bf, 0xc380, 0xc381, 0xc382, 0xc383, 0xc384, 0xc385, 0xc386, 0xc387, 0xc388, 0xc389, 0xc38a, 0xc38b, 0xc38c, 0xc38d, 0xc38e, 0xc38f, 0xc390, 0xc391, 0xc392, 0xc393, 0xc394, 0xc395, 0xc396, 0xc397, 0xc398, 0xc399, 0xc39a, 0xc39b, 0xc39c, 0xc39d, 0xc39e, 0xc39f, 0xc3a0, 0xc3a1, 0xc3a2, 0xc3a3, 0xc3a4, 0xc3a5, 0xc3a6, 0xc3a7, 0xc3a8, 0xc3a9, 0xc3aa, 0xc3ab, 0xc3ac, 0xc3ad, 0xc3ae, 0xc3af, 0xc3b0, 0xc3b1, 0xc3b2, 0xc3b3, 0xc3b4, 0xc3b5, 0xc3b6, 0xc3b7, 0xc3b8, 0xc3b9, 0xc3ba, 0xc3bb, 0xc3bc, 0xc3bd, 0xc3be, 0xc3bf, 0x0000 };
char UnicodeToAscii::Normal[] = { ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 'i', 'c', 'l', '?', '?', '|', 'S', '?', 'c', 'a', '?', '?', 'r', '-', 'o', '?', '2', '3', '\'', 'u', '?', '.', '.', '1', 'o', '?', '?', '?', '?', '?', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'd', 'n', 'o', 'o', 'o', 'o', 'o', '*', '0', 'u', 'u', 'u', 'u', 'u', 'p', 'b', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'o', 'n', 'o', 'o', 'o', 'o', 'o', '/', '0', 'u', 'u', 'u', 'u', 'y', 'p', 'y', '\0' };
char UnicodeToAscii::LowerCase[] = { ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 'i', 'c', 'l', '?', '?', '|', 'S', '?', 'c', 'a', '?', '?', 'r', '-', 'o', '?', '2', '3', '\'', 'u', '?', '.', '.', '1', 'o', '?', '?', '?', '?', '?', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'C', 'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I', 'D', 'N', 'O', 'O', 'O', 'O', 'O', '*', '0', 'U', 'U', 'U', 'U', 'Y', 'p', 'B', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'o', 'n', 'o', 'o', 'o', 'o', 'o', '/', '0', 'u', 'u', 'u', 'u', 'y', 'p', 'y', '\0' };

UnicodeToAscii::UnicodeToAscii()
{
}

void UnicodeToAscii::Convert ( const char * apcchInput, char * apchOutput, bool ablLowerCase )
{
  /*
  a: '`'
  f: 'g'
  A: '@'
  F: 'G'
  0: '/'
  9: ':'
  */

  int *lpsiList;
  int lsiCounter;
  int lsiConverter = 0;
  char lchCharacter;
  do
  {
    for ( int i = 4; i != 0; i-- )
    {
      if ( ( *apcchInput >= 'a' ) && ( *apcchInput <= 'f' ) )
      {
        lchCharacter = ( *apcchInput - 87 );
        apcchInput ++;
      }

      else if ( ( *apcchInput >= 'A' ) && ( *apcchInput <= 'F' ) )
      {
        lchCharacter = ( *apcchInput - 55 );
        apcchInput ++;
      }

      else if ( ( *apcchInput >= '0' ) && ( *apcchInput <= '9' ) )
      {
        lchCharacter = ( *apcchInput - 48 );
        apcchInput ++;
      }
      else
      {
        return;
      }

      switch ( i )
      {
        case 4:
          switch ( ( int ) lchCharacter )
          {
            case 0:  lsiConverter += 0;     break;
            case 1:  lsiConverter += 4096;  break;
            case 2:  lsiConverter += 8192;  break;
            case 3:  lsiConverter += 12288; break;
            case 4:  lsiConverter += 16384; break;
            case 5:  lsiConverter += 20480; break;
            case 6:  lsiConverter += 24576; break;
            case 7:  lsiConverter += 28672; break;
            case 8:  lsiConverter += 32768; break;
            case 9:  lsiConverter += 36864; break;
            case 10: lsiConverter += 40960; break;
            case 11: lsiConverter += 45056; break;
            case 12: lsiConverter += 49152; break;
            case 13: lsiConverter += 53248; break;
            case 14: lsiConverter += 57344; break;
            case 15: lsiConverter += 61440; break;
          }
          break;

        case 3:
          switch ( ( int ) lchCharacter )
          {
            case 0:  lsiConverter += 0;    break;
            case 1:  lsiConverter += 256;  break;
            case 2:  lsiConverter += 512;  break;
            case 3:  lsiConverter += 768;  break;
            case 4:  lsiConverter += 1024; break;
            case 5:  lsiConverter += 1280; break;
            case 6:  lsiConverter += 1536; break;
            case 7:  lsiConverter += 1792; break;
            case 8:  lsiConverter += 2048; break;
            case 9:  lsiConverter += 2304; break;
            case 10: lsiConverter += 2560; break;
            case 11: lsiConverter += 2816; break;
            case 12: lsiConverter += 3072; break;
            case 13: lsiConverter += 3328; break;
            case 14: lsiConverter += 3584; break;
            case 15: lsiConverter += 3840; break;
          }
          break;

        case 2:
          switch ( ( int ) lchCharacter )
          {
            case 0:  lsiConverter += 0;   break;
            case 1:  lsiConverter += 16;  break;
            case 2:  lsiConverter += 32;  break;
            case 3:  lsiConverter += 48;  break;
            case 4:  lsiConverter += 64;  break;
            case 5:  lsiConverter += 80;  break;
            case 6:  lsiConverter += 96;  break;
            case 7:  lsiConverter += 112; break;
            case 8:  lsiConverter += 128; break;
            case 9:  lsiConverter += 144; break;
            case 10: lsiConverter += 160; break;
            case 11: lsiConverter += 176; break;
            case 12: lsiConverter += 192; break;
            case 13: lsiConverter += 208; break;
            case 14: lsiConverter += 224; break;
            case 15: lsiConverter += 240; break;
          }
          break;

        case 1:
          switch ( ( int ) lchCharacter )
          {
            case  0:  lsiConverter += 0;  break;
            case  1:  lsiConverter += 1;  break;
            case  2:  lsiConverter += 2;  break;
            case  3:  lsiConverter += 3;  break;
            case  4:  lsiConverter += 4;  break;
            case  5:  lsiConverter += 5;  break;
            case  6:  lsiConverter += 6;  break;
            case  7:  lsiConverter += 7;  break;
            case  8:  lsiConverter += 8;  break;
            case  9:  lsiConverter += 9;  break;
            case  10: lsiConverter += 10; break;
            case  11: lsiConverter += 11; break;
            case  12: lsiConverter += 12; break;
            case  13: lsiConverter += 13; break;
            case  14: lsiConverter += 14; break;
            case  15: lsiConverter += 15; break;
          }
          break;
      }
    }

    lpsiList = &UnicodeToAscii::Value[ 0 ];
    lsiCounter = 0;

    while ( *lpsiList != '\0' )
    {
      if ( *lpsiList == lsiConverter )
      {
        if ( ablLowerCase == true )
        {
          *apchOutput = UnicodeToAscii::LowerCase[ lsiCounter ];
        }
        else
        {
          *apchOutput = UnicodeToAscii::Normal[ lsiCounter ];
        }

        apchOutput ++;
        *apchOutput = '\0';
        break;
      }
      lsiCounter ++;
      lpsiList ++;
    }
    lsiConverter = 0;
  }
  while ( true );


  return;
}
