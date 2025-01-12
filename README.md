# Simple C Shell
Based on the LSH simple implementation of a shell in C. This program demonstrates the basics of how a shell works. That is: read, parse, fork, exec, and of course, wait. It has the purpose to demostrate rather than be feature complete, and as such has several limitations at this time:

+ All Commands must be on a singular line.
+ Arguments must be separated by whitespace.
+ Arguments must not have qoutes or trailing whitespace.
+ There is no functionality for piping and or redirection.
+ Only builtins are: cd, help, exit, pwd, & echo.

# Running
In order to run the program. Use gcc -o shell src/main.c to compile, and then ./shell to run.

# License
This code is in the public domain (see UNLICENSE for more details). This means you can use, modify, and distribute it without restriction.
