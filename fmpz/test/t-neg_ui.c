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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

int
main(void)
{
    int i, result;

    flint_rand_t state;
    flint_randinit(state);

    printf("neg_ui....");
    fflush(stdout);

    for (i = 0; i < 10000 * flint_test_multiplier(); i++)
    {
        fmpz_t a, b;
        ulong c;

        c = n_randtest(state);

        fmpz_init(a);
        fmpz_init(b);

        fmpz_set_ui(a, c);
        fmpz_neg(a, a);

        fmpz_neg_ui(b, c);

        result = fmpz_equal(a, b);
        if (!result)
        {
            printf("FAIL:\n");
            printf("c = %lu\n", c);
            printf("a = "); fmpz_print(a); printf("\n");
            printf("b = "); fmpz_print(b); printf("\n");
            abort();
        }

        fmpz_clear(a);
        fmpz_clear(b);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
