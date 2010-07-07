/*
 * PolytopeValuation.h
 *
 *  Created on: Jun 25, 2010
 *      Author: Brandon Dutra and Gregory Pinto
 */

#ifndef POLYTOPEVALUATION_H_
#define POLYTOPEVALUATION_H_

#include <cstdlib>
#include <iostream>
#include <string>

#include "barvinok/barvinok.h"
#include "ReadPolyhedron.h"
#include "triangulation/triangulate.h"
#include "convert.h"
#include "print.h"
#include "gnulib/progname.h"
#include "barvinok/dec.h"
#include "valuation/PolytopeValuation.h"
#include <NTL/vec_ZZ.h>
#include <NTL/vec_RR.h>
#include "rational.h"
#include "cone.h"

using namespace std;

/*
 * Constructing:
 * 1) Pass in a Polyhedron is you know the polytope is full dim.
 * 2) Pass in ConeType::VertexRayCones is the cones represent the vertex-ray information of a polytope.
 * 3) Pass in ConeType::TriangulatedCones if the cones represent a triangulation of the polytope (may or may not be unimodular).
 *
 * Finding Volume:
 * 1) Call findVolume(DeterminantVolume) if you want to use the Determinant method. Will convert first
 * 		convert  vertexRayCones into a triangulation if needed.
 * 2) Call findVolume(LawrenceVolume) if you want to use the Lawrence method. Assumes you
 *      have constructed the object with ConeType::TriangulatedCones
 *
 */


class PolytopeValuation
{
	listCone * vertexRayCones;		//list of  vertex-ray pairs.
	BarvinokParameters parameters; //Barvinok Parameters.
	listCone * polytopeAsOneCone;	//From poly, create one code with vertex=[0,0...0], rays={[1, v] | v is a vertex of the polytope}
	listCone * triangulatedPoly;	//The triangulation of polytopeAsOneCone.
	int numOfVars;
	bool freeVertexRayCones, freePolytopeAsOneCone, freeTriangulatedPoly; //denotes if we made these objects (and should free them) or if they were passed in.

public:
	typedef enum {DeterminantVolume, LawrenceVolume} VolumeType;
	typedef enum {VertexRayCones, TriangulatedCones} ConeType;

	PolytopeValuation(Polyhedron *p, BarvinokParameters &bp);
	PolytopeValuation(listCone *cones, ConeType coneType, int numofvars, BarvinokParameters &bp);
	virtual ~PolytopeValuation();


	// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

	void convertToOneCone(); //convert from poly to polytopeAsOneCone
	RationalNTL findVolumeUsingDeterminant(const listCone * oneSimplex) const;
	RationalNTL findVolumeUsingLawrence();
	RationalNTL findVolume(const VolumeType v);		 //finds the volume of the Polyhedron.
	ZZ static factorial(const int n);
	void printLawrenceVolumeFunction();	//Finds the Lawrence rational function for the volume. triangulates vertexRayCones if needed.
	void triangulatePolytopeCone();  //convert polytopeAsOneCone to triangulatedPoly
	void triangulatePolytopeVertexRayCone(); //convert vertexRayCones to triangulatedPoly using decomposeCones

};

#endif /* POLYTOPEVALUATION_H_ */
