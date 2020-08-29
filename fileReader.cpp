#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "dataStruct.h"
#include "fileReader.h"

using namespace std;

static const string FILE_NOT_FOUND = "ERROR: Specified file not found";

vector<RowData> readFile(string filePath){

	vector<RowData> results;

	ifstream file(filePath);
	string currLine;
	string temp;
	string colValue;
	// string rowValue;

	int colCount = 0;
	int rowCount = 0;

	if(file.is_open()){

		//EXTRACT HEADERS
		if(file.good()){

			getline(file, currLine);
			stringstream ss(currLine);

			RowData rowData;
			rowData.setRow(rowCount);

			while(getline(ss, colValue, ',')){

				// cout << "found col: " << colValue << "\n";
				rowData.addValue(colValue);
				rowData.setDataBool(false);
				colCount++;

			}
			results.push_back(rowData);
			ss.str(string());
		}

		//EXTRACT VALUES
		while(getline(file, currLine)){

			RowData rowData;
			rowData.setRow(rowCount);
			rowData.setDataBool(true);

			// cout << currLine << endl;

			currLine.erase(remove(currLine.begin(), currLine.end(), '\r'), currLine.end());

			stringstream ss(currLine);
			int currentCol = 0;
			while(getline(ss, temp, ',')){

				// temp[temp.length()] = '\0';
				// cout << "READ: " << temp << endl;
				rowData.addValue(temp);
				currentCol++;
			}
			
			//empty column data on a row
			if(currentCol == (colCount - 1)){
				rowData.setDataBool(true);
				rowData.addValue(" ");

			}
			rowCount++;
			results.push_back(rowData);
		}
	} else {

		cout << FILE_NOT_FOUND << "\n";
	}

	cout << "INFO: Loaded " << rowCount << " rows of data\n";
	cout << "INFO: Loaded " <<  colCount << " columns of data\n";

	file.close();
	return results;
}