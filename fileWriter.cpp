#include <fstream>
#include <string>
#include <vector>

#include "dataStruct.h"

void writeToFile(vector<RowData>& data, string fileName){

	ofstream output(fileName);
	for(RowData rows : data){
		output << rows.getRawValue() << endl;
	}
}