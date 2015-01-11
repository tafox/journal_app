#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

class JournalEntry {
  public:
    JournalEntry(void);
    JournalEntry(string journal_entry);
    string getEntry(void);
    void setEntry(string entry);
    void setDate(string input_date);
    string getDate(void);
  private:
    void writeToFile(void);
    string entry;
    string date; 
};

int main(int args, char* argc[]) {
  string menu_selection;
  bool done = false;
  while (!done) {
    cout << "Welcome to your Journal" << endl;
    cout << "Type 'new' for new entry" << endl;
    cout << "Type 'view' to enter viewing mode" << endl;
    cout << "Type 'quit' to exit" << endl;
    menu_selection = "";
    cin >> menu_selection;
    cout << menu_selection;
    if (menu_selection == "new") {
      JournalEntry new_entry;
    } else if (menu_selection == "view") {
      cout << "Now in viewing mode" << endl;
    } else if (menu_selection == "quit") {
      done = true;
    } else {
      cout << "Please input a valid option" << endl;
      done = true;
    }
  }
  cout << "Goodbye!" << endl;
  return 0;
}

JournalEntry::JournalEntry(void) {
  time_t time_secs;
  struct tm * time_now;
  
  time(&time_secs);
  time_now = localtime(&time_secs);
  date = string(asctime(time_now)); 
  date = date.substr(0, date.size()-1); 
  cout << "Enter journal entry for " << date << " below:" << endl; 
  string line;
  while (!cin.eof()) {
    getline(cin, line);
    line += "\n";
    entry += line;
  }
  writeToFile();
}

JournalEntry::JournalEntry(string journal_entry) {
  time_t time_secs;
  struct tm * time_now;
  
  time(&time_secs);
  time_now = localtime(&time_secs);
  date = string(asctime(time_now));
  date = date.substr(0, date.size()-1);
  
  entry = journal_entry;
}

string JournalEntry::getEntry(void) {
  return entry;
}

void JournalEntry::setEntry(string entry) {
  cin >> entry;
}

void JournalEntry::setDate(string input_date) {
  date = input_date;
}

string JournalEntry::getDate(void) {
  return date;
}

void JournalEntry::writeToFile(void) {
  ofstream outStream;
  outStream.open("journal_entries.txt");
  outStream << "<date>" << date << "</date>" << endl;
  outStream << "<entry>" << entry << "</entry>" << endl;
  outStream.close();
}
  
  
  
