## `Lecture 5:` I/O in C++


### #include \<iostream\>
When we **#include \<iostream\>** we are importing 3 *stream* variables:
<pre>
1. <b>cout</b> - Write to <i>stdout</i> (ostream type)
2. <b>cerr</b> - Write to <i>stderr</i> (ostream type)
3. <b>cin</b> - Read from <i>stdin</i> (istream type)
</pre>


### I/O operators
<pre>
1. <b><<</b> - Output Operator (Use with ostream)
2. <b>>></b> - Input Operator (Use with istream)
</pre>
------------------------------------------------------------


### Examples
1. Read and add two integers.
```c++
#include <iostream>
using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  cout << x+y << endl;
}
```
------------------------------------------------------------


2. Read all intergers from stdin and echo them to stdout, stop when a **read fails**. 

#### Read-fail / EOF
- <b>cin</b> will ignore <i>whitespace</i> <br>
  -> Start reading at <i>first</i> none-whitespace character <br>
  -> Stop until a whitespace is hit 
- A read <i>fails</i>: <br>
  -> Due to incorrect type or <i>EOF</i> <br>
  -> Program still continue <br>
  -> All reads after will fail <br>
  -> Read-fail: <b>cin.fail()</b> is true <br>
  -> Read-fail due to <i>EOF</i>: <b>cin.fail()</b> and <b>cin.eof()</b> are true <br> 
- `cin` can be treated as a **boolean** (implicit conversion) <br>
  <i>i.e.</i> <b>cin</b> is <i>true</i> if <b>cin.fail()</b> is <i>false</i>

```c++
// all three of the following obtain the same functionality 

#include <iostream>
using namespace std;

int main() {
  int i;
  while(true) {
    cin >> i;
    if(cin.fail()) break;
    cout << i << endl;
  }
}

// or, simpler 

int main() {
  int i;
  while(true) {
    if(!(cin >> i)) break;
    cout << i << endl;
  }
}

// cin as boolean

int main() {
  int i;
  while(true) {
    cin >> i;
    if(!cin) break;
    cout << i << endl;
   }
}
```
------------------------------------------------------------


3. Read all integers and echo to stdout, **skip** the non-integers, and end at **EOF**:

#### Read Ignore / Clear Error Flage
- An <i>error flag</i> is set when read fails
- <b>Thus, all future attempts to get input will fail</b>
- To ignore this fail, we use `cin.clear()`
- But, program will <i>loop forever</i> after the error fleg has been cleared
- <b>Once this error flag is cleared, the current char will be read AGAIN </b>
- Hence, we need `cin.ignore()` to ignore current char and proceed to the next

#### \*\*SUMMARY**
- `cin.clear()` - Clears error flag 
- `cin.ignore()` - Ignore current read, proceed to next

```c++
#include <iostream>
using namespace std;

int main() {
  int i;
  while(true) {
    if(cin >> i) {
      cout << i << endl;
    }else { // read fails
      if (cin.eof()) break;
      // read fails, all future attempts to get input will fail. We need to clear
      cin.clear();
      // we ignore the current error to stop from looping 
      cin.ignore();
    }
  }
}
```
------------------------------------------------------------


### String
We use `#include <string>` to access the C++ string type
```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;
  cout << s << endl;
}
```

#### Recall 
- `cin` start reading at <i>first</i> none-whitespace character, and stop until a whitespace is hit
- To read an <i>entire line</i> use `getline (cin, str);` allowing to read until a <i>newline</i> is encountered 
------------------------------------------------------------

### IO Manipulators 
- In C we use <i>format specifier</i> (`%d` for int, `%s` for string) to change how input is read produced
- In C++ declared type in enough for `cin` to read approperate data, but we can do the same and more using **IO Manipulators**
- See `#include <iomanip>` 

```c++
int x = 95; 
cout << x; // prints 95 in decimal
cout << hex; // no output 
cout << x; // prints 95 in hex
cout << dec; //go back to decimal
```     
