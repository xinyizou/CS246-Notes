## `Lecture 13:` Const | Mutable | Static | Invariants and Encapsulation



### Const/ Mutable/ Static
**Const** method does not modify fields of objects on which the method was called <br>
`float grade() const {...}` promises not to change fields <br>
**Can only call methods that are cnost on const objects** <br>
<br>
Add a **mutable** field so can be modified by *grade()* <br>
<br>
**Static** member functions of a class are functions that do not require an instance of the class

-------------------------------------------------------------------------------



### Invariants and Encapsulation 
#### Invariants
```c++
struct Node {
  int data;
  Node *next;
  Node(int data, Node *next) : data{data}, next{next} {} // copy constructor 
  ...
  ~Node() { delete next; } 
};
 
int main() {
  Node n1{1, new Node{2, nullptr}}; // stack allocated
  Node n2{3, nullptr}; // stack allocated
  Node n3{4, &n2}; // stack allocated
  // dtors for n1, n2, n3 are automatically called
  //   dtor for n3 will call delete &n2 (which is a stack address)
 }
```
**Invariant:** assumption/statement that needs to be true for the class to function correctly <br>
  -> **Node Class Invariant:** `next` is either, a nullptr/ points to heap <br>
  -> **Stack Class Invariant:** Last thing pushed is first thing popped 
<pre>
<b>**NOTE**</b>
- When clients have access to the implementation of the class, it is hard to guarantee invariant
- It becomes difficult to reason about programs if we cannot guarantee class invariants
- <b>Solution:</b> Give clients no access to the implementation of the class (introducing <b>encapsulation</b>)
</pre> 

#### Encapsulation 
- Encapsulation = Data hiding (Treat objects as "black box") 
- Hide the implementation, allow clients to access through a provided interface
- **Keywords:** `private`, `public`
- `struct` default visibility is **public** 
- `class` default visibility is **private** 
```c++
// struct 
struct Vec {
  Vec(int x, int y) : ... // default visibility is public
private: // anything follows is hidden from the outside world
  int x;
  int y;
public: // anything follows is exposed to the outside world
  Vec operator+ (...) {...}
};

int main() {
   Vec v{1, 2}; // 2 parameter constructor is default public 
   Vec v1 = 1 + 1; // operator is public 
   cout << v.x << v.y << endl; // will not compile, fields x and y are private
}


// class 
class Vec {
  int x; 
  int y;
public:
  Vec(...) ...
  Vec operator+ (...) {...}
};
```
<b>\**At minimum all fields should be private!</b>

#### Example
Node Class Invariant
```c++ 
// Guaranteeing the Node Invariant, create a List wrapper class 
//   Node class is private & nested, code outside List cannot use the term Node

// List.h
class List {
  struct Node; // declared a private, nested class
  Node *theList = nullptr;
public:
  void addToFront(int n);
  int ith(int i);
  ~List();
};

// List.cc
Struct List::Node {
  int data;
  Node *next;
  Node(int data, Node *next): data{data}, next{next}{} 
  ~Node(){delete next;}
};

List::~List(){delete theList;}

void List::addToFront(int n) { 
  theList = new Node(n, theList); 
}

int List::ith(int i) {
  Node *curr = theList;
  for (int j=0; j<i && curr; ++j, curr=curr->next) {
    return curr->data;
  }
}
```
