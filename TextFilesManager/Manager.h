#pragma once
#include <fstream>
#include "File.h"

enum class SortBy {
	Name,
	CreateTime,
	ModificationTime,
	size
};

bool compare(const File& lhs, const File& rhs, SortBy sortBy);

class Manager
{
	File* files;
	unsigned filesCount = 0;
	unsigned maxSize;

	void free();
	void copyFrom(const Manager& other);

public:
	Manager(unsigned files);
	Manager(const Manager& other);
	Manager& operator=(const Manager& other);
	~Manager();

	bool newFile(const char* fileName, Event createDate, const char* perm);
	bool editFile(const char* fileName, const char* text, Event editTime, char group);	
	bool addText(const char* fileName, const char* text, Event editTime, char group);
	bool deleteFile(const char* fileName);
	bool chmod(const char* fileName, char group, char perm);
	bool printInfo(const char* fileName);
	bool printText(const char* fileName, char group);
	bool printAllFiles();

	unsigned getFilesCount() const;
	int getFileIndex(const char* name);
	unsigned gerGroup(char user, char mode);
	void sortBy(SortBy type);
};

