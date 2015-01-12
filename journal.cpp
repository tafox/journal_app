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
    bool endOfJournal(string last_line);
    static void getNumOfEntries(void);
    static int numOfEntries;
  private:
    int generateId(void);
    void writeToFile(void);
    string entry;
    string date; 
    int id;
};

int main(int args, char* argc[]) {
  bool done = false;
  string menu_selection;
  JournalEntry::getNumOfEntries();
  while (!done) {
    cout << "Welcome to your Journal" << endl;
    cout << "Type 'new' for new entry" << endl;
    cout << "Type 'view' to enter viewing mode" << endl;
    cout << "Type 'delete' to delete entire journal" << endl;
    cout << "Type 'quit' to exit" << endl;
    cin >> menu_selection;
    if (menu_selection == "new") {
      JournalEntry new_entry;
    } else if (menu_selection == "view") {
      cout << "Now in viewing mode" << endl;
      cout << "There are " << JournalEntry::numOfEntries << " entries" << endl; 
    } else if (menu_selection == "quit") {
      done = true;
    } else if (menu_selection == "delete") {
      ofstream ofs;
      ofs.open("journal_entries.txt", ofstream::out | ofstream::trunc);
      ofs.close();
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
  cout << "Type ^D to end journal entry." << endl;
  cout << "Enter journal entry for " << date << " below:" << endl; 
  string line;
  bool done = false;
  id = generateId();
  while (!done) {
    getline(cin, line);
    if (endOfJournal(line)) {
      done = true;
    } else {
      line += "\n";
      entry += line;
    }
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
  ofstream outStream("journal_entries.txt", ios_base::app);
  outStream << "<id>" << id << "</id>" << endl;
  outStream << "<date>" << date << "</date>" << endl;
  outStream << "<entry>" << entry << "</entry>" << endl;
  outStream.close();
}

bool JournalEntry::endOfJournal(string last_line) {
  int length = static_cast<int>(last_line.length());
  if (last_line[length-1] == 'D' && last_line[length-2] == '^') {
    return true;
  } else {
    return false;
  }
}

void JournalEntry::getNumOfEntries(void) {
  string line;
  ifstream inStream("journal_entries.txt");
  while (!inStream.eof()) {
    getline(inStream, line);
    if (line.substr(0,4) == "<id>") {
      numOfEntries++;
    }
  }
  inStream.close();
}

int JournalEntry::numOfEntries = 0;

int JournalEntry::generateId(void) {
  return numOfEntries++;
}
    
    
