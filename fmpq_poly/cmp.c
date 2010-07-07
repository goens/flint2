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
    Copyright (C) 2010 William Hart

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpq_poly.h"

// Compares the two non-zero polynomials, assuming they have the same degree.
int _fmpq_poly_cmp(const fmpz * lpoly, const fmpz_t lden, const fmpz * rpoly, const fmpz_t rden, const ulong len)
{
    ulong ans, i;
    fmpz_t lcoeff, rcoeff;
    
    i = len - 1UL;
    if (fmpz_equal(lden, rden))
    {
        while ((i != 0) && fmpz_equal(lpoly + i, rpoly + i))
            i--;
        ans = fmpz_cmp(lpoly + i, rpoly + i);
    }
    else if (*lden == 1)  /* Here rden exceeds 1 */
    {
        fmpz_init(lcoeff);
        fmpz_mul(lcoeff, lpoly + i, rden);
        while (i && fmpz_equal(lcoeff, rpoly + i))
            fmpz_mul(lcoeff, lpoly + (--i), rden);
        ans = fmpz_cmp(lcoeff, rpoly + i);
        fmpz_clear(lcoeff);
    }
    else if (*rden == 1)  /* Here lden exceeds 1 */
    {
        fmpz_init(rcoeff);
        fmpz_mul(rcoeff, rpoly + i, lden);
        while (i && fmpz_equal(rcoeff, lpoly + i))
            fmpz_mul(rcoeff, rpoly + (--i), lden);
        ans = fmpz_cmp(lpoly + i, rcoeff);
        fmpz_clear(rcoeff);
    }
    else  /* Here both lden, rden exceed 1 */
    {
        fmpz_init(lcoeff);
        fmpz_init(rcoeff);
        fmpz_mul(lcoeff, lpoly + i, rden);
        fmpz_mul(rcoeff, rpoly + i, lden);
        while (i && fmpz_equal(lcoeff, rcoeff))
        {
            i--;
            fmpz_mul(lcoeff, lpoly + i, rden);
            fmpz_mul(rcoeff, rpoly + i, lden);
        }
        ans = fmpz_equal(lcoeff, rcoeff);
        fmpz_clear(lcoeff);
        fmpz_clear(rcoeff);
    }
    return ans;
}

int fmpq_poly_cmp(const fmpq_poly_t left, const fmpq_poly_t right)
{
    if (left == right)
        return 0;
    
    if (left->length < right->length)
        return -1;
    else if (left->length > right->length)
        return 1;
    else if (left-> length == 0)
        return 0;
    else
        return _fmpq_poly_cmp(left->coeffs, left->den, right->coeffs, right->den, left->length);
}
