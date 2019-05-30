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
		if (data[index] && data[index]->next) {//if theres already 2 of them
			//resize the array
			resizeData(length*2);
			//printStudents();
			cout << endl;
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
		oldData[i] = data[i];
	
	
	length = newSize;
	delete[] data;
	data = new HashEntry*[newSize];
	for (int i = 0; i < newSize; i++)
		data[i] = nullptr;
	for (unsigned int i = 0; i < oldSize; i++) {//for all the old data
		if (oldData[i]) {//if it exists
			if (oldData[i]->next) {//if there are 2
				int index = hashFunc(oldData[i]->next->data);//get new hash
				if (data[index] != nullptr) {//if there is one in the new array already
					data[index]->next = oldData[i]->next;//add it
				}
				else {
					data[index] = oldData[i]->next;//add it
				}
				oldData[i]->next = nullptr;//just make sure nothing errors
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
	int f = 1; 
	for (unsigned int i = 0; i < strlen(in->firstName); i++)
		f += in->firstName[i]/3;
	int l = 1; 
	for (unsigned int i = 0; i < strlen(in->lastName); i++)
		l += in->lastName[i]/3;

	int total = (int)(in->gpa * (float)in->id/3 * abs(f-l));

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

int HashTable::countThings(HashEntry ** in, size_t size)
{
	int h = 0;
	for (int i = 0; i < size; i++) {
		if (in[i]) {
			if (in[i]->next) {
				h++;
			}
			h++;
		}
		
	}
	return h;
}


