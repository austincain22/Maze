/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef MAZE_H
#define MAZE_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */
#include <player.h>

using namespace std;



class Maze
{
    public:
        Maze();                           // Constructor
        Maze(int);                        // Overload Constructor
        virtual ~Maze();                  // Deconstructor

      void loadBackgroundImage(char *);   // set an image for the background
      void loadSetOfArrowsImage(char *);  // set an image for the Arrow Bundle
      void loadChestImage(char *);        // set an image for the Arrow

      void drawBackground();              // Draw background image
      void drawGrid();                    // Draw Grid
      void drawArrows();                  // Draw set of Arrows
      void drawChest();                   // Draw Chest

      int getGridSize();                  // return grid size

      void placeChest(int,int);           // Place Chest
      GridLoc GetChestLoc();              // Return grid location of the chest
      bool victory(Player*);              //check player collision with chest
      void victory( );                   //check if all enemies are dead

      void placeStArrws(int,int);         // Place set of arrows
      GridLoc GetStArrwsLoc();            // Return grid location of the arrows
      void arrowsPickUp(Player*);         //check player collision with arrow set


      float spin;                         // for spin chest
      bool liveChest;                     // status of the chest (collected or not)
      bool liveSetOfArrws;                // status of the arrows(collected or not)
      bool win;

      void addArrow(Player *);
      int level = 0;
      void loadBackgroundImage();   // set an image for the background------MD

    protected:

      int gridSize;                       // grid size
      float unitWidth;                    // Unit width of the grid

    private:

      GLuint bakTex;                       // Handler for background texture
      GLuint ArrBnchTex;                   // Handler for set of arrows texture
      GLuint chestTex;                     // Handler for Chest texture
      loc chestLoc;                        // chest Location
      loc setOfArrsLoc;                    // arrows Location
      loc converter(int, int);             // convert grid size to viewport
};

#endif // MAZE_H
