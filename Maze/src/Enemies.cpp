/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Enemies.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;



Timer *T1 = new Timer();                             // Set Timer for animation
Enemies::Enemies()
{
    //ctor
    enmLoc.x=0;
    enmLoc.y=0;

    xmax =1;
    ymax =0.25;
    xmin =0;
    ymin =0;
    up= down = left=right=false;
    live = false;

}

Enemies::~Enemies()
{
    //dtor
}

void Enemies::initEnm(int grid,int numFrames, char * FileName)
{
    live = true;
    gridSize = grid;
    frames = numFrames;
    xmax =1/(float)frames;
    T1->Start();
    t = (float)(2.0/grid)/frames;
    unitWidth = (float)2.0/gridSize;
    enmTex = TextureLoader(FileName);
}


void Enemies::drawEnemy(char** graph)
{
    if(live){
        glColor3f(1.0,1.0,1.0);
        glBindTexture(GL_TEXTURE_2D,enmTex);

        glPushMatrix();
            animate(graph);
            glTranslatef(enmLoc.x,enmLoc.y,0.0);

            glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);

            glBegin(GL_POLYGON);
                glTexCoord2f(xmin,ymin);
                glVertex3f(1,1,0.0f);

                glTexCoord2f(xmax,ymin);
                glVertex3f(-1,1,0.0f);

                glTexCoord2f(xmax,ymax);
                glVertex3f(-1,-1,0.0f);

                glTexCoord2f(xmin,ymax);
                glVertex3f(1,-1,0.0f);
            glEnd();
        glPopMatrix();
    }
}

void Enemies::placeEnemy(int x, int y)
{
    unitWidth = 2.0/gridSize;
    x+=1;
    y+=1;
    enmLoc.x =  -1-unitWidth/2+(unitWidth)*x;
    enmLoc.y =  -1-unitWidth/2+(unitWidth)*y;
}


/*Movement of the enemy is based on shortest path
Because shortest path returns us N (North), S (south),
E (East), W (West) we make the changes based on those
directions*/
void Enemies::moveDirection(char** graph, float x, float y, int i)
{

    char nextDir = BFS(graph, x, y);
    if(nextDir == 'N'){
        moveEnemy("up");
    }
    else if(nextDir == 'S'){
        moveEnemy("down");
    }
    else if(nextDir == 'E'){
        moveEnemy("right");
    }
    else if(nextDir == 'W'){
        moveEnemy("left");
    }
}


void Enemies::moveEnemy(string dir)
{
    if(moveDis<=0){
       if(dir=="up"){up=true; down=left=right=false;}
       else if(dir=="down"){down=true; up=left=right=false;}
       else if(dir=="left"){left=true; down=up=right=false;}
       else if(dir=="right"){right=true; down=left=up=false;}
       else{up=left=right=false;}
    }
}

void Enemies::animate(char** graph)
{
    if(moveDis < unitWidth)
    {

    if(T1->GetTicks()<1000)
    {

    if(up)
    {
       if(enmLoc.y< 0.999-unitWidth/2)
        {
            enmLoc.y += t;
            if(graph[getEnemyLoc().x][getEnemyLoc().y-1] == 'w')
                graph[getEnemyLoc().x][getEnemyLoc().y-1] = 'w';
            else
                graph[getEnemyLoc().x][getEnemyLoc().y-1] = '0';
            graph[getEnemyLoc().x][getEnemyLoc().y] = 'e';
        }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.0;
        ymax =0.25;
        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
        }
    }

    else if(down)
    {
             if(enmLoc.y > -0.999+unitWidth/2)
               {
                    enmLoc.y -= t;
                    if(graph[getEnemyLoc().x][getEnemyLoc().y+1] == 'w')
                        graph[getEnemyLoc().x][getEnemyLoc().y+1] = 'w';
                    else
                        graph[getEnemyLoc().x][getEnemyLoc().y+1] = '0';
                    graph[getEnemyLoc().x][getEnemyLoc().y] = 'e';
               }
               moveDis +=t;

                xmin +=1/(float)frames;
                xmax +=1/(float)frames;
                ymin =0.25;
                ymax =0.5;

                if(xmax>1){
                    xmax =1/(float)frames;
                    xmin =0;
                }
    }
   else if(left)
   {
       if(enmLoc.x>-0.999+unitWidth/2)
        {
            enmLoc.x -= t;
            if(graph[getEnemyLoc().x+1][getEnemyLoc().y] == 'w')
                graph[getEnemyLoc().x+1][getEnemyLoc().y] = 'w';
            else
                graph[getEnemyLoc().x+1][getEnemyLoc().y] = '0';
            graph[getEnemyLoc().x][getEnemyLoc().y] = 'e';
         }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.75;
        ymax =1.0;

        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
        }
   }

   else if(right)
   {
           if(enmLoc.x<0.999-unitWidth/2)
              {
                    enmLoc.x += t;
                    if(graph[getEnemyLoc().x-1][getEnemyLoc().y] == 'w')
                        graph[getEnemyLoc().x-1][getEnemyLoc().y] = 'w';
                    else
                        graph[getEnemyLoc().x-1][getEnemyLoc().y] = '0';
                    graph[getEnemyLoc().x][getEnemyLoc().y] = 'e';
              }

               moveDis +=t;

                xmin +=1/(float)frames;
                xmax +=1/(float)frames;
                ymin =0.5;
                ymax =0.75;

                if(xmax>1){
                    xmax =1/(float)frames;
                    xmin =0;
                  }


   }

  }else T1->Reset();
}
 else {moveDis =0;down=up=left=right=false; }
}

//Checks if the player and enemy collide and if they do, player dies
void Enemies::collision(Maze* m, Player* p)
{
    if(live && p->getPlayerLoc().x == getEnemyLoc().x && p->getPlayerLoc().y == getEnemyLoc().y){
        m->loadBackgroundImage("images/end.png");
        m->win = true;
    }
}

//checks if an arrow and enemy collide and if they do the enemy dies
void Enemies::dead(int& enemC, Player* p)
{
    if(live && p->arrowStatus && p->getArrowLoc().x == getEnemyLoc().x && p->getArrowLoc().y == getEnemyLoc().y){
        live = false;
        p->arrowStatus = false;
        cout << "dead enemy" << endl;
        enemC -= 1;
    }
}


GridLoc Enemies::getEnemyLoc()
{
   GridLoc val;
   val.x = (int)(ceil((enmLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((enmLoc.y +(1-unitWidth))/unitWidth));

    return val;
}

//Used to check if the current position has been traveled already
bool Enemies::InExplored(pos current, vector<pos> explore)
{
    for(int i = 0; i < explore.size(); ++i){
        if(current.x == explore.at(i).x && current.y == explore.at(i).y){
            return true;
        }
    }
    return false;
}


/*breadth first search used to return us a direction the player should
move to go the shortest path*/
char Enemies::BFS(char** graph, float x, float y)
{
    if(live){
    queue<pos> paths;
    vector<pos> explored;

    pos curr;
    curr.x = getEnemyLoc().x;
    curr.y = getEnemyLoc().y;

    pos nextPos = curr;

    paths.push(curr);
    while(!paths.empty()){
        curr = paths.front();
        paths.pop();
            if(!InExplored(curr, explored)){
                if(curr.x == x && curr.y == y){
                    while(!paths.empty()){
                        paths.pop();
                    }
                    if(!curr.dir.empty())
                        return curr.dir.at(0);
                }
                else{
                    explored.push_back(curr);
                }
                //check moving N
                nextPos = curr;
                if(graph[curr.x][curr.y+1] != 'w'){
                    nextPos.y++;
                    nextPos.dir.push_back('N');
                    paths.push(nextPos);
                }

                //check moving S
                nextPos = curr;
                if(graph[curr.x][curr.y-1] != 'w'){
                    nextPos.y--;
                    nextPos.dir.push_back('S');
                    paths.push(nextPos);
                }

                //check moving E
                nextPos = curr;
                if(graph[curr.x+1][curr.y] != 'w'){
                    nextPos.x++;
                    nextPos.dir.push_back('E');
                    paths.push(nextPos);
                }

                //check moving W
                nextPos = curr;
                if(graph[curr.x-1][curr.y] != 'w'){
                    nextPos.x--;
                    nextPos.dir.push_back('W');
                    paths.push(nextPos);
                }
        }
    }
    }
}

