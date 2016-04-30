#ifndef EDITOR_H
#define EDITOR_H

#include "Tab.h"

class Editor {
private:
  Tab* _activeTab;
  map<string, Tab*> _tabs;
  vector<string> _names;
  static Editor* t_instance;

  Editor();
  Editor(const Editor& other);
  Editor& operator=(const Editor& other);
  ~Editor();

  vector<string>::iterator FindName(const string& tabName);
public:
  Tab* GetActiveTab();
  string GetActiveTabName();

  void SetActiveTab(const string& tabName);

  void AddTab(const string& tabName);
  void AddTab(const string& tabName, const string& text);
  void DeleteTab(const string& tabName);
  void ShowTabs();

  static Editor* Instance();
};

#endif