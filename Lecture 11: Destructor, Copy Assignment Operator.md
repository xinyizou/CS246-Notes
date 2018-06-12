## `Lecture 11:` Destructor | Copy Assignment Operator 


### Destructor
- Destroying an object call the dtor
- Stack allocated objects are destoryed automatically when they go out of scope
- Heap allocated objects are destoryed when we call `delete` on a pointer to that object
- Each class can only have one dtor
- Dtor of a class is `~ClassName()`
- Each class comes with a default dtor 
<pre>
<b>Events when an object is destroyed</b>
  1. Dtor body runs
  2. Fields that are objects are destoryed in reverse declaration order
  3. Memory is reclaimed
</pre>
```c++
Node *np = new Node{1, new Node{2, new Node{3 nullptr}}; // if we do not delete this, 3 nodes leak 
delete np; // but this only destorys 'Node 1', Node 2 and 3 stil leak 
```  
We write our own destructor.
```c++
struct Node{ 
  ...
  ~Node(){
    delete next; // this recursively destorys the linked list
  }
}
```
---------------------------------------------------------------------------------------------------------

### Copy Assignment Operator (operator=)
```c++
// assignment associate to the right
a = b = c = 0; // going from right to left
```
**n1.operator= (n2.operator= (n3))**

```c++
student Billy {60, 70, 80};
Student Bobby = Billy; // copy ctor
Student Jane; 
Jean = Billy; // copy assignment operator (copy as-o)
```
You get a free copy assignment operator, but this does a shallow copy.
So, we write our own

<pre>
<b>**RECALL**</b>
[condition] ? [if_true] : [if_false]

<b>**NOTE**</b>
NULL evaluates to false.
Since C++ considers any non-zero value true and any zero value false.
NULL is essentially the zero address.
</pre>

1. First try
```c++
struct Node{
  ...
  Node& operator= (const Node& other) {
    data = other.data;
    delete next;
    next = other.next ? new Node{*other.next} : nullptr;
    return *this;
  }
}
// what if lhs=rhs?
// self-assignment will lead to accessing dangling pointer (since we deleted next)
```

2. Second try
```c++
struct Node{
  ...
  Node &operator= (const Node& other) {
    if (this == &other) return *this; // self-assignment check
    data = other.data;
    delete next;
    next = other.next ? new Node{*other.next} : nullptr; // new will fail if there is no memory left 
    return *this;
  }
}
// if new fails, method stops executing
// next is not assigned, resulting a dangling pointer
```

3. The Copy Assignment Operator
```c++
Node &operator= (const Node& other) {
  if (this == &other) return *this;
  Node* tmp = next;
  next = other.next ? new Node{*other.next} : nullptr;
  delete tmp;
  data = other.data;
  return *this;
}
```

4. We can also implementing `operator=` using **Copy&Swap Idiom**
```c++
#include <utility> 

struct Node{
  void swap(Node& other) { // implementing your own swap function 
    using std::swap;
    swap(data, other.data);
    swap(next, other.next);
  } // swap handles self-assignment properly 
  
  Node &operator= (const Node& other) { 
    Node tmp = other; // calls the deep copy ctor
    swap(tmp); // swap "this" with tmp (your implementation)
    return *this;
  } // tmp automatically deallocates 
}
// once swap returns, "this" contains the calue of "other"
// the old data in tmp is destoryed automatically because temp is stack allocated
```











