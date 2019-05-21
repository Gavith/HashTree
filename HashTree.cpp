#include <iostream>
#include <iostream>
#include "HashTable.h"

using namespace std;

int main()
{


	HashTable h;
	Student* s = new Student();
	strcpy(s->firstName, "joe");
	strcpy(s->lastName, "b");
	s->id = 200;
	s->gpa = 2.5;
	cout << h.hashFunc(s, 100) << endl;
    
}
