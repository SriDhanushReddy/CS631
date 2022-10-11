/* Kernel include files */
#include <sys/types.h>
#include <sys/stat.h>

/* /usr include files */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
/* Local include files */
#include "ls.h"

/* Private Functions*/
static void usage(void);

/*
*A-List all entries except for ‘.’ and ‘..’. Always set for the super-user
*a-Include directory entries whose names begin with a dot ( ‘.’ )
*c-Use time when file status was last changed, instead of time of last modification of the file for sorting ( −t ) or printing ( −l ) .
*d-Directories are listed as plain files (not searched recursively) and symbolic links in the argument
list are not indirected through.
*F-Display a slash ( ‘/’ ) immediately after each pathname that is a directory, an asterisk ( ‘∗’) after
each that is executable, an at sign ( ‘@’ ) after each symbolic link, a percent sign ( ‘%’ ) after each
whiteout, an equal sign ( ‘=’ ) after each socket, and a vertical bar ( ‘|’ ) after each that is a FIFO.
*f-Output is not sorted.
*h-Modifies the −s and −l options, causing the sizes to be reported in bytes displayed in a human
readable format. Overrides −k.
*i-For each file, print the file’s file serial number (inode number).
*k-Modifies the −s option, causing the sizes to be reported in kilobytes. The rightmost of the −k and
−h flags overrides the previous flag. See also −h.
*l-(The lowercase letter “ell”). List in long format. (See below.)
*n-The same as −l, except that the owner and group IDs are displayed numerically rather than converting to a owner or group name.
*q-Force printing of non-printable characters in file names as the character ‘?’; this is the default when output is to a terminal.
*R-Recursively list subdirectories encountered.
*r-Reverse the order of the sort to get reverse lexicographical order or the smallest or oldest entries first
*S-Sort by size, largest file first
*s-Display the number of file system blocks actually used by each file, in units of 512 bytes or
BLOCKSIZE (see ENVIRONMENT) where partial units are rounded up to the next integer value.
If the output is to a terminal, a total sum for all the file sizes is output on a line before the listing.
*t-Sort by time modified (most recently modified first) before sorting the operands by lexicographical
order.
*u-Use time of last access, instead of last modification of the file for sorting ( −t ) or printing ( −l ) .
*w-Force raw printing of non-printable characters. This is the default when output is not to a terminal.
*/
int
main(int argc, char *argv[])
{
    int option;
    while ((option = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1) {
    	switch (option){
    		case 'A':
    			all_unhidden();
    		break;
    		case 'a':
    			list_all();
    		break;
    		case 'c':
	    		char *path = ".";
	    		print_sorted(path);
    		break;
    		case 'd':
	    		char *dir = ".";
	    		print_dir_contents(dir);
	    	break;
    		case 'F':
	    		if( argc < 2 )
	    		return 1;
			show_dir(".");
    		break;
    		case 'f':
    			list_files_unsorted(".");
    		break;
    		case 'h':
    		;
    		break;
    		case 'i':
    			printFileInode2();
    		break;
    		case 'k':
    		;
    		break;
    		case 'l':
    			list_directory_contents(".");
    		break;
    		case 'n':
    			list_directory_contents2(".");
    		break;
    		case 'q':
    			non_printable_all();
    		break;
    		case 'R':
		    	DIR *sd;
    			sd = opendir(".");
    			depthFirst(sd);
    			closedir(sd);
    		break;
    		case 'r':
    			print_directory_contents3(".");
    		break;
    		case 'S':
    			sorting_function();
    		break;
    		case 's':
    			file_size();
    		break;
    		case 't':
    			file_sort();
    		break;
    		case 'u':
    			sortByLastAccess(".");
    		break;
    		case 'w':
    			non_printable_all();
    		break;
    		default:
    		; //error
    	}
    }
return 0;
}
