#ifndef COPY_H
#define COPY_H

class Copy
{
public:
  static const char *pcchSpacer;
  static char *pchSpacer;


  /** Recebe o espaçamento entre textos 
   *  @var pcchar ponteiro do array de char terminado em \0
   */
  static void Spacer ( const char *cchpData );

  /** Recebe o espaçamento entre os textos
   *  @var pchar ponteiro do array de char terminado em \0
   */
  static void Spacer ( char *cchpData );
  
  /** Concatena os dados contidos em Data1 e Data2 em Destination.
   *  Data1 e Data2 devem ser terminados em \0.
   *  Destination = Data1 + Spacer + Data2
   *  @var pchar Destination
   *  @var pcchar Data1
   *  @var pchar  Data2
   */
  static void  Data ( char *chpDestination, const char *cchpData1, char *chpData2 );
  static void  Data ( char *chpDestination, const char *cchpData1, const char *cchpData2 );
  static void  Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3 );
  static void  Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4 );
  static void  Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4, char *chpData5 );
  static void  Data ( char *chpDestination, const char *cchpData1, char *chpData2, char *chpData3, char *chpData4, char *chpData5, char *chpData6 );
  static char* Data ( char *chpDestination, const char *cchpData1 );
  static char* Data ( char *chpDestination, char *chpData1 );
  Copy();
};

#endif // COPY_H
