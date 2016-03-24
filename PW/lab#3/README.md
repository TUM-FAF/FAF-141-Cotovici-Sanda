# Windows Programming Laboratory Work #3


## Title
Basics of Working with Mouse. GDI Primitives. Bezier Curve.

## Contents
* Mouse
* Device context
* GDI Primitives
  * Line
  * Curve
  * Plane
  * Bitmap image
* Bezier curve

### Laboratory work Requirements:
  - for _Basic Level_ (grade 5 || 6) you should be able to:
    * Draw 5 lines of different colors and weights
    * Draw 2 Bezier curves
    * Draw 4 plane objects (ex. circle, square, pie, polygon...) of different colors, weights, filled and not
    * Draw 2 different objects using mouse
  - for _Normal Level_ (grade 7 || 8) you should be able to:
    * Realize the tasks from _Basic Level_.
    * Draw a custom bitmap image 
    * Fill 2 object with gradient 
    * Hook keyboard input. Add 2 different keyboard combinations that will change mouse ability to draw objects (ex. on Ctrl+C will draw circles, on Alt+R will continue to draw circles but of read color)
    * Draw a Bezier curve using mouse
  - for _Advanced Level_ (grade 9 || 10) you should be able to:
    * Realize the tasks from _Normal Level_.
    * Zoom in and out application working area using keyboard 
    * Use mouse as an eraser (choose 1 option):
      * delete objects using mouse clicking
      * eraser of a fixed width
      * eraser with adjustable width
  - for _Bonus Point Tasks_ :
    * Realize the task with mouse eraser for all 3 cases listed above. In order to choose one of them, add 3 buttons/icons or check boxes.

##Implemented tasks:
1.	Was created area for drawing.
2.	Also was created 2 objects with gradient.
3.	Tools and Shapes which will be used to draw, such as:
   *	**Pencil** tool will draw a continuous line with the stroke weight equal to 1.
   *	**Line** tool will draw a straight line between two points, with the selectable stroke weight and color using the mouse button.
   *	**Ellipse** tool will draw an ellipse, with selectable stroke weight and color, filled with a selectable color,using the mouse button.
   *	**Rectangle** tool will draw a rectangle, with selectable stroke weight and color, filled with a selectable color,using the mouse button.
   *	**Bezier curve.** The Bezier curve can be drawn using mouse,by clicking and draging two times.
   *  **Eraser** which will erase with different size
   * **Clear all** This button was created for clearing drawing area.
4.	Custom bitmap images : where used 4 bitmap images, like icons dor pencil ,line, rectangle and ellipse

##Conclusions

This laboratory work was very interesting and full of challenges, because of bugs and different approaches of the same problem. Was hard to work esspecially with Bezier curves. An interesting thing was to arrange all buttons to look like in a professional painter. I have tried to implement all tasks, but I think that I hasn't covered all. But it looks nice! I will work in future for a better quality of features from this laboratory.
