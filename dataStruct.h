#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// class DataStruct{

// 	int rows;
// 	int columns;

	
// };

class RowData{
private: 

	int row;
	vector<string> value;

	bool isData;

public:

	string getRawValue(){

		string result = "";
		for(int i = 0; i < value.size(); i++){
			if(i != (value.size() - 1)) result += value[i] + ",";
			if(i == (value.size() - 1)) result += value[i];
		}

		return result;
	}

	void setRow(int newRow){

		row = newRow;
	}

	void setDataBool(bool boolValue){
		this->isData = boolValue;
	}

	bool getDataBool(){
		return this->isData;
	}

	void printValues(){

		cout << "ROW[" << row << "]:  [";
		for(int i = 0; i < value.size(); i++){

			if(i != (value.size() - 1)) cout << this->value[i] << ", ";
			if(i == (value.size() - 1)) cout << this->value[i] << "]\n";

		}
	}

	void addValue(string value){
		this->value.push_back(value);
	}

	// void setValue(vector<string> value){
	// 	this->value = value;
	// }

	vector<string> getValue() const{
		return value;
	}

	int getRow(){
		return row;
	}
};

#endif