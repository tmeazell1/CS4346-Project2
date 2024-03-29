#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Path{

};

struct Node{
    //node
    int value;
    Path p;
};

int main(){
    return 0;
}

bool DEEPENOUGH(Node position, int depth){

}

int STATIC(Node position, int player){

}

int OPPOSITE(int player){
    //return opposite
}

vector<Node> MOVEGEN(Node position, int player)
{
    //return list of successors
}

Node MINIMAXAB(Node position, int depth, int player, int useThresh, int passThresh){
    if (DEEPENOUGH(position, depth)){ 
        //then return the structure
        Path p;
        return {STATIC(position, player), p};
        // int VALUE = STATIC(position, player);
        // //PATH=nil
    }
    else
    {
        //generate one more ply of the tree
        vector<Node> SUCCESSORS;
        SUCCESSORS = MOVEGEN(position, player);
        Path bestPath;
        if(SUCCESSORS.empty())
        {
            //there are no moves to be made
            //return the same structure that would have been returned if DEEP-ENOUGH had returned TRUE.
            Path p;
            return {STATIC(position, player), p};
        }
        else{
            //go through each element
            Node RESULTSUCC;
            int NEWVALUE;
            for(Node SUCC : SUCCESSORS){
                RESULTSUCC = MINIMAXAB(SUCC, depth+ 1, OPPOSITE(player), -passThresh, -useThresh);
                NEWVALUE = -1 * RESULTSUCC.value;
                if(NEWVALUE > passThresh){
                    //we have found a successor that is better than any we have examined so far
                    passThresh = NEWVALUE;
                    bestPath = {}; //TODO: set BEST-PATH to the result of attaching SUCC to the front of RESULT-SUCC.p
                }
                else{
                    //we should stop examining this branch. But both thresholds and
                    //values have been inverted. So, if Pass-Thresh>= Use Thresh, then return
                    //immediately with the value
                    return{passThresh, bestPath};
                }
            }
            return{passThresh, bestPath};
        }
    }
}