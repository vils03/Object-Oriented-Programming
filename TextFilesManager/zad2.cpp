#include "Manager.h"

const unsigned BUFF_SIZE = 20;

size_t mainMenu() {
	system("CLS");
	std::cout << "Homework 1, Task 2 - File Manager System\nVelislava Krumova - 0MI0600007\n";
	std::cout << "\nChoose option:\n";
	std::cout << "1. Create empty file\n2. Edit file\n3. Add text\n4. Delete file\n5. Change permission\n6. Print file info\n7. Print file text\n8. Print all files info\n9. Sort files\n";
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
	Manager myManager(3);
	while (true) {
		if (index == 1) {
			system("CLS");
			std::cout << "Enter file name: ";
			std::cin.ignore();
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			unsigned day, month, year, hours, mins, secs;
			std::cout << "\nEnter day, month, year, hours, mins and seconds of creation date: ";
			std::cin >> day >> month >> year >> hours >> mins >> secs;
			Event create(day, month, year, hours, mins, secs);
			std::cout << "\nEnter permission string: ";
			char permBuff[globalConstants::PERM_MAX];
			std::cin.ignore();
			std::cin.getline(permBuff, globalConstants::PERM_MAX);
			if (!myManager.newFile(nameBuff, create, permBuff))
				std::cout << "Error!\n";
			index = goBack();
		}
		else if (index == 2) {
			system("CLS");
			std::cout << "Enter the name of the file you want to edit: ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			std::cout << "\nEnter the new text: ";
			char textBuff[globalConstants::TEXT_MAX];
			std::cin.getline(textBuff, globalConstants::TEXT_MAX);
			char perm;
			std::cout << "\nEnter type of user(u for user, g for group, o for other): ";
			std::cin.get(perm);
			unsigned day, month, year, hours, mins, secs;
			std::cout << "\nEnter day, month, year, hours, mins and seconds of modification date: ";
			std::cin >> day >> month >> year >> hours >> mins >> secs;
			Event modify(day, month, year, hours, mins, secs);
			if (!myManager.editFile(nameBuff, textBuff, modify, perm))
				std::cout << "Error!\n";
			index = goBack();

		}
		else if (index == 3) {
			system("CLS");
			std::cout << "Enter the name of the file you want to add text to: ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			std::cout << "\nEnter the text you want to add: ";
			char textBuff[globalConstants::TEXT_MAX];
			std::cin.getline(textBuff, globalConstants::TEXT_MAX);
			char perm;
			std::cout << "\nEnter type of user(u for user, g for group, o for other): ";
			std::cin.get(perm);
			unsigned day, month, year, hours, mins, secs;
			std::cout << "\nEnter day, month, year, hours, mins and seconds of modification date: ";
			std::cin >> day >> month >> year >> hours >> mins >> secs;
			Event modify(day, month, year, hours, mins, secs);
			if (!myManager.addText(nameBuff, textBuff, modify, perm))
				std::cout << "Error!\n";
			index = goBack();
		}
		else if (index == 4) {
			system("CLS");
			std::cout << "Enter the name of the file you want to delete; ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			if (!myManager.deleteFile(nameBuff))
				std::cout << "Error!\n";
			index = goBack();
		}
		else if (index == 5) {
			system("CLS");
			std::cout << "Enter the name of the file: ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			std::cout << "\nEnter the type of group(u for user, g for group, o for others): ";
			char gr;
			std::cin.get(gr);
			std::cout << "\nEnter permission you want to change(r for read, w for write, x for execute): ";
			char perm;
			std::cin.ignore();
			std::cin.get(perm);
			if (!myManager.chmod(nameBuff, gr, perm))
				std::cout << "Error!";
			index = goBack();
		}
		else if (index == 6) {
			system("CLS");
			std::cout << "Enter the name of the file; ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			myManager.printInfo(nameBuff);
			std::cout << std::endl;
			index = goBack();
		}
		else if (index == 7) {
			system("CLS");
			std::cout << "Enter the name of the file; ";
			char nameBuff[globalConstants::NAME_MAX];
			std::cin.ignore();
			std::cin.getline(nameBuff, globalConstants::NAME_MAX);
			std::cout << "\nEnter the type of group(u for user, g for group, o for others): ";
			char gr;
			std::cin.get(gr);
			if (!myManager.printText(nameBuff, gr))
				std::cout << "Error!\n";
			std::cout << std::endl;
			index = goBack();
		}
		else if (index == 8) {
			system("CLS");
			myManager.printAllFiles();
			index = goBack();
		}
		else if (index == 9) {
			system("CLS");
			std::cout << "Enter what do you want to sort by(n for name, s for size, c for create date and m for modification date: ";
			char ch;
			std::cin.ignore();
			std::cin >> ch;
			if (ch == 'n')
				myManager.sortBy(SortBy::Name);
			else if (ch == 's')
				myManager.sortBy(SortBy::size);
			else if (ch == 'c')
				myManager.sortBy(SortBy::CreateTime);
			else if (ch == 'm')
				myManager.sortBy(SortBy::ModificationTime);
			std::cout << std::endl;
			index = goBack();
		}

	}
}