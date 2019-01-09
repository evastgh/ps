#include <sstream> // for sout
#include <fstream> // for fout
#include <iostream> // for cout
#include <iomanip> 
#include <vector>
#include <string>

class Food {
	private:
	std::string name;
	double caloriesContent;

	public:
	Food(const std::string& name, double caloriesContent)
	{
		this->name = name;
		this->caloriesContent = caloriesContent;
	}

	// Food()
	// 	: name(""),
	// 	caloriesContent(0)
	// {
	// }

	Food(const Food& food)
		: name(food.name),
		  caloriesContent(food.caloriesContent)
   	{
	}

	// Food& operator= (const Food& food) {
	// 	name = food.name;
	// 	caloriesContent = food.caloriesContent;
	// 	return *this;
	// }
	
	friend std::ostream& operator<<(std::ostream& os, const Food& food) {
		os << food.name << " contains " << food.caloriesContent << " calories!" << std::endl;
		return os;
	}
};

using namespace std;
int main() {
	vector<Food> cabinet;
	Food soylent("Soylent", 400);

	for (size_t i = 0; i < 10; ++i) {
		cabinet.push_back(soylent);
	}
	cout << cabinet[0];
	
	return 0;
}
