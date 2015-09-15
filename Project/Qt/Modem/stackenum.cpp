#include "stackenum.h"
#include "atmodem.h"

Event::eEvent StackEnum::EventList[ kDefEventListSize ];
int StackEnum::siEventListLineIn = 0;
int StackEnum::siEventListLineOut = 0;

StackEnum::StackEnum()
{
}

void StackEnum::Reset ()
{
  for ( int i = 0; i != kDefEventListSize; i++ )
  {
    StackEnum::EventList[ i ] = Event::None;
  }

  StackEnum::siEventListLineIn = 0;
  StackEnum::siEventListLineOut = 0;
}

void StackEnum::Add ( Event::eEvent asiEnum )
{
  StackEnum::EventList[ StackEnum::siEventListLineIn ] = asiEnum;

  if ( StackEnum::siEventListLineIn >= kDefEventListSize - 1 )
  {
    StackEnum::siEventListLineIn = 0;
  }

  else
  {
    StackEnum::siEventListLineIn += 1;
  }
}

Event::eEvent StackEnum::Get ()
{
  Event::eEvent lsiReturn;

  if ( StackEnum::siEventListLineIn == StackEnum::siEventListLineOut )
  {
    return Event::None;
  }

  lsiReturn = StackEnum::EventList[ StackEnum::siEventListLineOut ];

  if ( StackEnum::siEventListLineOut >= kDefEventListSize - 1 )
  {
    StackEnum::siEventListLineOut = 0;
  }

  else
  {
    StackEnum::siEventListLineOut += 1;
  }

  return lsiReturn;
}
