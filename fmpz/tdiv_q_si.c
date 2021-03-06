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

    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

void
fmpz_tdiv_q_si(fmpz_t f, const fmpz_t g, long h)
{
    fmpz c1 = *g;
    long c2 = h;

    if (h == 0)
    {
        printf("Exception (fmpz_tdiv_q_si). Division by zero.\n");
        abort();
    }

    if (!COEFF_IS_MPZ(c1))      /* g is small */
    {
        fmpz_set_si(f, c1 / c2);
    }
    else                        /* g is large */
    {
        __mpz_struct *mpz_ptr = _fmpz_promote(f);

        if (c2 > 0)
        {
            mpz_tdiv_q_ui(mpz_ptr, COEFF_TO_PTR(c1), c2);
        }
        else
        {
            mpz_tdiv_q_ui(mpz_ptr, COEFF_TO_PTR(c1), -(ulong) c2);
            mpz_neg(mpz_ptr, mpz_ptr);
        }
        _fmpz_demote_val(f);    /* division by h may result in small value */
    }
}
