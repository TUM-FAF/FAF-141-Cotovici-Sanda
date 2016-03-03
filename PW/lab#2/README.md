# Windows Programming Laboratory Work #2

## Title
Advanced Form Elements. Child Windowses. Basics of Working With Keyboard.

## Contents
* The Keyboard
* Child Window Controls
  * Scroll Bar
  * Listbox
* Menus and Other Resources
* Dialog Boxes

### Laboratory work Requirements:
  - for _Basic Level_ (grade 5 || 6) you should be able to:
    * Create a Windows application what will dispaly a dialog box on some event (ex. on clicking some button)
    * Add a system menu to your application with at least 3 items (add actions to that items)
    * Hook keyboard input. Add 2 custom events for 2 different keyboard combinations (ex. change window background on ctrl+space) 
  - for _Normal Level_ (grade 7 || 8) you should be able to:
    * Realize the tasks from _Basic Level_.
    * Add a scroll bar that will change any visible parameter of any other element (color of a text) OR other 2 scroll bars that will manage main window size or position
  - for _Advanced Level_ (grade 9 || 10) you should be able to:
    * Realize the tasks from _Normal Level_.
    * Customize your application by adding an icon and using different cursor in application
    * Add a listbox and attach some events when any element is accessed (clicked)
  - for _Bonus Point Tasks_ :
    * Use a scroll bar to scroll through application working space. Scroll should appear only when necessary (eg. when window width is smaller than 300px)
 


</br>
### Completed tasks:
  **Display a dialog box on some event (ex. on clicking some button)**

Is created a dialog box resources.rc file, which popup when is clicked Info option from menu. 
For this reason was created procedure`InfoDlgProc()` which will display the dialog box.
  **Add a system menu to your application with at least 3 items (add actions to that items)**

The menu has been created in the resources.rc file. <br> Were created 3 items : `File -> Exit` - exits from the program, `Edit -> Change background color` - changes background color and `Info -> Info` - displaying a dialog box with some information.

  **Add a scroll bar that will change any visible parameter of any other element (color of a text)**

Scroll bar is created by procedure`CreateWindowEx()` ,with some parameters:`"SCROLLBAR"` and a `xPos`. The last variable is changing in dependence of the case from `WM_VSCROLL`. In dependence of`xPos` variable and function `SetTextColor()`is changing color of the text from editbox.
  **Hook keyboard input. Add 2 custom events for 2 different keyboard combinations**

Hooks : `CTRL + E` for exiting from the application, and `CTRL + I` for displaying a dialog box. These actions are managed in the `WM_HOTKEY` case.

  **Add a listbox and attach some events when any element is accessed (clicked)**

Listbox is created using `CreateWindowEx()`  with the 2nd parameter`"LISTBOX"`. My listbox receives elements from a editbox and from Add button.Element could be double-clicked, and apears window with the element's name. Or you can press right click and is displayed a Warning that you can delete element.

  **Customize your application by adding an icon and using different cursor in application**

A custom cursor and icon were added in the main folder. So I have created file resource.rc,in which I have declared IDI\_ICON ICON DISCARDABLE "icon.ico" . This icon is a small bird, downloaded from internet. For cursor I declared ID\_CURSOR CURSOR DISCARDABLE "Button.cur". Also some of windowclass fields were changed `hIcon, hIconSm, hCursor` .

