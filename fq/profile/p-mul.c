/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Andres Goens

******************************************************************************/
#include "fq.h"
#include <stdio.h>
#include "profiler.h"

#ifndef REPS
#define REPS 1000000
#endif

int
main()
{
    flint_rand_t state;
    timeit_t t0;

    long i;
    fmpz_t p;
    long d;
    fq_ctx_t ctx;
    fq_t c;
    fq_struct a[REPS],b[REPS];

    flint_randinit(state);
    fmpz_init(p);
    fmpz_set_ui(p, n_randprime(state, 2+ n_randint(state,3),1));
    d = n_randint(state,10)+1;
    fq_ctx_init_conway(ctx,p,d,"a",PADIC_TERSE);

    padic_poly_init2(&a[0],d);
    padic_poly_init2(&b[0],d);
    padic_poly_init2(c,d);

    fq_randtest_not_zero(&a[0],state,ctx);
    fq_randtest_not_zero(&b[0],state,ctx);

    printf("MUL benchmark:single repeated multiplication: \n");
    timeit_start(t0);
    for(i=0;i<REPS;i++) fq_mul(c,a,b,ctx);
    timeit_stop(t0);
    printf ( " cpu = %ld ms, wall = %ld ms \n " , t0->cpu , t0->wall );

    printf("random multiplications: \n");

    for(i=0;i<REPS;i++)
    {
        if(i != 0) padic_poly_init2(&a[i],d);
        if(i != 0) padic_poly_init2(&b[i],d);
        fq_randtest(&a[i],state,ctx);
        fq_randtest(&b[i],state,ctx);
    }

    timeit_start(t0);
    for(i=0;i<REPS;i++) fq_mul(c,a,b,ctx);
    timeit_stop(t0);
    printf ( " cpu = %ld ms, wall = %ld ms \n " , t0->cpu , t0->wall );


    return 0;

}
