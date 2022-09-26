To compile and execute follow:
a)Using makefile
Step 1 - 
make -f makefile.mk

Step 2 - 
bbcp <source_filename> <target_filename>

b) without makefile
Step 1 -
gcc bbcp.c -o bbcp -Wall -Werror -O

Step 2 - 
bbcp <source_filename> <target_filename>

This assignment is not too difficult, however it is a bit difficult to handle the users' input, the arguments. The source file is simple since the manual page said that it could only be a normal file. However, the target file is complicated. I must determine whether the taget is an ordinary file or a directory. When the destination is followed by '/,' I must regard it as a directory and handle it as such.

9 test cases are failing out of 24

apue$ sh testcp.sh -p bbcp

