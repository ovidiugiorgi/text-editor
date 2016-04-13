#include "Tab.h"
#include "Editor.h"

Tab::Tab() :
  _text("\0")
{

}

Tab::Tab(const string& other)
{
  _text = other;
}

Tab::~Tab()
{
  while (!_stUndo.empty()) {
    Operation* purged = _stUndo.top();
    _stUndo.pop();
    delete purged;
  }
  while (!_stRedo.empty()) {
    Operation* purged = _stRedo.top();
    _stRedo.pop();
    delete purged;
  }
}

string Tab::GetText()
{
  return _text;
}

void Tab::SetText(const string& other)
{
  if (_locked) {
    return;
  }
  _text = other;
}

bool Tab::IsLocked()
{
  return _locked;
}

void Tab::Do(Operation* op)
{
  if (Editor::Instance()->GetActiveTab() != this) {
    return;
  }

  _locked = false;
  op->Do();
  _stUndo.push(op);
  while (!_stRedo.empty()) {
    _stRedo.pop();
  }
  _locked = true;
}

void Tab::Undo()
{
  if (Editor::Instance()->GetActiveTab() != this) {
    return;
  }

  if (_stUndo.empty()) {
    cout << "You cannot undo any action\n";
    return;
  }

  _locked = false;
  _stUndo.top()->Undo();
  _stRedo.push(_stUndo.top());
  _stUndo.pop();
  _locked = true;
}

void Tab::Redo()
{
  if (Editor::Instance()->GetActiveTab() != this) {
    return;
  }

  if (_stRedo.empty()) {
    cout << "You cannot redo any action\n";
    return;
  }

  _locked = false;
  _stRedo.top()->Do();
  _stUndo.push(_stRedo.top());
  _stRedo.pop();
  _locked = true;
}