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

    Copyright (C) 2008, 2009 William Hart

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

void
fmpz_poly_scalar_mul_ui(fmpz_poly_t poly1, const fmpz_poly_t poly2, ulong x)
{
    long i;

    /* Either scalar or input poly is zero */
    if ((x == 0) || (poly2->length == 0))
    {
        fmpz_poly_zero(poly1);
        return;
    }

    /* Special case, multiply by 1 */
    if (x == 1)
    {
        fmpz_poly_set(poly1, poly2);
        return;
    }

    fmpz_poly_fit_length(poly1, poly2->length);

    for (i = 0; i < poly2->length; i++)
        fmpz_mul_ui(poly1->coeffs + i, poly2->coeffs + i, x);

    _fmpz_poly_set_length(poly1, poly2->length);
}
