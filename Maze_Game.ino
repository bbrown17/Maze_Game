/*
  Maze_Game.pde
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
  from the Meggy Jr RGB library for Arduino
   

 
 Version 1.25 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
 	  
 */

/*
 * Adapted from "Blink,"  The basic Arduino example.  
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

// global variables go here
int xcoord = 3;
int ycoord = 4;
int yenemy = ycoord - 1;
void GreenWall()
{
  DrawPx(4,3,Green); DrawPx(4,4,Green); DrawPx(4,5,Green); 
}  

// see notes at /Arduino/notes.txt 

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
}

void loop()                     // run over and over again
{
  GreenWall(); // must be at top of loop so everything else isn't under it
  shift();
  DrawPx(xcoord,yenemy,Orange);
  DrawPx(xcoord,ycoord,Blue); // draw dot
  DisplaySlate();
  delay(150);
  ClearSlate();
}

void shift()
{
  CheckButtonsDown();
  if (Button_Right)
  {
    if (xcoord < 7)
      xcoord = xcoord + 1; // indented because belongs to inner if statement; could also say xcoord++
        if (ReadPx(xcoord, ycoord) == Green)
          xcoord = xcoord -1; // as soon as user lands on green pixel, go +1 pixels to original position
    if (xcoord == 7)
      Tone_Start (ToneC3,100); 
  }    
  if (Button_Left)
  {
    if (xcoord > 0)
      xcoord = xcoord - 1;
        if (ReadPx(xcoord, ycoord) == Green)
          xcoord = xcoord +1;
    if (xcoord == 0)
      Tone_Start (ToneC3,100);  
  }    
    if (Button_Up)
  {
    if (ycoord < 7)
      ycoord = ycoord + 1;
      if (ReadPx(xcoord, ycoord) == Green)
        ycoord = ycoord -1; // as soon as user lands on green pixel, go -1 pixels to original position
    if (ycoord == 7)
      Tone_Start (ToneC3,100); 
    if (yenemy < 7) // enemy moves up 1 on button up
    yenemy = yenemy + 1;     
  }    
  if (Button_Down)
  {
    if (ycoord > 0)
      ycoord = ycoord - 1;
        if (ReadPx(xcoord, ycoord) == Green)
          ycoord = ycoord +1;
    if (ycoord == 0)
      Tone_Start (ToneC3,100);
    if (yenemy > 0) // enemy moves up 1 on button up
    yenemy = yenemy - 1;       
  } 
}

