## `Lecture 1:` Intro to C++ | Linux Commands



### Shell 
- Interface to the OS (Operating System)
- The `Bourne Again Shell` (BASH) is an upgraded version of `Bourn Shell` (original unix shell)
- There are many other types of shells (e.g. C-Shell, Korn-Shell ect.) 

#### Graphical Shell v.s Command Line Shell
|   | Advantage | Disavantage |
| --- | --- | --- |
| **Graphical Shell** | intuitive | limited in functionality |
| **Command Line Shell** | not limited by functionality | hard to learn |
---------------------------------------------------------------



### File System
- aka `directories`, `folder` 
- Files within file
- Rrepresented in a "tree" form 
- "/" is the root directory, root of "tree" (other use of "/" is to separate the PATH names)
- **PATH**: location of a file in the file system (see *Command Lines* below)

<pre>
<b>NOTE</b>
"<b> ./ </b>" means within the current directory 
"<b> ../ </b>" means within the parent of the current directory
</pre>
---------------------------------------------------------------



### Command Lines
Command| Functionality
--- | ---
**ls** |  list none hidden files 
**ls -a** | list all files include hidden files
**pwd** | show present working directory |
**cd [*PATH*]** | change directory |
**cat** | display the content of a file <br> **e.g.** cat [<b>PATH with FileName</b>] <pre> $> cat desktop/smaple.txt <br> "this is the content of file" </pre> **e.g.** <pre> $> cat <br> $> test <br> test </pre> `cat` wait for further command -> "test" -> "test" will be repeated -> **Ctrl D** for EOF (End of File) signal
**PATH** | specific location of a file in the file system <br> **e.g.** <pre> $> PATH  <br> username/desktop/bin </pre> **Two types of PATH:** <br> 1. `Absolute Path:` path starts at *root* directory <br> 2. `Relative Path:` path starts relative to *current* directory (more simple)
**wc** | word count <br> **e.g.** <pre> $> wc sample.txt <br> 5 <i>(# of lines)</i> 13 <i>(# of words)</i> 57 <i>(# of chars)</i> sample.txt </pre>
---------------------------------------------------------------



### Ouput Redirection >
Creates the file and then you can type the desired text to enter in the file. End file with Ctrl+D
<pre>
$ cat > [<b>FileName</b>]
</pre>

overwite contents of file2 with file1
<pre>
$ cat file1 > file2
</pre>

#### Append >> 
<pre>
append file2 to file1
$ cat file2.txt >> file1.txt
</pre>

#### Concatenation "cat"
<pre>
$ cat file2.txt file1.txt
</pre>

<pre>
<b>**NOTE**</b>
- Concatenation creates a new object since it is immutable
- Append will not create a new object since it is mutable
</pre>

#### Flags
-n displays line numbers

#### [Standard Error >&2](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-3.html)
---------------------------------------------------------------


### End program 
- <b>Ctrl C</b>: Kill 
- <b>Ctrl D</b>: End of input (send EOF to program)
