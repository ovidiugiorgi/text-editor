#ifndef EDIT_H
#define EDIT_H

#include "Operation.h"

class Edit : public Operation {
protected:
  int _posEnd;
  string _s_edit;
public:
  Edit();
  Edit(int posBegin, int posEnd, string s);

  void Do();
  void Undo();
};

#endif