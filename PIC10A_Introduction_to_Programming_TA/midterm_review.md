# Midterm Review

#### Study material: 

* Course notes [[Data Types & Classes]](https://ccle.ucla.edu/pluginfile.php/1812773/mod_resource/content/0/Topic_DataTypesAndClasses.pdf) [[Control Flow & Vectors]](https://ccle.ucla.edu/pluginfile.php/1812445/mod_resource/content/0/Topic_ControlFlowAndVectors.pdf)
* Practice midterm [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/05-09/05-09.html) [[Stephanie's]](this)
* Past discussion content [[Geoffrey's]](http://www.math.ucla.edu/~gsiyer/PIC10AS2017/main.html) [[Stephanie's]](https://github.com/evastgh/problems_and_solutions/tree/master/PIC10A_Introduction_to_Programming_TA)



## Practice Problems

#### True/False

* unsigned integer types can store the value ```0```.
* ```size_t``` is gives the same type as ```unsigned long long```.
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


#### Short questions
* Sort the following in weakly increasing order: ```sizeof(short)```, ```sizeof(long long int)```, ```sizeof(int)```, ```sizeof(long int)```, ```sizeof(signed char)```
* Explain why floating point equality, e.g. ```8.1/6.3 == 9.0/7.0``` is a bad idea. ~~**[Bonus]** give a good alternative for it.~~
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
* Describe what you should see on the console: ```cout << fixed << setprecision(3) << 314.15926535```
* Explain what is a constructor of a class.
