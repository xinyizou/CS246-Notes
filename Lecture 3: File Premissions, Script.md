## `Lecture 3:` File Premissions | Script



### Recall
Expressions | Functionality 
--- | --- 
**?** | 0 or 1 preceding 
**+** | 1 or more preceding
<b>*</b> | 0 or more preceding  
**.** | any single character 
**^** | insist lines must begin with pattern
**$** | insist there is no character after the pattern

<pre>
<b>Examples</b>

1. Fetch lines of even length
<b>$ egrep "^(..)*$"</b>

2. List all files in the current directory whose name contains exactly one "a"
<b>$ ls | egrep "^[^a]*a[^a]*$"</b>
</pre>
--------------------------------------------------------------------------------------------



### File Premissions 
<pre>
// check for file premission
<b>$ ls -l</b>
</pre>

Owner | Group | Other
--- | --- | ---
r w x | _ w _ | r _ _ |
only the owner can modify permissions | users in the same group as the file other than owner | all other users

Read (r)| Write (w) | Execute (x)
--- | --- | ---
read file directory | modify file directory | ability to execute the file


#### Mode
Ownership | Operator | Permission
--- | --- | ---
g (Group) <br> o (Other) <br> a (All) | + (Add) <br> - (Remove) <br> = (Set) |  r (Read) <br> w (Write) <br> x (Execute)
  
<pre>
<b>Exampels</b>

<b>$ chmod [mode] [fileName]</b>

1. Giver others read permission to file 
<b>$ chmod o+r file1.txt</b>

2. Giver everyone permission to read and execute 
<b>$ chmod a=rx file2.txt</b>
</pre>
--------------------------------------------------------------------------------------------



### Shell 

#### Variables 
<pre>
<b>**NOTE**</b>
- There are no spacec when creating variables
<b> $ x=1 </b>
<b> $ y="hello.world" </b>

- The following are the same
<b> $ echo $x </b>
<b> $ echo ${x} </b>
</pre>

#### Script 
<pre>
<b>Example</b> 

#!/bin/bash 

whoami 
pwd 
date
</pre>

<pre>
<b>**NOTE**</B>
The "shebang" (#!/bin/bash) line allows text file to run as bash by giving a bash-PATH

<b>To run a file</b>
1. "chmod" for premission 
2. ./fileName
</pre>

#### Arguments
Command line arguments to a script are accessible within the script using: <br>
- <b>$#</b> number of arguments supplied to the currently-running script <br>
- <b>$?</b> return status of most recently-executed command <br>
  -> 0 (Success) <br>
  -> non-zero (Fail) <br>
- <b>$0</b> name of currently-running script <br> 
- <b>$1</b> 1st argument <br>
- <b>$2</b> 2nd argument <br>
...

#### Examples
1. Pass an argument to the file isItAWord `./isItAWord hello`
```
#!/bin/bash

egrep "${1}" user/share/dict/words
``` 

2. Check if argument word is a good password? not good if it's in the dictionary
<pre>
<b>**NOTE**</b>
<i>How do we know if the word was found in the dictionary?</i>
- Every command sets a status code ('$?' generates output 0/1)
- Use 'egrep' 
  -> 0 if match found 
  -> 1 if no match found 

<i>Compare '$?' with 0 or 1</i>: <b>$ [ $? -eq 0 ]</b>
</pre>

```
#!/bin/bash

egrep "${1}" user/share/dict/words > /dev/null

if [ $? -eq 0 ]; then 
  echo Not a good password
else 
  echo Maybe a good password
fi
``` 

<pre>
<b>**OTHER**</b>
1. Single quots are literal (' ')
2. <b>/dev/null</b> redirect to ignore the output
</pre>
