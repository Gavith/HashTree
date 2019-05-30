#pragma once
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
};

class HashTable
{
public:
	HashTable();
	~HashTable();

	void add(Student* in);

	int hashFunc(Student* in);
	void printStudents();
	int countThings(HashEntry ** in, size_t size);
private:
	void resizeData(size_t newSize);

	size_t length = 100;
	HashEntry ** data;
};

