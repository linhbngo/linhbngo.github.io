---
layout: lecture
pretty_table: true
order: 2
title: Bash Scriptings
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true
toc:
  - name: Setup
  - name: Introduction to Docker
  - name: Docker Images
  - name: Infrastructure as Code
  - name: "Infrastructure as Code: Storage"
  - name: "Infrastructure as Code: Networking"

---
 
# Bash Scriptings

Based on previous materials by Dr. Robert Kline

## 1. Bash Script

{% details note Overview %}



{% enddetails %}
- Just like the script for a movie that tells the actors what they should say and 
do, a script for a computer tells the computer what is should do or say.
- A bash script is a plain text file which contains a series of commands. 
- Anything you can run normally on the command line can be put into a script and it will do exactly the same thing. Similarly, anything you can put into a script can also be run normally on the command and it will do exactly the same thing. 

```

{% details note Setup %}



{% enddetails %}
- In your CloudLab experiment, run the following:

~~~bash
sudo su - seed
wget https://cs.wcupa.edu/lngo/assets/src/bash_basics.zip
sudo apt-get update
sudo apt-get install -y unzip
unzip bash_basics.zip
cd bash_basics
ls
~~~

- These scripts will be used to illustrate concepts in the remainder of 
this slide deck.
- There is far too much content in the Bash language to be covered in 
any single document like this one, a tutorial, or even an introductory 
textbook. Inevitably, if you need to write programs in Bash, you will 
have to consult the online manual: [https://linux.die.net/man/1/bash](https://linux.die.net/man/1/bash)

```

{% details note Executing a bash script %}



{% enddetails %}
- Bash script files can be named as you like. Unlike Windows systems, 
the extension is not an essential feature which determines the usage. 
The `.sh` extension is merely a convention which can assist editor 
recognition. All scripts can be executed explicitly using the bash executable:

~~~bash
bash SOME-SCRIPT.sh
~~~

- Create a file named `hello.sh` with the following content:

~~~bash
echo "hello world"
~~~ 

- Execute the file using the following command: 

~~~bash
bash hello.sh
~~~

```

{% details note Self-executing bash script %}



{% enddetails %}
-	The file itself must be executable by you. 
-	If you are the owner of the script you can add that 
permission with statements like:

~~~bash
chmod +x SOME-SCRIPT.sh          
~~~

or 

~~~bash
chmod 700 SOME-SCRIPT.sh       
~~~

-	The file must either be locatable by its path prefix or have its containing 
directory in the PATH variable. A full path to the script might be: `/usr/local/bin/SOME-SCRIPT.sh` 
-	If the script is in the shell's current directory, this is also a full path: `./SOME-SCRIPT.sh`
-	The file must identify itself as self-executing. 
  - If the first two characters are `#!`, this indicates that the file is a text-based 
  script file, and that the remaining portion of the first line provides the program to 
  run the script. Thus, a Bash script begins with this first line: `#!/bin/bash`

-	Edit and add `#!/bin/bash` to the first line of `hello.sh`

~~~bash
chmod +x hello.sh
./hello.sh
~~~

```


## 2. The Bash Language

{% details note Overview %}



{% enddetails %}
- The Bash language has three main functions:
  -	execute commands interactively
  -	extend the set of commands via scripts
  -	build up, via sourcing, the user environment with variables, aliases, functions
- In particular, Bash, per se, is not a general purpose programming script language 
like, say, Perl, Python or TCL. 
  - Its main orientation is towards executing the standard UNIX command set and Bash scripts 
  rely heavily on the standard UNIX commands.

```

{% details note Interactive Execution %}



{% enddetails %}
-	When a shell is run interactively the lines of a bash program a
re created one-by-one. 
-	Shell code usually is considers the script to be interactive if the 
prompt variable, PS1 is defined, since all statements receive this prompt 
before entry. 
  - In interactive execution, Bash will source each statement, which is a 
  form of execution in which all variable settings are retained. 
- Interactive execution also permits many user-friendly control features not 
necessary in script execution such as:
  -	line repeat control with up and down arrows
  -	line editing and extension features
  -	tab-based command and filename completion

```

## 3. Variables and Values

{% details note Overview %}



{% enddetails %}
- The program `scalars.sh` illustrates basic principles of 
Bash variables and values. In particular, the only scalar data 
type is a string. Values are created in several ways:

-	within uninterpolated quotes: ' '
-	within interpolated quotes: " "
-	the output of a command within shell evaluated back quotes $`\_`$ or within `$( )`
-	a bareword which is not a Bash reserved word and contains no special operator 
characters

```

{% details note String operations %}



{% enddetails %}
-	The most basic operation on strings is concatenation, which, in Bash, is simply juxtaposition. 
In general, whitespace sequences are collapsed into a single blank; whitespace sequences at the 
ends of strings are truncated (i.e., trimmed).
-	Variables are defined using the assign operator `=` in a very strict sort of way. 
  - Once a variable, `v`, is defined, its value is automatically used with the expression `$v`. 
  - A double-quoted variable's value, like `"$y"`, can behave differently from `$y` when the 
  value has internal whitespace. If there is any doubt, it is recommended to always use **double quotes**.
-	A newline is interpreted as a statement terminator. A semicolon (`;`) can also be used as 
a statement terminator if you want two or more statements on the same line.
-	View, then execute scalars.h
-	Observe the corresponding outcomes versus the codes

~~~bash
more scalars.sh
./scalars.sh
~~~

-	Type something and hit Enter to exit this script.

```

{% details note echo and printf %}



{% enddetails %}
- Although echo is the most common output statement, Bash 
also supports the C-style printf statement, e.g.,

~~~bash
printf "num=%05d\n" 27
echo AFTER
~~~

- There is an equivalent to sprintf (printf to a variable) in the form of

~~~bash
printf -v num "%05d" 27
echo $num
~~~

- For most situations, echo is more common. It is easy to use and, for 
the most part does what you want in a simple manner. One 
  - *problem* spot is printing control characters like `\t` for tab. 
  - The bash syntax for this control character has the cumbersome form: $'\t'
- For example, these two statements generate the same output:

~~~bash
echo   $'\t'foo
printf "\tfoo\n"
~~~

- As you can imagine the `printf` version is more memorable. On feature 
available to echo which is not available to printf is colorization. When used 
with the `-e` flag, echo interprets certain special convoluted escape sequences 
as indication to change the color of the output. For example this prints "HELLO" 
in bold red followed by "THERE" in (normal) black

~~~bash
echo -e "\033[01;31m HELLO \033[0m THERE"
~~~

- The output need not be separated like this, we are simply making it easier to see

```

## 4. More about Bash

{% details note Other types and declarations %}



{% enddetails %}
- Bash, just as other languages, does support additional structured data types in the 
form of lists and maps (associative lists). 
- It also provides a way of assigning a type to a variable through a the declare 
statement. View and execute the following script for observation

~~~bash
more scalar-declares.sh
./scalar-declares.sh
~~~

```

{% details note Command-line arguments %}



{% enddetails %}
- One of the primary purpose of the bash language is to extend the set of 
commands. For this reason Bash provides simple access to the command-line 
parameters. Bash uses the variables `$1`, `$2`, etc. The expression `$0` 
is the command name itself. They should be double-quoted. Use these test-runs:

~~~bash
$ more args.sh
$ ./args.sh 
$ ./args.sh  a     b    c
$ ./args.sh "a     b"   c
~~~

```

## 5. Bash condition

{% details note if-else statements %}



{% enddetails %}
- The bash if-else syntax is unusual compared to other languages. 
The format looks like this:

~~~bash
if ...
then
  some statements
elif ...
  some statements
else
  some statements
fi
~~~

The "..." sections represent boolean "tests". The chained `elif` and the `else` 
parts are optional. The "then" syntax is often written on the same line as the if 
portion like this: `if ...; then`

```

{% details note Program exit status %}



{% enddetails %}
~~~bash
more pingtest.sh
./pingtest.sh 
./pingtest.sh 8.8.8.8
./pingtest.sh 2.2.2.2
~~~

-	What is happening is that the ping operation with the options used 
is a single ping which can either succeed or fail within 2 seconds with these two possible outcomes:
  -	it succeeds with exit status is 0, the test is true and the if part is executed.
  -	it fails with non-zero exit status, the test is false and the else part is executed.
-	The notion of true and false in these bash tests can be counter-intuitive: an exit status 
of 0 means true, non-zero means false. The `$?` construct used in `echo status=$?` is a Bash 
special variable which gives the exit status of a previous command (and so it has to come before 
the second echo statement).
```

{% details note The && and || operators %}



{% enddetails %}
- The `&&` and `||` operators are much the same sense as other 
languages using short-circuit execution. 
- In Bash they are often used to express the chaining of operations based on 
success or failure. A good example is: `c++ myprog.cc && a.out`, in which 
we only run the compiled program if the compilation succeeds.

```

{% details note Boolean expressions in test statements %}



{% enddetails %}
- What is considered as boolean expression in an if test uses this syntax:

~~~bash
if [ BOOLEAN-EXPRESSION ]; then
  statements ...
fi
~~~

- The only value regarded as false is the empty string. Bash does not recognize 
any numerical types per se, only strings used in a numerical context. An undefined 
value is, in every way, equivalent to the empty string in Bash. 
- You have to be careful about using an undefined variable in a script since it may 
be an exported variable and, thereby, implicitly defined. You can always explicitly 
undefined a variable `x` by `unset x`. 
- You can verify the values of false by viewing and running this sample script: `falsetest.sh`


~~~bash
more falsetest.sh
./falsetest.sh
~~~

- An example usage is this line in `pingtest.sh`:

~~~bash
[ "$host" ] || { echo usage: $(basename $0) "<host or ip>"; exit 1; }
~~~

- In this example host is the first parameter; if undefined, give a "usage" message.

```

{% details note Unary file information operators %}



{% enddetails %}
- A number of common Bash constructions use the unary "–" prefix file test operators, e.g.,
  - `-e` NAME: NAME exists as a file (of some type)
  - `-f` NAME: NAME exists as a regular file
  -	`-d` NAME: NAME exists as a directory
- An example of this appears in the `~/.bashrc` startup script: 

~~~bash
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi
~~~

```

{% details note Binary test operators %}



{% enddetails %}
- The `if` operator (and other tests) can be used with boolean expressions 
using appropriate syntax. 
- The test expressions are normally within single brackets [ .. ]. 
  - There is a single space after `[` and before `]`. 
- Within these we have these operator usages:
  - `=`, `!=`: lexicographic comparison
  - `-eq`, `-ne`, `-lt`, `-le`, `-gt`, `-ge`: numerical comparison
- However both double brackets `[[ .. ]]` and double parentheses `(( .. ))` 
can serve as delimiters. 
- The operators `<` and `>` normally represent *file redirection*, 
but can be used for lexicographic comparison, within `[[ .. ]]` and numerical comparison within `(( .. ))`. 
- You can view and observe some examples from: `test-values.sh`

~~~bash
more test-values.sh
./test-values.sh
~~~

```

{% details note Subtle syntax issues %}



{% enddetails %}
- The way Bash deals with strings has certain unexpected consequences. 
Consider the program `errors.sh`:

~~~bash
more errors.sh
./errors.sh
~~~

- When executed, the 3 out of 4 test lines are flagged as errors:
  - line 4: `[a: command not found`
  - line 5: `[: missing `]'`
  - line 7: `[: a: unary operator expected`
- The first two mistakes were caused by having the expression `$x` touch a bracket. 
- The last was caused by the missing quotes around the `$y` expression in which case it 
interpreted the inserted expression `"a b"` as the operator `a` with argument `b`.

```

{% details note String patterns and the case statement %}



{% enddetails %}
-	Bash uses primitive globbing patterns for various matching operations. 
- The most common is the usage of `*` which matches any sequence of characters. 
- Less common is `?` which matches any single character and even less common are 
character sets, such as `[A-Z]` and `[^0-9]`.
-	These type of expressions stand in contrast to more powerful regular expression 
pattern generators which, in Bash, are only available through auxiliary commands. 
- Glob patterns are simple, familiar patterns such as those used commonly in file listing:
  -	`ls *.html`      # all HTML files (not starting with ".")
  -	`ls .??*`        # all dot files except "." and ".."
  -	`ls test[0-3]`   # "test0", "test1", "test2", "test3"
- The Bash `case` statement distinguishes itself from an `if/else` 
constructions primarily by its ability to test its cases by matching 
the argument against glob patterns. The syntax is like this:

~~~bash
case "$file" in
  *.txt)  # treat "$file" like a text file
          ;;
  *.gif)  # treat it like a GIF file
          ;;
  *) # catch-all
     ;;
esac 
~~~

- Unlike C++ or Java syntax, the break exits an enclosing loop, not exit the particular case.

```

## 6. Bash loop

{% details note Loops %}



{% enddetails %}
Bash has both for and while loops. However, the type of control for these is typically not numerical. The most common looping structure in Bash is the for/in structure like this:
for x in ...
do
  statements involving $x
done

Loops
The "..." is a list of things generated in a number of ways. The x is the loop variable which iterates through each item in the list. For example, try running this program in the current directory:
$ more fileinfo.sh
$ ./fileinfo.sh
In this case the things iterated are the files in the current directory. 
Loops
One can use numerical-like looping with the double-parentheses like those in for numerical comparison:
for ((i=1; i<=10; ++i)); do
  echo $i
done 

```

{% details note Reading lines in Bash %}



{% enddetails %}
- The while loop also has an advantage in its ability to read live input. 
For example, this simple program reads and echos input lines:

~~~bash
while read line; do
  echo "$line"
done
~~~

- In a programmatic setting, it is often useful to process lines generated 
from the output of some command. 
- Say we want to process all words starting with `my` in the system 
dictionary (`/usr/share/dict/words`) by removing - the initial `my` part. 
- The following two scripts represent two possible ways of doing so:

~~~bash
more process-lines-1.sh
more process-lines-2.sh
~~~

- The command `grep ^my /usr/share/dict/words` is used to generate the target information. 
- The two respective approaches to processing this are:
  -	input redirection into the `while ... done` loop using the manufactured "input device" `< (grep ^my /usr/share/dict/words)`
  -	piping (i.e., `|`) the command into the "while ... done" loop.
- It turns out that only the former method works as we want it to. The problem with the 
latter method is that the `count` variable is being manipulated in a subshell created by 
the pipe operation and so its value cannot be used upon exiting the while loop. 
  - In contrast, the former method with the odd syntax "<(..)" turns out to be more useful.

```

{% details note Command-line options %}



{% enddetails %}
- Command-line arguments commonly consist of option arguments 
beginning with a "-". Consider, for example, the follow `unzip` command 
which extracts `FILE.zip` into `/usr/local`, 
  - doing so with no output (-q) and 
  - overriding existing files (-o). 
  - The FILE.zip portion is the argument and others are options. 
  - Some options, like -d, take an argument themselves. 
- The unzip command takes many more options (mostly prior to the argument).

~~~bash
unzip -q -o FILE.zip -d /usr/local
~~~

- The options can be "compressed" under certain circumstances. For example, this is 
an equivalent call:

~~~bash
unzip -qo FILE.zip -d /usr/local
~~~

- The bash built-in operation `getopts` is meant to assist in extracting these options 
from the command line. 
- Consider the program getopts-test.sh:

~~~bash
more getopts-test.sh
./getopts-test.sh
~~~

- Running this command

~~~bash
./getopts-test.sh -q -o FILE.zip -d /usr/local
~~~

yields the output:

~~~bash
q 2
o 3
? 3
FILE.zip
d 3 /usr/local
? 3
~~~

- The while loop `while getopts` runs through the 
arguments looking for `-n`, `-o`, `-q`, `-s` options. 
  - OPTIND gives the position of the option (1-based). 
  - When a non-option argument is encountered the while loop terminates with 
  flag set to ?. We can keep on going by shifting everything out and resetting OPTIND back to 1.
- The second part of the option search uses: `while getopts "d:" flag`
  - The "d:" syntax indicates that the d option also takes an argument. 
  In this case, the $OPTARG expression captures that value.
- A useful style of option sensing is to set `option flag` variables as shown in `optflags.sh`. 
Try the followings: 

~~~bash
./optflags.sh
./optflags.sh -abc foo -d bar foobar barfoo
~~~

- What is happening is that the variables `opt_a`, `opt_b`, and `opt_c` are 
being created through deferred evaluation using the Bash eval function. 
- The actual `$flag`, say "b", subtitutes into the evaluated expression eval 
"opt_$flag=1" thus defining `opt_b` and setting it. We can later test for the 
presence of the "b" flag by: `if [ "$opt_b" ]; then ...`

```

## 7. More Bash

{% details note Built-in string processing operations %}



{% enddetails %}
- The Bash language itself has very unintuitive string-processing operations. 
Later we'll see how to use UNIX commands to do string processing.

~~~bash
more string-processing.sh
./string-processing.sh
~~~

```

{% details note Functions %}



{% enddetails %}
-	Functions offer an improvement of aliases. They must be defined before being used. In practice, they are often grouped into Bash files which are sourced within the script which uses them.
-	Functions are supposed to emulate the way commands work. They do not return values in the usual way; any value sent back by the return statement must be an integer which acts like the exit code of an executable.

~~~bash
more functions.sh
./functions.sh
~~~

```

{% details note System command string processing %}



{% enddetails %}
-	The Bash language relies heavily on the UNIX-like environment in which it resides in order to create utility scripts. This environment includes many standard UNIX string processing operations such as these:
  -	`sed`: (stream editor) for regular-expression substitution
  -	`grep`: can be used to perform match testing with -c (count) option; the -e option uses regular expression instead of glob patterns
  -	`awk`: captures the fields of a line (separated by whitespace) and does operations on these fields;
  -	`tr`: translate from one list of characters to another; often used to convert case of a string
- `sed`, `grep`, `awk`, and `tr` are used in Bash via standard I/O. All above operations act on text files when given file name as a parameter, or act from standard input with no arguments. 
- A common bash expression which uses an external OPERATION to compute some internal value 
looks something like this: `result="$(echo "input string" | OPERATION)"`
- The pipe operator "|" is crucial for passing the input string to OPERATION via echo. 
The following program illustrates some of these external operations.

~~~bash
more string-operations.sh
./string-operations.sh
~~~

```

