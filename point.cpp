/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#include "point.h"
#include <cassert>

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Point::Point(float x, float y) : x(0.0), y(0.0),
                                 check(false), dead(false), wrap(false)
{
   setX(x);
   setY(y);
}

/*******************************************
 * POINT : SET X
 * Set the x position if the value is within range
 *******************************************/
void Point::setX(float x)
{
   assert(xMin < xMax);

   // wrap as necessary
   if (wrap)
   {
      this->x = x;
      while (this->x > xMax)
         this->x -= (xMax - xMin);
      while (this->x < xMin)
         this->x += (xMax - xMin);
   }

   // trivial non-checking assignment
   else if (!check || (x >= xMin && x <= xMax))
      this->x = x;

   // of the screen
   else
      dead = true;
}

/********************************************
 * POINT : Assignmenet
 *******************************************/
const Point & Point :: operator = (const Point & rhs)
{
   x        = rhs.x;
   y        = rhs.y;
   check    = rhs.check;
   dead     = rhs.dead;
   wrap     = rhs.wrap;

   return *this;
}

/*******************************************
 * POINT : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Point::setY(float y)
{
   assert(yMin < yMax);

   // wrap as necessary
   if (wrap)
   {
      this->y = y;
      while (this->y > yMax)
         this->y -= (yMax - yMin);
      while (this->y < yMin)
         this->y += (yMax - yMin);
   }

   // trivial non-checking assignment
   else if (!check || (y >= yMin && y <= yMax))
      this->y = y;

   // of the screen
   else
      dead = true;
   
}

/******************************************
 * POINT insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Point & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*******************************************
 * POINT extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Point & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}