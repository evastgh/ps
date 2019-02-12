#pragma once
#include <string>
#include <iostream>

namespace std {
	class Person {
	private: // unnecessary
		string name, phone_number, favorite_dessert;
	public: // every member function following this line will be public
		void print_status() {
			cout << name << "'s phone number is " << phone_number;
			cout << ", their favorite dessert is " << favorite_dessert << endl;
		}
		void set_name() { getline(cin, name); }
		void set_phone_number() { getline(cin, phone_number); }
		void set_favorite_dessert() { getline(cin, favorite_dessert); }
	};
}
