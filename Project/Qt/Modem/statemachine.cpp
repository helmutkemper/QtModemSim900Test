#include "statemachine.h"

Action StateMachine::ActionList[ kDefActionListSize ];
int StateMachine::siActionListLineIn = 0;
int StateMachine::siActionListLineOut = 0;

StateMachine::StateMachine()
{
}

void StateMachine::Reset ()
{
  for ( int i = 0; i != kDefActionListSize; i++ )
  {
    StateMachine::ActionList[ i ] = '\0';
  }

  StateMachine::siActionListLineIn = 0;
  StateMachine::siActionListLineOut = 0;
}

void StateMachine::Add ( Action afnAction )
{
  StateMachine::ActionList[ StateMachine::siActionListLineIn ] = afnAction;

  if ( StateMachine::siActionListLineIn >= kDefActionListSize - 1 )
  {
    StateMachine::siActionListLineIn = 0;
  }

  else
  {
    StateMachine::siActionListLineIn += 1;
  }
}

void StateMachine::Step ()
{
  if ( StateMachine::siActionListLineIn == StateMachine::siActionListLineOut )
  {
    return;
  }

  if ( StateMachine::ActionList[ StateMachine::siActionListLineOut ] == '\0' )
  {
    return;
  }

  StateMachine::ActionList[ StateMachine::siActionListLineOut ] ();
  StateMachine::ActionList[ StateMachine::siActionListLineOut ] = '\0';

  if ( StateMachine::siActionListLineOut >= kDefActionListSize - 1 )
  {
    StateMachine::siActionListLineOut = 0;
  }

  else
  {
    StateMachine::siActionListLineOut += 1;
  }
}
