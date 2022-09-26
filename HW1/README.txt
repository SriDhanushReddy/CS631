To compile and execute follow:
a)Using Makefile
Step 1 - 
make -f Makefile

Step 2 - 
bbcp <source_filename> <target_filename>

b) without Makefile
Step 1 -
gcc bbcp.c -o bbcp -Wall -Werror -O

Step 2 - 
bbcp <source_filename> <target_filename>

This assignment is not too difficult, however it is a bit difficult to handle the users' input, the arguments. The source file is simple since the manual page said that it could only be a normal file. However, the target file is complicated. I must determine whether the taget is an ordinary file or a directory. When the destination is followed by '/,' I must regard it as a directory and handle it as such.

9 test cases are failing out of 24

apue$ sh testcp.sh -p bbcp
  Expected failure, but command returned 0:
    /home/kdreddy/Downloads/CS631/HW1/bbcp file file2
  Files '/etc/passwd' and 'file' differ.
  Expected success, but command failed:
    /home/kdreddy/Downloads/CS631/HW1/bbcp /etc/passwd .
  Expected success, but command failed:
    /home/kdreddy/Downloads/CS631/HW1/bbcp g ./sub/dir/.
  Expected success, but command failed:
    /home/kdreddy/Downloads/CS631/HW1/bbcp /etc/passwd ./sub/dir/.
  Expected success, but command failed:
    /home/kdreddy/Downloads/CS631/HW1/bbcp /etc/passwd /tmp/f
  Expected success, but command failed:
    /home/kdreddy/Downloads/CS631/HW1/bbcp /etc/passwd ../cptest.xQcf3n/
  Command timed out, marking as failure:
    /home/kdreddy/Downloads/CS631/HW1/bbcp big file
  Files 'file1' and 'file2' differ.
  testcp.sh: 9/24 tests failed.
