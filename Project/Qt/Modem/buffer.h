#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
  static const char kEmptyString[];

  static char *pCharBufferWrite;
  static char *pCharBufferStart;

  static int siTextLength;
  static int siBufferLength;

  Buffer();

  void static Set( char * apchBuffer );
  void static Concatenate ( char achChar );
  void static Concatenate ( char *apchChar );
  void static Concatenate ( const char *apchChar );
  void static Delete ( const char * apchSearch );
  void static Get ( char * apchReturn, int siStart, int siEnd );

  bool static Compare ( char * apchTextA, char * apchTextB );
  bool static Compare ( char * apchTextA, const char * apcchTextB );
  bool static Start ( const char * apchText );
  bool static Contains ( const char * apchText , bool ablDelete );
  bool EndsWith( const char * apchText );

  int static IndexOf ( const char * apchText, int auiOffset );
  int static IndexOf ( const char * apchText, bool ablCountToEnd );
  int static IndexOf ( const char * apchText, int auiOffset, bool ablCountToEnd );
};

#endif // BUFFER_H
