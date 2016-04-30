#include "Edit.h"
#include "Editor.h"

Edit::Edit() :
  Operation(),
  _posEnd(0)
{

}

Edit::Edit(int posBegin, int posEnd, string s) :
  Operation(posBegin, s),
  _posEnd(posEnd)
{

}

void Edit::Do()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();

  if (_posBegin < 0 || _posBegin >= tmp.length() ||
      _posEnd < 0 || _posEnd >= tmp.length() || 
      _posBegin > _posEnd) {
    cout << "Couldn't do edit, enter valid positions\n"; 
    return;
  }

  _s_edit = tmp.substr(_posBegin, _posEnd - _posBegin + 1);
  tmp.replace(_posBegin, _posEnd - _posBegin + 1, _s);
  tab->SetText(tmp);
}

void Edit::Undo()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();
  tmp.replace(_posBegin, _s.length(), _s_edit);
  tab->SetText(tmp);
}