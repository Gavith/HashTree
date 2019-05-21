#include "HashTable.h"



HashTable::HashTable()
{
}


HashTable::~HashTable()
{
}

int HashTable::hashFunc(Student * in, size_t arrSize)
{
	int f = 0; 
	for (unsigned int i = 0; i < strlen(in->firstName); i++)
		f += in->firstName[i];
	int l = 0; 
	for (unsigned int i = 0; i < strlen(in->lastName); i++)
		f += in->lastName[i];

	int total = (int)((float)((f + l)*in->id) / in->gpa);

	return total % arrSize;
}
