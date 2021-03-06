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
    Copyright (C) 2012 Sebastian Pancratz

******************************************************************************/

#include "fq_poly.h"

void _fq_poly_clear(fq_struct *v, long len)
{
    long i;

    for (i = 0; i < len; i++)
        fq_clear(v + i);

    flint_free(v);
}

void fq_poly_clear(fq_poly_t poly)
{
    if (poly->coeffs)
    {
        _fq_poly_clear(poly->coeffs, poly->alloc);
    }
}
