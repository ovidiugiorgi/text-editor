#include "Editor.h"

using namespace std;

Editor* Editor::t_instance = 0; 

int extractPosBegin(const string &s)
{
  int num = -1;
  bool ok = 0;
  for (int i = 0; i < s.length() && !ok; ++i) {
    while (isdigit(s[i])) {
      if (num == -1) num = 0;
      ok = 1;
      num = num * 10 + (s[i++] - '0');
    }
  }
  return num;
}

int extractPosEnd(const string &s)
{
  int num = -1;
  bool ok = 0;
  for (int i = 0; i < s.length() && !ok; ++i) {
    if (isdigit(s[i])) {
      while (isdigit(s[i++]));
      num = 0;
      while (isdigit(s[i])) {
        num = num * 10 + (s[i++] - '0');
      }
      break;
    }
  }
  return num;
}

string extractString(const string &s)
{
  string t;
  int i = 0;
  while (i < s.length() && s[i] != '\"') {
    i++;
  }
  i++;
  while (i < s.length() && s[i] != '\"') {
    t += s[i];
    i++;
  }
  return t;
}

string extractTabText(const string &s)
{
  string t;
  int i = 0;
  while (i < s.length() && s[i] != '(') {
    i++;
  }
  i += 2;
  while (i < s.length() && s[i] != '\"') {
    t += s[i];
    i++;
  }
  return t;
}

void clearScreen()
{
  for (int i = 0; i < 30; ++i) {
    cout << "\n";
  }
}

void help()
{
  cout << "\nCommands\n";
  for (int i = 0; i < 8; ++i) {
    cout << "-";
  }
  cout << "\n\n";
  cout << "INSERT Pos \"text\"" << "\n";
  cout << "ERASE LeftPos RightPos" << "\n";
  cout << "EDIT LeftPos RightPos \"text\"" << "\n";
  cout << "UNDO" << "\n";
  cout << "REDO" << "\n";
  cout << "SHOW" << "\n";
  cout << "LENGTH" << "\n";
  cout << "CREATE_TAB" << "\n";
  cout << "DELETE_TAB" << "\n";
  cout << "SWITCH_TAB" << "\n";
  cout << "ACTIVE_TAB" << "\n";
  cout << "TABS" << "\n";
  cout << "HELP" << "\n";
  cout << "EXIT" << "\n";

  cout << "\n";
}

int main()
{
  string command, s;
  int posBegin, posEnd;

  clearScreen();
  help();
  cout << "\nDefault tab opened\n";

  do
  {
    cout << "> ";
    getline(cin, command);
    posBegin = posEnd = 0;
    s.clear();

    if (command.find("INSERT") != string::npos) {    
      posBegin = extractPosBegin(command);
      s = extractString(command);
  
      Operation* op = new Insert(posBegin, s);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command.find("ERASE") != string::npos) {
      posBegin = extractPosBegin(command);
      posEnd = extractPosEnd(command);

      Operation* op = new Erase(posBegin, posEnd);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command.find("EDIT") != string::npos) {
      posBegin = extractPosBegin(command);
      posEnd = extractPosEnd(command);
      s = extractString(command);

      Operation* op = new Edit(posBegin, posEnd, s);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command == "UNDO") {
      Editor::Instance()->GetActiveTab()->Undo();
    } else if (command == "REDO") {
      Editor::Instance()->GetActiveTab()->Redo();
    } else if (command == "SHOW") {
      cout << Editor::Instance()->GetActiveTab()->GetText() << "\n";
    } else if (command == "LENGTH") {
      cout << Editor::Instance()->GetActiveTab()->GetText().length() << "\n";
    } else if (command.find("CREATE_TAB") != string::npos) {
      string tabName = extractString(command);
      string text = extractTabText(command);
      if (text.empty()) {
        Editor::Instance()->AddTab(tabName);
      } else {
        Editor::Instance()->AddTab(tabName, text);
      }
    } else if (command.find("DELETE_TAB") != string::npos) {
      string tabName = extractString(command);
      Editor::Instance()->DeleteTab(tabName);
    }  else if (command.find("SWITCH_TAB") != string::npos) {
      string tabName = extractString(command);
      Editor::Instance()->SetActiveTab(tabName);
    } else if (command == "ACTIVE_TAB") {
      cout << Editor::Instance()->GetActiveTabName() << "\n";
    } else if (command == "TABS") {
        Editor::Instance()->ShowTabs();
    } else if (command == "HELP") {
      help();
    } else {
      if (command != "EXIT") {
        cout << "Invalid command, type HELP for the available actions\n";
      }
    }
  } while (command != "EXIT");

  return 0;
}