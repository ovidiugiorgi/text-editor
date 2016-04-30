#ifndef ERASE_H
#define ERASE_H

#include "Operation.h"

class Erase : public Operation {
protected:
  int _posEnd;
public:
  Erase();
  Erase(int pos, int lg);

  void Do();
  void Undo();
};

#endif