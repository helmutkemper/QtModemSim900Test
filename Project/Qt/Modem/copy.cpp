#include "copy.h"

const char *Copy::pcchSpacer = '\0';
      char *Copy::pchSpacer  = '\0';

Copy::Copy()
{
}

void Copy::Spacer ( const char *cchpData )
{
  Copy::pcchSpacer = cchpData;
  Copy::pchSpacer  = '\0';
}

void Copy::Spacer ( char *cchpData )
{
  Copy::pchSpacer  = cchpData;
  Copy::pcchSpacer = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, const char *cchpData2 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, cchpData2 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, char *chpData2 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData2 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData2 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData3 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData2 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData3 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  Copy::Data ( chpDestination, chpData4 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4, char *chpData5 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData2 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData3 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData4 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData5 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

void Copy::Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4, char *chpData5, char *chpData6 )
{
  chpDestination = Copy::Data ( chpDestination, cchpData1 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData2 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData3 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData4 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData5 );

  chpDestination = Copy::Data ( chpDestination, pcchSpacer );
  chpDestination = Copy::Data ( chpDestination, pchSpacer );

  chpDestination = Copy::Data ( chpDestination, chpData6 );

  Copy::pcchSpacer = '\0';
  Copy::pchSpacer  = '\0';
}

char* Copy::Data ( char *chpDestination, const char *cchpData1 )
{
  if ( cchpData1 == '\0' )
  {
    return chpDestination;
  }

  while ( *chpDestination != '\0' )
  {
    chpDestination += 1;
  }

  do
  {
    *chpDestination = *cchpData1;
    chpDestination += 1;
    cchpData1 += 1;
  }
  while ( *cchpData1 != '\0' );

  *chpDestination = '\0';

  return chpDestination;
}

char* Copy::Data ( char *chpDestination, char *chpData1 )
{
  if ( chpData1 == '\0' )
  {
    return chpDestination;
  }

  while ( *chpDestination != '\0' )
  {
    chpDestination += 1;
  }

  do
  {
    *chpDestination = *chpData1;
    chpDestination += 1;
    chpData1 += 1;
  }
  while ( *chpData1 != '\0' );

  *chpDestination = '\0';

  return chpDestination;
}
