## `Lecture 7:` Pass-by-Reference | Dynamic Memory | Dangling Pointer

### Reference 
- C++ has another pointer-like type, called **reference**
- **Reference** acts as a constant pointers with *automatic dereferencing*
<pre>
<b>**THINGS YOU CANNOT DO WITH REFERENCES**</b>
1. Cannot leave references uninitialized (<i>e.g.</i> int& z; // this will not compile)
2. Must initialize a reference to a l-value (<i>e.g.</i> int& z=5; // this is saying some #=5, ILLEGAL)
3. Pointer-to-Reference (ILLEGAL) 
4. Reference-to-Pointer (OK)
5. Reference-to-Reference (ILLEGAL)
6. An array of refernces (ILLEGAL)
</pre>

#### Pointer-to-Reference
- [**ILLEGAL.**](https://stackoverflow.com/questions/1898524/difference-between-pointer-to-a-reference-and-reference-to-a-pointer)
- [Pointer  V.S Reference](https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in)

#### Reference-to-Pointer
```c++
voic fun(int*& ptr_to_ref) {
  ptr_to_ref=0; // set the "passed" pointer to 0
  // if pointer is not passed by reference,
  //   then only the copy you receive of "ptr_to_ref" is set to 0
  //     original pointer (outsideof function) is not affected
};
```

#### Pass-by-Value | Pass-by-Pointer | Pass-by-Reference
```c++
// pass by value 
// the function get s copy
void fun(int n) {
  n=n+1;
} 

int x=5;
fun(x);
cout << x <<endl; // prints 5
```
```c++
// pass by pointer 
void fun(int* n) {
  *n=*n+1;
} 
int x=5;
fun(&x); 
cout << x << endl; // prints 6 
```
```c++
// pass by reference
void fun(int& n) {
  n=n+1;
} 

int x=5;
fun(x);
cout << x <<endl; // prints 6 
```
```c++
// 'cin' is also pass by reference 
cin >> x;
istream& operator>> (istream& in, int& n){...}
operator>> (cin, x); // 'cin >> x;' is syntactic sugar for this 

// why is the first argument passed by refence? 
//   -> argument is a stream, streams cannot be copied 
//   -> pass-by-value will copy the stream, which is ILLEGAL
//   -> if read fails, we want to clear the fail bits of the actual 'cin', not its copy

// why does 'operator>>' return an 'istream'?
//   -> return by reference, since return by values would require a copy
```


#### Pass-by-Value V.S Pass-by-Reference
```c++
struct ReallybBig{...};
void fun(ReallyBig rb){...};
ReallyBig db = ...;
fun(db); // passed by value, a copy must be made-> expensive, since structures have big values

// to avoid making copies, create a pointer 
// pass-by-pointer and pass-by-reference have identical functionalities
// C/C++:
void fun(ReallyBig* rb){...};
ReallyBig db = ...;
fun(&db);

// C++:
void fun(ReallyBig& rb){...};
ReallyBig db = ...;
fun(db);
```


#### l-value 
- Interpret 'l' as "location" (address)
- Refers to a **storage location** (anything with an address)
- Local variables are l-values 
<pre>
<b>**NOTE**</b>
- In the following example, z is a l-value reference to y
  -> z is an alias for y
  -> z acts like y
  -> size of z = size of y
</pre>
```c++
int y=10;

int& z=y; // z is a l-value reference to y, z is a reference to y forever
z=15; // updates the value of y to 15
int* p=&z; // take the address of y, p now point to y
```


#### r-value 
- Interpret 'r' as "raed", read data
- Refers to **computed values/ temporaies** (anything not a l-value)
```c++
int y=10;

int& z=y; // from the l-value example
int& z=5; // ILLEGAL, if we call 'z=15;', this is saying 5=15
int& z=x+y; // ILLEGAL
```


<pre>
<b>**ADVICE**</b>
Always pass-by-reference to a <b>const</b> unless there's a reason not to.
We use <b>const</b> to prevent changes to the original value.
</pre>

```c++
void f(int& x) {...};
void g(const int& x) {...};

f(5); // ILLEGAL, 5 is not a l-value
f(x+y); // ILLEGAL, x+y is not a l-value

g(5); // LEGAL, pass-by-reference to const-> values are never going to change
g(x+y); // LEGAL, pass-by-reference to const can assign non-l-value to reference
```
-----------------------------------------------------------------------------------


### Dynamic/ Heap Allocation 
- In C, we manually allocate memory and return it back to the heap after use
- In C++, we use `new` and `delete` key words 
- `new` is **type aware**, it'll give you the exact memory you need for a Node (example below)
```c++
strcut Node {
  int data;
  Node *next;
};

Node *np = new Node; // 'new is type aware
// np is on the stack***** and points to memory in the heap

delete np; // to free the memory borrowed from 'new' 
```

```c++
// for accessing arrays
Node *np = new Node[10]; // must use '[]' or you will have memory-leak
delete[] np;
```

#### Dangling Pointer
Pointer that points to invalid data or data not valid anymore. <br>
For more information checkout [GeeksforGeeks](http://www.geeksforgeeks.org/dangling-void-null-wild-pointers/).
<pre>
<b>**IMPORTANT**</b>
Never return a pointer or reference to stack allocated data 
</pre>
```c++
Node *getANode() {
  Node n; 
  // n is a local variable that goes out of scope
  //   after an execution of *getANode() is over
  return &n; // address is gone
}
```
