#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class JournalEntry {
	public:
		JournalEntry(void);
		string getEntry(void);
		void setEntry(string entry);
		bool endOfJournal(string last_line);
	private:
		void writeToFile(void);
		string entry;
		string date; 
		int id;
};

class JournalResources {
	public:
		static int generateId(void);
		static void getNumOfEntries(void);
		static string getEntryById(int id);
		static string getDate(void);
		static void deleteJournal(void);
		static void browseEntries(void);
		static vector<int> searchByDate(void);

		static string fileName;

		static int numOfEntries;
};


