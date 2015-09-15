//
//  types.h
//  serial
//
//  Created by Kemper on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// <b>Tipos das Variáveis:</b>
//
//  <b>Inteiros sem sinal:</b>
//
//  UINT8  -> 8 bits
//  UINT16 -> 16 bits
//  UINT32 -> 32 bits
//
//  <b>Inteiros com sinal:</b>
//
//  SINT8  -> 8 bits
//  SINT16 -> 8 bits
//  SINT32 -> 8 bits
//
//  <b>Booleano:</b>
//
//  BOOL -> Valores possíveis TRUE ou FALSE
//
//  <b>Sem tipo:</b>
//
//  VOID
//
//  Para ponteiros dos tipos acima adicionar "P" no inicio.
//
//  Ex.:
//  Ponteiro para UINT8 -> PUINT8
//  Ponteiro para SINT16 -> PSINT16
//
//  Ponteiro de funcao " VOID funcao ( VOID ) "
//
//  PFUNC
#ifndef serial_types_h
#define serial_types_h

    #include <stdio.h> /* Standard input/output definitions */

    #ifndef NULL

        #define NULL    ((void *)0)

    #endif

    #if defined (__MAC_10_8) || defined (__MAC_10_7) || defined (__MAC_10_6) || defined (__linux__)

        /** Inteiro de 32bits sem sinal.
         *
         */
        typedef long UINT32;

        /** Ponteiro de 32bits sem sinal.
         *
         */
        typedef long * PUINT32;

        /** Redefinição de booleano para hardware.
         *
         */
        typedef enum //BOOLEAN
        {
            TRUE = 1,
            FALSE = 0
        } BOOL;

    #endif

    /** Constante de inteiro para 8bits sem sinal.
     *
     */
    typedef const char KUINT8;

    /** Constante de inteiro para 16bits sem sinal.
     *
     */
    typedef const int  KUINT16;

    /** Constante de inteiro para 32bits sem sinal.
     *
     */
    typedef const long KUINT32;

    /** Constante de inteiro para 8bits com sinal.
     *
     */
    typedef const char   KSINT8;

    /** Constante de inteiro para 16bits com sinal.
     *
     */
    typedef const int    KSINT16;

    /** Constante de inteiro para 32bits com sinal.
     *
     */
    typedef const long   KSINT32;

    /** Ponteiro de constante para 8bits sem sinal.
     *
     */
    typedef const char * KPUINT8;

    /** Ponteiro de constante para 16bits sem sinal.
     *
     */
    typedef const int *  KPUINT16;

    /** Ponteiro de constante para 32bits sem sinal.
     *
     */
    typedef const long * KPUINT32;

    /** Ponteiro de constante para 8bits com sinal.
     *
     */
    typedef const char *   KPSINT8;

    /** Ponteiro de constante para 16bits com sinal.
     *
     */
    typedef const int *    KPSINT16;

    /** Ponteiro de constante para 32bits com sinal.
     *
     */
    typedef const long *   KPSINT32;

    /** Inteiro de 8bits sem sinal.
     *
     */
    //typedef char UINT8;

    /** Inteiro de 16bits sem sinal.
     *
     */
    //typedef int  UINT16;

    /** Inteiro de 8bits com sinal.
     *
     */
    typedef char   SINT8;

    /** Inteiro de 16bits com sinal.
     *
     */
    typedef int    SINT16;

    /** Inteiro de 32bits com sinal.
     *
     */
    typedef long   SINT32;

    /** Ponteiro de 8bits sem sinal.
     *
     */
    //typedef char * PUINT8;

    /** Ponteiro de 16bits sem sinal.
     *
     */
    //typedef int *  PUINT16;

    /** Ponteiro de 8bits com sinal.
     *
     */
    typedef char *   PSINT8;

    /** Ponteiro de 16bits com sinal.
     *
     */
    typedef int *    PSINT16;

    /** Ponteiro de 32bits com sinal.
     *
     */
    typedef long *   PSINT32;

    /** Ponteiro de função que recebe e retorna void.
     *
     */
    typedef void ( *vdvdPFUNC ) ( void );

    /** Ponteiro de função que recebe UINT8 e retorna void.
     *
     */
    typedef void ( * vdsi8PFUNC ) ( SINT8 );

    /** Ponteiro de função que recebe UINT8 e retorna UINT8.
     *
     */
    typedef SINT8 ( * si8si8PFUNC ) ( SINT8 );

    /** Retorno vazio
     *
     */
//    typedef void  VOID;

    /** Casting para ponteiro de retorno vazio.
     *
     */
    typedef void * PVOID;

#endif
