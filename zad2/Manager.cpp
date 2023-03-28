#include "Manager.h"

Manager::Manager(unsigned maxFiles)
{
	maxSize = maxFiles;
	files = new File[maxFiles];

}

Manager::Manager(const Manager& other)
{
	copyFrom(other);
}

Manager& Manager::operator=(const Manager& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Manager::~Manager()
{
	free();
}

void Manager::newFile(const char* fileName, Event createDate, const char* perm) {

	File toAdd = File(fileName, "", 0, createDate,createDate, perm);
	if(filesCount == 0)
		files[0] = toAdd;
	files[filesCount - 1] = toAdd;
	filesCount++;

}

void Manager::editFile(const char* fileName, const char* text, Event editTime, char group)
{
	{
		unsigned index = getFileIndex(fileName);
		unsigned gr = gerGroup(group, 'w');
		if (files[index].getPermissions()[gr] != '-') {
			files[index].setText(text);
			files[index].setModiDate(editTime);
		}
	}
}

void Manager::addText(const char* fileName, const char* text, Event editTime, char group)
{
	unsigned index = getFileIndex(fileName);
	unsigned gr = gerGroup(group, 'w');
	if (files[index].getPermissions()[gr] != '-') {
		char oldText[512];
		strcpy(oldText, files[index].getText());
		strcat(oldText, text);
		files[index].setText(oldText);
		files[index].setModiDate(editTime);
	}
}

void Manager::deleteFile(const char* fileName)
{
	unsigned index = getFileIndex(fileName);
	files[index] = files[filesCount - 1];
	filesCount--;
}

void Manager::chmod(const char* fileName, char group, char perm)
{
	unsigned index = getFileIndex(fileName);
	unsigned place = gerGroup(group, perm);
	if (files[index].getPermissions()[place] == '-') {
		files[index].setPermissions(index, perm);
	}
	else
		files[index].setPermissions(index, '-');
}


void Manager::printInfo(const char* fileName)
{
	unsigned index = getFileIndex(fileName);
	files[index].printInfo();
}

void Manager::printText(const char* fileName, char group)
{
	unsigned index = getFileIndex(fileName);
	unsigned gr = gerGroup(group, 'r');
	if (gr != '-')
	{
		std::cout << files[index].getText();
	}
}

void Manager::printAllFiles()
{
	for (unsigned i = 0; i < filesCount; ++i) {
		files[i].printInfo();
		std::cout << std::endl << std::endl;
	}
}

unsigned Manager::getFilesCount() const
{
	return filesCount;
}

unsigned Manager::getFileIndex(const char* name)
{
	unsigned fCount = getFilesCount();
	for (unsigned i = 0; i < fCount; ++i) {
		if (strcmp(files[i].getName(), name) == 0) {
			return i;
		}
	}
}

unsigned Manager::gerGroup(char user, char mode)
{
	if (user == 'u' && mode == 'r')
		return 0;
	else if(user == 'u' && mode =='w')
		return 1;
	else if (user == 'u' && mode == 'x')
		return 2;
	else if (user == 'g' && mode == 'r')
		return 3;
	else if (user == 'g' && mode == 'w')
		return 4;
	else if (user == 'g' && mode == 'x')
		return 5;
	else if (user == 'o' && mode == 'r')
		return 6;
	else if (user == 'o' && mode == 'w')
		return 7;
	else if (user == 'o' && mode == 'x')
		return 8;
}

