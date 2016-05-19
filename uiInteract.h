/*********************************************
 * UI INTERFACE
 *
 * This module will create an OpenGL window,
 * enter the OpenGL main loop, and accept events.
 * The main methods are:
 *    1. Constructors - Create the window
 *    2. run()        - Run the main loop
 *    3. callback     - Specified in Run, this user-provided
 *                      function will get called with every frame
 *    4. isDown()     - Is a given key pressed on this loop?
 **********************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

/********************************************
 * INTERFACE
 * All the data necessary to keep our graphics
 * state in memory
 ********************************************/
class Interface
{
public:
   // Default constructor useful for setting up the random variables
   // or for opening the file for output
   Interface() { initialize(0, 0x0000, "Window");  }

   // Constructor if you want to set up the window with anything but
   // the default parameters
   Interface(int argc, char ** argv, const char * title)
   {
      initialize(argc, argv, title);
   }
   
   // Destructor, incase any housecleaning needs to occr
   ~Interface();

   // This will set the game in motion
   void run(void (*callBack)(const Interface *, void *), void *p);

   // Get various key events
   int  isDown()      const { return isDownPress;  }
   int  isUp()        const { return isUpPress;    }
   int  isLeft()      const { return isLeftPress;  }
   int  isRight()     const { return isRightPress; }
   bool isSpace()     const { return isSpacePress; }
   bool isEsc()       const { return isEscPress;   }
   bool isR()         const { return isRPress;     }
   bool isC()         const { return isCPress;     }
   bool isQ()         const { return isQPress;     }
   bool isY()         const { return isYPress;     }
   bool isN()         const { return isNPress;     }   

   static void *p;                   // for client
   static void (*callBack)(const Interface *, void *);

private:
   // Service function for the constructors
   void initialize(int argc, char ** argv, const char * title);
   
   // Is it time to redraw the screen
   bool isTimeToDraw();
   
   // Set the next draw time based on current time and time period
   void setNextDrawTime();
   
   // Retrieve the next tick time... the time of the next draw.
   unsigned int getNextTick() {  return nextTick;  }
   
   // How many frames per second are we configured for?
   void setFramesPerSecond(double value);
   
   // Key event indicating a key has been pressed or not.  The callbacks
   // should be the only onces to call this
   friend void keyDownCallback( int           key, int x, int y);
   friend void keyUpCallback(   int           key, int x, int y);
   friend void keyboardCallback(unsigned char key, int x, int y);
   friend void drawCallback();
   
   // Current frame rate
   double frameRate() const {  return timePeriod;  }
   
   // just some housekeeping stuff
   static bool         initialized;  // only run the constructor once!
   static double       timePeriod;   // interval between frame draws
   static unsigned int nextTick;     // time (from clock()) of our next draw

   // who has been pressed
   static int  isDownPress;          // is the down arrow currently pressed?
   static int  isUpPress;            //    "   up         "
   static int  isLeftPress;          //    "   left       "
   static int  isRightPress;         //    "   right      "
   static bool isSpacePress;         //    "   space      "
   static bool isEscPress;           //    "   escape     "
   static bool isRPress;             //    "   'r'        "
   static bool isCPress;             //    "   'c'        "
   static bool isQPress;             //    "   'q'        "
   static bool isYPress;             //    "   'y'        "
   static bool isNPress;             //    "   'n'        "
};

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run();

#endif // UI_INTERFACE_H