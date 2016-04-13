#include "Insert.h"
#include "Editor.h"

Insert::Insert() :
  Operation()
{

}

Insert::Insert(int pos, string s) :
  Operation(pos, s)
{

}

void Insert::Do()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();

  if (_posBegin < 0 || _posBegin > tmp.length()) {
    cout << "Couldn't do insert, enter a valid position\n"; 
    return;
  }

  tmp.insert(_posBegin, _s); 
  tab->SetText(tmp);
}

void Insert::Undo()
{
  Tab* tab = Editor::Instance()->GetActiveTab();

  if (Editor::Instance()->GetActiveTab()->IsLocked()) {
    return;
  }

  string tmp = tab->GetText();
  tmp.erase(_posBegin, _s.length());
  tab->SetText(tmp);
}