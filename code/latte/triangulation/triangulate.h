// This is a -*- C++ -*- header file.

/* triangulate.h -- Compute triangulations.

   Copyright 2006 Matthias Koeppe

   This file is part of LattE.
   
   LattE is free software; you can redistribute it and/or modify it
   under the terms of the version 2 of the GNU General Public License
   as published by the Free Software Foundation.

   LattE is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with LattE; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*/

#ifndef TRIANGULATION_TRIANGULATE__H
#define TRIANGULATION_TRIANGULATE__H

#include "cone.h"
#include "barvinok/barvinok.h"

BarvinokParameters::TriangulationType
triangulation_type_from_name(const char *name);

/* Parse a standard command-line option related to triangulations
   and fill the correspodingin slots in PARAMS.
   Return whether a supported option was found and handled.
*/
bool
parse_standard_triangulation_option(const char *arg,
				    BarvinokParameters *params);

/* CONE must be a full-dimensional pointed cone given by its minimal
   generators (rays).
   
   Triangulate CONE using some method specified in PARAMS, discarding
   lower-dimensional cones.  Return a linked list of freshly allocated
   cones.
   
   CONE is not consumed.
*/
listCone *
triangulateCone(listCone *cone, int numOfVars,
		BarvinokParameters *params);



#endif
