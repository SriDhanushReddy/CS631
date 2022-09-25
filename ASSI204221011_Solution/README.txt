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