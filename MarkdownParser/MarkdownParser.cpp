#include "MarkdownParser.h"
#pragma warning(disable: 4996)

char* removeSpace(char* s)
{
	char* toReturn = s;
	char* result = new char[20];
	int resInd = 0;
	for (char* s2 = toReturn; *s2; ++s2) {
		if (*s2 != ' ') {
			*toReturn++ = *s2;
			result[resInd] = *s2;
			resInd++;
		}
	}
	*toReturn = 0;
	result[resInd] = '\0';
	return result;
}

Row readRow(std::ifstream& ifs) {
	char buff[1024];
	ifs.getline(buff, 1024);
	std::stringstream ss(buff);

	Row currentRow;
	while (!ss.eof()) {
		unsigned& valuesCount = currentRow.valuesCount;
		ss.getline(currentRow.values[valuesCount++].str, globalConstants::MAX_SYMBOL, '|');

	}
	return currentRow;
}
mdTable parseFromFile(const char* str) {
	std::ifstream input(str);
	if (!input.is_open()) {
		throw std::exception("Error");
	}
	mdTable resultFile;
	resultFile.columnName = readRow(input);

	while (!input.eof()) {
		resultFile.rows[resultFile.rowsCount++] = readRow(input);

	}
	input.close();
	return resultFile;
}
void printRow(const Row& row) {
	for (int i = 0; i < row.valuesCount; ++i) {
		std::cout << row.values[i].str;
	}
	std::cout << std::endl;
}
void print(const mdTable& fileToPrint) {
	printRow(fileToPrint.columnName);
	for (int i = 0; i < fileToPrint.rowsCount; ++i) {
		printRow(fileToPrint.rows[i]);
	}
}
void saveRow(const Row& row, std::ofstream& ofs) {
	for (int i = 0; i < row.valuesCount; ++i) {
		ofs << row.values[i].str;
		if (i != row.valuesCount - 1) {
			ofs << "|";
		}

	}
	ofs << std::endl;
}
void saveMdTable(const mdTable& file, const char* fileName) {
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		return;
	}
	saveRow(file.columnName, ofs);
	for (unsigned i = 0; i < file.rowsCount; ++i) {
		saveRow(file.rows[i], ofs);
	}
	ofs.close();
	std::cout << "Successfully saved!" << std::endl;
}
int getColumnIndex(mdTable& mdtable, const char* columnName) {
	for (unsigned i = 0; i < mdtable.columnName.valuesCount; ++i) {
		if (strcmp(removeSpace(mdtable.columnName.values[i].str), columnName) == 0)
			return i;
	}
	return -1;
}
bool changeValue(mdTable& mdtable, const char* columnName, const char* valueToChange, const char* changeWith) {
	int columnIndex = getColumnIndex(mdtable, columnName);
	if (columnIndex == -1) {
		return false;
	}
	for (unsigned i = 0; i < mdtable.rowsCount; ++i) {
		if (strcmp(removeSpace(mdtable.rows[i].values[columnIndex].str), valueToChange) == 0) {
			strcpy_s(mdtable.rows[i].values[columnIndex].str, globalConstants::MAX_SYMBOL, changeWith);
			return true;
		}
	}
	return false;
}
bool changeColumnName(mdTable& mdtable, const char* oldName, const char* newName) {
	int columnIndex = getColumnIndex(mdtable, oldName);
	if (columnIndex == -1) {
		return false;
	}
	strcpy_s(mdtable.columnName.values[columnIndex].str, globalConstants::MAX_SYMBOL, newName);
	return true;
}
bool changeVal(mdTable& mdtable, unsigned rowNum, const char* columnName, const char* changeWith) {
	int columnIndex = getColumnIndex(mdtable, columnName);
	if (columnIndex == -1) {
		return false;
	}
	strcpy_s(mdtable.rows[rowNum - 1].values[columnIndex].str, globalConstants::MAX_SYMBOL, changeWith);
	return true;
}
void selectPrint(mdTable& mdtable, const char* column, const char* text) {
	printRow(mdtable.columnName);
	int columnIndex = getColumnIndex(mdtable, column);
	for (unsigned i = 0; i < mdtable.rowsCount; ++i) {
		if (strcmp(removeSpace(mdtable.rows[i].values[columnIndex].str), text) == 0) {
			printRow(mdtable.rows[i]);
		}
	}
}

bool addElement(mdTable& mdtable, const char* str, unsigned i)
{
	if (str == nullptr)
		return false;
	strcpy(mdtable.rows[mdtable.rowsCount - 1].values[i].str, str);
	return true;
}

unsigned getColumnsCount(mdTable& table)
{
	return table.columnName.valuesCount;
}
