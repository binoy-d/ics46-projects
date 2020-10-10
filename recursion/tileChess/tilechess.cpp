// © Michael Shindler -- University of California, Irvine
// This code may not be reposted without the express written permission of the professor teaching this course.  

/*
 * Recursively tiling a 2^n x 2^n chessboard with one piece removed.
 * There are four types of tiles:  
 	+--+		   +--+			+--+--+		+--+--+
 	|X |		   |X |        	|X |  |     |X |  |
 	+--+--+		+--+--+			+--+--+		+--+--+
	|  |  |     |  |  |		   	   |  |     |  |
	+--+--+     +--+--+            +--+     +--+

	Type 1		Type 2			Type 3		Type 4

Each referenced as being at location denoted in the X.
Note that for Type i, the missing piece of this tile, 
compared to a full 2x2 square, is quadrant i.

ChessBoard is 1..2^n x 1..2^n, with (1,1) in the top-left. 
 */

#include <cmath>
#include <fstream> 
#include <iostream>
#include "Point.hpp"

// prints a tiling of a 2^n x 2^n chessboard with L-shaped pieces.
// The board's upper-left coordinate is the first parameter and 
// the missing piece is identified by the third parameter. 
void printTiling(Point topLeft, unsigned n, Point missingPiece);

// Places a tile of the given type with the identifying square
// in the designated location. 
void placeTile(unsigned type, Point loc);

// returns which quadrant the missing piece is in.
// Assume it's in exactly one (that's always true) and n > 0
// Because this means the chessboard has an even number of 
// rows & cols, this means we don't have to worry about the
// corner case where a missing piece is on a boundary.
// As per math class, quadrant 1 is top-right, q2 is top-left
//	q3 is bottom-left, q4 is bottom-right
unsigned whichQuadrant(Point topLeft, unsigned n, Point missingPiece); 

// Gets the top-left of quadrant q from a 2^n x 2^n grid whose
//	top-left point is the first parameter. 
Point getTopLeftOfQuadrant(Point topLeft, unsigned n, unsigned q);

// Gets the "internal" corner of quadrant q from a 2^n x 2^n grid whose
//	top-left point is the first parameter. 
// An internal corner is the Point closest to the center of the grid.
Point getInternalCorner(Point topLeft, unsigned n, unsigned q);


int main()
{
	Point p(3,4);
	std::cout << "For a 4x4 with point " << p << " removed, tiling: " << std::endl;
	printTiling(Point(1,1), 2, p);

	return 0;
}

// For now, this just outputs it.  But this generalizes in case we want to do something else.
// For example, if we were to hook this up to a GUI, we could call the appropriate
//		drawing functions from here. 
void placeTile(unsigned type, Point loc)
{
	std::cout << "Block of type " << type << " at " << loc << std::endl;
}

void printTiling(Point topLeft, unsigned n, Point missingPiece)
{
	if (n == 0 ) return;
	else if (1 == n)
	{	// This is a base case;  a 2x2 with one square removed.
		// Let's find where the missing square is so we know
		// exactly what type to place. 
		if ( missingPiece == topLeft )
		{
			placeTile(2, Point(topLeft.row(), topLeft.col() + 1));

		}
		else if (missingPiece.isToRightOf(topLeft))
		{
			placeTile(1, topLeft);
		}
		else if (missingPiece.isBelow(topLeft))
		{
			placeTile(3, topLeft);
		}
		else
		{
			placeTile(4, topLeft);
		}
		return;
	}

// TODO 
	unsigned missingQuad = whichQuadrant(topLeft, n, missingPiece);
	if(missingQuad == 2){
		Point inCorner = getInternalCorner(topLeft, n, 1);
		placeTile(2, inCorner);
	}
	return; 
}




unsigned whichQuadrant(Point topLeft, unsigned n, Point missingPiece)
{
	unsigned rowBoundary = topLeft.row() + std::pow<unsigned>(2, n-1) - 1; 
	unsigned colBoundary = topLeft.col() + std::pow<unsigned>(2, n-1) - 1; 
	if(missingPiece.row() <= rowBoundary and missingPiece.col() <= rowBoundary)
		return 2;
	else if (missingPiece.row() <= rowBoundary){ // but not col
		return 1;
	}
	else if (missingPiece.col() <= colBoundary){
		return 3;
	}
	else return 4;
}


// Gets the top-left of quadrant q from a 2^n x 2^n grid whose
//	top-left point is the first parameter. 
Point getTopLeftOfQuadrant(Point topLeft, unsigned n, unsigned q)
{
	unsigned adj =  std::pow<unsigned>(2, n-1) ;
	if( q == 2 ){
		return Point(topLeft);
	}
	else if (q == 1 ){
		// Same row as top-left, more columns along.
		return  Point(topLeft.row(), topLeft.col() + adj);
	}
	else if (q == 3 ){
		return  Point(topLeft.row() + adj, topLeft.col());
	}
	else{ // q==4
		return  Point(topLeft.row() + adj, topLeft.col() + adj);
	}
}




// Gets the "internal" corner of quadrant q from a 2^n x 2^n grid whose
//	top-left point is the first parameter. 
// An internal corner is the Point closest to the center of the grid.
Point getInternalCorner(Point topLeft, unsigned n, unsigned q)
{
	// the point (rAdj, cAdj) is the internal corner for quadrant TWO
	unsigned rAdj = topLeft.row() + std::pow<unsigned>(2, n-1) - 1;
	unsigned cAdj = topLeft.col() + std::pow<unsigned>(2, n-1) - 1;
	if (q == 1){
		return Point(rAdj, cAdj+1);
	}
	else if (q == 2){
		return Point(rAdj, cAdj);
	}
	else if (q == 3 ){
		return Point(rAdj + 1, cAdj);
	}
	else{ // q4
		return Point(rAdj+1, cAdj+1);
	}
}
