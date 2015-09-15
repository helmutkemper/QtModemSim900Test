#ifndef MINIEXPREG_H
#define MINIEXPREG_H

#define kDefCharacterClassSize 3
#define kDefListSize 4

class MiniExpReg
{
public:

  static char kTeste[];
  static char *pTeste;
  static char schCharacterClassWhiteList[ kDefCharacterClassSize ][ 6 ];
  static char schCharacterClassIgnoreList[ kDefCharacterClassSize ][ 6 ];
  static char schCharacterClassBlackList[ kDefCharacterClassSize ][ 6 ];
  static char schWhiteList[ kDefListSize ];
  static char schIgnoreList[ kDefListSize ];
  static char schBlackList[ kDefListSize ];


  MiniExpReg();
  void static InitList ();
  void static Test ();
};

#endif // MINIEXPREG_H
