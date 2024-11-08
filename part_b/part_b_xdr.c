/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "part_b.h"

bool_t
xdr_input (XDR *xdrs, input *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->path, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->number1))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->number2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_output (XDR *xdrs, output *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->result, ~0))
		 return FALSE;
	return TRUE;
}
