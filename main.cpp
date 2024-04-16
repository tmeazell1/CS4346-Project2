#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Node{
    //node
    int value;
    vector<Node> path;
    int gameBoard[3][3];
};

// struct Path{

// };

// Prototype functions
Node newNode(int value, vector<Node> p);
bool DEEPENOUGH(Node position, int depth);
bool isWin(Node position, int player);
void printBoard(Node n);
bool gameOver(Node n);
int EV1(Node position, int player);
int EV2(Node position, int player);
int EV3(Node position, int player);
int EV4(Node position, int player);
int OPPOSITE(int player);
vector<Node> MOVEGEN(Node position, int player);
Node MINIMAXAB(Node position, int depth, int player, int EV, int useThresh, int passThresh);

Node newNode(int value, vector<Node> p){
    Node newNode;
    newNode.value = value;
    newNode.path = p;
    for (int i=0; i<3; i++){
        for (int j =0; j<3; j++){
            newNode.gameBoard[i][j]=0; //set the gameboard to be equal to all 0s
        }
    }
    return newNode;
}

Node newNode(int value, vector<Node> p, int gb[3][3]){
    Node newNode;
    newNode.value = value;
    newNode.path = p;
    for (int i=0; i<3; i++){
        for (int j =0; j<3; j++){
            newNode.gameBoard[i][j]= gb[i][j]; //set the gameboard to be equal to gb
        }
    }
    return newNode;
}

bool DEEPENOUGH(Node position, int depth){
    if (depth > 4)//each move is .5 depth, so 9 moves = 4.5, the game is over
        return true;
    else if (isWin(position, 1) || isWin(position, 2))
        return true;
    else
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


void printBoard(Node n){ //simply prints the node's configuration
    std::cout << "|---|---|---|\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
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
        std::cout << "|---|---|---|\n";
    }
    cout << "\n\n";
}

bool gameOver(Node n){
    //return true if the game is over ie all nodes are filled
    //or if isWin(n, 1) or isWin(n, 2)
    if (isWin(n,1) || isWin(n,2)){
        return true;
    }
    bool isFilled = true; //bool tracks if board is completely filled
     for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (n.gameBoard[i][j] == 0) {
                isFilled = false;
            }
        }
    }
    return isFilled;
}

//TODO: figure out what evaluation function means in the minimax algorithm.
//We need 4 different EVs apparently lol
/*
    Potential evaluation function ideas: (from chatgpt lowk)
    Center Control:
        Assign a higher value if X controls the center of the board, and a lower value if O controls the center.
        This function evaluates the importance of controlling the center as it provides more opportunities for creating winning combinations.
        For example, if X occupies the center cell, the function could return a positive value; if O occupies the center, it could return a negative value.

    Corner Control:
        Assign values based on how many corners each player controls.
        Corners are strategic positions in Tic-Tac-Toe as they give more control over the board.
        You could give a higher value if X controls more corners and a lower value if O controls more corners.
        For instance, if X occupies more corners than O, the function could return a positive value; if O controls more corners, it could return a negative value.

    Potential Forks:
        Evaluate potential fork opportunities for each player.
        A fork is a situation where a player can win on their next move regardless of the opponent's move.
        Look for configurations where placing a mark could potentially lead to two possible winning paths.
        Assign a higher value if X has more potential forks and a lower value if O has more potential forks.
        For instance, if X has more potential fork opportunities, the function could return a positive value; if O has more, it could return a negative value.
        
        */
int EV1(Node position, int player){
    //TODO: implement the EV described in class
    return 1;
}
int EV2(Node position, int player){
    //TODO: implement another EV
    return 1;
}
int EV3(Node position, int player){
    //TODO: implement another EV
    return 1;
}
int EV4(Node position, int player){
    //TODO: implement another EV
    return 1;
}

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
    //using position.Gameboard, return a vector of nodes that contains every possible move
    //that the given player could make. ie if player =2, fill in each open square with a 2 and return that list of nodes
    vector<Node> successors; //vector to hold each possible move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (position.gameBoard[i][j] == 0) { //if there is an empty space
                Node succ = position; //make a new node, equivalent to position
                succ.gameBoard[i][j] = player; //fill this empty position with player's value
                successors.push_back(succ); //add this new node to our list
            }
        }
    }
    return successors;
}

Node MINIMAXAB(Node position, int depth, int player, int EV, int useThresh, int passThresh){
    if (DEEPENOUGH(position, depth)){ 
        //then return the structure
        vector<Node> path;
        path.push_back(position);
        switch(EV){
        case 1:
        {
        Node n = newNode(EV1(position, player), path, position.gameBoard);
        return n;
        break;
        }
        case 2:
        {
        Node n = newNode(EV2(position, player), path, position.gameBoard);
        return n;
        break;
        }
        case 3:
        {
        Node n = newNode(EV3(position, player), path, position.gameBoard);
        return n;
        break;
        }
        case 4:
        {
        Node n = newNode(EV4(position, player), path, position.gameBoard);
        return n;
        break;
        }
        default:
        {
        Node n = newNode(EV1(position, player), path, position.gameBoard);
        return n;
        break;
        }
        }
    }
    else
    {
        //generate one more ply of the tree
        vector<Node> SUCCESSORS = MOVEGEN(position, player);
        vector<Node> bestPath;
        if(SUCCESSORS.empty())
        {
            //there are no moves to be made
            //return the same structure that would have been returned if DEEP-ENOUGH had returned TRUE.
            vector<Node> path;
            path.push_back(position);
            switch(EV){
            case 1:
            {
            Node n = newNode(EV1(position, player), path, position.gameBoard);
            return n;
            break;
            }
            case 2:
            {
            Node n = newNode(EV2(position, player), path, position.gameBoard);
            return n;
            break;
            }
            case 3:
            {
            Node n = newNode(EV3(position, player), path, position.gameBoard);
            return n;
            break;
            }
            case 4:
            {
            Node n = newNode(EV4(position, player), path, position.gameBoard);
            return n;
            break;
            }
            default:
            {
            Node n = newNode(EV1(position, player), path, position.gameBoard);
            return n;
            break;
            }
            }
        }
        else{
            //go through each element
            Node RESULTSUCC;
            int NEWVALUE;
            for(Node SUCC : SUCCESSORS){
                RESULTSUCC = MINIMAXAB(SUCC, depth+ 1, OPPOSITE(player), EV, -passThresh, -useThresh);
                NEWVALUE = -1 * RESULTSUCC.value;
                if(NEWVALUE > passThresh){
                    //we have found a successor that is better than any we have examined so far
                    passThresh = NEWVALUE;
                    bestPath = RESULTSUCC.path; //TODO: set BEST-PATH to the result of attaching SUCC to the front of RESULT-SUCC.p.p
                    bestPath.push_back(SUCC);
                }
                else{
                    //we should stop examining this branch. But both thresholds and
                    //values have been inverted. So, if Pass-Thresh>= Use Thresh, then return
                    //immediately with the value
                    Node n = newNode(passThresh, bestPath, position.gameBoard);
                    return n;
                }
            }
            Node n = newNode(passThresh, bestPath, position.gameBoard);
            return n;
        }
    }
}

int main(){
    //lets represent x as player 1
    //and represent O as player 2
    int eval1;
    int eval2;
    cout << "Enter evaluation function for player 1: " << endl;
    cin >> eval1;
    cout << "\n" << endl;
    cout << "Enter evaluation function for player 2: " << endl;
    cin >> eval2;
    cout << "\n" << endl;

    if(eval1 < 1 || eval1 > 4 || eval2 < 1 || eval2 >4)
    {
        cout << "Invalid evaluation functions" << endl;
        return 0;
    }

    cout << "Starting simulation..." << endl;


    vector<Node> p;
    int depth =0;
    int passT1, passT2, useT1, useT2;
    switch(eval1) //TODO: implement actual max and min values for each EV
    {
        case 1:
        passT1= -4;
        useT1=4;
        break;
        case 2:
        passT1= -10;
        useT1=10;
        break;
        case 3:
        passT1= -10;
        useT1=10;
        break;
        case 4:
        passT1= -10;
        useT1=10;
        break;
    }
    switch(eval2) //TODO: implement actual max and min values for each EV
    {
        case 1:
        passT2= -4;
        useT2=4;
        break;
        case 2:
        passT2= -10;
        useT2=10;
        break;
        case 3:
        passT2= -10;
        useT2=10;
        break;
        case 4:
        passT2= -10;
        useT2=10;
        break;
    }
    Node currentNode = newNode(-10, p);
    while(!gameOver(currentNode))
    {
        //btw i have no idea if this is how we're supposed to do it
        currentNode = MINIMAXAB(currentNode, depth, 1, eval1, useT1, passT1);
        printBoard(currentNode);
        currentNode = MINIMAXAB(currentNode, depth, 2, eval2, useT2, passT2);
        printBoard(currentNode);
        depth++;
    }
    return 0;
}