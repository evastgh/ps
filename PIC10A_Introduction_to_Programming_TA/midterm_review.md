# Midterm Review

#### Study material: 

* Course notes [[Data Types & Classes]](https://ccle.ucla.edu/pluginfile.php/1812773/mod_resource/content/0/Topic_DataTypesAndClasses.pdf) [[Control Flow & Vectors]](https://ccle.ucla.edu/pluginfile.php/1812445/mod_resource/content/0/Topic_ControlFlowAndVectors.pdf)
* Practice midterm [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/05-09/05-09.html) [[Stephanie's]](https://github.com/evastgh/problems_and_solutions/blob/master/PIC10A_Introduction_to_Programming_TA/midterm_review.md)
* Past discussion content [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/main.html) [[Stephanie's]](https://github.com/evastgh/problems_and_solutions/tree/master/PIC10A_Introduction_to_Programming_TA)



## Practice Problems

#### True/False

* unsigned integer types can store the value ```0```.
* ```size_t``` gives the same type as ```unsigned long long```.
* A byte is 8 bits.
* ```2 + 2 / 2``` evaluates to ```3```.
* ```1 + 2 / 3``` evaluates to ```1```.
* ```cout >> "Hello world!"``` will print ```Hello world!``` to the console.
* Variable names can't start with number, e.g. ```int 3n = 0; ``` would be an invalid declaration.
* ```2 < 3 < 2``` evaluates to ```0``` (false).
* ```cin``` ignores spaces, tabs, and linebreaks.
* ```string``` is in namespace ```std```.
* Let  ```string s1 = "Hello"```; then ```s1[1]``` gives the first character in ```"Hello"```, which is ```'H'```.
* ```string``` is a class.
* You can declare a variable to ```const``` to protect it from unwanted changes. You should initialize the value upon declaration.
* An (lvalue) reference gives us another name for avariable.
* You can't change a variable through its reference. 
* An (lvalue) reference can only be created from an lvalue and not an rvalue.
* For the code snippet ```if (n = 1) { A }```, the procedure ```A``` will be executed if the variable ```n``` has value ```1```.
* In the paranthesis after ```for```, we should put in  initialization statement, condition to check for, and statement to perform, separated by comma ```,```.
* ```for (; 1==1; ;) {}``` forms an infinite loop.
* ```vector``` is in the namespace ```std```.
* The type of the variables to be stored in a vector must be the same.
* You can have a vector of vectors.


#### Short questions
* Sort the following in weakly increasing order: ```sizeof(short)```, ```sizeof(long long int)```, ```sizeof(int)```, ```sizeof(long int)```, ```sizeof(signed char)```
* Explain why floating point equality, e.g. ```8.1/6.3 == 9.0/7.0``` is a bad idea. **[Bonus]** give a good alternative for it.
* Briefly explain why initialization of variables is important, ~~other than that if you don't, you don't get perfect score on homework.~~
* Explain what is a "magic number".
* Explain what it means when a variable is "uninitialized".
* Explain why ```3/2``` doesn't evaluate to ```1.5```.
* What's the output of ```++n```? What about ```n++```?
* Given two ```string``` variables ```s1``` and ```s2```, what is ```s1 + s2```?
* What type should we use to store the size of a container (string, vector, etc.)?
* We have ```string s1 = "Midterm is stressful..."```; what is ```s1.substr(2,5)```?
* What's the difference between ```=``` and ```==```?
* Explains the difference between ```cin``` and ```getline```?
* Give an example when we need ```cin.ignore()```.
* What's the name of the header file that you need to adjust the precision of your number outputs? List one more function that it provides. 
* Describe what you should see on the console: ```cout << fixed << setprecision(3) << 314.15926535```. (Some rounding error could occur due to casting binary representations; you don't have to argue it for this problem)
* Explain what is a constructor of a class.
* What is the special character we used to access a class member?
* Suppose you were given a header file ```hello.h``` and you need it for your program; what should you add in your ```main.cpp```?
* Why shouldn't you use ```using namespace std;``` in your header file?
* How to compute 3^2.5? Do you need to include any header file for this?
* What's the (nuanceful) difference between ```int```, ```const int```, ```int&```, and ```const int&```?
* If ```n``` is an ```int``` variable, explain what does ```static_case<signed long long int>(n)``` give?
* ```!(!(1<=2) || !(0!=0))``` = ?
* Explain what does ```do { A } while ( B );``` does.
* Explain what is "masking"
* ```break```, ```continue```, and ```return``` is very different. Explain how. 
* Should you use paranthesis ```()``` or braket ```[]``` to access the value in a vector?
* What's the difference between the ```size``` and ```capacity``` of a vector?
* What does ```srand(time(nullptr)); ```? What are some header files needed for this line?
* Explain how you can implement a random integer (```int```) uniformly distributed between 1 and 5. What about a random real number (```double```)? **[Hint]** default upper bound for ```rand()``` is ```RAND_MAX```.
