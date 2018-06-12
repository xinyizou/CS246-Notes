## `Lecture 17:` Templates(STL) | Exceptions


### Templates
```c++
// you can only make an int stack with this
class Stack { 
  int size;
  int cap;
  int *contents; // heap allocated array
public:
  Stack() { ... };
  void push(int x) { ... };
  int top() { ... };
  void pop() { ... };
};
```
How can we one template for multiple types without retyping everything? <br>
-> **Template Class:** a calss that is parameterized on one or more types 
```c++
template <typename T> // T is a placeholder for type
class Stack {
  int size;
  int cap;
  T *contents; // each element of array is of type T
public:
  void push(T x) { ... };
  T top() { ... };
  void pop() { ... };
}; // this closes the template, no other brackets needed 
```
#### Example
1. Calling template
```c++
// 1.
Stack<int> variableName; 
variableName.push(10); 

//2. 
Stack<Expression *> myStack;
myStack.push(new loneInt(5)); 
```
2. Template of the Iterator class
```C++
class List {
  struct Node;
  int data;
  Node *next;
};

template <typename T> // you always write it right before the class
class List {
  Struct Node{
    T data;
    Node *next;
  };
  
  Node *theList = nullptr;
  
public:
  class Iterator {
    Node *curr;
    explicit iterator(...){...} // list cant access unless it's a friend 
  public:
    T& operator*() {...}
    ...
    friend class List<T>;
  }; // end of Iterator class 
  
  void addToFront(const T& t) { ... } // we do not know the type, take const &
  T ith(int i) {...}
};
  
int main() {  
  List<int> l1;
  l1.addToFront(10);
  
  List<List<int>> l2; // List where each element is a List, and each element of that is an int 
  l2.addToFront(l1);
}
```
-----------------------------------------------------------------------------------------------------------------


### Standard Template Library (STL)
There are many templates in the STL.

#### [Vector Template Class](https://www.scss.tcd.ie/Martin.Emms/NLP/C++_notes/node87.html)
- **Vector:** Dynamic length array  
- Amongst the standard C++ library classes, there is a class called `vector`
- Implement internally using a heap allocated array 
- Dynamically increase capacity as needed 

1. Create a `vector`
```c++
#include <vector>
using namespace std; 

vector<int> vecs{3, 4}; // [3,4]
vecs.emplaces_back(5); // adds elements to the end [3, 4, 5]
vecs.emplaces_back(6); // [3, 4, 5, 6]

// ***** NOTE *****
vector<int> vecs(3,4); // {} and () are different 
// this means 3 elements in the vector with value 4
```

2. How to loop through vectors?
```c++
// 1.
for (int i=0; i<vecs.size(); i++){
  cout << vecs[i] << endl;
}

// 2.
for (vector<int>::iterator it=vecs.begin(); it != vecs.endl(); ++it){
  cout << *it << endl;
}

for (auto i : v) {
  cout << i << endl;
}

// 3. Reverse Iterator
for (vector<int>::reverse_iterator it=vecs.rbegin(); it != vecs.rend(); ++it){ // vector<int>::reverse_iterator can be reaplaced by auto
}
// vecs.rbegin(); access the laste element of vector
```

3. Other `vector` operations
```C++
vecs.pop_back(); // removes/ pops last element

auto it = vecs.erase(vecs.begin()); // remove 1st
auto it = vecs.erase(vecs.end() - 1); // remove second last
// once you erase these, they become invalid

rebegin(); // returns reverse iterator

vec.at(i); // returns a reference to the element at #
vec[i]; // similar to vec.at() but does not check if position is out of range
```
-------------------------------------------------------------------------------------------


### Exceptions
`#include <stdexcept>`
- When an error situation occurs the program can decide to raise or throw an exception
- When exception occurs, program terminates, we solve by **catching the exception**
- When an exception occurs, program begins to pop stack frames trying to find an appropriate **catch block**



