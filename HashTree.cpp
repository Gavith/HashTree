#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "HashTable.h"

using namespace std;

Student* generateStudent(int &seed);
int getFileLineNum(const char* name);

int main()
{
	srand(time(NULL));
	int seed = 100;//for incrementing the id in 
	HashTable h = HashTable();
	for (int i = 0; i < 50; i++) {
		h.add(generateStudent(seed));
	}
	h.printStudents();
}

Student* generateStudent(int &seed) {
	
	ifstream firstNames;
	ifstream lastNames;
	firstNames.open("FirstNames.txt");
	lastNames.open("LastNames.txt");
	
	char* first =  new char[100];
	char* last = new char[100];

	int h = rand() % getFileLineNum("FirstNames.txt");
	//cout << h << endl;
	for (int i = 0; i < h; i++) {
		firstNames.ignore(1000, '\n');
	}

	int j = rand() % getFileLineNum("LastNames.txt"); 

	//cout << j << endl;
	firstNames.getline(first, 100, '\n');
	for (int i = 0; i < j; i++) {
		lastNames.ignore(1000, '\n');
	}
	lastNames.getline(last, 100, '\n');
	Student* s = new Student();
	s->firstName = first;
	s->lastName = last;
	s->id = seed;


	int gpaInt = rand() % 400;
	s->gpa = (float)gpaInt / (float)100;
	//cout << s->gpa << endl;

	seed += 3; //making sure that the seed checks out
	if (seed > 999999) seed -= 1000000;
	return s;

}

int getFileLineNum(const char* name)
{
	ifstream f(name);
	char c;
	long i = 0;
	while (f.get(c))
		if (c == '\n')
			++i;
	f.close();
	return i;
}



