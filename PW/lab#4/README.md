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

This laboratory work was very interesting and full of challenges, because of bugs and different approaches of the same problem. Was hard to work esspecially with Bezier curves. An interesting thing was to arrange all buttons to look like in a professional painter. I have tried to implement all tasks, but I think that I hasn't covered all. But it looks nice! I will work in future for a better quality of features from this laboratory.

