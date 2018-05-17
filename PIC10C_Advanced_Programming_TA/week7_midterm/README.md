## Copy Elision
http://en.cppreference.com/w/cpp/language/copy_elision
https://en.wikipedia.org/wiki/Copy_elision
```cpp
class Algo {
    Algo () { std::cout << "Algo defultly constructed." << endl; }
    Algo (const Algo&) { std::cout << "Algo copied." << endl; }
};

int main () {
    Algo a = Algo();
}
```
Due to copy elision, no copying nor moving is called in this following line
```cpp
Algo a = Algo();
``` 
and it's equivalent to 
```cpp 
Algo a();
```

## Keyword ```explicit```
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/explicit_keyword.htm
```cpp
class Algo {
    Algo () { std::cout << "Algo defultly constructed." << endl; }
    explicit Algo (const Algo&) { std::cout << "Algo copied." << endl; }
};

int main () {
    Algo a = Algo();
}


## Pointer class member

```cpp
class Gigantic {
    Gigantic(const Data& data) { //... }
};

class Program {
    Gigantic gigantic;

    Program() : gigantic(data) {}
};
```
