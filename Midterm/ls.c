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
	if (isatty(STDOUT_FILENO)) {
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == 0 && win.ws_col > 0){
			termwidth = win.ws_col;
		}
		to_terminal_flag = q_flag = 1;
	} else{
		to_terminal_flag = 0;
		w_flag = one_flag = 1;
	}

	while((c = getopt(argc, argv, "1ACFRSacdfhiklnqrstuwx")) != -1)
		switch(c){
			case 'A':
				A_flag = 1;
				break;
			case 'a':
				a_flag = 1;
				readoption = FTS_PHYSICAL|FTS_SEEDOT;
				break;
			case 'c':
				c_flag = 1;
				u_flag = 0;
				compare = cmptimestch;
				break;
			case 'd':
				d_flag = 1;
				R_flag = 0;
				break;
			case 'F':
				F_flag = 1;
				break;
			case 'f':
				f_flag = 1;
				readoption = FTS_PHYSICAL|FTS_SEEDOT;
				break;
			case 'h':
				h_flag = 1;
				k_flag = 0;
				break;
			case 'i':
				i_flag = 1;
				break;
			case 'k':
				k_flag = 1;
				h_flag = 0;
				break;
			case 'l':
				l_flag = 1;
				one_flag = 0;
				n_flag = 0;
				C_flag = 0;
				x_flag = 0;
				display = longdisplay;
				break;
			case 'n':
				n_flag = 1;
				l_flag = 0;
				one_flag = 0;
				C_flag = 0;
				x_flag = 0;
				display = longdisplay;
				break;
			case 'q':
				q_flag = 1;
				w_flag = 0;
				break;
			case 'R':
				R_flag = 1;
				d_flag = 0;
				break;
			case 'r':
				r_flag = -1;
				break;
			case 'S':
				compare = cmpsize;
				break;
			case 's':
				s_flag = 1;
				break;
			case 't':
				compare = cmptimemdf;
				break;
			case 'u':
				u_flag = 1;
				c_flag = 0;
				compare = cmptimelacc;
				break;
			case 'w':
				w_flag = 1;
				q_flag = 0;
				break;
			case '1':
				n_flag = 1;
				l_flag = 0;
				one_flag = 0;
				C_flag = 0;
				x_flag = 0;
				display = onedisplay;
				break;
			case 'C':
				n_flag = 0;
				l_flag = 0;
				one_flag = 0;
				C_flag = 1;
				x_flag = 0;
				display = orderdisplay;
				break;
			case 'x':
				n_flag = 0;
				l_flag = 0;
				one_flag = 0;
				C_flag = 0;
				x_flag = 1;
				display = orderdisplay;
				break;
			default:
           	fprintf(stderr, "Usage: %s [−AaCcdFfhiklnqRrSstuwx1] [file ...]\n",
           	 pro_name);
           	exit(EXIT_FAILURE);
		}

	return 0;
}
