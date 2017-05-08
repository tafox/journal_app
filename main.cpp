#include "journal.h"

void viewing() {
    while (1) {
        string selection;
        if (JournalResources::getNumOfEntries() == 0) {
            cout << "There are 0 entries." << endl;
            break;
        }
        JournalResources::getNumOfEntries();
        cout << "Now in viewing mode" << endl;
        cout << "There are " << JournalResources::getNumOfEntries() << " entries" << endl; 
        cin >> selection;
        if (selection == "browse") {
            JournalResources::browseEntries();
        }/* else if (selection == "search") {
            vector<int> ids = JournalResources::searchByDate();
            vector<int>::iterator i;
            for (i = ids.begin(); i != ids.end(); i++) {
                if (i+1 == ids.end()) {
                    cout << *i << endl;
                } else {
                    cout << *i << ", ";
                }
            }
        }*/ else if (selection == "quit") {
            break;
        } else if (selection == "help") {
            cout << "Commands:" << endl;
            //cout << "\tsearch: search for entries by date"  << endl;
            cout << "\tbrowse: browse enteries in-order"  << endl;
            cout << "\thelp: see command information"  << endl;
            cout << "\tquit: exit viewing mode"  << endl;
        } else {
            cout << "Invalid command. Enter 'help' for command information" << endl;
        }
    }
}

void menuLoop(void) {
    while (1) {
        string menuSelection;
        cout << "There are " << JournalResources::getNumOfEntries() << " entries" << endl; 
        cout << "Enter 'help' to see commands" << endl;
        cin >> menuSelection;
        if (menuSelection == "new") {
            JournalEntry new_entry;
        } else if (menuSelection == "view") {
            viewing();
        } else if (menuSelection == "quit") {
            cout << "Goodbye!" << endl;
            break;
        } else if (menuSelection == "delete") {
            JournalResources::deleteJournal();
            cout << "All journal entries were successfully deleted." << endl;
        } else if (menuSelection == "help") {
            cout << "Commands:" << endl;
            cout << "\tnew: create a new journal entry"  << endl;
            cout << "\tview: enter journal viewing mode"  << endl;
            cout << "\tdelete: delete entire journal"  << endl;
            cout << "\thelp: see command information"  << endl;
            cout << "\tquit: exit journal"  << endl;

        } else {
            cout << "Invalid command. Enter 'help' for command information" << endl;
        }
    }
}

int main(int args, char* argc[]) {
    JournalResources::calcNumOfEntries();
    cout << "Welcome to your Journal: " << JournalResources::getFileName() << endl;
    menuLoop();
	return 0;
}
