#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

namespace globalConstants {
	const unsigned MAX_ROW = 50;
	const unsigned MAX_COLUMN = 10;
	const unsigned MAX_SYMBOL = 20;
}

char* removeSpace(char* s);

struct Values {
	char str[globalConstants::MAX_SYMBOL] = "";
};

struct Row {
	Values values[globalConstants::MAX_COLUMN];
	unsigned valuesCount = 0;
};

struct mdTable {
	Row columnName;
	Row rows[globalConstants::MAX_ROW];
	unsigned rowsCount = 0;
};

Row readRow(std::ifstream& ifs);
mdTable parseFromFile(const char* str);
void printRow(const Row& row);
void print(const mdTable& fileToPrint);
void saveRow(const Row& row, std::ofstream& ofs);
void saveMdTable(const mdTable& file, const char* fileName);
int getColumnIndex(mdTable& mdtable, const char* columnName);
bool changeValue(mdTable& mdtable, const char* columnName, const char* valueToChange, const char* changeWith);
bool changeColumnName(mdTable& mdtable, const char* oldName, const char* newName);
bool changeVal(mdTable& mdtable, unsigned rowNum, const char* columnName, const char* changeWith);
void selectPrint(mdTable& mdtable, const char* column, const char* text);
bool addElement(mdTable& mdtable, const char* str, unsigned i);
unsigned getColumnsCount(mdTable& table);
