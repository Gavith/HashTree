#include "HashTable.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

HashTable::HashTable()
{
	data = new HashEntry*[100];

	for (int i = 0; i < length; i++) {
		data[i] = nullptr;
	}
}


HashTable::~HashTable()
{
}

void HashTable::add(Student* in)
{
	int index = hashFunc(in);
	if (data[index] != nullptr) {//if there is an entry in the one im trying to add to
		if (data[index] && data[index]->next != nullptr) {//if theres already 2 of them
			//resize the array
			resizeData(length*2);
			add(in);//add it recursively
		}
		else {//add it to the next
			data[index]->next = new HashEntry(in);
		}
	}
	else {//put it in the array
		data[index] = new HashEntry(in);
	}
	
}

void HashTable::resizeData(size_t newSize)
{
	size_t oldSize = length;
	HashEntry ** oldData = new HashEntry*[length];
	for (int i = 0; i < oldSize; i++)
		oldData[i] = nullptr;
	memcpy(oldData, data, length);

	length = newSize;
	data = new HashEntry*[newSize];
	for (int i = 0; i < newSize; i++)
		data[i] = nullptr;
	for (unsigned int i = 0; i < oldSize; i++) {
		if (oldData[i]) {
			if (oldData[i]->next) {
				int index = hashFunc(oldData[i]->next->data);
				if (data[index] != nullptr) {
					data[index]->next = oldData[i]->next;
				}
				else {
					data[index] = oldData[i]->next;
				}
				oldData[i]->next = nullptr;
			}
			int index = hashFunc(oldData[i]->data);
			if (data[index] != nullptr) {
				data[index]->next = oldData[i];
			}
			else {
				data[index] = oldData[i];
			}
		}
		
	}
	
}



int HashTable::hashFunc(Student * in)
{
	int f = 0; 
	for (unsigned int i = 0; i < strlen(in->firstName); i++)
		f += in->firstName[i];
	int l = 0; 
	for (unsigned int i = 0; i < strlen(in->lastName); i++)
		l += in->lastName[i];

	int total = (int)((float)(abs(f - l) * in->id) / in->gpa);

	return total % length;
}


void HashTable::printStudents()
{
	for (int i = 0; i < length; i++) {
		if (data[i]) {
			cout << i << " " << data[i]->data->firstName << " " << data[i]->data->lastName;

			if (data[i]->next) {
				cout  << " -> " << data[i]->next->data->firstName << " " << data[i]->next->data->lastName;
			}
			cout << endl;
		}
	}
}


