/*******************************************************************************
* Program:
*    Project 4, Asteroids
*    Brother McCracken, CS165
* Authors:
*    Mohonri Dorff, Justin Waite
* Summary: 
*    Asteroids is awesome. Please play it.
*    Hours? Countless.
*
*******************************************************************************/

#include "gameObjects.h"
#include "game.h"
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>

// Bounds of the UI Interface.
float Point::xMin = 0;
float Point::xMax = 512;
float Point::yMin = 0;
float Point::yMax = 512;

void callBack(const Interface *pUI, void *p);
void displayHelp();
void displayQuitPrompt();
void getKeyboardInput(const Interface *pUI, KeyboardInputs & input);

/******************************************************************************
 * MAIN
 * Creates the interface object and runs the Asteroids program!
 *****************************************************************************/
int main(int argc, char **argv) {
   displayHelp(); // the reason for iostream, help displayed in console

   Interface ui(argc, argv, "Game");  
   Game asteroids;                        

   ui.run(callBack, (void *) & asteroids);  

   return 0;
}

/******************************************************************************
 * CALLBACK
 * Callback from the Interface. Performs game logic on every frame and draws
 * the game pieces.
 *****************************************************************************/
void callBack(const Interface *pUI, void *p) {
   // important to keep track of 'time' for certain elements of the game
   time_t timeNow = time(0);
   Game *pGame = (Game *)p;   
   
   // Creates once and then displays randomly generated background stars
   if (pGame->stars)
      pGame->createStars();
   assert(!pGame->stars);
   drawStars(pGame->backgroundStars);

   // I think this is obvious
   KeyboardInputs input;
   getKeyboardInput(pUI, input);

   // game logic and art gets drawn
   pGame->draw();

   // gameplay info
   pGame->displayHUD();
   
   // Sets the gameStall 7 minutes out. Needed so the quit prompt to stay alive
   if (input.isQ) {
      time_t t = time(0);
      pGame->setGameStall(t + 420);
   }

   // this just keeps the quit prompt alive. It will expire after 7 minutes.
   if (pGame->getGameStall() > timeNow) {
      displayQuitPrompt();
      if (input.isY)
         exit(0);
      if (input.isN)
         pGame->subGameStall(500);
   }
   
   // I could else-if this, but I like the objects to keep moving
   if (input.isEsc) {
     pGame->showPaused();
   } else {
     pGame->handleInputs(input);
     pGame->step();
   }
}

/******************************************************************************
 * GET KEYBOARD INPUT
 * The ever important key event grabber. Returns a bool for any given key that
 * is being pressed.
 *****************************************************************************/
void getKeyboardInput(const Interface *pUI, KeyboardInputs & input) {
   input.isLeft = pUI->isLeft();
   input.isRight = pUI->isRight();
   input.isDown = pUI->isDown();
   input.isUp = pUI->isUp();
   input.isSpace = pUI->isSpace();
   input.isEsc = pUI->isEsc();
   input.isR = pUI->isR();
   input.isC = pUI->isC();
   input.isQ = pUI->isQ();
   input.isY = pUI->isY();
   input.isN = pUI->isN();
}

/******************************************************************************
 * DISPLAY HELP
 * This displays some info, controls and help to the console. The user doesn't 
 * have to look at it but I find it useful.
 *****************************************************************************/
void displayHelp() {
   std::cout 
   << "*******************************READ ME*******************************"
   << std::endl
   << "This is Asteroids, the amazing game clean up space for New Horizon to"
   << std::endl
   << "travel unimpeded by asteroids. The controls/inputs are as follows:"
   << std::endl
   << "    UP/DOWN      Applies thrusters forward or backwards"
   << std::endl
   << "    LEFT/RIGHT   Rotates the spaceship left or right"
   << std::endl
   << "    SPACE        Fires our super advance, asteroid-destroying missles"
   << std::endl
   << "    ESC/P        Pauses the game"
   << std::endl
   << "    R            Resets the game"
   << std::endl
   << "    Q            Quits the game"
   << std::endl
   << "*********************************************************************"
   << std::endl;
}

/******************************************************************************
 * DISPLAY QUIT PROMPT
 * Just a function to dispplay the quit prompt and the 'Y' and 'N' underneath
 *****************************************************************************/
void displayQuitPrompt() {
   // shows shadow first, that normal text on top.
   Point cQuitPrompt;
   cQuitPrompt.setX(cQuitPrompt.getXMax() / 2 - 121.0);
   cQuitPrompt.setY(cQuitPrompt.getYMax() / 2 - 50.0);
   drawString(cQuitPrompt, "Are you sure you want to quit?", 0.65);
   cQuitPrompt.addX(1.995);
   cQuitPrompt.addY(1.995);
   drawString(cQuitPrompt, "Are you sure you want to quit?", 1.0);

   Point cYES;
   cYES.setX(cYES.getXMax() / 2 - 35.0);
   cYES.setY(cYES.getYMax() / 2 - 90.0);
   drawString(cYES, "Y", 0.65);
   cYES.addX(1.995);
   cYES.addY(1.995);
   drawString(cYES, "Y", 1.0);

   Point cNO;
   cNO.setX(cNO.getXMax() / 2 + 20.0);
   cNO.setY(cNO.getYMax() / 2 - 90.0);
   drawString(cNO, "N", 0.65);
   cNO.addX(1.995);
   cNO.addY(1.995);
   drawString(cNO, "N", 1.0);
}