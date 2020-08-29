#include <exception>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "dataStruct.h"
#include "fileReader.h"
#include "fileWriter.h"

using namespace std;

static const string INVALID_ARGS = "ERROR: Usage: ./dataOrganizer <inputFile> <outputFile>\n";
static const string HELP_MSG = 		"*** DataOrganizer ***\n" 
								+ string("Used to organize and sort a CSV file database \n") 
								+ string("Will automagically sort values inputted into the program\n")
								+ string("Usage: ./dataOrganizer <inputFile> <outputFile>\n");


//https://stackoverflow.com/questions/21807658/check-if-the-input-is-a-number-or-string-in-c/33894544#33894544
bool isNumber(const string& str){
   if(str.empty() || isspace(str[0]) || isalpha(str[0])) return false;
   char* p;
   strtod(str.c_str(), &p);
   return (*p == 0);
}


//returns true of d1 < d2 and false if d1 > d2
bool compareData(const RowData d1, const RowData d2, const vector<int> columnsToSort){

	if(columnsToSort.size() == 1) {
		// cout << "here to sort\n";

		if(isNumber(d1.getValue()[columnsToSort[0]]) && isNumber(d2.getValue()[columnsToSort[0]])){

			char* p, *q;
			// char* q;

			double x = strtod(d1.getValue()[columnsToSort[0]].c_str(), &p);
			double y = strtod(d2.getValue()[columnsToSort[0]].c_str(), &q);
			return x < y;
		}
		return d1.getValue()[(columnsToSort[0])] < d2.getValue()[(columnsToSort[0])];
	}

	//MULTIPLE PARAMTER SORT
	for(int i = 0; i < columnsToSort.size(); i++){

		if(d1.getValue()[columnsToSort[i]] < d2.getValue()[columnsToSort[i]]) return true;
		if(d1.getValue()[columnsToSort[i]] > d2.getValue()[columnsToSort[i]]) return false;
		continue;
	}
	return false;
}


void sortVector(vector<RowData>& rowData, const vector<int> columnsToSort, bool ascending, int start, int end){

	for(int i = 0; i < rowData.size() - 1; i++){
		for(int j = 0; j < rowData.size() - 1 - i; j++){

			//allow to sort only parts of datas
			if(rowData[j].getRow() >= start && rowData[j].getRow() <= end){
				if(rowData[j].getDataBool() && rowData[j + 1].getDataBool()){
					if(ascending){
						if(!compareData(rowData[j], rowData[j + 1], columnsToSort)){
							swap(rowData[j], rowData[j + 1]);
						} 
					} else {
						if(compareData(rowData[j], rowData[j + 1], columnsToSort)){
							swap(rowData[j], rowData[j + 1]);
						}
					}
				}
			}
		}
	}
}

vector<int> getNumbers(string message){

	vector<int> results;

	cout << message;

	string line;
	getline(cin, line);
	stringstream ss(line);
	while(getline(ss, line, ',')){

		try{

			int num = stoi(line) - 1;

			if(num >= 0) results.push_back(num);
			// cout << "converted " << line  << "to " << num << endl;

		} catch (exception exc){
			return {};
		}
	}
	return results;
}

int main(int argc, char** argv){

	if(argc == 3){
		if(string(argv[1]).compare("help") != 0){

			// cout << "*** DataOrganizer ***\n";
			// cout << "For help type, use ./dataOrganizer help\n";

			vector<RowData> fileContents = readFile(argv[1]);
			vector<int> columnsToSort = getNumbers("INFO: Enter columns to sort (ex: 1, 4, 9): ");
			vector<int> rowToSort = getNumbers("INFO: Enter the start row and end row to sort (ex: 1, 200): ");

			string outputFile = argv[2];
			string line;
			string temp;

			while(columnsToSort.size() == 0 || columnsToSort.size() != 1){
				columnsToSort = getNumbers("ERROR: Enter columns to sort (ex: 1, 4, 9): ");
			}	
			while(rowToSort.size() == 0 || rowToSort.size() != 2){
				rowToSort = getNumbers("ERROR: Enter the start row and end row to sort (ex: 1, 200): ");
			}
				
			if(outputFile.find(".csv") != string::npos){

				sortVector(fileContents, columnsToSort, true, rowToSort[0], rowToSort[1]);
				cout << "\nPossible commands:\n";
				cout << "	add <values1,value2,value3,etc...> \n";
				// cout << "	sort <column #> <ascending? true/false> \n";
				// cout << "	  	 <column # for secondary priority> <true/false>\n";
				cout << "	quit - sort and save all data, then quit the program\n";
				cout << "-> ";
				while(getline(cin, line) && line.compare("quit") != 0){


				}

				cout << "Quittting DataOrganizer...\n";
				cout << "Saving values and exporting csv...\n";
				writeToFile(fileContents, outputFile);
				return 0;

			} else {
				cout << INVALID_ARGS;
				cout << "ERROR: Invalid output file\n";
			}
		}
	} else {

		cout << INVALID_ARGS;
	}
	return 0;
}