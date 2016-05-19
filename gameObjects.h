#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H 

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"

enum AsteroidSize { LARGE, MEDIUM, SMALL };

/******************************************************************************
 * CLASS GAMEOBJECT
 * Parent class for any 'object' used in the game
 *****************************************************************************/
class GameObject {
public:
   GameObject();
   virtual ~GameObject()          { }
   virtual void draw() const = 0;
   virtual void move();
   virtual std::vector<Point> getBounds();
   
   Point& getPoint()              { return p;          }
   float  getDx() const           { return dx;         }
   float  getDy() const           { return dy;         }
   float  getSizeScalar()         { return sizeScalar; }
   int    getDirection() const    { return direction;  }
   bool   getIsValid() const      { return isValid;    }
   
   void setDirection(int val)     { direction = val;   }
   void setSizeScalar(float val)  { sizeScalar = val;  }
   void setIsValid(bool val)      { isValid = val;     }
   
protected:
   Point p;
   float dx; // Delta X
   float dy; // Delta Y
   int dr; // Delta rotation
   float sizeScalar;
   int direction; // Degrees
   bool isValid;
   std::vector<Point> points;
};

/******************************************************************************
 * CLASS SHIP
 * Ship the main the user controls
 *****************************************************************************/
class Ship : public GameObject {
public:
   Ship();
   
   virtual void draw() const;
   
   void turn(bool left);
   void accelerate(bool positive);
   
   Point getBow();
   Point getStarboard();
   Point getPort();
   
   static float maxSpeed;  
private:
   Point bow;
   Point starboard;
   Point port;
};

/******************************************************************************
 * CLASS Bullet
 * Bulles that the user shoots
 *****************************************************************************/
class Bullet : public GameObject {
public:
   Bullet(Ship* ship);
   
   virtual void draw() const;
   virtual void move();
   float distanceTraveled; 
};

/******************************************************************************
 * CLASS ASTEROID
 * Parent class for other asteroid sizes
 *****************************************************************************/
class Asteroid : public GameObject {
public:
   Asteroid();
   
   virtual void draw() const;
   virtual AsteroidSize getSize() = 0; 
};

/******************************************************************************
 * CLASS LARGE ASTEROID
 *****************************************************************************/
class LargeAsteroid : public Asteroid {
public: 
   LargeAsteroid();
   LargeAsteroid(Point pos);
   
   virtual AsteroidSize getSize() { return LARGE; }
};

/******************************************************************************
 * CLASS MEDIUM ASTEROID
 *****************************************************************************/
class MediumAsteroid : public Asteroid {
public:
   MediumAsteroid();
   MediumAsteroid(Point pos, float deltaX, float deltaY);
   
   virtual AsteroidSize getSize() { return MEDIUM; }   
};

/******************************************************************************
 * CLASS SMALL ASTEROID
 *****************************************************************************/
class SmallAsteroid : public Asteroid {
public:
   SmallAsteroid();
   SmallAsteroid(Point pos, float deltaX, float deltaY);
   
   virtual AsteroidSize getSize() { return SMALL; }   
};

/******************************************************************************
 * CLASS LIFE SHIP
 * Used to make mini ship object to display howmany lives the user has
 *****************************************************************************/
class LifeShip : public GameObject {
public:
   LifeShip();

   virtual void draw() const;
   
   void setPosition(float p1, float p2);
   void addX(float x);
   void setColor(float newColor)  { color = newColor; }
private:
   Point bow;
   Point starboard;
   Point port;
   float color;
};

#endif