/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Maze.h>


Maze::Maze()
{
    win = false;
}

Maze::Maze(int gSize)                                        // Constructor
{
    //ctor
    gridSize =gSize;

    unitWidth = (float)2/gridSize;
    liveChest = true;
    liveSetOfArrws=true;
}

Maze::~Maze()
{
    //dtor
}
void Maze::loadChestImage(char* FileName)
{
    chestTex = TextureLoader(FileName);
}

void Maze::loadBackgroundImage(char* FileName)
{
   bakTex = TextureLoader(FileName);
}

void Maze::loadSetOfArrowsImage(char* FileName)
{
    liveSetOfArrws = true;
    ArrBnchTex =  TextureLoader(FileName);
}

void Maze::placeChest(int x, int y)
{
   chestLoc.x =  converter(x,y).x;
   chestLoc.y =  converter(x,y).y;
}

void Maze::placeStArrws(int x, int y)
{
   setOfArrsLoc.x =  converter(x,y).x;
   setOfArrsLoc.y =  converter(x,y).y;
}



GridLoc Maze::GetChestLoc()
{
   GridLoc val;

   val.x = (int)(ceil((chestLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((chestLoc.y +(1-unitWidth))/unitWidth));

   return val;
}



GridLoc Maze::GetStArrwsLoc()
{
    GridLoc val;

   val.x = (int)(ceil((setOfArrsLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((setOfArrsLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

void Maze::arrowsPickUp(Player* p)
{
    if(liveSetOfArrws && p->getPlayerLoc().x == GetStArrwsLoc().x && p->getPlayerLoc().y == GetStArrwsLoc().y){
        liveSetOfArrws = false;
    }
}


int Maze::getGridSize()
{
  return gridSize;
}


void Maze::drawBackground()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,bakTex);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}


void Maze::drawGrid()
{
   float a;
   glColor4f(1.0,1.0,1.0,0.2);
   glDisable(GL_TEXTURE_2D);
   glPointSize(1);
   glBegin(GL_LINES);

   for(int i =0;i<gridSize;i++)
    {
         a = -1+(float)unitWidth*i;
         glVertex3f(a,1,-0.4);
         glVertex3f(a,-1,-0.4);
         glVertex3f(-1,a,0.4);
         glVertex3f(1,a,0.4);
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void Maze::drawArrows()
{
    if(liveSetOfArrws)
    {

    glColor3f(1.0,1.0,1.0);

    glTranslatef(setOfArrsLoc.x,setOfArrsLoc.y,1.0);
    glRotated(-spin,0,0,1);

    glBindTexture(GL_TEXTURE_2D,ArrBnchTex);
    glScaled(1.0/(float)(gridSize),1.0/(float)(gridSize),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }
}

void Maze::victory()
{
    loadBackgroundImage("images/victory.jpg");
    win = true;
}

//takes in a player and checks if they have reached the dragon chest
bool Maze::victory(Player* p)
{
    if((p->getPlayerLoc().x == GetChestLoc().x && p->getPlayerLoc().y == GetChestLoc().y)){
        ++level;
        loadBackgroundImage();
         return true;
    }
    return false;
}


//If the player has come across explosive arrows they add them to their arrows
void Maze::addArrow(Player* P)
{
    if(liveSetOfArrws && P->getPlayerLoc().x == GetStArrwsLoc().x && P->getPlayerLoc().y == GetStArrwsLoc().y){
        P->arrows = P->arrows + 10;
        //placeStArrws(-88,-88);
        liveSetOfArrws = false;
        cout << "Add arrows" << endl;
    }
}


void Maze::drawChest()
{
    if(liveChest){
    glColor3f(1.0,1.0,1.0);

    glTranslatef(chestLoc.x,chestLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,chestTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);
    glRotated(spin,0,0,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

     spin +=0.5;
    }
}

loc Maze::converter(int x, int y)
{
       loc val;

        x+=1;
        y+=1;
       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}

//Load images based off of the current level
void Maze::loadBackgroundImage(){

    if(level == 0){
        cout << "LV 0" << endl;
        bakTex = TextureLoader("images/landing.jpg");
    }
    else if(level == 1){
        cout << "LV 1" << endl;
        bakTex = TextureLoader("images/bak.jpg");
    }

    else if(level == 2){
        cout << "LV 2" << endl;
        bakTex = TextureLoader("images/back.png");
    }
    else if(level == 3){
        bakTex = TextureLoader("images/victory.jpg");
        win = true;
    }
}

