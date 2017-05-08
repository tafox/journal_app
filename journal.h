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
	private:
		void writeToFile(void);
		string entry;
		string date; 
		int id;
};

class JournalResources {
	public:
		static int generateId(void);
		static string getEntryById(int id);
		static string getDate(void);
		static void deleteJournal(void);
		static void browseEntries(void);
		static vector<int> searchByDate(void);
    
        static void setFileName(string inFile);
        static string getFileName(void);

        static int getNumOfEntries(void);
        static void calcNumOfEntries(void);


    private:
		static string fileName;
		static int numOfEntries;
};
