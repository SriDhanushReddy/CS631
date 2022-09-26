#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>

int main(int argc,char* argv[])
{

int desptr1, srcptr;
char c[1024] = {0};
int numRead;
struct stat buf;

//opening input file to read  and target file to copy
srcptr = open(argv[1], O_RDWR | O_CREAT);
desptr1 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

//error checks on return of function calls while opening of file and if file exists
if (argc != 3)
{
        fprintf(stderr, "Error-Insufficient Arguments (%d/3)\n", argc);
        exit(1);
}

if (strcmp(argv[1], argv[2]) == 0) 
{
        fprintf(stderr, "Both files are same \n");
	exit(1);
}
if (srcptr == -1)
{
        fprintf(stderr, "Cannot open file %s \n", argv[1]);
        exit(1);
}
if (desptr1 == -1)
{
        fprintf(stderr, "Cannot open file %s \n", argv[2]);
        exit(1);
}
if (access(argv[1], R_OK) != 0) {
	fprintf(stderr, "%saccess denied\n", argv[1]);
	exit(1);
}
if(access((dirname(strdup(argv[2]))), W_OK) != 0) {
	fprintf(stderr, "%s access denied", dirname(strdup(argv[2])));
	exit(1);
}

stat(argv[2], &buf);

mkdir(dirname(strdup(argv[2])),0777);

if(S_ISDIR(buf.st_mode)) {
	strcat(argv[2],"/");
	strcat(argv[2],basename(strdup(argv[1])));
}

//doing read operation and then write to detination file
do
    {
        numRead = read(srcptr, c, 1);
        
        if (numRead < 0)
        {
            
            fprintf(stderr, "Error-Reading from Source file\n");
            break;
        }
        else if (numRead == 0)
        {
                break;
        }
        else
        {
           c[numRead] = '\0';
        }

        if (write(desptr1,c,1) < 0 )
        {
            fprintf(stderr, "Error-Writing to Target file\n");
            break;
        }
    }
while (1);

//closing the opened files and checking for any error
if (close(srcptr) < 0) 
{ 
        fprintf(stderr, "Cannot close file %s \n", argv[1]); 
        exit(1); 
}
if (close(desptr1) < 0) 
{ 
        fprintf(stderr, "Cannot close file %s \n", argv[2]); 
        exit(1); 
}

return 0;
}
