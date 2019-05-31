#include <cstring>


struct Student {
	char* firstName;
	char* lastName;
	int id;
	float gpa;

	Student() {
		firstName = new char[20];
		lastName = new char[20];
	}

	~Student() {
		delete[] firstName;
		delete[] lastName;
	}
};

struct HashEntry {
	Student* data;
	HashEntry* next;

	HashEntry() {
		data = nullptr;
		next = nullptr;
	}

	HashEntry(Student* data) {
		this->data = data;
		next = nullptr;
	}

	~HashEntry() {
		delete data;
	}
};

class HashTable
{
public:
	HashTable();
	~HashTable();

	void add(Student* in);

	void remove(int index, bool chain);
	void remove(int id);

	int hashFunc(Student* in);
	void printStudents();
private:
	void resizeData(size_t newSize);

	size_t length = 100;
	HashEntry ** data;
};

