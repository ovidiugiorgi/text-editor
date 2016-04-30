#ifndef TAB_H
#define TAB_H

#include "Operation.h"

class Tab {
private:
  string _text;
  stack<Operation*> _stUndo, _stRedo;
  bool _locked;
public:
  Tab();
  Tab(const string& other);
  ~Tab();

  string GetText();

  void SetText(const string &other);

  bool IsLocked();

  void Do(Operation* op);
  void Undo();
  void Redo();
};

#endif