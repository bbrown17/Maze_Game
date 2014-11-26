/*
  Maze_Game.pde
 
A fun maze game with a green wall obstacle and death zone to
get around, as well as an enemy to keep track of.
   

 
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

/* Rules

How to Win: Make the blue dot touch the violet dot
How to Lose: Make the blue dot touch the red X, make the red dot touch the violet dot

*/

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

// global variables go here
int xcoord = 0;
int ycoord = 7;
int yenemy = ycoord - 1;
void GreenWall()
{
  DrawPx(4,3,Green); DrawPx(4,4,Green); DrawPx(4,5,Green); // draw green wall obstacle
  DrawPx(5,5,Green); 
  
}  

void DeathZone()
{
  DrawPx(2,0,Red); DrawPx(2,2,Red); DrawPx(1,1,Red); 
  DrawPx(0,0,Red); DrawPx(0,2,Red);
} // enemy can touch death zone, if player touches, player dies. 

void WinZone()
{
  DrawPx(5,4,Violet);
}  // if enemy touches WinZone, player loses. must go around

// see notes at /Arduino/notes.txt 

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
}


void gameWon() // won the game
{
  
  for(int x=0;x<8;x++)
   {
      for(int y=0;y<8;y++)
        {

          DrawPx(x,y,Green);
          DisplaySlate();
           
        }  
   }
   
    Tone_Start(ToneG4,100); delay(150); // plays win music
    Tone_Start(ToneC5,100); delay(150);
    Tone_Start(ToneE5,100); delay(150);
    Tone_Start(ToneG4,100); delay(150);
    Tone_Start(ToneC5,100); delay(150);
    Tone_Start(ToneE5,100); delay(150);
    Tone_Start(ToneG4,100); delay(150);
    Tone_Start(ToneC5,100); delay(150);
    Tone_Start(ToneE5,100); delay(150);
    Tone_Start(ToneA5,250); delay(350);
    Tone_Start(ToneG5,100); delay(150);
    Tone_Start(ToneA5,100); delay(150);
    Tone_Start(ToneG5,100); delay(150);
    Tone_Start(ToneA5,100); delay(150);
    Tone_Start(ToneG5,250); delay(650);
    Tone_Start(ToneC6,500); delay(1000);  
}

void gameLost() // lost the game
{  
  for(int x=0;x<8;x++)
   {
      for(int y=0;y<8;y++)
        {

          DrawPx(x,y,Red);
          DisplaySlate();
           
        }  
   }
   
   Tone_Start(ToneGs4, 100); delay(150); // plays loss music
   Tone_Start(ToneC5, 100); delay(150);
   Tone_Start(ToneE5, 100); delay(150);
   Tone_Start(ToneGs4, 100); delay(150);
   Tone_Start(ToneC5, 100); delay(150);
   Tone_Start(ToneE5, 100); delay(150);
   Tone_Start(ToneGs4, 100); delay(150);
   Tone_Start(ToneC5, 100); delay(150);
   Tone_Start(ToneE5, 100); delay(150);
   Tone_Start(ToneGs4, 100); delay(300);
   Tone_Start(ToneG4, 500); delay(750); 
}

void loop()                     // run over and over again
{
  GreenWall(); // must be at top of loop so everything else isn't under it
  DeathZone();
  WinZone();
  shift();
  DrawPx(xcoord,yenemy,DimRed); // draw enemy
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
      Tone_Start (ToneC3,100); // play error sound when go off screen
    if (yenemy < 7) // enemy moves up 1 on button up
    yenemy = yenemy + 1;     
      if (ReadPx(xcoord, yenemy) == Green)
        yenemy = yenemy -1; //
    if (yenemy == 7)
      yenemy = ycoord -1; // prevents enemy from going off screen 
  }    
  if (Button_Down)
  {
    if (ycoord > 0)
      ycoord = ycoord - 1;
        if (ReadPx(xcoord, ycoord) == Green)
          ycoord = ycoord +1;
    if (ycoord == 0)
      Tone_Start (ToneC3,100); // play error sound when go off screen
    if (yenemy > 0) // enemy moves up 1 on button up
      yenemy = yenemy - 1;       
        if (ReadPx(xcoord, yenemy) == Green)
          yenemy = yenemy +1; //
    if (yenemy == 0)
      yenemy = ycoord + 1; // prevents enemy from going off screen   
  } 

  
  if (ReadPx(xcoord, ycoord) == Violet) 
  {
    gameWon(); // if user touches WinZone, end game
  } 
  
  if (ReadPx(xcoord, ycoord) == Red) 
  {
    gameLost(); // if user touches DeathZone, end game
  } 
  
  if (ReadPx(xcoord, yenemy) == Violet) 
  {
    gameLost(); // if enemy touches WinZone, end game
  } 
  
}

