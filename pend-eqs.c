/*
 * The function provides the RHS of the two 
 * first order differential equations, which describe 
 * the ardial mass distrubution inside white dwarf star
 *
 */

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int func (double t, const double y[], double f[], 
	  void *params) 
{
	/*
	 * y[0] - phi
	 * y[1] - X
	 */
	double ommega = *(double *) params;

	f[0] = y[1];
	f[1] = -(1 - 0.01 * ommega * ommega * sin(ommega * t)) * sin(y[0]);

	return GSL_SUCCESS;
}

