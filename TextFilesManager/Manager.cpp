#include "Manager.h"

bool compare(const File& lhs, const File& rhs, SortBy sortBy)
{
	if(sortBy == SortBy::Name)
		return strcmp(lhs.getName(), rhs.getName()) < 0;
	else if(sortBy == SortBy::size)
		return lhs.getSize() < rhs.getSize();
	else if (sortBy == SortBy::CreateTime) {
		Event ev = lhs.getCreationDate();
		return ev.lessThan(rhs.getCreationDate());
	}
	else if (sortBy == SortBy::ModificationTime) {
		Event e = lhs.getLastMDate();
		return e.lessThan(rhs.getLastMDate());
	}
	return false;
}

void Manager::free()
{
	
		delete[] files;
		filesCount = 0;
	
}

void Manager::copyFrom(const Manager& other)
{
	filesCount = other.filesCount;
	for (unsigned i = 0; i < filesCount; ++i) {
		files[i] = other.files[i];
	}
	maxSize = other.maxSize;
}

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

bool Manager::newFile(const char* fileName, Event createDate, const char* perm) {

	if (filesCount == maxSize)
		return false;
	File toAdd = File(fileName, "", createDate,createDate, perm);
	files[filesCount] = toAdd;
	filesCount+=1;
	return true;

}

bool Manager::editFile(const char* fileName, const char* text, Event editTime, char group)
{
	unsigned index = getFileIndex(fileName);
	if (index == -1)
		return false;
	unsigned gr = gerGroup(group, 'w');
	if (files[index].getPermissions()[gr] != '-') {
		files[index].setText(text);
		files[index].setModiDate(editTime);
		files[index].setSize();
		return true;
	}
	std::cout << "You do not have the rights to write in this file.\n";
	return false;
}

bool Manager::addText(const char* fileName, const char* text, Event editTime, char group)
{
	int index = getFileIndex(fileName);
	if (index == -1)
		return false;
	unsigned gr = gerGroup(group, 'w');
	if (files[index].getPermissions()[gr] != '-') {
		char oldText[512];
		strcpy(oldText, files[index].getText());
		strcat(oldText, text);
		files[index].setText(oldText);
		files[index].setModiDate(editTime);
		files[index].setSize();
		return true;
	}
	std::cout << "You do not have the rights to write in this file.\n";
	return false;
}

bool Manager::deleteFile(const char* fileName)
{
	int index = getFileIndex(fileName);
	if (index == -1)
		return false;
	files[index] = files[filesCount - 1];
	filesCount--;
	return true;
}

bool Manager::chmod(const char* fileName, char group, char perm)
{
	int index = getFileIndex(fileName);
	if (index == -1)
		return false;
	unsigned place = gerGroup(group, perm);
	if (files[index].getPermissions()[place] == '-') {
		files[index].setPermissions(index, perm);
	}
	else
		files[index].setPermissions(index, '-');
	return true;
}


bool Manager::printInfo(const char* fileName)
{
	int index = getFileIndex(fileName);
	if (index == -1)
		return false;
	files[index].printInfo();
	return true;
}

bool Manager::printText(const char* fileName, char group)
{
	int index = getFileIndex(fileName);
	if (index == -1)
		return false;
	unsigned gr = gerGroup(group, 'r');
	if (files[index].getPermissions()[gr] != '-')
	{
		std::cout << files[index].getText();
		return true;
	}
	std::cout << "You do not have the rights to read this file.\n";
	return false;
}

bool Manager::printAllFiles()
{
	for (unsigned i = 0; i < filesCount; ++i) {
		files[i].printInfo();
		std::cout << std::endl << std::endl;
	}
	return true;
}

unsigned Manager::getFilesCount() const
{
	return filesCount;
}

int Manager::getFileIndex(const char* name)
{
	unsigned fCount = getFilesCount();
	for (unsigned i = 0; i < fCount; ++i) {
		if (strcmp(files[i].getName(), name) == 0) {
			return i;
		}
	}
	return -1;
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

void Manager::sortBy(SortBy type)
{
		for (unsigned i = 0; i < filesCount - 1; ++i) {
			int minIndex = i;
			for (int j = i; j < filesCount; j++)
			{
				if (compare(files[j], files[minIndex], type))
					minIndex = j;
			}

			if (i != minIndex)
				std::swap(files[i], files[minIndex]);
		}
}

