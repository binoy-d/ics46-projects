// © Michael Shindler -- University of California, Irvine
// This code may not be reposted without the express written permission of the professor teaching this course.  

#ifndef __POINT_HPP
#define __POINT_HPP

#include <ostream>


class Point{
public:
	Point(unsigned row, unsigned col) : r(row), c(col){}
	
	unsigned row() const{ return r; }

	unsigned col() const{ return c; } 

	// Points are cheap to copy, we don't really need
	// these to be const references as parameters, we 
	// could instead pass them directly. 
	bool isToLeftOf (const Point & p) const;

	bool isToRightOf (const Point & p) const;

	bool isAbove  (const Point & p) const;

	bool isBelow(const Point & p) const ;

	// You may or may not have seen operator overloading, and I 
	// do not expect you to know it for ICS 46.
	// The following two functions are for convenience in the 
	// code and allow us to do things like:
	// Point p(3,4);
	// std::cout << p << std::endl;

	friend std::ostream& operator<<(std::ostream& os, const Point & p)
	{
		os << "(" << p.row() << ", " << p.col() << ")"; 
		return os;
	}

	friend bool operator==(const Point & lhs, const Point & rhs)
	{
		return lhs.row() == rhs.row() && lhs.col() == rhs.col() ; 
	}


private:
	unsigned r, c;

};



#endif 