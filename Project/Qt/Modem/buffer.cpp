#include "buffer.h"

const char Buffer::kEmptyString[] = { "\0" };

char *Buffer::pCharBufferStart = 0;
char *Buffer::pCharBufferWrite = 0;

int Buffer::siTextLength = 0;
int Buffer::siBufferLength = 0;

Buffer::Buffer()
{
}

void Buffer::Set( char * apchBuffer )
{
  Buffer::pCharBufferWrite = apchBuffer;
  Buffer::pCharBufferStart = apchBuffer;

  Buffer::siBufferLength = 0;

  do
  {
    if ( *apchBuffer == '\0' )
    {
      Buffer::siBufferLength --;
      return;
    }

    apchBuffer ++;
    Buffer::siBufferLength ++;
    Buffer::pCharBufferWrite ++;
  }
  while ( true );
}

void Buffer::Get ( char * apchReturn, int siStart, int siEnd )
{
  for ( char * i = ( Buffer::pCharBufferStart + siStart ); i != ( Buffer::pCharBufferStart + siEnd + 1 ); i ++ )
  {
    *apchReturn = *i;
    apchReturn ++;
  }
}

void Buffer::Concatenate ( char *apchChar )
{
  do
  {
    if ( *apchChar == '\0' )
    {
      return;
    }

    *Buffer::pCharBufferWrite = *apchChar;
    Buffer::pCharBufferWrite ++;
    *Buffer::pCharBufferWrite = '\0';
    Buffer::siBufferLength ++;

    apchChar ++;
  }
  while ( true );
}

void Buffer::Concatenate ( const char *apchChar )
{
  do
  {
    if ( *apchChar == '\0' )
    {
      return;
    }

    *Buffer::pCharBufferWrite = ( char ) *apchChar;
    Buffer::pCharBufferWrite ++;
    *Buffer::pCharBufferWrite = '\0';
    Buffer::siBufferLength ++;

    apchChar ++;
  }
  while ( true );
}

void Buffer::Delete ( const char * apchSearch )
{
  // Ola mundo cruel
  // mundo

  int lsiStart = Buffer::IndexOf ( apchSearch, 0 );
  int lsiCounter = Buffer::siBufferLength;

  char * lcchStart = Buffer::pCharBufferStart + lsiStart;
  char * lcchEnd = Buffer::pCharBufferStart + lsiStart + Buffer::siTextLength;

  //Buffer::siTextLength

  do
  {
    if ( *lcchEnd == '\0' )
    {
      *lcchStart = '\0';
      Buffer::pCharBufferWrite = lcchStart;
      Buffer::siBufferLength -= lsiCounter;
      return;
    }

    *lcchStart = *lcchEnd;
    lcchStart ++;
    lcchEnd ++;
    lsiCounter --;
  }
  while ( true );
}

bool Buffer::Compare ( char * apchTextA, const char * apcchTextB )
{
  do
  {
    if ( *apchTextA != *apcchTextB )
    {
      return false;
    }

    if ( ( *apchTextA == '\0' ) && ( *apcchTextB == '\0' ) )
    {
      return true;
    }

    apchTextA ++;
    apcchTextB ++;
  }
  while ( true );
}

bool Buffer::Compare ( char * apchTextA, char * apchTextB )
{
  do
  {
    if ( *apchTextA != *apchTextB )
    {
      return false;
    }

    if ( ( *apchTextA == '\0' ) && ( *apchTextB == '\0' ) )
    {
      return true;
    }

    apchTextA ++;
    apchTextB ++;
  }
  while ( true );
}

bool Buffer::EndsWith ( const char * apchText )
{
  Buffer::siTextLength = 0;
  Buffer::siBufferLength = 0;

  const char * lpchText = apchText;
  const char * lpchBuffer = Buffer::pCharBufferWrite;

  while ( *lpchText != '\0' )
  {
    Buffer::siTextLength ++;
    lpchText ++;
  }

  lpchText = apchText;
  
  do
  {
    if ( *( lpchText + Buffer::siTextLength ) == *( lpchBuffer + Buffer::siBufferLength ) )
    {
      Buffer::siBufferLength --;
      Buffer::siTextLength --;

      if ( Buffer::siTextLength == 0 )
      {
        return true;
      }
    }

    else
    {
      return false;
    }
  }
  while ( true );
}

int Buffer::IndexOf ( const char * apchText, bool ablCountToEnd )
{
  if ( ablCountToEnd == true )
  {
    return Buffer::IndexOf ( apchText, 0 ) + Buffer::siTextLength - 1;
  }

  return Buffer::IndexOf ( apchText, 0 );
}

int Buffer::IndexOf ( const char * apchText, int auiOffset, bool ablCountToEnd )
{
  if ( ablCountToEnd == true )
  {
    return Buffer::IndexOf ( apchText, auiOffset ) + Buffer::siTextLength - 1;
  }

  return Buffer::IndexOf ( apchText, auiOffset );
}

int Buffer::IndexOf ( const char * apchText, int auiOffset )
{
  const char * lpchText = apchText;
  const char * lpchBuffer = Buffer::pCharBufferStart + auiOffset;
  const char * lpchBufferInc = Buffer::pCharBufferStart + auiOffset;
  Buffer::siTextLength = 0;
  int lsiCountAtual = 0;
  unsigned int lsiCountStart = 0;

  while ( *lpchText != '\0' )
  {
    Buffer::siTextLength ++;
    lpchText ++;
  }

  lpchText = apchText;

  do
  {
    if ( *lpchText == *lpchBuffer )
    {
      lsiCountAtual ++;
      lpchText ++;
      lpchBuffer ++;

      if ( Buffer::siTextLength == lsiCountAtual )
      {
        return lsiCountStart + auiOffset;
      }

      continue;
    }

    if ( *lpchBuffer == '\0' )
    {
      return -1;
    }

    lpchText = apchText;
    lpchBufferInc ++;
    lsiCountStart ++;
    lpchBuffer = lpchBufferInc;
    lsiCountAtual = 0;
  }
  while ( true );
}

bool Buffer::Contains ( const char * apchText, bool ablDelete )
{
  const char * lpchText = apchText;
  const char * lpchBuffer = Buffer::pCharBufferStart;
  const char * lpchBufferInc = Buffer::pCharBufferStart;
  unsigned int luiCountTotal = 0;
  unsigned int luiCountAtual = 0;

  while ( *lpchText != '\0' )
  {
    luiCountTotal ++;
    lpchText ++;
  }

  lpchText = apchText;

  do
  {
    if ( *lpchText == *lpchBuffer )
    {
      luiCountAtual ++;
      lpchText ++;
      lpchBuffer ++;

      if ( luiCountTotal == luiCountAtual )
      {
        if ( ablDelete == true )
        {
          Buffer::Delete( apchText );
        }
        return true;
      }

      continue;
    }

    if ( *lpchBuffer == '\0' )
    {
      return false;
    }

    lpchText = apchText;
    lpchBufferInc ++;
    lpchBuffer = lpchBufferInc;
    luiCountAtual = 0;
  }
  while ( true );
}

bool Buffer::Start ( const char * apchText )
{
  char * lcchStart = Buffer::pCharBufferStart;

  while ( *apchText == *lcchStart )
  {
    apchText++;
    lcchStart++;

    if ( *apchText == 0 )
    {
      return true;
    }

    if ( *lcchStart == 0 )
    {
      return false;
    }
  }
  return false;
}
