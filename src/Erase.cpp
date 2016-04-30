#include "Erase.h"
#include "Editor.h"

Erase::Erase() :
  Operation(),
  _posEnd(0)
{

}

Erase::Erase(int posBegin, int posEnd) :
  Operation(posBegin, "\0"),
  _posEnd(posEnd)
{

}

void Erase::Do()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();

  if (_posBegin < 0 || _posBegin >= tmp.length() || 
      _posEnd < 0 || _posEnd >= tmp.length() || 
      _posBegin > _posEnd) {
    cout << "Couldn't do erase, enter valid positions\n"; 
    return;
  }

  _s = tmp.substr(_posBegin, _posEnd - _posBegin + 1);
  tmp.erase(_posBegin, _posEnd - _posBegin + 1);
  tab->SetText(tmp);
}

void Erase::Undo()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();
  tmp.insert(_posBegin, _s);
  tab->SetText(tmp);
}