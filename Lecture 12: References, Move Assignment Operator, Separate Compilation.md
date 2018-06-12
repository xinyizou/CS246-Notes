## `Lecture 12:` References | Move Assignment Operator | Separate Compilation 



### Methods v.s Standelone  
From previous, `Operator=` must be implemented as a **method** 

#### Example
1. The **left hand operant** takes the value of "this"
```c
Vec Operator*(const int k); // this is a method, calls on "this"
Vec Operator*(const int  k, const Vec& other); // this is a standelone function
```

2. Add two vectors
```c++
struct Vec{
  int x, y;
  Vec Operator+(const Vec& v){
    return{x+v.x, y+v.y};
  }
}

// calling 
v1 + v2; // this is v1.Operator+(v2)
```

<pre>
<b>**NOTE**</b>
1. Operator Overloading
  - e.g. Operator= must be implement as a method
  - LHS represented by "this*"
2. Implementie +, /, * for Vec as methods 
</pre> 

Can we implement the I/O Operators as methods? **You need to implement the I/O Operators outside of the class!**
##### Consider lhs operant being replaced with "this" 
```c++
struct Vec{
  Ostram& operator<<(Ostream& out){
  return out;
  }
}

// calling
<< cout; //  this is v.Operator<<(cout); 

// this is not a good idea
// thus, implement I/O operators as functions
```

#### Summary
The following operators must be implementd as methods:
1. Operator=; // since the free assignment operator= is a method, thus when you implement it must be a method
2. Operator[]; 
3. Operator();
4. Operator->; // obejct as pointer
5. OperatorT(); // where T is a type
----------------------------------------------------------------------------------------------------------



### r-value References (&&) 
A r-value references that is referencing a r-value. 
**Recall:** [r-value](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/Lecture%207:%20Reference%2C%20Dynamic%20%20Memory.md)
```c++
int a = 5; // "a" is a l-value 
int& b = a; // "b" is a l-value reference (a reference to a l-value) 
int&& c; // "c" is a r-value reference
```
```c++
// function overloading 
void funRef(int& r) { ... } // func1
void funRef(int&& r) { ... } // func2

int main() {
  int a = 5;
  funRef(a); // call func1 
  funRef(6); // call func2, because 6 is a r-value 
}
```
What is purpose of r-value reference?
```C++
Node plusOne(Node n) {
  return n;
}

Node n{1, new node{2, nullptr}};
Node n2{plusOne(n)}; // plusOne(n) will return an r-value, which is a temp that will be destoryed 
// there is no point in making a copy of the tmp and passing it around
```
----------------------------------------------------------------------------------------------------------


###  [Move Constructor](https://www.youtube.com/watch?v=IOkgBrXCtfo) (Steal)
- Purpose of move constructor is to avoid costly and unnecessary deep copying.
- Move constructor is particularly powerful where pass-by-reference and pass-by-value are both needed
- Move constructor give you finer control of which part of your object is to be moved
- [When Does Move Constructor get called?](https://stackoverflow.com/questions/13125632/when-does-move-constructor-get-called)
**Example**
1. 
```c++ 
int main() {
  Node n {1, new Node {2, nullptr}}; // 2 constructors called

  Node n2 {plusOne(n)}; //

  cout << n << endl << n2 << endl;
}
```

**Move Constructor**
```c++
struct Node{
  Node(Node&& other) : data{other.data}, next{other.next} {
    other.next = nullptr;
  }
}

Node m;
m = pulsOne(m);
```
![move ctor](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/L12%20Move%20Constructor.jpg) 
**Source**: http://avidinsight.uk/2013/05/understanding-cpp11-move-semantics/


----------------------------------------------------------------------------------------------------------


### Move Assignment Operator
```c++
struct Node{
  Node& operator= (Node&& other) {
     swap (other); 
     // swap (other); swaps the first value of "this" object with the first value of "other" 
     //    then "this" points to the rest of "other" (linked list) and "other" takes the rest of "this"
     return *this;
  }
}
```
----------------------------------------------------------------------------------------------------------



### Copy Move Elision
<pre>
<b>**NOTE**</b>
Checkout in-class examples
<b>node.cc</b> requires 4 copy ctors 
<b>nodemove.cc</b> requires 2 copy ctors + 1 move ctor
</pre>

```c++
Vec makeAVec() {
  return {2, 3};
}

Vec v = makeAVec();
```
- We would expect either a **copy ctor** or **move ctor** to be called 
- Compilers are allowed (though not required) to omit calls to **copy ctor** or **move ctor** under certain circumstances <br>
  (To turn off optimization execute: `g++14 -fno-elide-construction [fileName]`)
----------------------------------------------------------------------------------------------------------



### Rule of 5

If you need to implement a custom varsion of the **Big Five**, then you should implement all of them![Example](https://blog.feabhas.com/2015/01/the-rule-of-the-big-four-and-a-half-move-semantics-and-resource-management/)

----------------------------------------------------------------------------------------------------------



### Arrays of Objects 
```c++
struct vec {
  int x,y;
  Vec(int x, int y) : x{x}, y{y} {}
}

Vec veca[3]; // stack allocated array of vec objects 
Vec *vecb = new vec[3]; // heap allocated array of vec objects 
```
<pre>
<b>**NOTE**</b>
The above code will not compile, since creating an array of objects require <b>default construction</b>
of each object in the array, but <b>default ctor</b> goes away as soon as we implement our own!
</pre>

#### Fix 
1. Provide default (0 parameter) ctor
2. Stack allocated arrays of objects, use array initialization `Vec vec1[3] = {vec{0,0}, vec{1,2}, vec{3,4}}`
3. For stack/heap arrays, create array of pointers instead of objects
```c++
// stack 
Vec *vec3[10]; // stack allocat array of vec pointers 
   
// heap 
Vec *vec4[0] = new Vec*[10];
vec4[0] = new vec{2, 3}; // heap allocated array containing heap allocated vecs
   
for(int i=0, i<vec.size(), ++i) {
  delete vec4[i];
}

delete[] vec4;
```
----------------------------------------------------------------------------------------------------------



### Separate Compilation 
- Method **declaration** go in the header(.h) file
- Method **definition** goes in the (.cc) file 

#### Headr(.h) File
```c++
Node.h

#ifndf NODE_H
#define NODE_H

struct node {
  int data;
  Node *next;
 
  Node(int data, node *next);
  int getData();
};

#endif
```

#### Implementation(.cc) File 
```c++
Node.cc

#include "node.h"

Node::Node(int data, node *next) : data{data}, next{next} {}; // "Node::" scope implementor
int Node::getData() {
  return data;
}
```   
<pre>
<b>**NOTE**</b>
<b>"::"</b> is the scope resolution operator 
<b>"Node::"</b> means in the scope of class <b>Node</b>
</pre>
