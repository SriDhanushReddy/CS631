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


#define BUF_SIZE 1024

struct entry {
    char *name;
    long long int size;
    struct entry *next;
};


//This code will print out the names of all of the files in the current directory
int
list_all()
{
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
  return(0);
}

//The code returns the names of all non-hidden files in the current directory
int
all_unhidden()
{
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] != '.') {
        printf("%s\n", dir->d_name);
       }
    }
    closedir(d);
  }
  return(0);
}

//This is a function to compare two struct dirent objects by their file creation times
int
compare(const struct dirent **a, const struct dirent **b)
{
    struct dirent *d1 = *(struct dirent **)a;
    struct dirent *d2 = *(struct dirent **)b;
    struct stat s1, s2;

    stat(d1->d_name, &s1);
    stat(d2->d_name, &s2);

    return s1.st_ctime - s2.st_ctime;
}

void
print_sorted(char *path)
{
    DIR *dir;
    struct dirent **namelist;
    int n;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    n = scandir(path, &namelist, NULL, compare);
    if (n < 0) {
        perror("scandir");
        exit(1);
    }

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%s\n", namelist[i]->d_name);
    }

    free(namelist);
}
/*
  This code opens a directory and uses scandir to get a list of all the files in that directory. It then uses compare to sort the files and prints them out.
*/
void
print_dir_contents(char *dir)
{
  DIR *directory = opendir(dir);
  struct dirent *entry;
  while ((entry = readdir(directory)) != NULL) {
    printf("%s\n", entry->d_name);
  }
  closedir(directory);
}

/*
This  function opens a directory and prints out the contents. If the first character of the name of the directory entry is a '.', it is ignored.
*/
void
show_dir( const char *dir_name )
{
  struct dirent *d_ent;
  struct stat f_stat;
  DIR *dir;
  int i;
  if( (dir = opendir(dir_name)) == NULL )
  {
    perror("opendir");
    return;
  }
    while( (d_ent = readdir(dir)) != NULL )
  {
    if( d_ent->d_name[0] == '.' ) /* ignore current, parent, hidden */
      continue;

    if( lstat(d_ent->d_name, &f_stat) )
      continue;

    if( S_ISDIR(f_stat.st_mode) )
      printf("/");
    else if( S_ISLNK(f_stat.st_mode) )
      printf("@");
    else if( S_ISFIFO(f_stat.st_mode) )
      printf("|");
    else if( S_ISSOCK(f_stat.st_mode) )
      printf("=");
    else if( S_ISCHR(f_stat.st_mode) )
      printf("%c", '%');
    else if( f_stat.st_mode & S_IXUSR ||
             f_stat.st_mode & S_IXGRP ||
             f_stat.st_mode & S_IXOTH )
      printf("*");

    printf("%s\n", d_ent->d_name);
  }
  closedir(dir);
}

//The code below will list all files (unsorted) in the directory given by "path"
void
list_files_unsorted(const char *path)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

//The code below is used to print the inode number of a given file
void
printFileInode(char* file) 
{ 
    struct stat fileStat; 
    if(stat(file,&fileStat) < 0) 
        return; 
    printf("%ld",fileStat.st_ino); 
}

/*
The code below opens the current directory and reads the contents of the directory one entry at a time. For each entry, the inode number is printed. The inode number is a unique identifier for each file
*/
int
printFileInode2()
{
	DIR *d; 
	struct dirent *dir; 
	d = opendir("."); 
	if (d) 
	{ 
	while ((dir = readdir(d)) != NULL) 
	{ 
	printFileInode(dir->d_name); 
	printf("\n"); 
	} 
	closedir(d); 
}
}

/*
The code below lists the contents of a given directory, including information on each file such as the file name, the number of links, the owner and group, the size, and the last modification time. If the directory cannot be opened, an error message is printed.
*/
int
list_directory_contents(const char *dirname)
{
    DIR *dirp;
    struct dirent *entry;
    struct stat statbuf;
    dirp = opendir(dirname);
    if (dirp == NULL) {
        perror("opendir");
        return -1;
    }
    while ((entry = readdir(dirp)) != NULL) {
        stat(entry->d_name, &statbuf);
        printf(" %10.10s ", entry->d_name);
        printf(" %4d ", (int)statbuf.st_nlink);
        printf(" %8.8s ", getpwuid(statbuf.st_uid)->pw_name);
        printf(" %8.8s ", getgrgid(statbuf.st_gid)->gr_name);
        printf(" %8.8d ", (int)statbuf.st_size);
        printf(" %20.20s ", ctime(&statbuf.st_mtime));
        printf(" %s\n ", (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    }
    closedir(dirp);
    return 0;
}

/*
This code prints out the contents of a directory. It uses the opendir() function to open a directory stream, and then reads from it using readdir(). For each entry read, it calls stat() to get information about the file, and then prints out various bits of information about the file
*/
int
list_directory_contents2(const char *dirname)
{
    DIR *dirp;
    struct dirent *entry;
    struct stat statbuf;
    dirp = opendir(dirname);
    if (dirp == NULL) {
        perror("opendir");
        return -1;
    }
    while ((entry = readdir(dirp)) != NULL) {
        stat(entry->d_name, &statbuf);
        printf("%10.10s", entry->d_name);
        printf("%4d", (int)statbuf.st_nlink);
        printf("%8.8d", (int)statbuf.st_uid);
        printf("%8.8d", (int)statbuf.st_gid);
        printf("%8.8d", (int)statbuf.st_size);
        printf("%20.20s", ctime(&statbuf.st_mtime));
        printf("%s\n", (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    }
    closedir(dirp);
    return 0;
}

/*
*The code opens the current directory and loops through each file, printing the name of the file.
*If any character in the file name is not printable, the name is printed again.
*/
int
non_printable_all()
{
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
    	char *name = dir->d_name;
    	printf("%s\n", name);
      for(int i=0; i<strlen(name); i++)
	{
        if (!isprint(name [i]))
    	{
        printf("%s\n", name);
        }
	}
    }
    closedir(d);
  }
  return(0);
}

/*
The function depthFirst() calls itself recursively in order to print out all the files in a directory. It takes in a DIR pointer and reads all the files in the directory. If the file is a directory, it calls depthFirst() again with the new directory
*/
void
depthFirst(DIR *dir)
{
  struct dirent *sd;
  char path[PATH_MAX];

  if(dir == NULL){
    printf("Error, unable to open\n");
    exit(1);
  }

  while( (sd = readdir(dir)) != NULL){
    if(strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0){
      printf("%s\n", sd->d_name);
      realpath(sd->d_name,path);

      if(isdirectory(path)){
        depthFirst(opendir(sd->d_name));
      }               
    }
  }
}
/*
The code checks if a given path is a directory. It does this by checking the file's stats and seeing if the file is a directory type. If the file is a directory, it returns 1, else it returns 0
*/
int
isdirectory(char *path)
{
  struct stat statbuf;
  if (stat(path, &statbuf) == -1)
    return 0;
  else
    return S_ISDIR(statbuf.st_mode);
}

/*
The code opens the specified directory and reads the contents one by one. For each entry read, the name of the entry is printed. If the directory can't be opened, an error message is printed
*/
void
print_directory_contents3(char *dir)
{
    DIR *dp;
    struct dirent *ep;     
    dp = opendir (dir);

    if (dp != NULL)
    {
        while (ep = readdir (dp))
            puts (ep->d_name);

        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory.");
}

/*
The code defines a sorting function that takes in a directory and prints out the contents of the directory in order from largest file to smallest file
*/
int
sorting_function()
{
    DIR *dir;
    struct dirent *dp;
    struct stat st;
    struct entry *head = NULL, *ep, **npp;

    dir = opendir(".");
    if (dir == NULL) {
        perror("cannot open directory");
        return 1;
    }
    while ((dp = readdir(dir)) != NULL) {
        ep = calloc(sizeof(*ep), 1);
        if (ep == NULL) {
            perror("cannot allocate memory");
            return 1;
        }
        ep->name = strdup(dp->d_name);
        if (ep->name == NULL) {
            perror("cannot allocate memory");
            return 1;
        }
        if (!stat(dp->d_name, &st)) {
            ep->size = st.st_size;
        }
        for (npp = &head; *npp && (*npp)->size <= ep->size; npp = &(*npp)->next)
            continue;
        ep->next = *npp;
        *npp = ep;
    }
    closedir(dir);
    for (ep = head; ep; ep = ep->next) {
        printf("%s\n", ep->name);
    }
    while ((ep = head) != NULL) {
        head = ep->next;
        free(ep->name);
        free(ep);
    }
    return 0;
}

//The code below prints the name and size of each file in the current directory
void
file_size()
{
    DIR *dp;
    struct dirent *ep;
    struct stat st;
    dp = opendir (".");
            while (ep = readdir (dp))
        {
            stat(ep->d_name, &st);
            printf("name: %s, size: %ld\n", ep->d_name, st.st_size);
        }
        (void) closedir (dp);
}

/*
This is a function that reads the contents of a directory and prints the name and modification time of each file
*/
int
file_sort()
{
    DIR *dp;
    struct dirent *d;
    struct stat s;
    char *path;
    char *buf;
    int i;

    path = (".");
    dp = opendir(path);
    if (!dp) {
        perror("opendir");
        return 1;
    }

    while ((d = readdir(dp))) {
        buf = malloc(strlen(path) + strlen(d->d_name) + 2);
        sprintf(buf, "%s/%s", path, d->d_name);
        stat(buf, &s);
        printf("%s %lu\n", d->d_name, s.st_mtime);
        free(buf);
    }

    closedir(dp);

    return 0;
}

/*
The code below opens the directory specified by dirname, and then reads through each file in the directory. For each file, it prints the filename and the last access time
*/
int
sortByLastAccess(const char *dirname)
{
    struct dirent *dp;
    DIR *dir = opendir(dirname);
    if (!dir)
        return -1;
 
    while ((dp = readdir(dir)) != NULL) {
        if (dp->d_name[0] != '.'){
            struct stat sb;
            stat(dp->d_name, &sb);
            printf("%s %ld\n", dp->d_name, (long) sb.st_atime);
        }
    }
    closedir(dir);
    return 0;
}
