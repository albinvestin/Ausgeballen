#include "Points.h"

using namespace std;

//Constructor
Points::Points(int numberofplayers)
{
    for (int i = 0; i < numberofplayers; i++)
    {
        playerpoints.push_back(0);
    }
}


void Points::increasePoints(int playerindex)
{
    if(playerindex > static_cast<int>(playerpoints.size()) || playerindex <= 0)
    {
        throw Points_Error("Invalid playerindex! " + to_string(playerindex));
    }
    else
    {
        ++playerpoints.at(playerindex - 1);
    }
}

int Points::getPoints(int playerindex)
{
    if(playerindex > static_cast<int>(playerpoints.size()) || playerindex < 1)
    {
        throw Points_Error("Invalid playerindex! " + to_string(playerindex));
    }
    else
    {
        return playerpoints.at(playerindex - 1);
    }
}
