#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include <vector>     // for drawShape
#include "point.h"    // Where things are drawn
using std::string;

// Brought to public view to be used in GameObject classes.
void rotate(Point & point, const Point & origin, int rotation);

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned int number);

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 ************************************************************************/
void drawText(const Point & topLeft, const char * text);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point & center, int radius);

/************************************************************************
 * DRAW POLYGON
 * Draw a polygon from a given location (center) of a given size (radius).
 *************************************************************************/
void drawPolygon(const Point & center, int radius, int points, int rotation);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Point & point);

/************************************************************************
 * DRAW SHAPE
 * Draws a shape on the screen using vector of points.
 *  INPUT point    The center of the shape
 *        rotation Which direction it is pointed
 *        points   The vector of points to use.
 *        scalar   Scalar for shape size (default is 1.0).
 *        color    Optional float to change color of shape (0.0 to 1.0)
 *************************************************************************/
void drawShape(Point center, int rotation, std::vector<Point> points,
               float scalar = 1.0, float color = 1.0);

/************************************************************************
 * DRAW Ship
 * Draw the spaceship on the screen
 *************************************************************************/
void drawShip(const Point & point, int rotation, float scalar = 1.0);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);

/************************************************************************
 * DRAW STARS
 * Given a vector of points, this prints one dot at each point
 *************************************************************************/
void drawStars(std::vector<Point> backgroundStars);

/*************************************************************************
 * DRAW STRING
 * Draw string using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The string to be displayed
 *          color     Optional float to change color of text
 ************************************************************************/
void drawString(const Point & topLeft, const string text, float color = 1.0);

#endif // UI_DRAW_H