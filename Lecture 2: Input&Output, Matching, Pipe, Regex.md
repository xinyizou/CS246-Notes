## `Lecture 2:` Input&Output | Matching | Pipe | Regex



### [Linux Command Sheet](https://github.com/lilcser/CS246-University-of-Waterloo/blob/master/L2%20Linux%20Command.pdf)
------------------------------------------------------------------------------------------



### Recall
`Output Redirection (>):` redirect outputs to a file

------------------------------------------------------------------------------------------



### Input Redirection 
<pre>
// the following gives the same outputs 

// shell opens the file, and makes content of the file avaliable to cat 
//   (direct content of file into program)
<b>$ cat < [FileName]</b>

// cat opens the file and reads it
<b>$ cat [FileName]</b>
</pre>
------------------------------------------------------------------------------------------



### Pipe
Use the output from one command as the input for another.
<pre>
<b>Examples</b> 

1. head -10 file.txt | wc 
2. cat words | sort | unique
</pre>
------------------------------------------------------------------------------------------



### Parameter - Embeded Commands
Use the output from one command as the parameter for another.
<pre>
<b>Examples</b>

1. echo "Today is $(date)"
2. echo "I am $(whoami)"
</pre>

------------------------------------------------------------------------------------------



### Matching - Globbing Pattern
Expressions that let you identify multiple files.<br>
*(shell looks at given pattern -> match files with this pattern -> replace pattern with corresponding file)*

Expressions | Functionality
| --- | --- |
| <b>*</b> | replace any number of characters in file <br> **e.g.** ls \*.txt |
| <b>?</b> | replace a single characer <br> **e.g.** ls CS2?? |
------------------------------------------------------------------------------------------



### Regular Expressions
`$ egrep [pattern] [fileName]`

Expressions | Functionality | Examples
--- | --- | --- 
**()** | sub-expression gets evaluated | `$ egrep "(cs\|CS) 246" myfile.txt` <br> -> *cs246* or *CS246*
**[]** | match a single char in brackets | `$ egrep "text[abc]" myfile.txt` <br> -> *texta* or *textb* or *textc*
**^** | indicates the beginning of the line | `$ egrep "^this" myfile.txt` <br> -> print lines begin with "this"
**$** | indicates the end of the line | `$ egrep "^this$" myfile.txt` <br> -> print lines of only the word "this"
**[^...]** | indicates any character not within this set | `$ egrep "[^abc]" myfile.txt` <br> -> print lines without neither *a*,*b* or *c* 

#### Frequency of characters
Expressions | Functionality 
--- | --- 
**?** | preceding item can be matched 0 or 1 times 
**+** | preceding item can be matched 0 or more times
<b>*</b> | preceding item can be matched 0 or more times
**.** | matches any single character
------------------------------------------------------------------------------------------



### Types of Quotes
#### Double Quotes " "
<pre>
<b>$ ls "*.txt"</b> -> prints <i>*.txt</i>
<i>*.txt</i> is no longer treated as a globbing pattern 

<b>$ echo "$(cat word.txt)"</b> -> prints the content of word.txt
double qoutes here does not change the functionality of embeded command
</pre>

#### Single Qoutes ' '
<pre>
<b>$ ls '*.txt'</b> -> prints <i>*.txt</i>
<i>*.txt</i> is no longer treated as a globbing pattern 

<b>$ echo '$(cat word.txt)'</b> -> prints <i>$(cat word.txt)</i>
<i>$(cat word.txt)</i> is no longer treated as an embeded command
</pre>
