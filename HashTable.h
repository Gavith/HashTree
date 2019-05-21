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

class HashTable
{
public:
	HashTable();
	~HashTable();

	int hashFunc(Student* in, size_t arrSize);
private:
	
};

