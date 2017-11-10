/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _SQUARE_H_RPCGEN
#define _SQUARE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct square_in {
	long args;
};
typedef struct square_in square_in;

struct square_out {
	long result;
};
typedef struct square_out square_out;

#define SQUARE_PROG 0x3123000
#define SQUARE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define SQUAREPROC 1
extern  square_out * squareproc_1(square_in *, CLIENT *);
extern  square_out * squareproc_1_svc(square_in *, struct svc_req *);
extern int square_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SQUAREPROC 1
extern  square_out * squareproc_1();
extern  square_out * squareproc_1_svc();
extern int square_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_square_in (XDR *, square_in*);
extern  bool_t xdr_square_out (XDR *, square_out*);

#else /* K&R C */
extern bool_t xdr_square_in ();
extern bool_t xdr_square_out ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_SQUARE_H_RPCGEN */
