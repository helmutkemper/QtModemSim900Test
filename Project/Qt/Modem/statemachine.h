#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#define kDefActionListSize 5

extern "C"
{
  typedef void ( * Action ) ();
}

class StateMachine
{
public:
  static Action ActionList[];

  static int siActionListLineIn;
  static int siActionListLineOut;

  StateMachine();
  void static Reset ();
  void static Add ( Action afnAction );
  void static Step ();
};

#endif // STATEMACHINE_H
