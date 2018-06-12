## `Lecture 6:` Filestream | Stringstream


### Filestream
To read and write to files use `#include <fstream>`
<pre>
1. <b>ifstream</b> - Read from a file (input stream)
2. <b>ofstream</b> - Write to a file (output stream)

<i>e.g.</i> [<b>Type</b>] [<b>Variable Name</b>]{<b>"Initialization</b>}

<b>**NOTE**</b>
- Anything you can do with <b>cin</b> you can do with a <b>ifstream</b> variable
- Treat <b>ofstream</b> like <b>cout</b>
</pre>

```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  ifstream f ("myfile.txt");
  string s;
  while(f >> s) {
    cout << s << endl;
  }
}
```
-------------------------------------------------------


### Stringstream
We can stream a string as a source of data, to read and write to string we use `#include <sstream>`
<pre>
1. <b>istringstream</b> - Read from a string (input stream)
2. <b>ostringstream</b> - Write to a string (output stream)
3. <b>str()</b> -  Returns the contents of its buffer in string type

<b>**NOTE**</b>
In C++ when you #include < iostream > you have already included the < string > type
But, it is still highly recommended that you <b>#include <string></b> especially when:
1. When using <b>string</b> type 
2. When using <i>cin</i> and <i>cout</i> for any <b>string</b> type variables（* You will also have to <b>#include <sstream></b>）
3. When using <i>memset()</i>, <i>strlen()</i>, <i>strcpy()</i> etc.
</pre>

### Examples
1. Checkout example: io/buildstring.cc 
```c++
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  int hi=100, lo=0;
  ostringstream os;
  os << "Enter a number between " << hi << " and " << lo << " ." << endl;
  string s=os.str(); // declare string "s" to be the input of "os"
  cout << s;
}

// you should see: "Enter a numebr between 100 and 0." as your output
```
------------------------------------------------------------


2. Insist user for input 
```c++
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  int num;
  while(true) {
    cout << "Enter a numebr:" << endl;
    string s; 
    cin >> s; // this only fails on EOF 
    istringstream userinput(s); // userinput is a local variable, which is why the code works
    if (userinput >> num) break;
    // give a if statement, if input to num fails you are stuck in this loop
    //   otherwise break out of the loop
  } 
}
```
-----------------------------------------------------


### Strings 
- In C, we used characer arrays with a *null terminator* to represent strings (Manage size of array manually)
- Recall: in C++, we can access to the "string" type by `#include <string>` (Size is automatically managed)

#### C vs C++
h | e | l | l | o | \0 
--- | --- | --- | --- | --- | ---           

`string s = "hello";` 

#### Strign Access In C++
|      | Symbol |
--- | --- 
**Equality** | s1 == s2 
**Comparisons** | !=, <, >, <=, >=
**Length** | s.length() 
**Access To Certain Char** | s[0], s[1] 
**Concatenation** | s3=s1+s2 / s1=s1+s2
-----------------------------------------------------------


### Default Arguments
- The compiler uses <b>defult value</b> if there is no parameter when calling a function (i.e. `printfile();`)
- But you can assign parameters to a function if you wish to. (i.e. `printfile("myotherfile.txt")`)
```C++
void printfile(string name="myfile.txt") {
   string s;
   ifream filestream(name);
   while (ifstrema >> s) {
    cout << s << endl;
   }
}
```

<b>\*\*Important**</b>
- If function does not have a **defult value**, you cannot follow a *"parameter with a defult value"*
- Parameter with defult value must occur last `void test(int num=0, string str); // not legal`
- If an argument is left blank, it must be the last one `test(,"thisisastring");// not legal`
```c++
// the following are allowed:

void test(int num=0, string str="bla");

// you can call the function by:
test();
test(5);
test(5, "thisisastring);
```
--------------------------------------------------------------


### Function Overloading 
- It is **LEGAL** to create functions with the <b>same name</b> as long as type or amount of parameters are different <br>
  (Compiler uses the <i>number or type of arguments</i> to decide which funcion is called) <br>
- It is not sufficient to differ only on return type 
```c++
// 1.
int neg(int a) { 
 return -a;
} 

// 2. 
int neg(bool a) {
 return a;
}
```

#### Did You Know 
- In `a= a >> b;`, `>>` acts as a *bit shift* <br>
- In `cin >> x`, `>>` is the *input operator* (This is due to **function overloading**: `operator >> (cin x);`)
-------------------------------------


### Structure
#### Structure in C
```c
struct Node {
  int data;
  struct Node *next;
};

struct Node n={5, NULL};
```

#### Now in C++
- You no longer have to keep using the word `struct` 
- `nullptr` is used instead of `NULL`


 
 
