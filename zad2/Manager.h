#pragma once
#include <fstream>
#include "File.h"

class Manager
{
	File* files;
	unsigned filesCount = 0;
	unsigned maxSize;

	void free() {
		delete[] files;
		filesCount = 0;
	}
	void copyFrom(const Manager& other) {
		filesCount = other.filesCount;
		for (unsigned i = 0; i < filesCount; ++i) {
			files[i] = other.files[i];
		}
	}

public:
	Manager(unsigned files);
	Manager(const Manager& other);
	Manager& operator=(const Manager& other);
	~Manager();

	void newFile(const char* fileName, Event createDate, const char* perm);
	void editFile(const char* fileName, const char* text, Event editTime, char group);	
	void addText(const char* fileName, const char* text, Event editTime, char group);
	void deleteFile(const char* fileName);
	void chmod(const char* fileName, char group, char perm);
	void printInfo(const char* fileName);
	void printText(const char* fileName, char group);
	void printAllFiles();

	unsigned getFilesCount() const;
	unsigned getFileIndex(const char* name);
	unsigned gerGroup(char user, char mode);
	//void sortBy(); // enum class
};

