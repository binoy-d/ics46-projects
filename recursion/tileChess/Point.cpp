// © Michael Shindler -- University of California, Irvine
// This code may not be reposted without the express written permission of the professor teaching this course.  

#include "Point.hpp"


bool Point::isToLeftOf(const Point & p) const{
	// this is to the left of point p if they are
	// in the same row and p.c == this->c + 1
	return r == p.r and c + 1 == p.c;
}

bool Point::isToRightOf(const Point & p) const{
	return r == p.r and c - 1 == p.c;
}

bool Point::isAbove(const Point & p) const{
	return r + 1 == p.r and c == p.c;
}

bool Point::isBelow(const Point & p) const{
	return r - 1 == p.r and c == p.c;
}
