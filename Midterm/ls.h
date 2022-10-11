
#ifndef ls_h
#define ls_h

int list_all();
int all_unhidden();
int compare(const struct dirent **a, const struct dirent **b);
void print_sorted(char *path);
void print_dir_contents(char *dir);
void show_dir( const char *dir_name );
void list_files_unsorted(const char *path);
void printFileInode(char* file);
int printFileInode2();
int list_directory_contents(const char *dirname);
int list_directory_contents2(const char *dirname);
int non_printable_all();
void depthFirst(DIR *dir);
int isdirectory(char *path);
void print_directory_contents3(char *dir);
int sorting_function();
void file_size();
int file_sort();
int sortByLastAccess(const char *dirname);

#endif
