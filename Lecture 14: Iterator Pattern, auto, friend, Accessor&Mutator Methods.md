## `Lecture 14:` Iterator Pattern | auto, friend, Accessor&Mutator Methods 


### Designe Pattern 
1. Iterator Pattern
2. Observer Pattern
3. Decorator Pattern
4. Factory Mathod Pattern
5. Template Method Pattern
6. Visitor Pattern 

#### 1. Iterator Pattern
- Provide a way to access the elements of an aggregate(combined several) object sequentially <br>
  -> Without exposing its underlying representation
- Iterator is an abstraction of a pointer 

**Example**
- Create `class Iterator{}` that manages access to Node
- This class will act as an abstraction of a pointer to the linked list

**Inspiration** <br>
Iterating an array using pointers.
![PtoA](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/L14%20Pointer%20to%20Array.png)

<pre>
<b>**NOTE**</b>
Iterator class should support:
1. operator* (); // pointer to Node
2. operator++ (); // next Node
3. operator== ();
4. operator!= ();
5. begin();
6. end();
</pre>

```c++
class List{
  class Node;
  Node *thelist = nulptr;
public:
  class Iterator {
    Node *curr;
  pubilc:
    explicit Iterator(Node *curr) : curr{curr} {} // explicit keyword for constructor that has one and only one argument
    
    int& operator* () const{
      return curr->data;
    }
    
    Iterator& operator++ () { // p = p + 1 (see figure above) 
      curr = curr->next;
      return *this;
    }
    
    bool operator== (const Iterator& other) {
      return (curr == other.curr); // compare address of curr to the address of other's curr 
    }
    
    bool operator!= (const Iterator& other) { 
      return !(*this == other); // calls operator==
      // comparing '*this' (which is "this" Iterator class)
      //   with the value of 'other' (since '&other' is passed by & in this function, so 'other' is the value)
    }
  }; // end of Iterator class 
  
  Iterator begin() {
    return Iterator{theList};
  }
  
  Iterator end() {
    return Iterator{nullptr}; 
  }
 
  void addToFront(int n);
  int ith(int i);
  
  ~List();
}

int main() {
  List lst;
  for (int i=1; i<4; ++i) {
    lst.addToFront(i);
  }
  for(List::Iterator it=lst.begin(); it != lst.end(); ++it) {
    cout << *it << endl;
  }
}
```
-----------------------------------------------------------------------------------------


### Auto Type Detection
- C++ now has built-in support for the Iterator pattern in the form of *range-based for loops*
- Use the `auto` keyword
- `auto x = y;` x is defined to be the same type as y
 **e.g.**
 ```c++
vector<int> vec;
auto itr = vec.iterator(); // instead of vector<int>::iterator itr
```

<pre>
<b>**NOTE**</b> 
This can be used:
1. The calss implements <b>begin();</b> and <b>end();</b> which return iterator objects
2. Iterator class implements *, !=, ++
</pre> 

```c++
// before
  for(List::Iterator it=lst.begin(); it != lst.end(); ++it) {
    cout << *it << endl;
  }

// auto type detection 
for (auto n : lst) { // for the range of lst
  cout << n << endl; // pass by value, print each element
}

for (auto &n : lst) {
  ++n; // pass by reference, increment each element by 1 
}
```
-----------------------------------------------------------------------------------------

### Invariants and Encapsulation
#### Friend
1. The constructor for Iterator is public, clients can do: `auto it = Iterator{nullptr};`
   -> We do not want clients to create their own Iterators (due to [encapsulation](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/Lecture%2013:%20.md))
   -> We want them to use `begin();` and `end();` instead of a constructor
2. Let's make the constructor in Iterator *private*
   -> But `List::begin()` & `List::end()` uses the constructor
   -> Now, we are not able to call those either
      (Just because *Iterator* is a nested class in *List*, does not mean *List* gets special
       access to the *private* members of Iterator)
3. **Solution:** We can declare *list* as a friend 
```c++
class List{
  class Node;
  Node *thelist = nulptr;
public:
  class Iterator {
    Node *curr;
    explicit Iterator(Node *curr) : curr{curr} {} 
  pubilc:
    ...
    friend class List;
  }; // end of iterator class 
...
};
```
<pre>
<b>**NOTE**</b> 
Friendship breaks encapsulation, we want to make as few *friends* as possible
</pre> 

#### Accessor & Mutator Method 
*accessors(getters)* and *mutators(setters)* will allow flexibility in changing implementation,
but still guarantee invariants.
```c++
class Vec {
  int x;
  int y;
public:
  int getX() const { return x }; // accessors
  int getY() const { return y }; // accessors
  
  void setX(int v) { this->x = v; }; // mutators
  void setY(int v) { this->y = v; }; // mutators
}; 
```
Lets say we didnt have  `getX();` and `getY();` provided with `Vec::x` and `Vec::y` being *private*.
We can implement an output operator, and `friend` it.
```C++
class Vec {
  int x, y;
  ...
public:
  ...
  friend std::ostream& operator<< (std::ostream& out, const Vec& v);
};
```
