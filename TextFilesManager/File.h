#pragma once
#pragma warning (disable:4996)
#include <iostream>
#include "Event.h"

namespace globalConstants {
	const unsigned NAME_MAX = 65;
	const unsigned TEXT_MAX = 513;
	const unsigned PERM_MAX = 10;
}
class File
{
	char name[globalConstants::NAME_MAX];
	char text[globalConstants::TEXT_MAX];
	unsigned size;
	Event createDate;
	Event lastModified;
	char permissions[globalConstants::PERM_MAX];

public:
	void setName(const char* name);

	void setText(const char* text);
	void setSize();
	void setPermissions(unsigned index, char mode);
	void setModiDate(const Event& newDate);

	File();
	File(const char* name, const char* text, const Event& create, const Event& modified, const char* perm);
	File(const char* name, const char* text, const char* perm, unsigned dayCreate, unsigned monthCreate, unsigned yearCreate,
		unsigned hoursCreate, unsigned minsCreate, unsigned secCreate,
		unsigned dayModified, unsigned monthModified, unsigned yearModified,
		unsigned hoursModified, unsigned minsModified, unsigned secModified);

	const char* getName() const;
	const char* getText() const;
	const char* getPermissions() const;
	const Event& getCreationDate() const;
	const Event& getLastMDate() const;
	unsigned getSize() const;

	void printInfo() const;

};
