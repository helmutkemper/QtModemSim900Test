#ifndef STACKENUM_H
#define STACKENUM_H

#include "atmodem.h"

#define kDefEventListSize 16

class StackEnum
{
  public:
    static Event::eEvent EventList[];
    static int siEventListLineIn;
    static int siEventListLineOut;
    StackEnum ();
    static void Add ( Event::eEvent asiEnum );
    static void Reset ();
    static Event::eEvent Get();
};

#endif // STACKENUM_H
