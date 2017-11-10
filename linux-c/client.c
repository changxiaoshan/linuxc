#include "square.h"
int main(int argc,char **argv)
{
	CLIENT *cl;
	square_in in;
	square_out *outp;
	cl=clnt_create(argv[1],SQUARE_PROG,SQUARE_VERS,"tcp");
	in.args=atol(argv[2]);
	outp=squareproc_1(&in,cl);
	printf("%ld",outp->result);
	return 0;
}
