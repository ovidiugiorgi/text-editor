#ifndef INSERT_H
#define INSERT_H

#include "Operation.h"

class Insert : public Operation {
public:
  Insert();
  Insert(int pos, string s);

  void Do();
  void Undo();
};

#endif