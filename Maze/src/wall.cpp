/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <wall.h>
#include <iostream>

using namespace std;


wall::wall()
{
    //ctor
    liveWall = false;
}

wall::~wall()
{
    //dtor
}

void wall::wallInit(int grid,char* FileName)
{
    liveWall = true;
    gridSize = grid;
    unitWidth = (float)2.0/grid;
    wallTex = TextureLoader(FileName);
}

void wall::drawWall()
{
    if(liveWall)
    {

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,wallTex);

    glPushMatrix();
    glTranslatef(wallBrk.x,wallBrk.y,0.0);

    glScalef(1.0/(float)gridSize,1.0/(float)gridSize,1);


     glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex3f(1,1,0.0f);

            glTexCoord2f(1,0);
            glVertex3f(-1,1,0.0f);

            glTexCoord2f(1,1);
            glVertex3f(-1,-1,0.0f);

            glTexCoord2f(0,1);
            glVertex3f(1,-1,0.0f);
    glEnd();
    glPopMatrix();
    }
}

void wall::placeWall(int x, int y)
{

    GetWallLoc.x= x;
    GetWallLoc.y= y;

    x+=1;
    y+=1;

    wallBrk.x =  (unitWidth)*x-1-unitWidth/2;
    wallBrk.y =  (unitWidth)*y-1-unitWidth/2;
}


void wall::drawWall(Player *p, char ** graph)
{
    if(liveWall)
    {

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,wallTex);

    glPushMatrix();
    glTranslatef(wallBrk.x,wallBrk.y,0.0);

    glScalef(1.0/(float)gridSize,1.0/(float)gridSize,1);


     glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex3f(1,1,0.0f);

            glTexCoord2f(1,0);
            glVertex3f(-1,1,0.0f);

            glTexCoord2f(1,1);
            glVertex3f(-1,-1,0.0f);

            glTexCoord2f(0,1);
            glVertex3f(1,-1,0.0f);
    glEnd();
    glPopMatrix();
    }
    /*Here we check to see if an arrow and a wall collide
if the do then we stop drawing both of them and update our matrix
We would also see arrowStatus to false because if not when a new level
is loaded and a wall is place on that location while it was active it would
read it as a collusion and not spawn the wall. We set the liveWall to false so
once collusion happens the wall no longer appears */

    if(p->getArrowLoc().x == GetWallLoc.x && p->getArrowLoc().y == GetWallLoc.y && liveWall && p->arrowStatus){
        p->arrowStatus = false;
        liveWall = false;
        graph[GetWallLoc.x][GetWallLoc.y] = '0';
    }

}
