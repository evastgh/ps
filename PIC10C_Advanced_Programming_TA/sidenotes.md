
## Smart Pointers
In lecture I mentioned smart pointers, especially unique_ptr<T>, can be used to implement ownership of data with the convenicne to initialize the member after initialization.

```cpp
class SomeData;

class Foo {
    SomeData data;
    Foo() {
        data( /*might be nontrivial, or using some parameters you can yet to provide*/ ); // have to initialize data here
    }
};

class FooAlternative {
    std::unique_ptr<SomeData> data_ptr;
    Foo () {
        // no need to initialize data_ptr
    }
};
```

So it seems FooAlternative is almost equivalent to Foo except better, right? However, you notice the following code compiles 

```cpp
SomeData& FooAlternative::getData() const {
    return *(data_ptr.get());
}
```

FooAlternative::getData was declared const, however it returns a reference to the actual data on the heap without a quantifier! As explained [here](https://stackoverflow.com/questions/16425345/how-to-pass-const-pointer-to-const-object-using-unique-ptr), the const quantifer only protests the content of unique_ptr but it does not protect the content which the unique_ptr points to. 

## Virtual Function Table
I spent entire two days this week to debug some issue in my own research project. It turned out the bug was coming from someone else made the following changes in the shared repository
```cpp
class SharedBaseClass {
    virtual void doSomething(const std::string& s) {}
    // virtual void doSomething(std::string& s) {}
};
```
In the other corner of the repository, my derived class remained unchanged
```cpp
class MyDerivedClass : SharedBaseClass {
    void doSomething(std::string& s) {
        // something important
    }
}
```
As you can see, since the signature of the virtual function in ```SharedBaseClass``` changed, my derived function no longer overrides it, and hence when I'm calling doSomething through a ```SharedBaseClass``` pointer, nothing gets excuted. A good practice of programming would include using the keyword ```override``` here to prevent the same tragedy
```cpp
class MyDerivedClass : SharedBaseClass {
    void doSomething(std::string& s) override {
        // something important
    }
}
```
This way when the signature in ```SharedBaseClass``` changes, the compiler would detect this derived ```doSomething``` doesn't properly override anything and throw an error message. I hope you all don't make the same mistake as I did. :p
