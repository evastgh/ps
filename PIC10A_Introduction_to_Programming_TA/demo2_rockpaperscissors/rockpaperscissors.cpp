#include <iostream>

using namespace std;
int main(){
	// Randomly select an integer value from 1 to 10 inclusive
	int randomFrom1To10 = rand() % 10 + 1;
	// Variable to store whether the user needs to continue guessing
	bool notCorrectYet = true; // start it being true
	/* The user will be asked to guess until they are correct */
	while( notCorrectYet ) { // while the user has not yet guessed correctly
		cout <<"Guess the number from 1 to 10: ";
		int guess; // value the user will guess
		cin >>guess; // take the user’s guess
		if ( guess == randomFrom1To10 ) { // if the guess is correct
			notCorrectYet = false; // update status so loop can terminate
		}
	}
	cout <<"You guessed the number!"; // tell them they guessed it
}

while (true) {
	cout << "Rock--";
	sleep(0.1);
	cout << "paper--";
	sleep(0.1);
	cout << "scissors--";
	sleep(0.1);
	cout << "SHOOT!" << endl;
	cout << "Please play a shape (Rock: 1\t Paper: 2\t Scissors: 3):";
	int player;
	cin << player;
	int computer = rand() % 3 + 1;
	bool game;
	if (computer == 1){
		cout << "Computer played rock!";
		if (player == 1){
			cout << ""
		}
	}


}