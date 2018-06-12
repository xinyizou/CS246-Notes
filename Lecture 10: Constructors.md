## `Lecture 10:` Constructors 


**Every class comes with:**
1. Default constructor 
2. Copy constructor 
3. Destructor
4. Copy Assignment Operator
5. Move constructor 
6. Move assignment operator 
------------------------------------------------------------------------


### 1. Default Constructor
- Every class comes with a **default constructor** (0 parameter) 
- The class calls default ctor on any fields that are objects
- Default ctor goes away as soon as you implement any ctor 

#### Examples 
1. Call default ctor 
```c++
struct A {
  int x; // not an object 
  Student y; // call default ctor 
  Vec *v; // not an object 
}

A myA; // an object named myA, calls the default ctor 
```
2. Implement default ctor
```c++
struct Vec {
  int x, y;
  Vec (int x, int y) {
    this->x = x;
    this->y = y;
}

Vec v; // want to compile default ctor, but it's no longer there
```
-------------------------------------------------------------------------------------


#### [Member Initialization List](https://stackoverflow.com/questions/926752/why-should-i-prefer-to-use-member-initialization-list)
Fields that are <b>constants</b> or <b>references</b> must be initialized. <br> 
<pre>
<b>**NOTE**</b>
If your class stores <b>references to objects</b> or <b>const variables</b> then you don't have but to use MIL!
</pre>
```c++
// i.e.
struct myStruct  {
  const int x=5;
  int& z=y;
}
```

**You cannot initialize constants ot references in the ctor body. <br>
These fields must be fully constructed by the time ctor body executes.
Thus, we have Member Initialization List :)**

<pre>
<b>3 Steps To Object Creation</b>
1. Speace is allocated (stack/heap)
2. Fields are default constructed
3. Ctor body runs 
</pre>

Lets hijack step2 using **Member Initialization List (MIL)**
```c++
struct Student {
  const int id;
  int assign, mt, final;
  Student (int id, int assign, int mt, int final) : 
  id{id}, assign{assign}, mt{mt}, final{final} {}
}

// lhs "id" is the field (this->id)
// rhs {id} is the value 
``` 

<pre>
<b>**NOTE**</b>
- MIL can be used to initialize all fields 
- The "thing" outside {} must be a field 
- Fields are initialized in class declearation order 
- MIL can be more efficient ctor body
- MIL has priority over in-class initialization
</pre>
```c++
// e.g.
struct Vec {
  int x = 5;
  int y = id;
  Vec (int x, int y): x{x}, y{y} {} // priority over in-class initialization
}
```
------------------------------------------------------------------------------------------


### 2. Copy Constructor 
 - When you think of pass-by-value you think that a new object is created using the **copy constructor**
 - A copy ctor constructs(create) an object as a copy of an existing object
 - You get a copy ctor for free (which does a field for field copy)
 - [Why is call by reference used in a copy constructor?](https://www.quora.com/Why-is-call-by-reference-used-in-a-copy-constructor)
```c++
// free copy ctor
struct Student {
  int assign, mt, final;
  Student (const Student& other) : 
  assign{other.assign}, mt{other.mt}, field{other.field} {} 
};

Student Billy{60, 70, 80};
Student Bobby = Billy; // call the copy constructor 
Student Bobby = {billy}; // SAME 
```

The free copy ctor just copies the address, sometimes that is not what we want. 
```c++
struct Node{
  int data;
  Node* next;
  Node (int data, Node* next) : data{data}, next{next} {} // default ctor
  Node (const Node& other) : data{other.data}, next{other.next} {} // free copy ctor
}
```

What if there is a linked list?
```c++
Node* np = new {1, new Node{2, new Node{3, nullptr{}};

Node n{*np}; // call copy ctor (stack)
Node* m = new Node{*np}; // call copy ctor (heap)
```
![Linked-list](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/L10%20Linked%20List.png)


#### Deep Copy Constructor
If we don't want nodes to be shared, we cannot use the free copy ctor. <br>
We implement our own. <br>
(Typically when a class has a pointer to heap allocated memory, we need to write our own copy constructor)
```c++
struct Node {
  Node(const Node& other) {
    data = other.data;
    next = new Node {*other.next}; // set next to a copy of other's next
    // this crashes if next is NULL
  }
}
```
```c++ 
// we do a check
struct Node {
  Node(const Node& other) {
    data = other.data;
    if (other.next) 
      next = new Node{*other.next};
    else 
      next = nullptr;
  }
}

// a simpler way 
struct Node {
  Node(const Node& other) :
    data{other.data},
    next{other.next ? new Node{*other.next} : nullptr} {}
}
```
<pre>
<b>When is a copy constructor called?</b>
1. Constructing an object as a copy of another 
2. Pass by value 
3. Returns by value 

<b>** Parameter of copy constructot cannot be passed by value**</b> 
</pre> 
------------------------------------------------------------------------------------------


### [Implicit Conversion](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)
One parameter constructor create implicit conversions.
```c++
struct Node {
  ...
  Node (int data) : data{data}, next{nullptr} {} 
}

Node n = 4; // LEGAL

void foo(Node n) {...}; 
foo(4); // LEGAL, knowing that Node takes an int, convert foo(4) to foo(Node(4))
```
Disable the auto conversion with keyword `explicit`.
```c++
struct Node {
  ...
  explicit Node (int data) : data{data}, next{nullptr} {} 
}

Node n = 4; // LEGAL

void foo(Node n) {...};
foo(4); // ILLEGAL, foo is expecting a Node, but passed in an int
```   
<pre>
<b>**NOTE**</b>
- Use it when the constructor has one and only one argument
- Use it only on the default, copy, and move constructor
</pre>
