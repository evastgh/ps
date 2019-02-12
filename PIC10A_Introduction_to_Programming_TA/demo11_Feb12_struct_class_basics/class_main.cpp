#include <string>
#include <iostream>
#include "Person_class.h"

using namespace std;
int main()
{
	Person person1, person2, person3;
	cout << "Please input the first person's name, phone number, favorite dessert, separated by new line character." << endl;
	person1.set_name();
	person1.set_phone_number();
	person1.set_favorite_dessert();
	person1.print_status();
    return 0;
}

