# Shell

## Introduction
- Basing our code off of our previous Rshell assignment, we now needed to
implement the use of piping, appending redirection, input redirection and output
redirection. For piping, we had to redirect standard output and input to a pipe
to connect two processes. For output redirection, we redirected our standard
output to a file ID. This also happens for the appending redirection but it also
includes an append flag when opening the file. Lastly for input redirection, we
needed to redirect our standard input to a file ID and executing a command which
will use the new file ID as input instead of standard input.
---
## How to run Rshell
After downloading from Github, you're gonna have to do the following (but make and bin/Rshell also works too):

- cd src
- g++ Rshell.cpp
- ./a.out
---
## Code Examples
$ cat &lt; existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z
A-Z &gt; newOutputFile2

This concatenates the contents of the existingInputFile to the newOutputFile1
lower cased and upper cased to the newOutputFile2.
---
## Tests
There are 12 test files:
1. singleCommand.sh (Testing single command)
2. multiCommand.sh (Testing multiple commands)
3. paraCommand.sh (Testing precedence operator)
4. multiParaCommand.sh (Testing multiple precedence operator)
5. nestParaCommand.sh (Testing nested precedence operator)
6. brackCommand.sh (Testing keyword "test")
7. multiBrackCommand.sh (Testing brackets and keyword "test")
8. brackWParaCommand.sh (Testing brackets, keyword "test" and precedence
operators)
9. input_redirect_test.sh (Testing for &lt;)
10. output_redirect_test.sh (Testing for &gt;)
11. append_redirect_test.sh (Texting for &gt;&gt;)
12. pipe_test.sh (Testing for |)
---
## Limitations/Known Bugs
- When using the command "echo" with more than 2 parameters, the program
displays the second to last parameter n-1 amount of times, where n is the number
of parameters that has been inputted, and then the last parameter once.
(Resolved in assignment 3)
- Also when there are two parameters and a comment after for the command "echo",
the first listed bug happens but prints out n amount of times instead without
outputting the comment. (Resolved in assignment 3)
- After entering a command then semi-colon and nothing else either causes the
next inputted command to execute also the last command that ended in a
semicolon or just displays an error or does not execute at all.
- Trying to exit after getting errors does not exit. You must "exit" m+1 amount
of times with m being the number of errors that has appeared.
- Comments with multiple commands sometimes results in segmentation faults
- After using pipe correctly, everything will work properly but there will be
 a "wait" that is waiting for additional input. A way to resolve this is just
 pressing enter again. (Assignment 4 bug)
---
## Contributors
- Brett McCausland <bmcca009@ucr.edu>
---
## License & copyright
(c) Brett McCausland, University of California, Riverside.

Licensed under the [MIT License](License.txt).
