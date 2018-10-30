/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef ENEMIES_H
#define ENEMIES_H

#include<CommonThings.h>
#include <Maze.h>
#include <player.h>
#include <time.h>
#include <thread>
#include <string>
#include <math.h>       /* ceil */
#include <vector>

//This was used for shortest path
//It was to hold coordinates that have been visited and
//the string of the path it has traveled
struct pos{
    int x, y;
    string dir;
};


class Enemies
{
    public:
        Enemies();                          // constructor
        virtual ~Enemies();                 // DeConstructor
        void initEnm(int, int, char *);     // Initialize Enemy

        void placeEnemy(int,int);           // place enemy
        void drawEnemy(char**);             // Draw Enemy with Animation
        void moveEnemy(string);             // move Enemy left,right,up,down
        void moveDirection(char**, float, float, int);         //determine direction
        void animate(char**);                     // Animate sprite
        GridLoc getEnemyLoc();              // Return Enemy current grid location
        void collision(Maze*, Player*);
        void dead(int&, Player*);

        char BFS(char**, float, float); //breadth first search
        bool InExplored(pos, vector<pos>);  //Used to check if the current position has been traveled already


        int gridSize;                       // Grid size of the maze
        float unitWidth;                    // Unit width of the grid
        int stepsPerMove;                   // Step count for animation
        bool live;                          // Status of the Enemy
    protected:

    private:
         int frames;                        // number of frames generally
         float t;                           // steps for animation count
         GLuint enmTex;                     // Image Texture

         float xmax, xmin,ymax,ymin;        // Animated Texture mapping
         bool up,down,left,right;           // move direction
         float moveDis=0;                   // Moving distance for animation
         loc enmLoc;                        // location of the enemy
};

#endif // ENEMIES_H
