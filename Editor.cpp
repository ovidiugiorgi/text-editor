#include "Editor.h"

Editor::Editor() 
{
  Tab* tab = new Tab();
  _tabs["Untitled"] = tab;
  _names.push_back("Untitled");
  _activeTab = tab;
}

Editor::Editor(const Editor& other)
{

}

Editor& Editor::operator=(const Editor& other)
{
  
}

Editor::~Editor()
{
  while (!_names.empty()) {
    Tab* purged = _tabs[*_names.begin()];
    _names.erase(_names.begin());
    delete purged;
  }
}

vector<string>::iterator Editor::FindName(const string& tabName)
{
  vector<string>::iterator it;
  for (it = _names.begin(); it != _names.end(); ++it) {
    if (*it == tabName) {
      return it;
    }
  }
  return it;
}

Tab* Editor::GetActiveTab()
{
  return _activeTab;
}

string Editor::GetActiveTabName()
{
  for (vector<string>::iterator it = _names.begin(); it != _names.end(); ++it) {
    if (_tabs[*it] == _activeTab) {
      return *it;
    }
  }
}

void Editor::SetActiveTab(const string& tabName)
{
  vector<string>::iterator it = FindName(tabName);

  if (it == _names.end()) {
    cout << "There is no tab with that name\n";
    return;
  }

  _activeTab = _tabs[*it];
}

void Editor::AddTab(const string& tabName)
{
  vector<string>::iterator it = FindName(tabName);

  if (it != _names.end()) {
    cout << "There is already a tab with that name\n";
    return;
  }

  Tab* tab = new Tab();
  _tabs[tabName] = tab;
  _names.push_back(tabName);
}

void Editor::AddTab(const string& tabName, const string& text)
{
  vector<string>::iterator it = FindName(tabName);

  if (it != _names.end()) {
    cout << "There is already a tab with that name\n";
    return;
  }

  Tab* tab = new Tab(text);
  _tabs[tabName] = tab;
  _names.push_back(tabName);
}

void Editor::DeleteTab(const string& tabName)
{
  vector<string>::iterator it = FindName(tabName);

  if (it == _names.end()) {
    cout << "There is no tab with that name\n";
    return;
  }

  if (_activeTab == _tabs[tabName]) {
    if (_names.size() == 1) {
      cout << "You cannot delete the only remaining tab\n";
    } else {
      Tab* purged = _tabs[tabName];
      _names.erase(it);
      _tabs.erase(_tabs.find(tabName));
      delete purged;

      _activeTab = _tabs[*_names.begin()];
      cout << "Active tab now set to " << *_names.begin() << "\n";
    }
    return;
  }

  Tab* purged = _tabs[tabName];
  _names.erase(it);
  _tabs.erase(_tabs.find(tabName));
  delete purged;
}

void Editor::ShowTabs()
{
  for (vector<string>::iterator it = _names.begin(); it != _names.end(); ++it) {
    cout << *it << "\n";
  }
}

Editor* Editor::Instance()
{
  if (!t_instance) {
    t_instance = new Editor;
  }
  return t_instance;
}