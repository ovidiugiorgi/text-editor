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
  cout << "insert <pos> <text>" << "\n";
  cout << "erase <left_pos> <right_pos>" << "\n";
  cout << "edit <left_pos> <right_pos> <text>" << "\n";
  cout << "undo" << "\n";
  cout << "redo" << "\n";
  cout << "show" << "\n";
  cout << "length" << "\n";
  cout << "tab_create" << "\n";
  cout << "tab_del" << "\n";
  cout << "tab_switch <tab_name>" << "\n";
  cout << "tab_active" << "\n";
  cout << "tab" << "\n";
  cout << "help" << "\n";
  cout << "clear" << "\n";
  cout << "exit" << "\n";

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

    if (command.find("insert") != string::npos) {
      posBegin = extractPosBegin(command);
      s = extractString(command);

      Operation* op = new Insert(posBegin, s);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command.find("erase") != string::npos) {
      posBegin = extractPosBegin(command);
      posEnd = extractPosEnd(command);

      Operation* op = new Erase(posBegin, posEnd);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command.find("edit") != string::npos) {
      posBegin = extractPosBegin(command);
      posEnd = extractPosEnd(command);
      s = extractString(command);

      Operation* op = new Edit(posBegin, posEnd, s);
      Editor::Instance()->GetActiveTab()->Do(op);
    } else if (command == "undo") {
      Editor::Instance()->GetActiveTab()->Undo();
    } else if (command == "redo") {
      Editor::Instance()->GetActiveTab()->Redo();
    } else if (command == "show") {
      cout << Editor::Instance()->GetActiveTab()->GetText() << "\n";
    } else if (command == "length") {
      cout << Editor::Instance()->GetActiveTab()->GetText().length() << "\n";
    } else if (command.find("tab_create") != string::npos) {
      string tabName = extractString(command);
      string text = extractTabText(command);
      if (text.empty()) {
        Editor::Instance()->AddTab(tabName);
      } else {
        Editor::Instance()->AddTab(tabName, text);
      }
    } else if (command.find("tab_del") != string::npos) {
      string tabName = extractString(command);
      Editor::Instance()->DeleteTab(tabName);
    }  else if (command.find("tab_switch") != string::npos) {
      string tabName = extractString(command);
      Editor::Instance()->SetActiveTab(tabName);
    } else if (command == "tab_active") {
      cout << Editor::Instance()->GetActiveTabName() << "\n";
    } else if (command == "tab") {
        Editor::Instance()->ShowTabs();
    } else if (command == "help") {
      help();
    } else if (command == "clear") {
      cout << string( 100, '\n' );
    } else {
      if (command != "exit") {
        cout << "Invalid command, type help for more information\n";
      }
    }
  } while (command != "exit");

  return 0;
}
