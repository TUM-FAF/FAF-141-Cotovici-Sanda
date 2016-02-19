# FAF-141-Cotovici-Sanda
# Windows Programming Laboratory Works No.1


## Title
Window. Window handling. Basic window’s form elements

## Contents
* Win32 API
* GIT
* Window
* Button
* Text Input
* Text

### Laboratory work Requirements:
  - for _Basic Level_ (grade 5 || 6) you should be able to:
    * Create a Windows application
    * In the middle of the window should be present the following text: "Done with Pride and Prejudice by student name". Replace student name with your name.
    * On windows resize, text should reflow and be in window's middle (vertically and horizontally)
  - for _Normal Level_ (grade 7 || 8) you should be able to:
    * Realize the tasks from _Basic Level_.
    * Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family/size)
    * Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family/size)
  - for _Advanced Level_ (grade 9 || 10) you should be able to:
    * Realize the tasks from _Normal Level_.
    * Make elements to interact or change other elements (2 different interactions)  _(ex. on button click, change text element color or position)_
    * Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display working space 

## References
* Programming Windows by Charlez Petzold, 5th edition:
  * Section I, Chapter 1
  * Section I, Chapter 2
  * Section I, Chapter 3
  * Section I, Chapter 4
  * Section I, Chapter 9
##Practical Work:
####Create A Windows application

I had followed all steps by "Windows Programming" by Charles Petzhold
## In the middle of the window should be present the following text: "Done with Pride and Prejudice by student name". Replace student name with your name.
  I printed this text with function DrawText. It appears in the middle of the window , because of used properties : DT_SINGLELINE | DT_CENTER | DT_VCENTER.
##On windows resize, text should reflow and be in window's middle (vertically and horizontally)  
  For this reason I used properties CS_HREDRAW | CS_VREDRAW
##Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family/size)
 I added 4 buttons. First two buttons are for inserting text and for clear it. The last 2 buttons are for changing color of text,
 one edit text's color in Violet and another change it in Orange. I had created this buttons and then I used function WM_CTLCOLORSTATIC 
 to edit text, and then I used function WM_DRAWITEM to color this button.

##Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family/size)
I had default text , introduced by user and the second text is showed on the screen .
The second text has different color, in dependence of pushed button.
##Make elements to interact or change other elements (2 different interactions)  _(ex. on button click, change text element color or position)
I added 2 buttons : Violet and Orange , which edit text's color.
##Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display working space 
I changed minimize button to appear warning that you pushed minimize button.For Maximize button I choose to be changed background's color;
And for last exit button - when it is pushed appear a new window with question : "Do you want to close the window? ".
And user has to choose :"YES or No".
