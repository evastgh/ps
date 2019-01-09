#include <iostream>
#include <string>
#include <vector>
#include <time.h>

class Inventory{
	const static size_t inventoryMax = 100;
	// size_t inventoryMax = 100;
	std::vector<char> itemList;
	size_t sizeList;

	public:
	Inventory(){
		srand(time(nullptr));
		size_t sizeList = rand() % inventoryMax;
		for (size_t i = 0; i < sizeList; ++i){
			itemList.push_back(static_cast<char>(rand() % std::numeric_limits<char>::max()));
		}
	}

	bool hasItem(const char itemLookup){
		for (size_t i = 0; i < sizeList; ++i){
			if (itemLookup == itemList[i]) {
				return true;
			}
		}
		return false;
	}
};

class Shopper{
	std::string shopperName;
	std::vector<char> toBuyList;
	Inventory& inventory;

	public:
	Shopper(std::string& name, Inventory& _inventory) // can mask inventory variable!
	:shopperName(name),
	inventory(_inventory)	
	{
	}

	std::string getName() const {
		return shopperName;
	}

	void addToBuy(const char item){
		toBuyList.push_back(item);
	}

	
};
using namespace std;
int main(){
	Inventory ralphs;

	cout << "Please input the shopper\'s name: ";
	string shopperName;
	getline(cin, shopperName);
	Shopper stef(shopperName, ralphs);
	cout << "The designated shopper is " << stef.getName() << endl;

	cout << "Please input the item you wish the shopper to buy: ";
	char itemToBuy;
	cin >> itemToBuy;
	stef.addToBuy(itemToBuy); // b for banana!
}

