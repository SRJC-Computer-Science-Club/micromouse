/*
 Nick Alvarez
 CS Club
 2/9/16
 
 */

#include <iostream>
using namespace std;
class node {
public:
    int h;
    int g;
    int f;
    
    enum parent;
    
    bool Top;
    bool Left;
    bool Right;
    bool Bottom;
};

int main()
//........................................................................................

{
    bool pathfound = false;
    node maze[6][6];
    
    object pathfinder(maze[][], int start, int end){
        for(int h; h < 4; h++){
            findG(maze, h, finish);
            findH(maze, h, start);
        }
    }
    
    
}
