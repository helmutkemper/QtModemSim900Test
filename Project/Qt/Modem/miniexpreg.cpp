//lidi
#include "miniexpreg.h"
#include <QDebug>

char MiniExpReg::kTeste[] = { "adicionar telefone [0-9]{8,20}\0" };
char *MiniExpReg::pTeste = &MiniExpReg::kTeste[ 0 ];

char MiniExpReg::schCharacterClassWhiteList[ kDefCharacterClassSize ][ 6 ];
char MiniExpReg::schCharacterClassIgnoreList[ kDefCharacterClassSize ][ 6 ];
char MiniExpReg::schCharacterClassBlackList[ kDefCharacterClassSize ][ 6 ];
char MiniExpReg::schWhiteList[ kDefListSize ];
char MiniExpReg::schIgnoreList[ kDefListSize ];
char MiniExpReg::schBlackList[ kDefListSize ];

//C\Bl\Bm - lista de classe permitida byte low,byte high
//c\Bl\Bm - lista de classe negada byte low,byte high
//L - lista permitida
//l - lista negada
//. - tudo

//allowed
//denied
//ignored

//z - zero ou mais
//+ - um ou mais
//* - guloso
//, - nao guloso
//? - zero ou um
//[not] greedy

//[ch-ch <-- lista de classe]
//[chch] <-- lista simples
//[chch-] <-- lista simples
//

//adicionar telefone &a[0-9]{8,20}i[0-9]{8,20}d[0-9]{8,20}\0
void MiniExpReg::Test ( char *apchText, char *apchExp )
{
  char lchStatus = 'l';
  int lchCount = 0;

  while ( *apchExp != '\0' )
  {
    qDebug() << *apchExp;

    if ( ( lchStatus == 'l' ) && ( *apchExp != '&' ) )
    {
      apchExp ++;
      continue;
    }
  }
}

void MiniExpReg::InitList ()
{
  int l,c;

  for ( l = 0; l != kDefCharacterClassSize; l++ )
  {
    for ( c = 0; c != 6; c++ )
    {
      MiniExpReg::schCharacterClassWhiteList[ l ][ c ]  = '\0';
      MiniExpReg::schCharacterClassIgnoreList[ l ][ c ] = '\0';
      MiniExpReg::schCharacterClassBlackList[ l ][ c ]  = '\0';
    }
  }

  MiniExpReg::schWhiteList[ 0 ] = '\0';
  MiniExpReg::schIgnoreList[ 0 ] = '\0';
  MiniExpReg::schBlackList[ 0 ] = '\0';
}

//[a-z]
//[a-z0-9]
//[a-zA-Z0-9]
//[a-zA-Z0-9]{9}
//[a-zA-Z0-9]{9,}
//[a-zA-Z0-9]{9,5}
//telefone [0-9]{8,15}
MiniExpReg::MiniExpReg()
{

}
