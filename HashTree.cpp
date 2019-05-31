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

		if (strcmp(input, "add") == 0) {//adding new students
			do {
				cout << "How many do you want to add?" << endl;
				cin.get(input, 10);
				cin.ignore(100, '\n');
			} while (!isDigit(input));
			
			int num = atoi(input);
			cout << "Generating " << num << " students." << endl;
			for (int i = 0; i < num; i++)//generates students
				h.add(generateStudent(seed));
		}
		else if (strcmp(input, "delete") == 0) {//delete stuff
			cout << "Do you want to delete from student id or index? (id/index)" << endl;
			cin.get(input, 10);
			cin.ignore(100, '\n');
			stringToLower(input);
			
			if (strcmp(input, "id") == 0) {//deleting based on student id
				cout << "Do you want to see the students?" << endl;//for reference
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
				h.remove(atoi(input));//delete it
			}
			else if (strcmp(input, "index") == 0) {//based on array index
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
				} while (!isDigit(input));//get number
				int ind = atoi(input);
			
				cout << "Is it the second in the chain?" << endl;//if its chained
				cin.get(input, 10);
				cin.ignore(100, '\n');
				stringToLower(input);
				bool ye = false;
				if (input[0] == 'y') {
					ye = true;
				}

				h.remove(ind, ye);//delete it 
			}
		}
		else if (strcmp(input, "print") == 0) {
			h.printStudents();
		}
	} while (input[0] != 'q');//quit


}

Student* generateStudent(int &seed) {
	
	ifstream firstNames;
	ifstream lastNames;
	firstNames.open("FirstNames.txt");//files
	lastNames.open("LastNames.txt");
	
	char* first =  new char[100];
	char* last = new char[100];

	int h = rand() % getFileLineNum("FirstNames.txt");//random name
	for (int i = 0; i < h; i++) {//ignore till random
		firstNames.ignore(1000, '\n');
	}
	firstNames.getline(first, 100, '\n');//get name

	int j = rand() % getFileLineNum("LastNames.txt"); //same thing for last
	for (int i = 0; i < j; i++) {
		lastNames.ignore(1000, '\n');
	}
	lastNames.getline(last, 100, '\n');
	Student* s = new Student();
	if (first[strlen(first) - 1] == '\r') {//differences between windows and linux
		first[strlen(first) - 1] = '\0'; //to do with endlines being \r\n in windows and \n only in linux
	}
	if (last[strlen(last) - 1] == '\r') {
		last[strlen(last) - 1] = '\0';
	}

	s->firstName = first;
	s->lastName = last;
	s->id = seed;


	int gpaInt = rand() % 400;//rand gpa
	s->gpa = (float)gpaInt / (float)100;
	//cout << s->gpa << endl;

	seed += 3; //making sure that the seed checks out
	if (seed > 999999) seed -= 1000000;//for id
	return s;

}

int getFileLineNum(const char* name)
{
	ifstream f(name);
	char c;
	long i = 0;
	while (f.get(c))//for every character
		if (c == '\n')
			++i;
	f.close();
	return i;
}

char * stringToLower(char * in)
{
	for (unsigned int i = 0; i < strlen(in); i++)
		in[i] = tolower(in[i]);//for every char go to lower
	return in;
}

bool isDigit(char* in) {
	for (unsigned int i = 0; i < strlen(in); i++)//checking if all chars are ints
		if (in[i] > 57 || in[i] < 48)
			return false;
	return true;
}