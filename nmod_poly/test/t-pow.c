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

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, j, result;
    flint_rand_t state;
    flint_randinit(state);

    printf("pow....");
    fflush(stdout);

    /* Check powering against naive method */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        nmod_poly_t a, b, c;
        mp_limb_t n = n_randtest_not_zero(state);
        long e;

        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(c, n);
        nmod_poly_randtest(a, state, n_randint(state, 30));
        e = n_randint(state, 20);

        nmod_poly_pow(b, a, e);
        
        nmod_poly_set_coeff_ui(c, 0, 1);
        for (j = 0; j < e; j++)
            nmod_poly_mul(c, c, a);

        result = (nmod_poly_equal(b, c) 
            || (a->length == 0 && e == 0 && c->length == 1 && c->coeffs[0] == 1));
        if (!result)
        {
            printf("FAIL:\n");
            printf("a->length = %ld, n = %lu, exp = %ld\n", a->length, a->mod.n, e);
            nmod_poly_print(a), printf("\n\n");
            nmod_poly_print(b), printf("\n\n");
            nmod_poly_print(c), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(c);
    }

    /* Check aliasing */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        nmod_poly_t a, b, c;
        mp_limb_t n = n_randtest_not_zero(state);
        long e;

        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(c, n);
        nmod_poly_randtest(a, state, n_randint(state, 30));
        e = n_randint(state, 20);

        nmod_poly_pow(b, a, e);
        
        nmod_poly_set(c, a);
        nmod_poly_pow(c, c, e);
        
        result = (nmod_poly_equal(b, c));
        if (!result)
        {
            printf("FAIL:\n");
            printf("a->length = %ld, n = %lu, exp = %ld\n", a->length, a->mod.n, e);
            nmod_poly_print(a), printf("\n\n");
            nmod_poly_print(b), printf("\n\n");
            nmod_poly_print(c), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(c);
    }

    flint_randclear(state);

    printf("PASS\n");
    return 0;
}
