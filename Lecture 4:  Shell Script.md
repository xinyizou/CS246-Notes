## `Lecture 4:` Shell Script


### Script 
<pre>
<b>Example</b> 
#!/bin/bash

egrep "^${1}$" /usr/share/dict/words > /dev/null

usage() {
  echo "Usage: $0 password" >&2
  exit 1
}

if [ ${#} -ne 1 ]; then 
  usage
fi
</pre>

####  Recap
|      | Functinoality
--- | ---
**$#** | number of arguments supplied to the currently-running script 
**$0** | name of currently-running script 
**exit** | exit script 
**if [ -e file ] ; then** | check if file exist 

#### Examples
1. Print numbers form 1 to $1
<pre>
<b>While Loop</b>
#!/bin/bash

x=1

while [ ${x} -le $1 ]; do 
  echo ${x}
  x=$((X+1)) ##double bracket!!
done 
</pre>

2. Rename all .c files to .cc 
```
file=hello.c
mv $file ${file%c}cc

##To remove part of a name
file=123hello
${file#123} ##removes just 123

#!/bin/bash 

for name in *.C; do
  mv ${name} ${name%c}cc 
done
```

3. count numeber of occurances of $1 in the file $2 
```
#!/bin/bash 

count=0
for word in $(cat "$2"); do ##it is a good practice to put double qouts ("") around any user input
  if [ $word = "$1" ]; then 
    count=$((count+1))
  fi
done

echo count
``` 
--------------------------------------------------------------------------------------------



### C v.s C++
<pre>
<b>C</b>
`````````````````````````
#include<stdio.h>

int main (void) {
  printf("helloworld");
  return 0;
}


<b>C++</b> 
In C++ we use <iostram> which includs <b>std::cin</b> and <b>std::cout</b>
`````````````````````````
#include<iostream>
using namespace std;
  
int main () {
  cout << "helloworld" << endl; 
}
</pre>
