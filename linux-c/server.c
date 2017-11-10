#include "square.h"
square_out * squareproc_1_svc(square_in *inp,struct svc_req *rqstp)
{
	static square_out out;
	out.result=inp->args*inp->args;
	return &out;	
}
