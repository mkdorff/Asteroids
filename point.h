/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#ifndef POINT_H
#define POINT_H

#include <iostream> // needed for insertion and extraction operator

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0),
                        check(false), dead(false), wrap(false)   {}
   Point(bool check)  : x(0.0), y(0.0),
                        check(check), dead(false), wrap(false)   {}
   Point(float x, float y);
   Point(const Point & point) { *this = point; }

   // getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }
   bool  getCheck()   const { return check;          }
   bool  isDead()     const { return dead;           }
   float getXMin()    const { return xMin;           }
   float getXMax()    const { return xMax;           }
   float getYMin()    const { return yMin;           }
   float getYMax()    const { return yMax;           }
   bool  getWrap()    const { return wrap;           }

   // setters
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }
   void setCheck(bool f)    { check = f;             }
   void setWrap(bool f)     { wrap = f;              }
   void kill()              { dead = true;           }
   void resurrect()         { dead = false;          }
   const Point & operator = (const Point & rhs);

private:
   float x;           // horizontal position
   float y;           // vertical position
   bool  check;       // do bounds checking
   bool  dead;        // have we exceed our bounds?
   bool  wrap;        // do we wrap around the edge?
   static float xMin; // minimum extent of the x position
   static float xMax; // maximum extent of the x position
   static float yMin; // minimum extent of the y position
   static float yMax; // maximum extent of the y position
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H