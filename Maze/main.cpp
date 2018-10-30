/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <fstream>
#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <math.h>
#include <Sounds.h>

/* GLUT callback Handlers */

using namespace std;

Sounds *snds = new Sounds();

Maze *M = new Maze(20);                         // Set Maze grid size
Player *P = new Player();                       // create player

wall W[200];                                    // wall with number of bricks
Enemies E[10];                                  // create number of enemies
Timer *T0 = new Timer();                        // animation timer
char** graph = new char*[20];                   //matrix representation
int enemCount = 10;

struct vec2{
    int x,y;
};
vec2 walls[200];
int numW = 0;
vec2 enemies[10];
int numE = 0;
int plyerX, plyerY;
int chestX, chestY;
int arrowX, arrowY;


float wWidth, wHeight;                          // display window width and Height
float xPos,yPos;                                // Viewpoar mapping


void display(void);                             // Main Display : this runs in a loop

void resize(int width, int height)              // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}


//place player
void placePlyer(ifstream &file){
    file >> plyerX >> plyerY;
    graph[plyerX][plyerY] = 'p';
}

//place walls
void placeWalls(ifstream &file){
    file >> walls[numW].x >> walls[numW].y;
    graph[walls[numW].x][walls[numW].y] = 'w';
    numW++;
}

//place enemies
void placeEnemy(ifstream &file){
    file >> enemies[numE].x >> enemies[numE].y;
    graph[enemies[numE].x][enemies[numE].y] = 'e';
    numE++;
}

//place chest
void placeChest(ifstream &file){
    file >> chestX >> chestY;
    graph[chestX][chestY] = 'c';
}

//place arrows
void placeArrows(ifstream &file){
    file >> arrowX >> arrowY;
    graph[arrowX][arrowY] = 'a';
}

//print the matrix
void printGraph(){
    for(int i = 19; i >= 0; --i){
        for(int j = 0; j < 20; ++j){
            cout << graph[j][i] << " ";
        }
        cout << endl;
    }
}


void init(){
    //numE = 0;
    //numW = 0;

    snds->initSounds();
    snds->playMusic("sounds/TechnoChick.mp3");

    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    M->loadBackgroundImage();                           // Load maze background image

}

/*
next level increases the level
*/
void nextLevel(){
    if(M->level == 0){          //menu screen
        M->loadBackgroundImage();
    }
    else{                   //load level
        for(int i = 0; i < 100; ++i){
            W[i].liveWall = false;      //re-initializes our walls
        }
        numW = 0;
        numE = 0;

        string levelArray[3];           //hols the name or our level loaders
        levelArray[1] = "placer.txt";
        levelArray[2] = "level2.txt";

        ifstream file(levelArray[M->level]);    //opens level
        string line;

        if(!file.is_open()){
            cout << "DID NOT OPEN FILE" << endl;
        }

        for(int i = 0; i < 20; ++i){    //for graph matrix
            graph[i] = new char[20];
        }

        for(int i = 0; i < 20; ++i){
            for(int j = 0; j < 20; ++j){
               graph[i][j] = '0';       //initializes our graph
            }
        }

        while(file >> line){
            if(line == "w"){        //wall indicator
                placeWalls(file);
            }
            else if(line == "p"){   //player indicator
                placePlyer(file);
            }
            else if(line == "e"){   //enemy indicator
                placeEnemy(file);
            }
            else if(line == "c"){   //chest indicator
                placeChest(file);
            }
            else if(line == "a"){   //arrow indicator
                placeArrows(file);
            }
        }

        printGraph();

        M->loadBackgroundImage();                           // Load maze background image
        M->loadChestImage("images/chest1.png");             // load chest image
        M->placeChest(chestX,chestY);                       // place chest in a grid

        M->loadSetOfArrowsImage("images/arrows.png");       // load set of arrows image
        M->placeStArrws(arrowX,arrowY);                     // place set of arrows

        P->initPlayer(M->getGridSize(),6,"images/p.png");   // initialize player pass grid size,image and number of frames
        P->loadArrowImage("images/arr.png");                // Load arrow image
        P->placePlayer(plyerX,plyerY);                      // Place player

        for(int i=0; i< numW;i++)
        {
            W[i].wallInit(M->getGridSize(),"images/wall.png");                    // Load walls
            W[i].placeWall(walls[i].x,walls[i].y);                              // place each brick
        }


        for(int i=0; i<numE;i++)
        {
            E[i].initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image
            E[i].placeEnemy(enemies[i].x, enemies[i].y); //float(rand()%(M->getGridSize())),float(rand()%(M->getGridSize())));
        }
        file.close();
    }
}


//display everything on screen
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();
        glPopMatrix();

    if(!M->win && M->level > 0){
        for(int i=0; i<numW;i++)
        {
           W[i].drawWall(P, graph);
        }

        glPushMatrix();
            M->drawGrid();
        glPopMatrix();

        glPushMatrix();
            P->drawplayer();
        glPopMatrix();

        //check if all enemies are dead
        //if(enemCount == 0)
            //M->victory();

        glPushMatrix();
            P->drawArrow();
        glPopMatrix();

         glPushMatrix();
            M->drawChest();
            if(M->victory(P) && M->level != 3){  //checks if player won and that there's another level
                nextLevel();
            }
        glPopMatrix();

        for(int i=0; i<10;i++)
        {
            E[i].drawEnemy(graph);
            E[i].collision(M, P);   //checks if the player and enemy have collided
            E[i].dead(enemCount, P);    //checks if the player's arrow and enemy have collided
        }

        glPushMatrix();
           M->drawArrows();
           M->addArrow(P);  //checks if player is at arrow location
        glPopMatrix();
    }

    glutSwapBuffers();
}


bool shooting = false;
void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        if(!M->win && M->level > 0){
            case ' ':
                if(P->arrows > 0){     // if setof arrows were picked by player
                    if(!shooting){          //shooting mode
                        cout << "Shoot in a Direction" << endl;
                        shooting = true;
                    }
                    else{                   //movement mode
                        cout << "Move in a Direction" << endl;
                        shooting = false;
                    }
                }
            break;
        }

        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    if(M->level >= 3){      //reset game
        switch (key){
            case 'r':
                M->level = 0;
                M->win = false;
                nextLevel();
            break;
        }
    }

    if(M->level == 0){  //start a new game
        switch (key){
            case 'n':
                M->level++;
                nextLevel();
            break;
        }
    }
    glutPostRedisplay();
}


void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =posX ;
    yPos =posY ;
}

 void idle(void)
{

    //Your Code here

    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                GetOGLPos(x,y);
            }
            break;

        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN){
                GetOGLPos(x,y);
            }
            break;
    }
     glutPostRedisplay();
};

void Specialkeys(int key, int x, int y)
{
    // Your Code here
    if(!M->win && !P->arrowStatus && M->level > 0){
        switch(key)
        {
        case GLUT_KEY_UP:
                if(!shooting){      //if shooting = false player moving in up dir
                    if(P->getPlayerLoc().y+1 < 20 && graph[P->getPlayerLoc().x][P->getPlayerLoc().y+1] != 'w'){ //determine if next cell is available
                         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
                         P->movePlayer(graph,"up");
                         cout<< M->GetChestLoc().x<< "    "<<M->GetChestLoc().y<<endl;
                         if((P->getPlayerLoc().x != M->GetChestLoc().x) || (P->getPlayerLoc().y != M->GetChestLoc().y)){    //if player win game don't move enemies
                             for(int i = 0; i < numE; i++){ //loop through all enemies and determine movement
                                E[i].moveDirection(graph, P->getPlayerLoc().x, P->getPlayerLoc().y, i);
                             }
                         }
                         printGraph();
                    }
                }
                else{           //else shooting in up dir
                    P->shootArrow("up");
                    shooting = false;
                }
        break;

        case GLUT_KEY_DOWN:
                if(!shooting){      //if shooting = false player moving in down dir
                    if(P->getPlayerLoc().y-1 >= 0 && graph[P->getPlayerLoc().x][P->getPlayerLoc().y-1] != 'w'){ //determine if next cell is available
                         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
                         P->movePlayer(graph, "down");
                         if(P->getPlayerLoc().x != M->GetChestLoc().x || P->getPlayerLoc().y != M->GetChestLoc().y){
                             for(int i = 0; i < numE; i++){ //loop through all enemies and determine movement
                                E[i].moveDirection(graph, P->getPlayerLoc().x, P->getPlayerLoc().y, i);
                             }
                         }
                         printGraph();
                    }
                }
                else{               //else shooting in down dir
                    P->shootArrow("down");
                    shooting = false;
                }
        break;

        case GLUT_KEY_LEFT:
                if(!shooting){      //if shooting = false player moving in left dir
                    if(P->getPlayerLoc().x-1 >= 0 && graph[P->getPlayerLoc().x-1][P->getPlayerLoc().y] != 'w'){ //determine if next cell is available
                         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
                         P->movePlayer(graph, "left");
                         if(P->getPlayerLoc().x != M->GetChestLoc().x || P->getPlayerLoc().y != M->GetChestLoc().y){
                             for(int i = 0; i < numE; i++){ //loop through all enemies and determine movement
                                E[i].moveDirection(graph, P->getPlayerLoc().x, P->getPlayerLoc().y, i);
                             }
                         }
                         printGraph();
                    }
                }
                else{               //else shooting in left dir
                    P->shootArrow("left");
                    shooting = false;
                }

        break;

        case GLUT_KEY_RIGHT:
                if(!shooting){      //if shooting = false player moving in right dir
                    if(P->getPlayerLoc().x+1 < 20 && graph[P->getPlayerLoc().x+1][P->getPlayerLoc().y] != 'w'){ //determine if next cell is available
                         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
                         P->movePlayer(graph, "right");
                         if(P->getPlayerLoc().x != M->GetChestLoc().x || P->getPlayerLoc().y != M->GetChestLoc().y){
                             for(int i = 0; i < numE; i++){ //loop through all enemies and determine movement
                                E[i].moveDirection(graph, P->getPlayerLoc().x, P->getPlayerLoc().y, i);
                             }
                         }
                         printGraph();
                    }
                }
                else{               //else shooting in right dir
                    P->shootArrow("right");
                    shooting = false;
                }
        break;

       }
    }
  glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}
