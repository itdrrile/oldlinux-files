#!/bin/bash

#               factorial
#               ---------


# Does bash permit recursion?
# Well, yes, but...
# You gotta have rocks in your head to try it.


MAX_ARG=5
E_WRONG_ARGS=65
E_RANGE_ERR=66


if [ -z "$1" ]
then
  echo "Usage: `basename $0` number"
  exit $E_WRONG_ARGS
fi

if [ "$1" -gt $MAX_ARG ]
then
  echo "Out of range (5 is maximum)."
  # Let's get real now.
  # If you want greater range than this,
  # rewrite it in a real programming language.
  exit $E_RANGE_ERR
fi  

fact ()
{
  local number=$1
  # Variable "number" must be declared as local,
  # otherwise this doesn't work.
  if [ "$number" -eq 0 ]
  then
    factorial=1    # Factorial of 0 = 1.
  else
    let "decrnum = number - 1"
    fact $decrnum  # Recursive function call.
    let "factorial = $number * $?"
  fi

  return $factorial
}

fact $1
echo "Factorial of $1 is $?."

exit 0
