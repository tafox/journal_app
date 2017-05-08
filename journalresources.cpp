#include "journal.h"

string strip(string str) {
    int j = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            j++;    
        } else {
            j = 0;
        }
        if (j >= 2) {
            str.erase(i, 1);
            i++;
        }
    }
    return str;
}

string JournalResources::getDate(void) {
	string date, str_time;
	time_t time_secs;
  	struct tm * time_now;
	time(&time_secs);
	time_now = localtime(&time_secs);
	date = string(asctime(time_now)); 
	date = date.substr(0, date.size()-1); 
	str_time = date.substr(11,5);
	date.erase(11, 9);
    date = strip(date);
	date = str_time + " " + date;
	return date;
}

void JournalResources::calcNumOfEntries(void) {
    string line;
    numOfEntries = 0;
    ifstream inStream(fileName);
    while (getline(inStream, line)) {
        if (line.substr(0,4) == "<id>") {
          numOfEntries++;
        }
    }
    inStream.close();
}

string JournalResources::getEntryById(int entry_id) {
    string line, entry;
    int cur_id;
    bool foundEntry = false;
    ifstream inStream(fileName);
    while (!foundEntry && getline(inStream, line)) {
        cout << "loop" << endl;
        int i = 4;
        if (line.substr(0,4) == "<id>") {
            while (line[i] != '<') {
                i++;
            }
        } else {
            continue;
        }
        cur_id = stoi(line.substr(4,i-4));
        if (cur_id == entry_id) {
            cout << "found" << endl;
            foundEntry = true;
            getline(inStream, line);
            //get date
            entry = line.substr(6,line.length()-13) + "\n";
            while (getline(inStream, line) && line.substr(0,4) != "<id>") {
                if (line.substr(0,2) != "<e" && line.substr(0,2) != "</") { 
                    entry += (line + "\n");
                }
            }
        }
    }
    inStream.close();
    return entry;
}

void JournalResources::deleteJournal(void) {
	ofstream ofs;
	ofs.open(fileName, ofstream::out | ofstream::trunc);
	ofs.close();
	numOfEntries = 0;
}

int JournalResources::generateId(void) {
    return ++numOfEntries;
}

void JournalResources::browseEntries(void) {
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
				cout << "At beginning of journal." << endl;
			}
		} else if (selection == "n") {
			if (i == numOfEntries) {
				cout << "At end of journal." << endl;
			} else {
				i++;
			}
		} else if (selection == "q") {
			break;
	 	} else {
            try {
                cout << "115" << endl;
                i = stoi(selection);
                cout << "117" << endl;
            } catch (std::exception ex) {
                cout << "Invalid input" << endl;
            }
		}
	}
	cout << "Leaving browse mode" << endl;
}

vector<int> JournalResources::searchByDate(void) {
	string date, day, month, year;
	vector<int> ids;
	cout << "Enter a day, month, and year (DD/MM/YYYY):" << endl;
    cin >> date;
    day = date.substr(0,2);
    month = date.substr(3,2);
    year = date.substr(6,4);
	cout << "Entries for " << day << " " << month << " " << year << endl;
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

void JournalResources::setFileName(string inFile) {
    fileName = inFile;
}

string JournalResources::getFileName(void) {
    return fileName;
}

int JournalResources::getNumOfEntries(void) {
    return numOfEntries;
}

int JournalResources::numOfEntries = 0;

string JournalResources::fileName = "journal.xml";
