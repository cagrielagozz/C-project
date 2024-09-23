#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


const int WALLS=1; //Constant representing a walls
const int PATH=0;  //Constant representing a path


//2D vector representing the maze
vector<vector<int>>maze;
int size;
int firstX=0, firstY=0;
int lastX, lastY;
vector<pair<int,int>>path; //Vector storing the correct path



//Start the maze with walls
void startMaze() {
    maze.resize(size, vector<int>(size, WALLS)); //Set all cells to walls '1'
}


//Create a path from start to end
void createPath() {
    int x=firstX, y=firstY;
    maze[x][y]=PATH; //Set the starting point for (0,0)

    while(x<size-1||y<size-1) {
        if(x<size-1) {
            x++;
            maze[x][y]=PATH;
        }
        if(y<size-1) {
            y++;
            maze[x][y]=PATH;
        }
    }
}


//Create random paths
void createRandomPaths() {
//Initialize random number generator
    srand(time(0));
    for (int i=1;i<size-1;++i) {
        for(int j=1;j<size-1;++j) {
            if (maze[i][j]==WALLS&&(rand()%4==0)) {
                maze[i][j]=PATH;
            }
        }
    }
}


//Print the maze
void printMaze() {
    cout<<"------\n|MAZE|\n------\n";
    for(int i=0;i<size;++i) {
        for(int j=0;j<size;++j) {
            cout<<maze[i][j]<<" ";
        }
        cout<<endl;
    }
}


//Find the correct path using DFS
bool correctPath(int x,int y) {
    if(x<0||x>=size||y<0||y>=size||maze[x][y]!=PATH) {
        return false;
    }

    if(x==lastX&&y==lastY) {
        path.push_back({x,y});
        return true;
    }

    maze[x][y]=WALLS; //Mark as visited

    //Try moving in all four directions
    if(correctPath(x+1,y)||correctPath(x-1,y)||correctPath(x,y+1)||correctPath(x,y-1)) {
        path.push_back({x,y});
        return true; //Save the coordinates if the correct path was found
    }

    return false;
}


//Print the coordinates of the correct path
//Always true
void printXY() {
    cout<<"\n\nOutputh Path"<<endl;
    cout<<" ---------";
    cout<<"\n | X | Y |"<<endl;
    cout<<" ---------"<<endl;
    for(auto it=path.rbegin();it!=path.rend();++it) {
        cout<< " | ";
        cout<<it->first<<" | "<<it->second; 
        cout<<" |"<<endl;
    }
}


int main() {
    //Applies to higher sizes, but is limited for a more stable image
    cout<<"Enter one side length of the square maze(1-50): ";
    cin>>size;
    lastX=size-1;
    lastY=size-1;

    startMaze();
    createPath();
    createRandomPaths();
    printMaze();
    
    if(correctPath(firstX,firstY)) {
        printXY();
    }

    return 0;
}