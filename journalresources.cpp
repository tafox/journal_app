#include "journal.h"

string JournalResources::getDate(void)
{
	string date;
	time_t time_secs;
  	struct tm * time_now;
  
	time(&time_secs);
	time_now = localtime(&time_secs);
	date = string(asctime(time_now)); 
	date = date.substr(0, date.size()-1); 
	return date;
}

void JournalResources::getNumOfEntries(void)
{
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

string JournalResources::getEntryById(int entry_id)
{
  string line, entry;
  int found_id;
  bool foundEntry = false;
  ifstream inStream("journal_entries.txt");
  while (!foundEntry) {
    getline(inStream, line);
    if (inStream.eof()) {
		return "";
    }
    if (line.substr(0,4) == "<id>") {
      int i = 4;
      while (line[i] != '<') {
        i++;
      }
      found_id = stoi(line.substr(4,4-i));
      if (found_id == entry_id) {
        foundEntry = true;
        getline(inStream, line);
        entry = line.substr(6,line.length()-13) + "\n";
        while (getline(inStream, line) && line.substr(0,4) != "<id>" && !inStream.eof()) {
		  entry += (line + "\n");
        }
      }
    }
  }
  inStream.close();
  return entry;
}

void JournalResources::deleteJournal(void)
{
	ofstream ofs;
	ofs.open("journal_entries.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	numOfEntries = 0;
}

int JournalResources::generateId(void)
{
  return ++numOfEntries;
}

void JournalResources::browseEntries(void)
{
	string selection;
	for (int i = 1; i <= numOfEntries;) {
		cout << "At entry " << i << endl;
		cout << getEntryById(i);
		cout << "Press p to view previous entry" << endl; 
		cout << "Press n to view next entry" << endl; 
		cout << "Enter an entry ID to go to that entry" << endl; 
		cin >> selection;
		if (selection == "p") {
			if (i >= 2) {
				i--;
			} else {
				cout << "At first entry" << endl;
			}
		} else if (selection == "n") {
			i++;
	 	} else {
			i = stoi(selection);
		}
	}
	cout << "Reached end of journal" << endl;
}


int JournalResources::numOfEntries = 0;
