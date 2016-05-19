/*******************************************************************************
* Program:
*    Project 4, Asteroids
*    Brother McCracken, CS165
* Authors:
*    Mohonri Dorff, Justin Waite
* Summary:
*    Asteroids is awesome. Please play it.
*
*******************************************************************************/

#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"
#include "game.h"
#include "gameObjects.h"

#include <cassert>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
// #include <iterator>

/******************************************************************************
 * DOES IT INTERSECT
 * This returns a boolean value that gets turned true if the testPoint
 * intersects with the vector of points represented by the a game object
 *****************************************************************************/
bool doesIntersect(std::vector<Point> points, Point testPoint) {
   int i;
   int j;
   bool col = false;
   for (i = 0, j = points.size() - 1; i < points.size(); j = i++) {
      if ( ((points[i].getY() > testPoint.getY()) !=
            (points[j].getY()>testPoint.getY()))
         && (testPoint.getX() < (points[j].getX() - points[i].getX()) *
             (testPoint.getY()-points[i].getY()) /
             (points[j].getY()-points[i].getY()) +
              points[i].getX()) )
         col = !col;
  }
  return col;
}


std::string IntToString(int number)
{
  std::ostringstream oss;

  // Works just like cout
  oss << number;

  // Return the underlying string
  return oss.str();
}




/******************************************************************************
 * GAME::CONSTRUCTOR
 * Default constructor for the Game class.
 * Sets forth really important things.
 *****************************************************************************/
Game::Game() {
   // Here is a new ship, some asteroids, and life counter 'ships'
   ship = new Ship();
   generateAsteroids(2);
   lifeShip = new LifeShip();

   // Initiate the things!
   level = 0;
   lives = 3;
   score = 0;
   colorMode = false;
   stars = true;
   immunityFlicker = 1;
   gameStall = 0;
}

/******************************************************************************
 * GAME::DESTRUCTOR
 * Deletes allocated objects.
 *****************************************************************************/
Game::~Game() {
   delete ship;
}

/******************************************************************************
 * GAME::STEP
 * Does all the game operations or calls what is necessary for every frame drawn
 *****************************************************************************/
void Game::step() {
   // Keep track of the time NOW
   time_t now = time(0);
   immunityFlicker++;

   // stops the flickering if NOW has passed that time we gave for immunity
   if (now > immunity)
      immunityFlicker = 1;

   // if there's a ship, move it... yo
   if (ship != NULL)
      ship->move();

   // move every asteroids, yo
   for (int i = 0; i < asteroids.size(); i++)
      asteroids[i]->move();

   // move every bullet, yo
   for (int i = 0; i < bullets.size(); i++)
      bullets[i]->move();

   // sets any collisions as invalid objects
   checkCollisions();

   // remove any invalid objects.
   clean();

   // level up!
   if (asteroids.size() <= 0) {
      score += 400 * (level + 1);
      level++;
      lives++;
      generateAsteroids(2 + level);
   }
}

/******************************************************************************
 * DRAW PIECES
 * Draws the individual game pieces now that the game logic has been done.
 *****************************************************************************/
void Game::draw() const {
   for (int i = 0; i < bullets.size(); i++)
      bullets[i]->draw();

   for (int i = 0; i < asteroids.size(); i++)
      asteroids[i]->draw();

   if (ship != NULL && (immunityFlicker % 3 != 0))
      ship->draw();
}

/******************************************************************************
 * GAME::DISPLAYHUD
 * Displays game info. Score, lives, level, gameover text
 *****************************************************************************/
void Game::displayHUD() const {
   // each one draws the shadow fist, offsets the text and draws white text over
   // it. this shadow - text drawing should be in a function, but it seems
   // easier to  call it a few times instead.

   // score
   Point scoreLoc;
   scoreLoc.setX(scoreLoc.getXMax() - 511.0);
   scoreLoc.setY(scoreLoc.getYMax() - 16.0);
   string sScore = IntToString(score);
   drawString(scoreLoc, sScore, 0.65);
   scoreLoc.addX(1.995);
   scoreLoc.addY(1.995);
   drawString(scoreLoc, sScore, 1.0);

   // level
   Point levelLoc;
   if (level < 9) {
      levelLoc.setX(levelLoc.getXMax() - 68.0);
      levelLoc.setY(levelLoc.getYMax() - 16.0);
   } else {
      levelLoc.setX(levelLoc.getXMax() - 77.0);
      levelLoc.setY(levelLoc.getYMax() - 16.0);
   }
   string sLevel = "Level: " + IntToString(level + 1);
   drawString(levelLoc, sLevel, 0.65);
   levelLoc.addX(1.995);
   levelLoc.addY(1.995);
   drawString(levelLoc, sLevel, 1.0);

   // lives
   lifeShip->setPosition(4.895, 480.895);
   lifeShip->setColor(0.65);
   for (int i = lives; i > 1; i--) {
      lifeShip->draw();
      lifeShip->addX(13.0);
   }
   lifeShip->setPosition(6.0, 482.0);
   lifeShip->setColor(1.0);
   for (int i = lives; i > 1; i--) {
      lifeShip->draw();
      lifeShip->addX(13.0);
   }

   // gameover
   if (lives <= 0) {
      Point gameOverText;
      gameOverText.setX(gameOverText.getXMax() / 2 - 57.0);
      gameOverText.setY(gameOverText.getYMax() / 2);
      drawString(gameOverText, "GAME OVER", 0.65);
      gameOverText.addX(1.995);
      gameOverText.addY(1.995);
      drawString(gameOverText, "GAME OVER", 1.0);
   }
}

/******************************************************************************
 * GAME::HANDLE INPUTS
 * Handles the different inputs for the game.
 *****************************************************************************/
void Game::handleInputs(KeyboardInputs ki) {
   if (ship != NULL) {
      if (ki.isLeft) {
         ship->turn(true);
      }

      if (ki.isRight) {
         ship->turn(false);
      }

      if (ki.isUp) {
         ship->accelerate(true);
      }

      if (ki.isDown) {
         ship->accelerate(false);
      }
   }

   if (ki.isSpace) {
      if (ship != NULL)
         fireBullet();
      else {
         if (lives > 0) {
            ship = new Ship();
            time_t t = time(0);
            immunity = t + 2;
         }
      }
   }

   if (ki.isR) {
      removeAsteroids();
      ship = new Ship();
      generateAsteroids(2);
      lifeShip = new LifeShip();
      level = 0;
      lives = 3;
      score = 0;
      stars = true;
      immunityFlicker = 1;
      gameStall = 0;
   }
}

/******************************************************************************
 * GAME::FIREBULLET
 * Makes a new bullet, add it to the bullet vector, and gives the direction and
 * rotational data of the ship
 *****************************************************************************/
void Game::fireBullet() {
   bullets.push_back(new Bullet(ship));
}

/******************************************************************************
 * GAME::CLEAN
 * Checks through each bullet, asteroid and the ship for validity. If not, we
 * delete it.
 *****************************************************************************/
void Game::clean() {
   // bullets
   for (int i = 0; i < bullets.size(); i++)
      if (!bullets[i]->getIsValid()) {
         delete bullets[i];
         bullets[i] = NULL;
      }

   bullets.erase(std::remove(begin(bullets), end(bullets), nullptr),
      end(bullets));

   // asteroids
   for (int i = 0; i < asteroids.size(); i++)
      if (!asteroids[i]->getIsValid()) {
         delete asteroids[i];
         asteroids[i] = NULL;
      }

   asteroids.erase(std::remove(begin(asteroids), end(asteroids), nullptr),
          end(asteroids));

   // Das ship, ya
   if (ship != NULL && !ship->getIsValid()) {
      delete ship;
      ship = NULL;

      for (int i = 0; i < bullets.size(); i++) {
         delete bullets[i];
         bullets[i] = NULL;

         bullets.erase(std::remove(begin(bullets), end(bullets), nullptr),
            end(bullets));
      }
   }
}

/******************************************************************************
 * GAME::GENERATE ASTEROIDS
 * Given number of asteroids (determined by level) we generate random ones and
 * add it to our asteroids vector
 *****************************************************************************/
void Game::generateAsteroids(int num) {
   for (int i = 0; i < num; i++) {
      Point startPos;

      int rand = random (1, 4);
      if (rand == 1)
         startPos = Point(0, random(0.0, startPos.getYMax()));
      else if (rand == 2)
         startPos = Point(random(0.0, startPos.getXMax()), 0.0);
      else if (rand == 3)
         startPos = Point(startPos.getXMax(), random(0.0, startPos.getYMax()));
      else if (rand == 4)
         startPos = Point(random(0.0, startPos.getXMax()), startPos.getYMax());

      asteroids.push_back(new LargeAsteroid(startPos));
   }
}

/******************************************************************************
 * GAME::REMOVE ASTEROIDS
 * Function to clean all all the asteroids.
 *****************************************************************************/
void Game::removeAsteroids() {
   for (int i = 0; i < asteroids.size(); i++) {
      delete asteroids[i];
      asteroids[i] = NULL;
   }

   asteroids.erase(std::remove(begin(asteroids), end(asteroids), nullptr),
      end(asteroids));
}

/******************************************************************************
 * GAME::CHECK COLLISIONS
 * We have to check each obeject (and for the ship, every side of the ship)
 * calling the doesIntersect() witht those bounds. If they do, we have some work
 * to do.
 *****************************************************************************/
void Game::checkCollisions() {
   int aCount = asteroids.size();
   for (int i = 0; i < aCount; i++) {
      std::vector<Point> bounds = asteroids[i]->getBounds();
      time_t now = time(0);

      // the ship has to exist and not have temporary immunity
      if (ship != NULL && now > immunity) {
         Point bowPoint = ship->getBow();
         Point starboard = ship->getStarboard();
         Point port = ship->getPort();

         // each side of the ship
         if (doesIntersect(bounds, bowPoint) ||
            doesIntersect(bounds, starboard) ||
            doesIntersect(bounds, port)) {
               ship->setIsValid(false);
               lives--;
               score -= 600;
         }
      }

      // Let's check these bullets
      for (int j = 0; j < bullets.size(); j++) {
         if (doesIntersect(bounds, bullets[j]->getPoint())) {
            asteroids[i]->setIsValid(false); // marks invalid for later
            bullets[j]->setIsValid(false);   // marks invalid for later

            float dx = asteroids[i]->getDx();
            float dy = asteroids[i]->getDy();
            Point p = asteroids[i]->getPoint();

            // 30 points and big asteroid bye-bye, hi smaller ones
            if (asteroids[i]->getSize() == LARGE) {
               asteroids.push_back(new MediumAsteroid(p, dx, dy + 1));
               asteroids.push_back(new MediumAsteroid(p, dx, dy - 1));
               asteroids.push_back(new SmallAsteroid(p, dx + 2, dy));
               score += 30;
            }

            // 90 points to Gryffindor!
            if (asteroids[i]->getSize() == MEDIUM) {
               asteroids.push_back(new SmallAsteroid(p, dx + 2, dy));
               asteroids.push_back(new SmallAsteroid(p, dx - 2, dy));
               score += 90;
            }

            // 270 points to Ravenclaw!
            if (asteroids[i]->getSize() == SMALL) {
               score += 270;
            }
         }
      }
   }
}

/******************************************************************************
 * GAME::SHOW PAUSED
 * Displays text (with shadow)
 *****************************************************************************/
void Game::showPaused() {
   if (lives > 0) {
      Point cPaused;
      cPaused.setX(cPaused.getXMax() / 2 - 66.0);
      cPaused.setY(cPaused.getYMax() / 2);
      drawString(cPaused, "GAME PAUSED", 0.65);
      cPaused.addX(1.995);
      cPaused.addY(1.995);
      drawString(cPaused, "GAME PAUSED", 1.0);
   }
}

/******************************************************************************
 * GAME::TOGGLE COLOR
 * Just toggles color mode
 *****************************************************************************/
void Game::toggleColor() {
   colorMode ? colorMode = false : colorMode = true;
}

/******************************************************************************
 * GAME::CREATE STARS
 * Should only be called once a game, but it randomly generates the backgound
 *****************************************************************************/
void Game::createStars() {
   backgroundStars.clear();
   assert(backgroundStars.empty());
   for (int i = 0; i < 35; i++) {
      Point starPoint(random(0, 512), random(0, 512));
      backgroundStars.push_back(starPoint);
   }

   stars = false;
}

/******************************************************************************
 * GAME::GETGAMESTALL
 * Does this need explanation?
 *****************************************************************************/
int Game::getGameStall() {
   return gameStall;
}

/******************************************************************************
 * GAME::SET GAME STALL
 * I mean, I could levae this in the header, but everything is here so... yeah
 *****************************************************************************/
void Game::setGameStall(int seconds) {
   gameStall = seconds;
}

/******************************************************************************
 * GAME::SUBTRACT GAME STALL
 * Guess what? It subtracts the parameter from the private variable gameStall
 *****************************************************************************/
void Game::subGameStall(int seconds) {
   gameStall -= seconds;
}
