#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "gameObjects.h"

#include <cassert>
#include <math.h>
#include <vector>

#define PI 3.14159265

/******************************************************************************
 * GAMEOBJECT::CONSTRUCTOR
 * Sets the defaults values of a game object.
 *****************************************************************************/
GameObject::GameObject() { 
   p = Point();
   p = Point(p.getXMax()/2, p.getYMax()/2); 
   dx = 0.0;
   dy = 0.0;
   dr = 0;
   direction = 0;
   sizeScalar = 1.0;
   isValid = true;
}

/******************************************************************************
 * GAMEOBJECT::MOVE
 * Moves the game object based on its delta x and delta y
 *****************************************************************************/
void GameObject::move() {
   p.addX(dx);
   p.addY(dy);
   
   direction += dr;
   if (direction > 359)
      direction = 0 + direction - 360;
   
   if (p.getX() < p.getXMin())
      p.setX(p.getXMax() - std::abs(p.getX()));
      
   if (p.getX() > p.getXMax())
      p.setX(p.getXMin() + (p.getX() - p.getXMax()));      
      
   if (p.getY() < p.getYMin())
      p.setY(p.getYMax() - std::abs(p.getY()));
      
   if (p.getY() > p.getYMax())
      p.setY(p.getYMin() + (p.getY() - p.getYMax()));
}

/******************************************************************************
 * GAMEOBJECT::GET BOUNDS
 * Gets the current bounds on the screen of a game object.
 *****************************************************************************/
std::vector<Point> GameObject::getBounds() {
   std::vector<Point> bounds;
   for (int i = 0; i < points.size(); i++) {
      Point temp = Point(p);
      temp.addX((int)(sizeScalar * points[i].getX()));
      temp.addY((int)(sizeScalar * points[i].getY()));
      rotate(temp, p, direction);
      bounds.push_back(temp);
   }
   return bounds;
}

/******************************************************************************
 * SHIP::CONSTRUCTOR
 * Creates the ship with a default position of 90 degrees and a scalar of 4.0
 *****************************************************************************/
Ship::Ship() : GameObject() {
   direction = 90;
   sizeScalar = 3.0;
   
   bow = Point(6, 0);
   starboard = Point(-3, -3);
   port = Point(-3, 3);
   
   points.push_back(bow);           // Bow
   points.push_back(starboard);     // Starboard
   points.push_back(Point(-2, 0));  // Stern
   points.push_back(port);          // Port
}

/******************************************************************************
 * SHIP::DRAW
 * Draws the ship based on it's position, direction, and size scalar.
 *****************************************************************************/
void Ship::draw() const {
   drawShape(p, direction, points, sizeScalar);
}

/******************************************************************************
 * SHIP::ROTATE
 * Rotates the ship by 10 degrees left or right depending on bool that is
 * passed in paramters. Makes sure the degrees stay 0 <= direction <= 359
 *****************************************************************************/
void Ship::turn(bool left) {
   if (left) {
      direction += 10;
      if (direction > 359)
         direction -= 360;
   } else {
      direction -= 10;
      if (direction < 0)
         direction += 360;
   }
   
   assert(direction >= 0 && direction <= 360);
}

/******************************************************************************
 * SHIP::ACCELERATE
 * Accelerates the ship positively (direction the ship is facing) if positive
 * is true, otherwise negatively (opposite direction the ship is facing).
 *****************************************************************************/
void Ship::accelerate(bool positive) {      
   float x = 0.2 * cos(direction * PI / 180);
   float y = 0.2 * sin(direction * PI / 180);
   
   dx += (positive) ? x : -x;
   dy += (positive) ? y : -y;
}

/******************************************************************************
 * SHIP::GET BOW
 * Gets the current position of the bow.
 *****************************************************************************/
Point Ship::getBow() {
   Point temp = Point(p);
   temp.addX((int)(sizeScalar * bow.getX()));
   temp.addY((int)(sizeScalar * bow.getY()));
   rotate(temp, p, direction);
   return temp;
}

/******************************************************************************
 * SHIP::GET STARBOARD
 * Gets the current position of the starboard.
 *****************************************************************************/
Point Ship::getStarboard() {
   Point temp = Point(p);
   temp.addX((int)(sizeScalar * starboard.getX()));
   temp.addY((int)(sizeScalar * starboard.getY()));
   rotate(temp, p, direction);
   return temp;
}

/******************************************************************************
 * SHIP::GET PORT
 * Gets the current position of the port.
 *****************************************************************************/
Point Ship::getPort() {
   Point temp = Point(p);
   temp.addX((int)(sizeScalar * port.getX()));
   temp.addY((int)(sizeScalar * port.getY()));
   rotate(temp, p, direction);
   return temp;
}

/******************************************************************************
 * BULLET:CONSTRUCTOR
 * Constructs a default bullet based on a ship and it's current velocity,
 *****************************************************************************/
Bullet::Bullet(Ship* ship) {
   p = Point(ship->getBow());
   direction = ship->getDirection();
   
   float x = 10.0 * cos(direction * PI / 180);
   float y = 10.0 * sin(direction * PI / 180);
   
   dx = ship->getDx() + x;
   dy = ship->getDy() + y;
   
   distanceTraveled = 0.0;
}

/******************************************************************************
 * BULLET:DRAW
 * Draws a dot at the bullets position.
 *****************************************************************************/
void Bullet::draw() const {
   drawDot(p);
}

/******************************************************************************
 * BULLET:MOVE
 * Overwrites the default move for a GameObject, keeps track of the bullet's
 * total distance traveled. Set's bullet inactive after it's moved 90% of the 
 * screen.
 *****************************************************************************/
void Bullet::move() {
   p.addX(dx);
   p.addY(dy);
   
   float magnitude = std::sqrt((dx * dx) + (dy * dy));
   distanceTraveled += magnitude;
   
   if (distanceTraveled >= ((float)p.getXMax() * 0.9))
      isValid = false;
      
   if (p.getX() < p.getXMin())
      p.setX(p.getXMax() - std::abs(p.getX()));
      
   if (p.getX() > p.getXMax())
      p.setX(p.getXMin() + (p.getX() - p.getXMax()));      
      
   if (p.getY() < p.getYMin())
      p.setY(p.getYMax() - std::abs(p.getY()));
      
   if (p.getY() > p.getYMax())
      p.setY(p.getYMin() + (p.getY() - p.getYMax()));
}

/******************************************************************************
 * ASTEROID::CONSTRUCTOR
 * Builds the default asteroid.
 *****************************************************************************/
Asteroid::Asteroid() : GameObject() {
   points.push_back(Point(8 + random(-2, 2), 8 + random(-2, 2)));
   points.push_back(Point(0 + random(-2, 2), 10 + random(-2, 2)));
   points.push_back(Point(-2 + random(-2, 2), 6 + random(-2, 2)));
   points.push_back(Point(-6 + random(-2, 2), 4 + random(-2, 2)));
   points.push_back(Point(-8 + random(-2, 2), -4 + random(-2, 2)));
   points.push_back(Point(-3 + random(-2, 2), -9 + random(-2, 2)));
   points.push_back(Point(4 + random(-2, 2), -10 + random(-2, 2)));
   points.push_back(Point(8 + random(-2, 2), -5 + random(-2, 2)));
   points.push_back(Point(10 + random(-2, 2), 2 + random(-2, 2)));
}

/******************************************************************************
 * ASTEROID::DRAW
 * Draws the asteroid using it's points.
 *****************************************************************************/
void Asteroid::draw() const {
   drawShape(p, direction, points, sizeScalar);
}

/******************************************************************************
 * LARGE ASTEROID::CONSTRUCTOR
 * Creates a large asteroid with the given position and a random velocity.
 *****************************************************************************/
LargeAsteroid::LargeAsteroid(Point pos) : Asteroid() {
   dr = 2;
   dx = random(-2.0, 2.0);
   dy = random(-2.0, 2.0);
   sizeScalar = 4.0;
   p = Point(pos);
}

/******************************************************************************
 * MEDIUM ASTEROID::CONSTRUCTOR
 * Creates a medium asteroid with a given velocity and position.
 *****************************************************************************/
MediumAsteroid::MediumAsteroid(Point pos, float deltaX, float deltaY) : 
                               Asteroid() {
   p = Point(pos);
   dr = 5;
   dx = deltaX;
   dy = deltaY;
   sizeScalar = 3.0;
}

/******************************************************************************
 * SMALL ASTEROID::CONSTRUCTOR
 * Creates a small asteroid with a given velocity and position.
 *****************************************************************************/
SmallAsteroid::SmallAsteroid(Point pos, float deltaX, float deltaY) : 
                             Asteroid() {
   p = Point(pos);
   dr = 10;
   dx = deltaX;
   dy = deltaY;
   sizeScalar = 2.0;
}

/******************************************************************************
 * LIFESHIP::CONSTRUCTOR
 * Super simple version, rotation set to 90, small version of the user ship
 *****************************************************************************/
LifeShip::LifeShip() {
   direction = 90;
   sizeScalar = 1.7;
   
   bow = Point(6, 0);
   starboard = Point(-3, -3);
   port = Point(-3, 3);
   
   points.push_back(bow);           // Bow
   points.push_back(starboard);     // Starboard
   points.push_back(Point(-2, 0));  // Stern
   points.push_back(port);          // Port
   setPosition(6.0, 482.0);
}

/******************************************************************************
 * LIFESHIP::SET POSITION
 * just sets the point p to what is given in parameters
 *****************************************************************************/
void LifeShip::setPosition(float p1, float p2) {
   p = Point(p1, p2);
}

/******************************************************************************
 * LIFESHIP::ADD X
 * Pretty simple, just adds to the x
 *****************************************************************************/
void LifeShip::addX(float x) {
   p.addX(x);
}

/******************************************************************************
 * LIFESHIP::ADD Y
 * Pretty simple, just adds to the y
 *****************************************************************************/
void LifeShip::draw() const {
   drawShape(p, direction, points, sizeScalar, color);
}