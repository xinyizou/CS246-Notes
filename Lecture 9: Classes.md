## `Lecture 9:` Separate Compilation | Classes 


### [Separate Compilation](http://www.cppforschool.com/tutorial/separate-header-and-implementation-files.html)
Compiler tries to compile, link, produce executable.
1. Compile to object files: `g++14 -c vector.cc main.cc` 
2. Link object files: `g++14 vector.o main.o` (Linking the pieces together to procedure executable)
<pre>
<b>**IMPORTANT**</b> 
1. Never include a <b>.cc</b> file
2. Never compile a <b>.h</b> file 
</pre>
-------------------------------------------------------

### Global Variables 
#### [Extern](http://www.geeksforgeeks.org/understanding-extern-keyword-in-c/) 
Declare the existence of global variables in a header, so that each source file that includes the header knows about it.
```c++
// abc.h
extern int n; // declear it here

// abc.cc 
int n; // definition it here 

// you can decleared many times, but only defined once*****
```

#### Include Guard
`/preprocess/example3` does not compile, because `struct Vec` was defined twice <br>
Since we don't want to track `includeds` manually, we use <b>include guard</b> in the header file
```c++
// vector.h 
#ifndef VECTOR_H
#define VECTOR_H

struct Vec {
  ...
};

#endif
```
<pre>
<b>**NOTE**</b>
- Always add an include guard in all header files
- Do not use <b>using namespace std;</b> in a header file (instead use <i>e.g.</i> <b>std::string</b>)
</pre>  
-------------------------------------------------------------------------

### Class
A class is a `struct` that may contain functions.
(Members are *private* by default, will be discussed in later lectures)
```c++
struct Student {
  int assign, mt, final;
  float Grade() {
    return 0.4*assign + 0.2*mt + 0.4*final;
  }
// this is a class since it contains a function
//   only Student will use Grade()
```
#### Object
An instance of a class.

|     | Object? |
| --- | --- |
| `int x;` | No |
| `Vec* vpointer;` | No |
| `Node n;` | Yes |
| `cin` | Yes |
| `Student Billy;` | Yes |
| `string s;` | Yes |

#### Member Function/ Method
- A function defined inside a class
- Method has access to fields of the object which this method was called
- Method for a class can only be called using an object of that class
```c++
billy.grade(); // GOOD
grade(); // BAD 
```

#### [This Pointer](http://www.geeksforgeeks.org/this-pointer-in-c/)
- All methods have a hidden parameter called `this`
- `this` is a pointer to the object on which this method was called 
```c++
struct Student {
  int assign, mt, final;
  float Grade() {
    return this->assign*0.4;
    return this->mt*0.2;
    return this->final*0.3;
   }
}

Student Billy{70, 80, 90};
Bill.Grade();
// inside grade(), this=&Billy
// *this produces the object Billy
```
------------------------------------------------------------------


### Uniform Initilization 
Older version of C++ use `=` or `()` to initialize, these don't always work, so we create an uniform <br>
way of initializing all types of values.
```c++
// stack allocation
int x = 5;
string s = "hello";

int x(5);
string s("hello");
 
// now in the new version "{}" always work 
int x{5};
string s{"hello"};

Student Billy = Student{60, 70, 80}; // SAME
Student Billy = Student(60, 70, 80); // SAME 
Student Billy{60, 70, 80}; // SAME

// heap allocation 
Student *PBilly = new Student{60, 70, 80};
delete pBilly;
```
------------------------------------------------------------------


### Constrcutor
C++ uses **constructor** to construct objects.
```c++
struct Student {
  int assgin, mt, final;
  float Grade() { ... }
  Student(int assgn=0, int mt=0, int final=0) {
    this->assign = assign < 0 ? 0 : assign; // (condition) ? (if_true) : (if_false)
    this->mt = mt < 0 ? 0 : mt;
    this->final < 0 ? 0 : final;
  }
}

Student Billy {60, 70}; // final = 0
Student Billy {60}; // mt and final = 0 
Student Billy {}; = Student Billy // all three = 0
```
