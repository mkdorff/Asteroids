################################################################################
# Program:
#    Project 4, Asteroids
#    Brother McCracken, CS165
# Authors:
#    Mohonri Dorff, Justin Waite
# Summary: 
#    Asteroids is awesome. Please play it.
#    So we have everything required by the project outline. Things such as the
#    ship following laws of interita. Bullets follow their laws. They travel 90%
#    of the screen length before they dissolve into nothingness. Asteroids break
#    according to the laws of nature: Big -> 2 Medium & 1 Small, Medium -> 
#    2 Small. I think that was everything requried.
#
#    Okay, here's for our additions.
#    2 quick notes: I kept the iostream in the main asteroids.cpp so that I
#    print controls and instructions to the console. Otherwise, normal game play
#    is obvious, so the user doesn't have to ever actually look at the console.
#    Secondly, when Q is pressed to quit the game. The user is given a prompt to
#    confirm they want to quit. We didn't have the game pause because... we like
#    it better that way.
#
#    We added scoring. The big asteroids give 30 points, the medium asteroids
#    give 90 points and the small asteroids give 270 points. When a level is 
#    cleared, they recieve 400 times the level number We added lives. The
#    user starts with 3. Another stylistic choise was that the lives displayed
#    in the top left shows how many extra lives. When the user loses a life, he
#    loses 600 points. There is a level indicator in the top right. What's cool
#    is that all the text or scoring information is in white text but has a grey
#    drop shadow to the bottom left. It is subtle, but it makes the text that 
#    much more readable and stand out from the game objects.
#    We didn't stop there. We have options to press either the escape key or the
#    'p' key to pause the game. Pressing 'q' brings up an option to quit the 
#    game. 'y' pressed then actually quits and 'n' allows the user to cotinue 
#    the game. 'r' pressed at anytime restarts the game entirely. This is useful
#    when the user dies and there is a gameover text written and nothing else 
#    more can be done with the game.
#    Almost done. We added a function that randomly generates 35 stars as the 
#    background each time the game is started. (So restarting with 'r' draws 
#    them! It's pretty.) Finally, we added a second of immunity right after the
#    ship spawns after a death. This is necessary because sometimes there are 
#    asteroids in the middle of the field and that is where the ship spawns.
#    Otherwise, the ship would die immediately. (This is my favorite bit) To 
#    show immunity, the ship flickers in what seems to be a very natural and 
#    obvious way. Once the immunity clock has run out, it becomes solid again.
#    
#    That is all, enjoy!
################################################################################

# Uncomment for Linux. Also make changes in uiInteract.cpp and uiDraw.cpp
linux : asteroids.o uiInteract.o uiDraw.o point.o game.o gameObjects.o
	g++ asteroids.o uiInteract.o uiDraw.o point.o game.o gameObjects.o \
		-lglut -lGLU
	tar -cf asteroids.tar *.cpp *.h makefile

# Uncomment for Mac. Also make changes in uiInteract.cpp and uiDraw.cpp
mac : asteroids.o uiInteractMac.o uiDrawMac.o point.o game.o gameObjects.o
	g++ asteroids.o uiInteractMac.o uiDrawMac.o point.o game.o gameObjects.o \
		-framework GLUT -framework OpenGL
	tar -cf asteroids.tar *.cpp *.h makefile

uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

# Needed only for Mac
uiInteractMac.o : uiInteractMac.cpp uiInteract.h point.h
	g++ -c uiInteractMac.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

# Needed only for Mac
uiDrawMac.o : uiDrawMac.cpp uiDraw.h point.h
	g++ -c uiDrawMac.cpp

point.o : point.cpp point.h
	g++ -c point.cpp
	
gameObjects.o : gameObjects.cpp gameObjects.h point.cpp point.h uiInteract.cpp \
	uiInteract.h uiDraw.cpp uiDraw.h
	g++ -c gameObjects.cpp
    
game.o : game.cpp game.h gameObjects.cpp gameObjects.h point.cpp point.h \
	uiInteract.cpp uiInteract.h uiDraw.cpp uiDraw.h
	g++ -c game.cpp

asteroids.o : asteroids.cpp uiDraw.h uiInteract.h point.h game.h gameObjects.h
	g++ -c asteroids.cpp

clean :
	rm *.o *.tar *.out