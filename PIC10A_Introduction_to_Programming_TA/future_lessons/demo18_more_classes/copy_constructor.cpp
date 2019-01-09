#include <string>

using namespace std;
class Foo
{
	private:
		string name;

	public:
		Foo(const string& _name)
			: name(_name)
		{
		}

};

int main(){
	string s1 = string(100,'a');
	for (size_t i = 0; i < 500000; ++i){
		Foo p1(s1);
	}
}
