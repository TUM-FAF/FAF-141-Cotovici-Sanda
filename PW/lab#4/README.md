# Windows Programming Laboratory Work #4

## Title
Windows Timer. Animation.

## Contents
* Windows timer

### Laboratory work Requirements:
  - for _Basic Level_ (grade 5 || 6) you should be able to:
    * Create an animation based on Windows timer which involves at least 5 different drawn objects
  - for _Normal Level_ (grade 7 || 8) you should be able to:
    * Realize the tasks from _Basic Level_.
    * Increase and decrease animation speed using mouse wheel/from keebord 
    * Solve flicking problem _describe in your readme/report the way you had implemented this_
  - for _Advanced Level_ (grade 9 || 10) you should be able to:
    * Realize the tasks from _Norma Level_ without _Basic Level_
    * Add 2 animated objects which will interact with each other. Balls that have different velocity and moving angles. They should behave based on following rules:
        * At the begining you should have 3 bals of different colours of the same size
        * On interaction with each other, if they are of the same class (circle, square), they shuld change their color and be multiplied.
        * On interaction with the right and left wall (the margins of the window), they should be transformed into squares.
        * On interaction with the top and bottom of the window - the figures should increase their velocity.
        * Please, take into consideration that the user can increase and decrease animation speed using mouse wheel/from keebord 
    
  - for _Bonus Point Tasks_ :
    * For the task above, add balls with mouse.

 
## References
* Programming Windows by Charlez Petzold, 5th edition:
  * Section I, Chapter 8
* [http://www.winprog.org/tutorial/animation.html]
* [Flicker free drawing](http://www.catch22.net/tuts/flicker-free-drawing)
* [Double buffering in win32 api](http://www.cplusplus.com/forum/windows/35484/)

##Implemented tasks:
a.	I have created an animation with sobe balls which appear on the screen when you push right click of the mouse.
b.	The velocity or speed could be increased with the mouse wheel and with keyboard : when you press UP button the
speed increase and when you press DOWN the ball's speed decrease.
c.	Each of two animated objects behave such as:they can move with different velocity, when is collision with another object ,
the color is changed.When objects interacts with margins of the window, they are changed into sqares.
   

##Conclusions

This laboratory work was very interesting because I understand why my last laboratory work had bugs, because of flickering problem. Now I solved this problem with double-buffering technique and including case of WM_ERASEBKGND message, which clears the background. Also, in this laboratory was the first using of Timer and creating some animated balls which can change their velocity,color and shape. Their shape is changed if it is an iteraction with window's margins, color - if objects interacts with others and velocity can be changed using mouse or keyboard.

