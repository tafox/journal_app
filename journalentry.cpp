#include "journal.h"

JournalEntry::JournalEntry(void)
{
	string line;
	date = JournalResources::getDate();
	cout << "Type ^D at the start of a newline to end journal entry." << endl;
	cout << "Enter journal entry for " << date  << " below:" << endl; 
	bool done = false;
	id = JournalResources::generateId();
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

void JournalEntry::writeToFile(void) 
{
	ofstream outStream(JournalResources::fileName, ios_base::app);
	outStream << "<id>" << id << "</id>" << endl;
	outStream << "<date>" << date << "</date>" << endl;
	outStream << "<entry>" << entry << "</entry>" << endl;
	outStream.close();
}

bool JournalEntry::endOfJournal(string last_line) 
{
	int length = static_cast<int>(last_line.length());
	if (last_line[length-1] == 'D' && last_line[length-2] == '^') {
		return true;
	} else {
		return false;
	}
}



     
      
      
      
    
    
