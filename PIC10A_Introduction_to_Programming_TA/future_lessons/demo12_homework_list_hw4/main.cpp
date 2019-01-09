#include "HomeworkList.h"
#include <iostream>
#include <iomanip>

using namespace std;
int main() {
  string student_name;
  HomeworkList homework_list;
  int score, max_possible;
  char yn;
  cout << "Enter student\'s name: ";
  cin >> student_name;
  int top_number;

  // while (yn == 'y') {
  do {
    cout << "Enter student\'s score and max possible score: ";
    cin >> score >> max_possible;
    homework_list.addScore(score, max_possible);

    cout << "More scores? (y/n) ";
    cin >> yn;
    while (yn != 'y' && yn != 'n') {
      cout << "Invalide input. Please enter y or n: ";
      cin >> yn;
    }
  } while (yn == 'y');

  cout << "Enter top number: ";
  cin >> top_number;

  cout << "The average is " << fixed << setprecision(2) << homework_list.percentageFromBest(top_number) << endl;

  return 0;
}
