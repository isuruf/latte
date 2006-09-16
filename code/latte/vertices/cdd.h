// This is a -*- C++ -*- header file.

/* cdd.h -- Computation of all vertex cones via CDD

   Copyright 2002 Raymond Hemmecke, Ruriko Yoshida
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

#ifndef VERTICES_CDD__H
#define VERTICES_CDD__H

void createCddIneFile(listVector*, int);
void createCddExtFile(listVector*, int);
void createCddIneLPFile(listVector* matrix, int numOfVars, vec_ZZ & cost);
listVector* createListOfInequalities(listVector*, int);
listCone* readCddExtFile();
rationalVector* ReadLpsFile(int numOfVars, bool verbose = true);
listCone* readCddEadFile(listCone*, int);
listCone* readCddEadFileFromVrep(listCone* cones, int numOfVars);
listCone* computeVertexCones(char*, listVector*, int);
rationalVector* LP(listVector* matrix, vec_ZZ& cost, int numOfVars,
		   bool verbose = true);
listCone* CopyListCones(listCone* RudyCones, int numOfVars, 
			rationalVector* Opt_vertex);
listCone* CopyListCones(listCone* RudyCones, int numOfVars); 
listCone* computeVertexConesFromVrep(char* fileName, int numOfVars);
listCone* computeVertexConesViaLrs(char* fileName, listVector* matrix, 
				   int numOfVars);
void CreatExtEadFile();

#endif
