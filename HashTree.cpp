#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "HashTable.h"

using namespace std;

Student* generateStudent(int &seed);
int getFileLineNum(const char* name);
char* stringToLower(char* in);
bool isDigit(char* in);

int main()
{
	srand(time(NULL));
	int seed = 100;//for incrementing the id in 
	HashTable h = HashTable();
	char* input = new char[10];

	do {
		cout << "1)ADD\n2)DELETE\n3)PRINT\n4)QUIT\n? ";
		cin.get(input, 10);
		cin.ignore(100, '\n');
		stringToLower(input);

		if (strcmp(input, "add") == 0) {
			do {
				cout << "How many do you want to add?" << endl;
				cin.get(input, 10);
				cin.ignore(100, '\n');
			} while (!isDigit(input));
			
			int num = atoi(input);
			cout << "Generating " << num << " students." << endl;
			for (int i = 0; i < num; i++)
				h.add(generateStudent(seed));
		}
		else if (strcmp(input, "delete") == 0) {
			cout << "Do you want to delete from student id or index? (id/index)" << endl;
			cin.get(input, 10);
			cin.ignore(100, '\n');
			stringToLower(input);
			
			if (strcmp(input, "id") == 0) {
				cout << "Do you want to see the students?" << endl;
				cin.get(input, 10);
				cin.ignore(100, '\n');
				stringToLower(input);
				if (input[0] == 'y') {
					h.printStudents();
				}
				do {
					cout << "What is the ID?" << endl;
					cin.get(input, 10);
					cin.ignore(100, '\n');
				} while (!isDigit(input));
				h.remove(atoi(input));
			}
			else if (strcmp(input, "index") == 0) {
				cout << "Do you want to see the students?" << endl;
				cin.get(input, 10);
				cin.ignore(100, '\n');
				stringToLower(input);
				if (input[0] == 'y') {
					h.printStudents();
				}
				do {
					cout << "What is the index?" << endl;
					cin.get(input, 10);
					cin.ignore(100, '\n');
				} while (!isDigit(input));
				int ind = atoi(input);
			
				cout << "Is it the second in the chain?" << endl;
				cin.get(input, 10);
				cin.ignore(100, '\n');
				stringToLower(input);
				bool ye = false;
				if (input[0] == 'y') {
					ye = true;
				}

				h.remove(ind, ye);
			}
		}
		else if (strcmp(input, "print") == 0) {
			h.printStudents();
		}
	} while (input[0] != 'q');


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
	firstNames.getline(first, 100, '\n');

	int j = rand() % getFileLineNum("LastNames.txt"); 

	//cout << j << endl;
	
	for (int i = 0; i < j; i++) {
		lastNames.ignore(1000, '\n');
	}
	lastNames.getline(last, 100, '\n');
	Student* s = new Student();
	if (first[strlen(first) - 1] == '\r') {
		first[strlen(first) - 1] = '\0';
	}
	if (last[strlen(last) - 1] == '\r') {
		last[strlen(last) - 1] = '\0';
	}

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

char * stringToLower(char * in)
{
	for (unsigned int i = 0; i < strlen(in); i++)
		in[i] = tolower(in[i]);
	return in;
}

bool isDigit(char* in) {
	for (unsigned int i = 0; i < strlen(in); i++)
		if (in[i] > 57 || in[i] < 48)
			return false;
	return true;
}