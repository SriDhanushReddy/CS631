#include "ls.h"

#define NOTPRINT 1

int A_flag, a_flag, c_flag, d_flag, F_flag, f_flag, h_flag, i_flag;
int k_flag, l_flag, n_flag, q_flag, R_flag, r_flag, S_flag, s_flag;
int t_flag, u_flag, w_flag, one_flag, C_flag, x_flag; 
int to_terminal_flag; 
int dirprint_total;
int regular_file_total;
int totalprint_flag;
int readoption;
int dirprint;
int termwidth = 80;
float blktimes;

static char *pro_name;
static void (*display)(void);
static int (*compare)(const FTSENT *a, const FTSENT *b);

int main
(int argc, char *argv[]){
	int    		   c;
	char 		   dot[] = ".", *dotav[] = { dot, (char *)NULL };
	struct winsize win;
	FTS 		   *ftsp;
    FTSENT         *p, *tmp;

	pro_name = *argv;
	r_flag     = 1;
	C_flag     = 1;
	display    = orderdisplay;
	compare    = cmpname;
	readoption = FTS_PHYSICAL;
	blktimes   = 1;

	/* 
	** determine output to terminal or file
	** meantime if output is not a terminal 
	** set w, 1 flag to 1
	*/

	return 0;
}
