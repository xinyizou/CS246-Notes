## `Lecture 8:` Operator Overloading | Separate Compilation


### Operator Overloading 
In C++ we can give additional meaning to operators.
Some reference on [Operator Overloading](http://www.eecs.umich.edu/courses/eecs2807/generalFAQ/Operator_Overloading.html).
<pre>
<b>**IMPORTANT**</b>
Previously we have discussed about <b>Function Overloading</b>, this is not the same as <b>Operator Overloading</b>

<b>Function Overloading</b>
- Several functions of <i>same name</i> defined with different types/ number of parameters
- Appropriate function identified by the compiler by examining the types/ number of parameters 
- Helps to reduces investment of different function names

<b>Operator Overloading</b>
- Redefinition of operators
- Operates on user defined objects
</pre>

#### Example
```c++
struct Vec{
  int x;
  int y;
};

// operator overloading 
Vec operator+ (const Vec& v1, const Vec& v2) {
  Vec v{v1.x+v2.x, v1.y+v2.y};
  return v;
};
 
Vec v1{1, 2};
Vec v2{3, 4};
Vec v3 = v1 + v2; // calls operator+
``` 

#### LHS and RHS operands
<pre>
<b>**IMPORTANT**</b>
Since operator is in the middle (e.g. lhs + rhs), the operator overloading function takes its
parameters as the left-hand-side object and the right-hand-side object
</pre> 
```c++
// 1.
Vec operator* (const int n, const Vec& v) {
  return {n*v.x, n*v.y}; // compiler is smart enough to make a vector 
};
Vec v4 = 5 * v3;

// 2.
// if we want to write 'Vec v4 = v3 * 5;' 
//   we also have to define 'operator* (const Vec& v, const int n)'
//     order of argument types is different*****
Vec operator* (const Vec& v, const int n) {
  return n*v; // calls the above 'operator*'
};
Vec v4 = v3 * 5;
```

#### Overloading Stream Insertion (<< , >>) operators
- The first parameter has to be a **reference-type**, and not set to `const` so we can clear possible *fail bits* 
- `operator<<` function cannot be a member of your own class, since left-hand operand is an *ostream* object <br>
   **i.e.** `operator<< (ostream& out, const Student& s)`
- The return type has to be a reference to an iostream object <br>
  **e.g.**`istream& operator>> ( ... )`
- You cannot make copies of streams ([Why is copying ANY stream in C++ not allowed?](https://stackoverflow.com/questions/6010864/why-copying-stringstream-is-not-allowed))
- For more information on checkout [GeeksforGeeks](http://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/)
```c++
struct Student{
  int grade;
};
 
// operator overloading (output stream <<)
ostream& operator<< (ostream& out, const Student& s) {
  out << "Your grade is " << s.grade << " %";
  return out;
}

// operator overloading (input stream >>)
istream& operator>> (istream& in, const Student& s) {
  in >> s.grade;
  if(s.grade > 100) { s.grade = 100; }
  if(s.grade < 0) { s.grade = 0; }
  return in;
}
```
<pre>
<b>**ADDITION**</b>
Some operators return by value, some by reference. 
<i>In general:</i>
- An operator whose result is a new value (such as +, -, etc) must return the new value by value.
- An operator whose result is an existing value, but modified (such as <<, >>, +=, -=, etc), should 
  return a reference to the modified value
</pre>
-----------------------------------------------------------------------------------------------


### [Preprocessor](http://www.cprogramming.com/reference/preprocessor/)
- Preprocessor is executed before compilation. The result is a single file which is then passed to the actual compiler.
- Copy&paste the file and removes the line (**e.g.** `#include "file.h"`)
- Allowing: <br>
  -> **Conditional Compilation** with `#ifdef` <br>
  -> **Defining Constants** with `#define` <br>
  -> **Including Header-Files** with `#include` <br>
  -> **Using Builtin Macros** such as `__FILE__` <br>

#### [Defining Constant](http://www.cprogramming.com/reference/preprocessor/define.html)
`#define token [value]`

#### [Conditional Compilation](http://www.cprogramming.com/reference/preprocessor/ifdef.html)
#### 1. "#ifdef"
Checks whether the given token has been #defined earlier in the file or in an included file
- `#ifdef <token>` True if token is defined
- `#ifndef <token>` True if token is not defined
```c++
#ifdef <token> 
/* code */
#else
/* code to include if the token is not defined */
#endif
```

#### 2. "#if"
```c++
#if <value>
/* code to execute if this value is true */
#elif <value>
/* code to execute if this value is true */
#else
/* code to execut otherwise */
#endif
```

#### 3. To see the preprocessor output
```
g++14 -E -P <fileName.cc>
```
-----------------------------------------------------------------------------------------------


### [Separate Compilation](http://www.cppforschool.com/tutorial/separate-header-and-implementation-files.html)
C++ classes are split up into two files: 
- The **header file** with extension `.h`, contains class definitions and functions 
- **Implementations** of classes goes into the `.cc` file
  
For more information see file `CS246-University-of-Waterloo/Separate Compilation.pdf` <br>
**Source:** http://www.math.uaa.alaska.edu/~afkjm/csce211/handouts/SeparateCompilation.pdf





