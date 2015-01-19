#include "journal.h"

string JournalResources::getDate(void)
{
	string date, str_time;
	time_t time_secs;
  	struct tm * time_now;
  
	time(&time_secs);
	time_now = localtime(&time_secs);
	date = string(asctime(time_now)); 
	date = date.substr(0, date.size()-1); 
	str_time = date.substr(11,5);
	date.erase(11, 9);
	date = str_time + " " + date;
	return date;
}

void JournalResources::getNumOfEntries(void)
{
  string line;
  ifstream inStream(fileName);
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
  ifstream inStream(fileName);
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
	ofs.open(fileName, ofstream::out | ofstream::trunc);
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
		cout << "Press q to quit" << endl;
		cout << "Enter an entry ID to go to that entry" << endl; 
		cin >> selection;
		if (selection == "p") {
			if (i >= 2) {
				i--;
			} else {
				cout << "At first entry" << endl;
			}
		} else if (selection == "n") {
			if (i == numOfEntries) {
				cout << "At end of journal" << endl;
			} else {
				i++;
			}
		} else if (selection == "q") {
			break;
	 	} else {
			i = stoi(selection);
		}
	}
	cout << "Leaving browse mode" << endl;
}

vector<int> JournalResources::searchByDate(void) 
{
	string day, month, year;
	vector<int> ids;
	cout << "Enter a day, month, and year " << endl;
	cin >> day;
	cin >> month;
	cin >> year;
	cout << "Enteries for " << day << " " << month << " " << year << endl;
	ifstream inStream(fileName);
	string prev_line, line;
	while (getline(inStream, line) && !inStream.eof()) {
		if (line.substr(0,6) == "<date>") {
			string j_day, j_month, j_year;
			j_day = line.substr(20,2);
			j_month = line.substr(16,3);
			j_year = line.substr(23,4);
			if (j_day == day && j_month == month && j_year == year) {
				ids.push_back(stoi(prev_line.substr(4,1)));
			}
		}
		prev_line = line;
	}
	return ids;
}

int JournalResources::numOfEntries = 0;

string JournalResources::fileName = "journal_entries.txt";