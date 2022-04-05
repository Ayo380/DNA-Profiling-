// Project 1 Starter Code - DNA Profiling
// TODO(Ayokunle Olugboyo):  Put your header info here.
// Update line above.
// CUSOTMIZED COMMAND: "Add" it allows the user to input name
// and STR for the person manually. input format: "Ayo,3,4,5"
// the way it was formatted in file.#
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ourvector.h"

using namespace std;
struct DATA {
  ourvector<char> name;
  ourvector<int> matches;
};
// Function #1 : load
// Parameter: ourvector<char> dna, string s
// Description: helper function for load_dna(loading the dna file)
void load(string s, ourvector<char>& dna) {
  for (unsigned long int i = 0; i < s.size(); i++) {
    dna.push_back(s[i]);
  }
}
// Function #2: Load_dna
// Parameter: string filename, ourvector<char> &d_n_a
// Description: Called when "load_dna" command is called
// it opens the file and read each line
void Load_dna(string filename, ourvector<char>& d_n_a) {
  ifstream openfile;
  openfile.open(filename);
  string file_data;
  if (openfile.is_open()) {
    while (openfile >> file_data) {
      load(file_data, d_n_a);
    }
  } else {
    cout << "Error: unable to open "
         << "'" << filename << "'" << endl;
  }
  openfile.close();
}
// Function #3: Load_Line
// Parameter: ourvector<DATA> &database, ourvector<char> &str, string s
// Description: Helper function for load_db(loading database) and add
// it takes each line for database and sort it in its respective vector
void Load_Line(ourvector<DATA> &database, ourvector<char> &str, string s) {
  DATA d;
  string number;
  int num;
  // using this to filter off the first line containing
  // the str's by check if the first char is lower case
  if (islower(s[0])) {
    for (unsigned long int i = 5; i < s.length(); i++) {
      str.push_back(s[i]);
    }
  } else {
    for (unsigned long int i = 0; i < s.size(); i++) {
      // if its an alphabet it would save in the name member of the struct
       if (isalpha(s[i])) {
        d.name.push_back(s[i]);
      } else if (isdigit(s[i])) {
        // filters the number off to save in its proper member
        number += s[i];
        if (number.length() == 0) {
          continue;
        } else if ((s[i + 1] == ',') || (s[i + 1] == '\0')) {
          num = stoi(number);
          number = "";
          d.matches.push_back(num);
        }
      }
    }
    // pushes the struct into the vector of structs
    database.push_back(d);
  }
}
// Function #4: Load_db
// Parameter: ourvector<DATA> &database, string filename,
// ourvector<char> &str
// Description: function for the "Load_db" command,
// opens file and loads the in their appropriate vector
void Load_db(ourvector<DATA> &database, string filename,
             ourvector<char> &str) {
  ifstream openfile;
  openfile.open(filename);
  string file_data;
  if (openfile.is_open()) {
    while (openfile >> file_data) {
      Load_Line(database, str, file_data);
    }
  } else {
    cout << "Error: unable to open "
         << "'" << filename << "'" << endl;
  }
  openfile.close();
  str.push_back(',');
}
// Function #5: Display_Process
// parameter: int &processed, ourvector<int>&str_count,
// ourvector<char> &str
// Description: Helper function to help display process and when
// when data has been processed
void Display_Process(int &processed, ourvector<int>
&str_count, ourvector<char> &str) {
  if (processed == 0) {
    cout << endl
         << "No DNA has been processed." << endl;
  } else if (processed == 1) {
    cout << endl
         << "DNA processed, STR counts:" << endl;
    int j = 0;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == ',') {
        cout << ":"
             << " " << str_count[j] << " ";
        j++;
        cout << endl;
        continue;
      }
      cout << str[i];
    }
    cout << endl;
  }
}
// Function #6: Display_Dna
// Parameter: ourvector<char> d_n_a
// Description: Helper function to display DNA
void Display_Dna(ourvector<char>& d_n_a) {
  // checking if anything has been loaded into the dna vector
  if (d_n_a.size() == 0) {
    cout << endl
         << "No DNA loaded." << endl;
  } else {
    cout << endl
         << "DNA loaded: " << endl;
    for (int i = 0; i < d_n_a.size(); i++) {
      cout << d_n_a.at(i);
    }
    cout << endl;
  }
}
// Function #6: display
// Parameter: ourvector<DATA> &database, ourvector<char> &str,
// ourvector<char> d_n_a, int &processed,ourvector<int> &str_count
// Description: displays the required output when the display command
// is called
void display(ourvector<DATA> &database, ourvector<char> &str,
ourvector<char>& d_n_a, int &processed,
ourvector<int> &str_count) {
  if (database.size() == 0) {
    cout << "No database loaded.";
  } else {
    cout << "Database loaded: " << endl;
    for (int i = 0; i < database.size(); i++) {
      // printing out the names
      for (int j = 0; j < database.at(i).name.size(); j++) {
        cout << database.at(i).name.at(j);
      }
      // printing out the numbers for each names
      for (int index = 0; index < database.at(i).matches.size(); index++) {
        cout << " ";
        cout << database.at(i).matches.at(index);
      }
      cout << endl;
    }
  }
  Display_Dna(d_n_a);
  Display_Process(processed, str_count, str);
}
// Function #7: add
// Parameter: ourvector<DATA> &database, ourvector<char> &str
// Description: Customized command "Add" uses Load_Line function
// to load the user input
void add(ourvector<DATA> &database, ourvector<char> &str) {
  string data;
  getline(cin, data);
  Load_Line(database, str, data);
}
// Function #8: Longest_Sequence
// Parameter: ourvector<char> each_str,ourvector<char> d_n_a,
// int &dna_index, int &index, int &num_matches, int &largest,
// unsigned long int &i, int &j
// Description: Helper Function compares each characters of str
// and dna to see if they match to equal the
// lenght of the each_str it returns true
// it also returns true if it doesnt match so the program knows when to
// break and check the next character. Returns False when nothing happens
// so the program continues
bool Longest_Sequence(ourvector<char>& each_str,
ourvector<char>& d_n_a, int &dna_index,
int &index, int &num_matches, int &largest,
unsigned long int &i, int &j) {
	// checking each character if they match
  if (d_n_a.at(dna_index) == each_str[j]) {
    index++;
    // if the index gets to each_str size then it is
    // a match, then the index of dna becomes i+index
    if (index == each_str.size()) {
      i += index;
      num_matches++;
      return true;
    } else {
       dna_index++;
    }
  } else {
  	// comparing to find the longest reptition
    if (largest < num_matches) {
      largest = num_matches;
      num_matches = 0;
    }
    num_matches = 0;
    i++;
    index = 0;
    return true;
  }
  return false;
}
// Function #9: Sequence
// Parameter: ourvector<char> each_str,ourvector<char> d_n_a,
// ourvector<int> &str_count
// Description: Helper function for the process Command Function
// it loops through dna ourvector and each_str ourvector
// and gets each character.
// And passes it into Longest_Sequence function, it updates str_count with
// longest repetition
void Sequence(ourvector<char>& each_str,
              ourvector<char>& d_n_a, ourvector<int> &str_count) {
  int num_matches = 0;
  int dna_index;
  int largest = 0;
  int index = 0;
  bool match;
  unsigned long int i = 0;
  while (i < d_n_a.size()) {
    index = 0;
    dna_index = i;
    for (int j = 0; j < each_str.size(); j++) {
    	// checks if the updated dna_index is getting more than
    	// the dna ourvector size
      if (dna_index < d_n_a.size()) {
        match = Longest_Sequence(each_str, d_n_a, dna_index,
                                 index, num_matches, largest, i, j);
        if (match == true) {
          break;
        } else {
          continue;
        }
        // it updates counter of dna size if dna_size is less
      } else {
        i = dna_index;
        i++;
        break;
      }
    }
  }
  str_count.push_back(largest);
}
// Function #10: Process
// Parameter: ourvector<char> str, ourvector<char> d_n_a,
// ourvector<int> &str_counts
// Description: This is the Process command function, this function collects
// Each strs and loads them into Sequence funtion to be processed
void Process(ourvector<char>& str, ourvector<char>&
d_n_a, ourvector<int> &str_counts) {
  cout << "Processing DNA..." << endl;
  int j = 0;
  // vector for each str
  ourvector<char> each_str;
  // first get the str in the str vector
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != ',') {
      each_str.push_back(str[i]);
    } else if ((str[i] == ',') || (str[i] == '\0')) {
      Sequence(each_str, d_n_a, str_counts);
      each_str.clear();
      j = 0;
    }
  }
}
// Function #11: Found
// Parameter: ourvector<int> str_counts, ourvector<DATA> data_base,
// int &index
// Description: Helper function for Search, takes in the data_base and the
// str_counts to compare the str counts to get the person, returns true
// When a match is found, and false when no one is found
bool Found(ourvector<int>& str_counts, ourvector<DATA>& data_base,
int &index) {
  cout << "Searching database..." << endl;
  int size_index;
  bool found = false;
  // the index of the data_base to get the index of the name match
  for (int i = 0; i < data_base.size(); i++) {
    size_index = 0;
    // going through the str_count and comparing to data_base match
    for (int j = 0; j < str_counts.size(); j++) {
      if (data_base[i].matches[j] == str_counts[j]) {
        size_index++;
        if (size_index == str_counts.size()) {
          cout << "Found in database! DNA matches: ";
          index = i;
          found = true;
          break;
        }
        // if no match sets size_index to 0 to compare the next
        // name
      } else {
        size_index = 0;
        break;
      }
    }
  }
  return found;
}
// Function #12: Search
// Parameter: ourvector<int> str_counts, ourvector<DATA> data_base
// Description: Funtion for the command Search, get the index of the person
// and gets notified when a match is found from Found funtion.
void Search(ourvector<int>& str_counts, ourvector<DATA>& data_base) {
  int name_index;
  if (Found(str_counts, data_base, name_index) == true) {
    for (int i = 0; i < data_base[name_index].name.size(); i++) {
      cout << data_base[name_index].name[i];
    }
  } else {
    cout << "Not found in database.";
  }
  cout << endl;
}
int main() {
  // store the str from the database file
  ourvector<char> str;
  // stores the dna from the dna file
  ourvector<char> d_n_a;
  // store the name and number of sequence
  // from the database file using the DATA struct
  ourvector<DATA> data_base;
  // store the number of counts after entering the process commmand
  ourvector<int> str_counts;
  int multiple_times_db = 0;
  int multiple_times_dna = 0;
  int processed = 0;
  string input, file_name, command;
  cout << "Welcome to the DNA Profiling Application." << endl;
  while (1) {
    cout << "Enter command or # to exit: ";
    getline(cin, input);
    stringstream s(input);
    s >> command >> file_name;
    if ((command[0] == 'l') || (command[0] == 'L')) {
      // checks the command for loading dna,
     // command to load: "load_dna "name of file""
      if (command == "load_dna" || command == "Load_dna") {
        // to check if the command has been
       // used multiple times so it can clear the vector for reusage
        if (multiple_times_dna >= 1) {
          processed = 0;
          d_n_a.clear();
        }
        cout << "Loading DNA..." << endl;
        multiple_times_dna++;
        Load_dna(file_name, d_n_a);
        // the command for loading database,
       // command to load: "load_db "name of file""
      } else if (command == "load_db" || command == "Load_db") {
        // to check if the command has been used
       // multiple times so it can clear the vector for reusage
        if (multiple_times_db >= 1) {
          processed = 0;
          data_base.clear();
        }
        cout << "Loading database..." << endl;
        multiple_times_db++;
        Load_db(data_base, file_name, str);
      }
      // Command for Searching
    } else if ((command == "search") || (command == "Search")) {
      if (str.size() == 0 && data_base.size() == 0) {
        cout << "No database loaded." << endl;
      } else if (d_n_a.size() == 0) {
        cout << "No DNA loaded." << endl;
      } else if (processed == 0) {
        cout << "No DNA processed." << endl;
      } else {
        Search(str_counts, data_base);
      }
      // command to display
    } else if ((command == "display") || (command == "Display")) {
      display(data_base, str, d_n_a, processed, str_counts);
      // Command to Process
    } else if ((command == "process") || (command == "Process")) {
      if (str.size() == 0 && data_base.size() == 0) {
        cout << "No database loaded." << endl;
      } else if (d_n_a.size() == 0) {
        cout << "No DNA loaded." << endl;
      } else {
        Process(str, d_n_a, str_counts);
        processed = 1;
      }
      // Command for the customized function
    } else if ((command == "add") || (command == "Add")) {
      add(data_base, str);
    } else {
      return 0;
    }
  }
}
