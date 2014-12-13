/*
 * The program solves the following system of two 
 * first order differential equations, which describe 
 * the motion of a pendulum on verticaly driven pivot
 * 
 * The step-size of the integrator is automatically 
 * adjusted by the controller to maintain the 
 * requested accuracy
 */

#define PI 3.14159265359

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int func (double t, const double y[], double f[], void *params);

int main (void) 
{
	size_t neqs = 2;					/* number of equations */
	double eps_abs = 1.e-8, 
		eps_rel = 0.;					/* desired precision */
	double stepsize = 1e-6;				/* initial integration step */
	int status;
	double t = 0., t1 = 100.;			/* time interval */
	
	double ommega = 150.;				/* ommega for stable oscillation */
	double y[2] = { 0.99 * PI, 0. };	/* initial conditions (phi, phy dot) */
	
	/*
	 * Explicit embedded Runge-Kutta-Fehlberg (4,5) method. 
	 * This method is a good general-purpose integrator.
	 */
	gsl_odeiv2_step    *s = gsl_odeiv2_step_alloc 
					(gsl_odeiv2_step_rkf45, neqs);
	gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs, 
					eps_rel);
	gsl_odeiv2_evolve  *e = gsl_odeiv2_evolve_alloc (neqs);

	gsl_odeiv2_system sys = {func, NULL, neqs, &ommega};

	/*
	 * Evolution loop 
	 */
	while (t < t1)
	{
		status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t,
			t1, &stepsize, y);

		if (status != GSL_SUCCESS) {
			printf ("Troubles: % .5e  % .5e  % .5e\n", 
				t, y[0], y[1]);
			break;
		}

	printf ("% .5e  % .5e  % .5e\n", t, y[0], y[1]);
  }

	gsl_odeiv2_evolve_free (e);
	gsl_odeiv2_control_free (c);
	gsl_odeiv2_step_free (s);

	return 0;
}
