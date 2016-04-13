#include "Operation.h"

Operation::Operation() :
  _posBegin(0),
  _s("\0")
{

}

Operation::Operation(int posBegin, string s) :
  _posBegin(posBegin)
{
  _s = s;
}