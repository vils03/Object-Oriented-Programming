#include "MarkdownParser.h"

const unsigned BUFF_SIZE = 20;

size_t mainMenu() {
	system("CLS");
	std::cout << "Homework 1, Task 1 - Markdown Table Parser\nVelislava Krumova - 0MI0600007\n";
	std::cout << "\nChoose option:\n";
	std::cout << "1. Print table\n2. Change column name\n3. Add row\n4. Change value(row index, column name)\n5. Change value(column name,value)\n6. Select\n7. Save to file\n";
	size_t index;
	std::cin >> index;
	return index;
}

size_t goBack() {
	std::cout << "Press b to go back to main menu...";
	char ch;
	std::cin >> ch;
	size_t index = 0;
	if (ch == 'b')
		index = mainMenu();
	return index;
}

int main() {

	size_t index = mainMenu();
	mdTable myFile = parseFromFile("table.txt");
	while (true) {
		if (index == 1) {
			system("CLS");
			print(myFile);
			index = goBack();
		}
		else if (index == 2) {
			system("CLS");
			std::cout << "Enter old column name: ";
			char oldName[BUFF_SIZE];
			std::cin.ignore();
			std::cin.getline(oldName, BUFF_SIZE);
			std::cout << "\nEnter new column name: ";
			char newName[BUFF_SIZE];
			std::cin.getline(newName, BUFF_SIZE);
			if (!changeColumnName(myFile, oldName, newName))
				std::cout << "Wrong input\n";
			index = goBack();
		}
		else if (index == 3) {
			system("CLS");
			unsigned columns = getColumnsCount(myFile);
			std::cout << "The columns in this file are " << columns << ".\nNow enter " << columns << " values to be added.\n";
			std::cin.ignore();
			myFile.rowsCount++;
			for (unsigned i = 0; i < columns; ++i) {
				char buff[BUFF_SIZE];
				std::cin.getline(buff, BUFF_SIZE);
				addElement(myFile, buff, i);
			}
			index = goBack();
		}
		else if (index == 4) {
			system("CLS");
			std::cout << "Enter row index: ";
			unsigned row;
			std::cin >> row;
			std::cout << "\nEnter column name: ";
			char col[BUFF_SIZE];
			std::cin.ignore();
			std::cin.getline(col, BUFF_SIZE);
			std::cout << "\nEnter new value: ";
			char val[BUFF_SIZE];
			std::cin.getline(val, BUFF_SIZE);
			if (!changeVal(myFile, row, col, val)) {
				std::cout << "Wrong input\n";
			}
			index = goBack();
		}
		else if (index == 5) {
			system("CLS");
			std::cout << "Enter column name: ";
			char column[BUFF_SIZE];
			std::cin.ignore();
			std::cin.getline(column, BUFF_SIZE);
			std::cout << "\nEnter old value: ";
			char oldV[BUFF_SIZE];
			std::cin.getline(oldV, BUFF_SIZE);
			std::cout << "\nEnter new value: ";
			char newV[BUFF_SIZE];
			std::cin.getline(newV, BUFF_SIZE);
			if (!changeValue(myFile, column, oldV, newV))
				std::cout << "Wrong input\n";
			index = goBack();
		}
		else if (index == 6) {
			system("CLS");
			std::cout << "Enter column name: ";
			char c[BUFF_SIZE];
			std::cin.ignore();
			std::cin.getline(c, BUFF_SIZE);
			std::cout << "Enter value: ";
			char v[BUFF_SIZE];
			std::cin.getline(v, BUFF_SIZE);
			std::cout << std::endl;
			selectPrint(myFile, c, v);
			index = goBack();
		}
		else if (index == 7) {
			system("CLS");
			saveMdTable(myFile, "table.txt");
			index = goBack();
		}
	}
}