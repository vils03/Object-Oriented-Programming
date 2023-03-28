#include "File.h"

void File::setName(const char* name) {
	if (name != nullptr)
		strcpy(this->name, name);
}

void File::setText(const char* text) {
	if (text != nullptr) {
		strcpy(this->text, text);
	}
}
void File::setSize(unsigned size) {
	this->size = size;
}
void File::setPermissions(unsigned index, char mode)
{
	permissions[index] = mode;
}


void File::setModiDate(const Event& newDate)
{
	lastModified = newDate;
}

File::File():File("", "", 0, "---------", 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0){}

File::File(const char* name, const char* text, unsigned size, const Event& create, const Event& modified, const char* perm) :createDate(create),lastModified(modified)
{
	setName(name);
	setText(text);
	strcpy(permissions, perm);
	setSize(size);
}

File::File(const char* name, const char* text, unsigned size, const char* perm, unsigned dayCreate, unsigned monthCreate, unsigned yearCreate, unsigned hoursCreate, unsigned minsCreate, unsigned secCreate, unsigned dayModified, unsigned monthModified, unsigned yearModified, unsigned hoursModified, unsigned minsModified, unsigned secModified):
	createDate(dayCreate,monthCreate,yearCreate, hoursCreate, minsCreate,secCreate), lastModified(dayModified,monthModified,yearModified,hoursModified,minsModified,secModified)
{
	setName(name);
	setText(text);
	setSize(size);
	strcpy(permissions, perm);
}

const char* File::getName() const
{
	return name;
}

const char* File::getText() const
{
	return text;
}

const char* File::getPermissions() const
{
	return permissions;
}

const Event& File::getCreationDate() const
{
	return createDate;
}

const Event& File::getLastMDate() const
{
	return lastModified;
}

unsigned File::getSize() const
{
	return size;
}

void File::printInfo() const
{
	std::cout << name << std::endl;
	std::cout << "Size: " << size << std::endl;
	std::cout << "Permissions: " << permissions << std::endl;
	std::cout << "Date of creation: ";
	createDate.print();
	std::cout << "\nDate of last modification: ";
	lastModified.print();
}
