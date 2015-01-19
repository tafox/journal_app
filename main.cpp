#include "journal.h"

int main(int args, char* argc[]) 
{
	bool done = false;
	string menu_selection;
	JournalResources::getNumOfEntries();
	cout << "Welcome to your Journal" << endl;
	while (!done) {
		cout << "Type 'new' for new entry" << endl;
		cout << "Type 'view' to enter viewing mode" << endl;
		cout << "Type 'delete' to delete entire journal" << endl;
		cout << "Type 'quit' to exit" << endl;
		cin >> menu_selection;
		if (menu_selection == "new") {
			JournalEntry new_entry;
		} else if (menu_selection == "view") {
			bool done_viewing = false;
			while (!done_viewing) {
				string selection;
				if (JournalResources::numOfEntries == 0)
					break;
				cout << "Now in viewing mode" << endl;
				cout << "There are " << JournalResources::numOfEntries << " entries" << endl; 
				cout << "Enter browse to browse all entries" << endl;
				cout << "Enter search to search by date" << endl;
				cout << "Enter quit to quit viewing mode" << endl;
				cin >> selection;
				if (selection == "browse") {
					JournalResources::browseEntries();
				} else if (selection == "search") {
					vector<int> ids = JournalResources::searchByDate();
					vector<int>::iterator i;
					for (i = ids.begin(); i != ids.end(); i++) {
						if (i+1 == ids.end()) {
							cout << *i << endl;
						} else {
							cout << *i << ", ";
						}
					}
				} else if (selection == "quit") {
					done_viewing = true;
				} else {
					cout << "Invalid input" << endl;
				}
			}
		} else if (menu_selection == "quit") {
			done = true;
		} else if (menu_selection == "delete") {
			JournalResources::deleteJournal();
		} else {
			cout << "Please input a valid option" << endl;
			done = true;
		}
	}
	cout << "Goodbye!" << endl;
	return 0;
}
