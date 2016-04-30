#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <vector>
#include <map>

using namespace std;

class Operation {
protected:
  int _posBegin;
  string _s;
public:
  Operation();
  Operation(int posBegin, string s);

  virtual void Do() = 0;
  virtual void Undo() = 0;
};

#include "Insert.h"
#include "Erase.h"
#include "Edit.h"

#endif