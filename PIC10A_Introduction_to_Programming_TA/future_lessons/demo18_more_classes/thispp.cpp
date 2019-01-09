class Foo
{
		int foo;

		Foo(const int foo)
				// : foo(foo) // 1st way: colon
		{
			// this->foo = foo; // 2nd way: this->
			(*this).foo = foo; // 3rd way: * and .
			// this++; // this causes compiler error
		}

};
int main(){
}
