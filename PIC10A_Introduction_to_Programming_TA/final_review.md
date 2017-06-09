# Final Review

#### Study material: 

* Course notes [[Functions]](https://ccle.ucla.edu/pluginfile.php/1842526/mod_resource/content/0/Topic_Functions.pdf) [[Classes]](https://ccle.ucla.edu/pluginfile.php/1845817/mod_resource/content/0/Topic_Classes.pdf) [[Streams]](https://ccle.ucla.edu/pluginfile.php/1857376/mod_resource/content/0/Topic_Streams.pdf) [[Standard Library & Generic Algorithms]](
https://ccle.ucla.edu/pluginfile.php/1857727/mod_resource/content/0/Topic_StandardLibraryAndGenericAlgorithms.pdf)
* Practice final [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/06-08/06-08.html) [[Stephanie's]](https://github.com/evastgh/problems_and_solutions/blob/master/PIC10A_Introduction_to_Programming_TA/final_review.md)
* Past discussion content [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/main.html) [[Stephanie's]](https://github.com/evastgh/problems_and_solutions/tree/master/PIC10A_Introduction_to_Programming_TA)

#### Disclaimers: 
The following practice problems emphasized on mostly conceptual problems and will not prepare you completely for the final. You should also study Geoff's problems in order to practice code snippets related problems!

#### Some goodies we discussed on Thursday:
* The following is a code snippet showing how default constructor ```myClass()``` and copy constructor ```myClass(const myClass&)``` can be implicitly called. 
```cpp
std::vector<myClass> vec(10); // myClass() will be called

std::vecotr<myClass> vec2 = vec; // this is the same as for vec3

std::vector<myClass> vec3;
for (size_t i = 0; i < vec.size(); ++i) {
	vec3.push_back(myClass(vec[i]));
}
```
* What is ```->```? Assuming ```myClass``` has a member ```name``` and an accessor ```getName()```.
```cpp
myClass foo("name");
myClass* address = &foo; // & extracts the address of object foo
cout << address->getName(); // this is the same as the next line
cout << (*address).getName(); // *address is the same as foo; we use . to call member function
```
* Note the difference between the following two for loop!
```cpp
for (auto iter = vec.begin(); iter != vec.end(); ++iter){
    cout << *iter;  // in this case, iter POINTS to each entry of vec, we need to use * to dereference it to access the content
}
for (const auto& iter : vec) {
    cout << iter;  // in this case, iter is the REFERENCE of each entry of vec, no dereferencing is required!
}
```

## Practice Problems

#### True/False
* Every function has a **return** statement. 
* Return statement needs to be placed at the very end of the function definition.
* Usually functions are **declared** in .h (header) files and **defined** in .cpp files.
* Every argument needs to be named in the function **declaration**.
* A function can be defined in the same file as the main function, or in hearder files.
* A function won't effect variables that don't belong to its scope.
* You can **pass by value**, or pass a **const reference** to protect the variable from being unexpectedly changed.
* We can overload functions as long as they can be differentiated based on the arguments types or the returned types. 
* All forms of conversion are not allowed in function overloading; only when the types specified in the definition are exactly the same as in the use cases will the function be overloaded. 
* Default arguments need to be givem from right to left.
* Default values could be provided in both declaration and definition; they just need to be consistent.
* ```auto``` can only infer the types of an r-value expression; it won't help us infer references or help establish const correctness.
* You need to put a semicolon after the definition of a class interface. 
* You can use the member access operator ```.``` to access the public members of a class. 
* You can use the member access operator ```.``` **inside the class** to access the private members of a class.
* A class can only have 1 constructor.
* Class members need to be initialized (in constructor) in the order of their declaration. 
* Any member function not declared as **const** are assumed to modify the class content.
* A class function declared to be **const** but the definition doesn't specify it to be **const** will cause compiler/linker error.
* ```std::cout``` cannot be copied; you can only pass it by reference. Same for ```std::cint```.
* We can overload operators like ```<<``` or ```>>``` for ```ostream``` and ```istream``` to prevent overloading for string streams and file streams separately.
* Manipulators like ```setw```, etc. doesn't work for file streams.
* ```std::set``` will not have repeated item, but the content is sorted in the order of insertion. 
* Just like integers, we can do ```++it``` for an iterator ```it```; we can also do ```it -= 7```.
> This question should have different answer for different containers. Try to do this for vector, set, and list.
* We can use pop_front on ```std::vector``` and ```std::list```.

#### Short questions
* Wrtie a sample comment that documents the following function **definition**
```cpp
int my_max(std::vector<int> list, size_t start = 0) {
    int temp_max = list[start];
    for (size_t i = start + 1; i < list.size(); ++i) {
		if (list[i] > temp_max) {
		    temp_max = list[i];
		}
    }
    return temp_max;
} 
```
* Write down the **signature** for the above function.
* Briefly describe what is **variable masking**.
* Describe the roll of declaration and definition in the process of **compiling** and **linking**. 
* Explain why passing by reference is more efficient than passing by value for non-primitive types. (Primitive types mean char, bool, int, long, double, etc.)
* Explain what is overloading.
* Provide an one-line code to remove the second entry of a vector ```vec```.
> vec.erase(vec.begin()+1); // it's NOT vec.erase(1)
* Explain what is happening when a array is passed to a function. 
* Can we use **const** to protect a pointer?
* Why do we pass **nullptr** to the ```std::time```? What are some other possible input?
* Write a sample range-based for loop.
* Shorten the following codes to one line. (Hint: use ternary operator)
```cpp
int x;
if (y + z < 0) {
    x = 1;
}
else {
    x = 2;
}
```
* Write a templatized version of the ```my_max``` function in the first problem (templatized the type ```int``` in ```my_max```).
* What's the difference between class and struct?
* Briefly explain the benefits of having private members with accessors and mutators.
* What does the ```const``` in the following code snippet mean?
```cpp
class Foo {
    public:
	std::string msg;
	Foo () { msg = "Hello!"; }
	void yell() const { std::cout << msg; }
};
```
* What is the scoping operator? (The operator you use when defining a member function outside of the class scope)
* Write a sample constructor that utilizes constructor initializer list that does the same thing as following.
```cpp
class Foo {
    public:
	std::string msg;
	uint age;
	bool is_fake;
	Foo(const std::string& default_message, uint age_in = 0; bool is_fake = false) {
	    msg = default_message;
	    age = age_in;
	    this->is_fake = is_fake;
	}
};
```
* Describe why initializer list helps boost efficiency. Come up with some examples. 
* What would happen if you don't initialize a class member in your constructor?
* What would happen if you don't have any constructor for a class? What if you have 1 constructor? At the very last, why do we sometimes need multiple constructors?  
* What do ```#ifndef SOME_NAME #define SOME_NAME ... #endif``` in a header file serve for?
* Which one of the following is the most efficient? Why?
```cpp
string s1("cat");
string s2 = string("cat");
string s3 = "cat";
```
* Write a sample code of overloaded ```operator+``` that sums the two vectors entry-wise. (Assume the two vectors are of the same size)
> Overloaded operator can be a class member or an independently existing function. In this class, you should mostly consider the later one. 
* Can I use the same ```std::fostream``` object to write to 2 different files? How?
* How do I detect if a file exist in the directory of the executable? (This could be very useful since you don't want your program to read into a non-existing file)
* What would happen if ```file.txt``` doesn't exist, and I run the following codes? What if ```file.txt``` DOES EXIST?
```cpp
std::fostream fout("file.txt");
fout << "YOLO";
fout.close();
```
* What is the difference between ```'\n'``` and ```std::endl```?
* Why is it important to ```close``` file streams? When will them be automatically closed?
* Write a function for the following documentation. (Use ```int``` type for input)
```cpp
/**
  This function converts its input argument to a string based on how it
  would be rendered through an output stream and operator<<.
  @tparam T the type of data being converted to a string
  @param input the value being turned into a string
  @return the string representation of value
*/
template<typename T>
string toString( const T& input );
```
* Describe what would cause an in stream to fail. What do you do to revert the fail state?
* What's EOF?
* Describe the difference between how the data are stored in ```std::vector``` and ```std::set```. (You can skip the details of the tree, but you need to name the main difference.)
* What would happen if I try to erase an element that is not in the set?
* Write down the content of ```list``` after executing the following.
```cpp
std::list<uint> list = { 2, 4, 5, 9, 7, 0 };
auto iter = list.end();
--iter;
list.insert(--iter, 100);
auto iter2 = list.rbegin();
list.erase(iter2);
```
* What's the public member functions of a ```std::pair``` to access the entries?
* Why do we use ```iter != vec.end()``` instead of ```iter < vec.end()```?
* What is ```crbegin()```?
* How do you utilize ```std::sort``` to sort a vector of uint **in reverse order**?
* Given a vector of uint, utilize some generic algorithm and find an even entry of this vector.
