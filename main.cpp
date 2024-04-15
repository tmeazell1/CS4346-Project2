#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Path{
    vector<Node> p;
};

struct Node{
    //node
    int value;
    Path p;
    int gameBoard[3][3];
};

int main(){
    //lets represent x as player 1
    //and represent O as player 2
    Path p;
    int depth =0;
    Node currentNode = newNode(-10, p);
    while (!gameOver(currentNode))
    {
        //btw i have no idea if this is how we're supposed to do it
        currentNode = MINIMAXAB(currentNode, depth, 1, 1, 10, -10);
        printBoard(currentNode);
        currentNode = MINIMAXAB(currentNode, depth, 2, 1, 10, -10);
        printBoard(currentNode);
        depth++;
    }
    return 0;
}

Node newNode(int value, Path p){
    Node newNode;
    newNode.value = value;
    newNode.p = p;
    for (int i=0; i<3; i++){
        for (int j =0; j<3; j++){
            newNode.gameBoard[i][j]=0; //set the gameboard to be equal to all 0s
        }
    }
}

bool DEEPENOUGH(Node position, int depth){
    if (depth > 4)//each move is .5 depth, so 9 moves = 4.5, the game is over
        return true;
    else if (isWin(position, 1) || isWin(position, 2))
        return true;
    else
        return false;

}


void printBoard(Node n){ //simply prints the node's configuration
    std::cout << "--|---|---|---|\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < 3; ++j) {
            if (n.gameBoard[i][j] == 1) {
                std::cout << "X | ";
            } else if (n.gameBoard[i][j] == 2) {
                std::cout << "O | ";
            } else {
                std::cout << "  | ";
            }
        }
        std::cout << "\n";
        std::cout << "--|---|---|---|\n";
    }
}

bool gameOver(Node n){
    //TODO: return true if the game is over ie all nodes are filled
    //or if isWin(n, 1) or isWin(n, 2)
    return false;
}

bool isWin(Node position, int player){
    //return true if the node represents a winning position for that player
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (position.gameBoard[i][0] == player && position.gameBoard[i][1] == player && position.gameBoard[i][2] == player) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (position.gameBoard[0][j] == player && position.gameBoard[1][j] == player && position.gameBoard[2][j] == player) {
            return true;
        }
    }
    // Check diagonals
    if ((position.gameBoard[0][0] == player && position.gameBoard[1][1] == player && position.gameBoard[2][2] == player) ||
        (position.gameBoard[0][2] == player && position.gameBoard[1][1] == player && position.gameBoard[2][0] == player)) {
        return true;
    }
    
    return false; // If no win condition is met
}

//TODO: figure out what evaluation function means in the minimax algorithm.
//We need 4 different EVs apparently lol
int EV1(Node position, int player){
    //TODO: implement the EV described in class
}
int EV2(Node position, int player){
    //TODO: implement another EV
}
int EV3(Node position, int player){
    //TODO: implement another EV
}
int EV4(Node position, int player){
    //TODO: implement another EV
}

//we dont need this?

// int STATIC(Node position, int player){ //returns the win / lose / draw. ie win = 10, loss =-10, draw =0
//     if (isWin(position, player)){
//         return 10;
//     }
//     else if (isWin(position, OPPOSITE(player))){
//         return -10;
//     }
//     else{
//         return 0;
//     }
// }

int OPPOSITE(int player){
    //return opposite player
    if (player == 1)
        return 2;
    else
        return 1;
}

vector<Node> MOVEGEN(Node position, int player)
{
    //return list of successors
    //TODO: using position.Gameboard, return a vector of nodes that contains every possible move
    //that the given player could make. ie if player =2, fill in each open square with a 2 and return that list of nodes
}

Node MINIMAXAB(Node position, int depth, int player, int EV, int useThresh, int passThresh){
    if (DEEPENOUGH(position, depth)){ 
        //then return the structure
        Path path;
        path.p.push_back(position);
        switch(EV){
        case 1:
         return {EV1(position, player), p};
         break;
        case 2:
        return {EV2(position, player), p};
        break;
        case 3:
        return {EV3(position, player), p};
        break;
        case 4:
        return {EV4(position, player), p};
        break;
        default:
         return {EV1(position, player), p};
         break;
        }

        //return {STATIC(position, player), p};
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