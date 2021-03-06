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
#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

mp_bitcnt_t _fmpz_poly_2norm_normalised_bits(const fmpz * poly, long len)
{
   fmpz_t norm;
   mp_bitcnt_t bits;
   fmpz_init(norm);

	_fmpz_poly_2norm(norm, poly, len);

	bits = fmpz_bits(norm);
	fmpz_clear(norm);
   
   return bits - fmpz_bits(poly + len - 1) + 1;
}
