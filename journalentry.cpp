#include "journal.h"

JournalEntry::JournalEntry(void) {
	string line;
	date = JournalResources::getDate();
	cout << "Type \\DONE on a blank line to end journal entry." << endl;
	cout << "Enter journal entry for " << date  << " below:" << endl; 
	bool done = false;
	id = JournalResources::generateId();
	while (getline(cin, line)) {
        if (line == "\\DONE") {
            break;
        }
        line += "\n";
        entry += line;
	}
	writeToFile();
}

void JournalEntry::writeToFile(void) {
	ofstream outStream(JournalResources::getFileName(), ios_base::app);
	outStream << "<id>" << id << "</id>" << endl;
	outStream << "<date>" << date << "</date>" << endl;
	outStream << "<entry>" << entry << "</entry>" << endl;
	outStream.close();
}
