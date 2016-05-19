#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"
#include "gameObjects.h"
#include <vector>

/**************************************************************
 * KEYBOARD INPUTS
 *    A simple structure that store user input as bools
 *************************************************************/
struct KeyboardInputs {
   bool isLeft;
   bool isRight;
   bool isDown;
   bool isUp;
   bool isSpace;
   bool isEsc;
   bool isR;
   bool isC;
   bool isQ;
   bool isY;
   bool isN;
};

/*****************************************************************
 * GAME
 *    Our big bad game class. Our UML in our design document is
 *    better to dsecribe this, but this has all gameObjects, 
 *    methods to draw, edit, change, add, or delete asteroids, 
 *    ship, bullets. There are also things to make this feel like 
 *    a polished game.
 ****************************************************************/
class Game {
public:
   Game(); 
   ~Game();
   
   void handleInputs(KeyboardInputs ki);
   void step();
   void draw() const;
   void displayHUD() const;
   void clean();
   
   void fireBullet();
   void generateAsteroids(int num);
   void removeAsteroids();
   void checkCollisions();

   void showPaused();
   void toggleColor();
   void createStars();

   int getGameStall();
   void setGameStall(int seconds);
   void subGameStall(int seconds);

   std::vector<Point> backgroundStars;
   bool stars;
private:
   Ship* ship;
   LargeAsteroid* ast;
   std::vector<Asteroid*> asteroids;
   std::vector<Bullet*> bullets;
   LifeShip* lifeShip;
   int level;
   int lives;
   int score;
   bool colorMode;
   int immunity;
   int immunityFlicker;
   int gameStall;
};

#endif // GAME_H