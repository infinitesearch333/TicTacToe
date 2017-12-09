#include "TicTacToe.h"
#include <iostream>
# include <ctime>
#include <time.h>
using namespace std;
//Default Constructor
TicTacToe :: TicTacToe()
{
    gameStart = false;
    gameEnd   = false;
    gameOutcome = Undetermined;
    typeOfGame  = U;
    
    clickCount  = 0;
    
    winningIndex1 = -1;
    winningIndex2 = -1;
    winningIndex3 = -1;
    
    FIRST_CORNER  = -1;
    SECOND_CORNER = -1;
}

//Setters
void TicTacToe :: setGameStart()
{
    gameStart = !gameStart;
}

void TicTacToe :: setGameType(gameType type)
{
    typeOfGame = type;
}

//Getters
bool TicTacToe :: getGameStartStatus(){return gameStart;}
bool TicTacToe :: getGameEndStatus(){return gameEnd;}
shape TicTacToe :: getGameOutcome(){return gameOutcome;}
gameType TicTacToe :: geTypeOfGame(){return typeOfGame;}

int TicTacToe :: getWinningIndex1(){return winningIndex1;}
int TicTacToe :: getWinningIndex2(){return winningIndex2;}
int TicTacToe :: getWinningIndex3(){return winningIndex3;}

//PRIVATE FUNCTIONS:
shape TicTacToe :: playerUp()
{
    
    //Player One Always Gets X's
    switch(clickCount % 2)
    {
        case 0:
            return O;
        case 1:
            return X;
    }
    
    //Will Never Reach...Avoids Warning
    return Undetermined;
    
}

//Board Examiners
void TicTacToe :: ExamineBoard(vector<Square *>& container)
{
    //Check First Row
    ExamineColumnRows(0, 2, 1, container);
    
    //Check Second Row
    ExamineColumnRows(3, 5, 1, container);
    
    //Check Third Row
    ExamineColumnRows(6, 8, 1, container);
    
    //Check First Column
    ExamineColumnRows(0, 6, 3, container);
    
    //Check Second Column
    ExamineColumnRows(1, 4, 3, container);
    
    //Check Third Column
    ExamineColumnRows(2, 8, 3, container);
    
    //Check Diagonals
    ExamineColumnRows(0, 8, 4, container);
    
    ExamineColumnRows(2, 6, 2, container);
    

    //Check If Game Is Over By Draw
    if((clickCount == 9) && (gameOutcome == Undetermined))
    {
        gameEnd = true;

    }
}

void TicTacToe :: ExamineColumnRows(int start, int end, int offset, vector<Square *> &container)
{
    int XCount = 0;
    int OCount = 0;
    
    //Count Number Of X's ANd O's In Combination
    for(int i = start; i <= end; i += offset)
    {
        if(container[i]->getShapeType() == X)
            ++XCount;
        else if(container[i]->getShapeType() == O)
            ++OCount;
    }
    
    //Check For Winner
    if(OCount == 3)
    {
        gameOutcome = O;    //Second Player Wins
        gameEnd = true;     //Game Is Over
        
        //Determine Winning indices
        winningIndex1 = start;
        winningIndex2 = start + offset;
        winningIndex3 = end;
    }
    else if(XCount == 3)
    {
        gameOutcome = X;    //Player One Wins
        gameEnd = true;     //Game Is Over
        
        //Determine Winning indices
        winningIndex1 = start;
        winningIndex2 = start + offset;
        winningIndex3 = end;
    }
    
}

//Decision Makers
bool TicTacToe :: HumanDecision(int index, vector<Square *> &container)
{
    //Check If Valid Move
    if(container[index]->getShapeType() != Undetermined)
        return false;
    
    //Else
    ++clickCount;
    //Insert Deision Into Grid
    container[index]->setShape(playerUp());
    //SetColor
    switch(clickCount % 2)
    {
        case 0:
            container[index]->setColors(1.0f, 0.43f, 0.78f);
            break;
        case 1:
             container[index]->setColors(0.0f, 1.0f, 0.0f);
    }
    //Examine Board
    ExamineBoard(container);
    
    //Valid Move
    return true;
}

//Computer Decision Helper Functions
bool TicTacToe :: ComputerExamineBoard(vector<Square *>& container)
{
    //Check First Row
    if(SearchXsANDOs(0, 2, 1, container))
        return true;
    //Check Second Row
    else if(SearchXsANDOs(3, 5, 1, container))
        return true;
    //Check Third Row
    else if(SearchXsANDOs(6, 8, 1, container))
        return true;
    //Check First Column
    else if(SearchXsANDOs(0, 6, 3, container))
        return true;
    //Check Second Column
    else if(SearchXsANDOs(1, 4, 3, container))
        return true;
    //Check Third Column
    else if(SearchXsANDOs(2, 8, 3, container))
        return true;
    //Check Diagonals
    else if(SearchXsANDOs(0, 8, 4, container))
        return true;
    else if(SearchXsANDOs(2, 6, 2, container))
        return true;
    
    //Else
    return false;
    
}

bool TicTacToe :: SearchXsANDOs(int start, int end, int offset, vector<Square *>& container)
{
    int XCount = 0;
    int OCount = 0;
    int totalCount = 0;
    int winningIndex = -1;
    
    //Count X And O Occurrences
    for(int i = start; i <= end; i += offset)
    {
        if(container[i]->getShapeType() == X)
        {
            ++XCount;
            ++totalCount;
        }
        else if(container[i]->getShapeType() == O)
        {

            ++OCount;
            ++totalCount;
        }
        else{
            std::cout << "Winning Index: " << winningIndex << "\n";
            winningIndex = i;}
    }
    
    //Block Or Complete Winning Moves
    if(((XCount == 2) || (OCount == 2)) && (totalCount < 3) && (winningIndex != -1))
    {
        cout << winningIndex <<endl;
        cout << "Xcount: " << XCount << "\n";
        cout << "OCount: " << OCount << "\n";
        container[winningIndex]->setShape(X);
        //Computer Has Made Move
        //SetColor.......
        container[winningIndex]->setColors(0.0, 1.0, 0.0);
        return true;
    }
    
    //Computer Has Not Made A Move
    return false;
}

//Artificial Intelligence
void TicTacToe :: ComputerDecision(vector<Square *> &container)
{
    //Increment Click Count
    ++clickCount;
    
    //Prioritize Blocking Human's Winning Moves OR Making Three Consequitve X's
    if(ComputerExamineBoard(container))
    {
        ExamineBoard(container);
        return;
    }
    //CORNER GAME
    //O's Correspond To Human
    //Computer's First Move
    if(clickCount == 1)
    {
        //Containing Ideal First Moves
        int corners[4] = {0,2,6,8};
        

        int time = clock();
        srand(time);
        //Record The First Corner
        FIRST_CORNER = corners[rand() % 4];
        //Make Move
        container[FIRST_CORNER]->setShape(X);
        //SetColor.......
        container[FIRST_CORNER]->setColors(0.0, 1.0, 0.0);
    }
    //Computer's Second Move
    else if(clickCount == 3)
    {
        //If Human's First Move Is Not Center
        if(container[4]->getShapeType() != O)
        {
            //Check FIRST_CORNER
            switch(FIRST_CORNER)
            {
                    //Top Left Corner
                case 0:
                    //Check If ML AND BL Are Not Human
                    if((container[3]->getShapeType() != O) && (container[6]->getShapeType() != O))
                    {
                        //Record 2nd Corner
                        SECOND_CORNER = 6;
                        //Make Move On BL
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    else
                    {
                        //Choose Alternative Corner TR
                        //Record Second Corner
                        SECOND_CORNER = 2;
                        //Make Move On TR
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    //Top Right Corner
                case 2:
                    //Check If MR AND BR Are Not Human
                    if((container[5]->getShapeType() != O) && (container[8]->getShapeType() != O))
                    {
                        //If So
                        //Record 2nd Corner
                        SECOND_CORNER = 8;
                        //Make Move On BR
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    else
                    {
                        //Choose Alternative Corner TL
                        //Record Second Corner
                        SECOND_CORNER = 0;
                        //Make Move On TL
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    
                    //Bottom Left Corner
                case 6:
                    //Check If ML AND TL Are Not Human
                    if((container[3]->getShapeType() != O) && (container[0]->getShapeType() != O))
                    {
                        //If So
                        //Record 2nd Corner
                        SECOND_CORNER = 0;
                        //Make Move On TL
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    else
                    {
                        //Choose Alternative Corner BR
                        //Record Second Corner
                        SECOND_CORNER = 8;
                        //Make Move On BR
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    
                    //Bottom Right Corner
                case 8:
                    //Check If MR AND TR Are Not Human
                    if((container[5]->getShapeType() != O) && (container[2]->getShapeType() != O))
                    {
                        //If So
                        //Record 2nd Corner
                        SECOND_CORNER = 2;
                        //Make Move On TR
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    else
                    {
                        //Choose Alternative Corner BL
                        //Record Second Corner
                        SECOND_CORNER = 6;
                        //Make Move On BL
                        container[SECOND_CORNER]->setShape(X);
                        //SetColor.......
                        container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
            }
        }
        //If Human's First Move Is Center
        //Different Approach
        else
        {
            //Check First Corner
            switch(FIRST_CORNER)
            {
                    //Top Left Corner
                case 0:
                    //Computer Automatically Selects BR
                    //Record Second Corner
                    SECOND_CORNER = 8;
                    //Make Move On BR
                    container[SECOND_CORNER]->setShape(X);
                    //SetColor.......
                    container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    break;
                    //Top Right Corner
                case 2:
                    //Computer Automatically Selects BL
                    //Record Second Corner
                    SECOND_CORNER = 6;
                    //Make Move On BL
                    container[SECOND_CORNER]->setShape(X);
                    //SetColor.......
                    container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    break;
                    
                    //Bottom Left Corner
                case 6:
                    //Computer Automatically Selects TR
                    //Record Second Corner
                    SECOND_CORNER = 2;
                    container[SECOND_CORNER]->setShape(X);
                    //SetColor.......
                    container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    break;
                    
                    //Bottom Right Corner
                case 8:
                    //Computer Automatically Selects TL
                    //Record Second Corner
                    SECOND_CORNER = 0;
                    container[SECOND_CORNER]->setShape(X);
                    //SetColor.......
                    container[SECOND_CORNER]->setColors(0.0, 1.0, 0.0);
                    break;
            }
        }
    }
    
    //Computer's Third Move
    else if(clickCount == 5)
    {

        //Special Cases Where Ideal Corners Are Picked But MR OR ML Were Human's First Move
        if((((FIRST_CORNER == 0) || (FIRST_CORNER == 6)) && ((SECOND_CORNER == 6)||(SECOND_CORNER == 0))) && (container[5]->getShapeType() == O))
        {
            //Computer Automatically Choses Center...Killer Move
            container[4]->setShape(X);
            //SetColor.......
            container[4]->setColors(0.0, 1.0, 0.0);
            return;
        }
        else if((((FIRST_CORNER == 2) || (FIRST_CORNER == 8)) && ((SECOND_CORNER == 8)||(SECOND_CORNER == 2))) && (container[3]->getShapeType() == O))
        {
            //Computer Automatically Choses Center...Killer Move
            container[4]->setShape(X);
            //SetColor.......
            container[4]->setColors(0.0, 1.0, 0.0);
            return;
        }
        //End Of Special Cases
        //Regular Cases
        //Check First Corner
        switch(FIRST_CORNER)
        {
                //TL
            case 0:
                //Check Second Corner
                switch (SECOND_CORNER)
            {
                    //Ideal 2nd Corner BL
                case 6:
                    //Check If TR Is Not Chosen By Human(Ideal 3rd Corner)
                    if(container[2]->getShapeType() != O)
                    {
                        //If So Make A Move On TR
                        container[2]->setShape(X);
                        //SetColor.......
                        container[2]->setColors(0.0, 1.0, 0.0);
                    }
                    //Alternative 3rd Corner
                    else
                    {
                        //Make Move On BR
                        container[8]->setShape(X);
                        //SetColor.......
                        container[8]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    //Alternative 2nd Corner TR
                case 2:
                    //Automatically Make Move On BR
                    container[8]->setShape(X);
                    //SetColor.......
                    container[8]->setColors(0.0, 1.0, 0.0);
                    break;
            }
                break;
                
                //TR
            case 2:
                //Check Second Corner
                switch (SECOND_CORNER)
            {
                    //Ideal 2nd Corner BR
                case 8:
                    //Check If TL Corner Is Not Chosen By Human(Ideal 3rd Corner)
                    if(container[0]->getShapeType() != O)
                    {
                        //If So Make A Move On TL
                        container[0]->setShape(X);
                        //SetColor.......
                        container[0]->setColors(0.0, 1.0, 0.0);
                    }
                    //Alternative Corner BL
                    else
                    {
                        //Make Move On BL
                        container[6]->setShape(X);
                        //SetColor.......
                        container[6]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    
                    //Alternative 2nd Corner
                case 0:
                    //Automatically Make Move On BL
                    container[6]->setShape(X);
                    //SetColor.......
                    container[6]->setColors(0.0, 1.0, 0.0);
                    break;
            }
                break;
                
                //BL
            case 6:
                //Check Second Corner
                switch(SECOND_CORNER)
            {
                    //Ideal Second Corner TL
                case 0:
                    //Check If BR Is Not Chosen By Human(Ideal 3rd Corner)
                    if(container[8]->getShapeType() != O)
                    {
                        //If So Make A Move On BR
                        container[8]->setShape(X);
                        //SetColor.......
                        container[8]->setColors(0.0, 1.0, 0.0);
                    }
                    //Alternative Corner TR
                    else
                    {
                        //Make A Move On TR
                        container[2]->setShape(X);
                        //SetColor.......
                        container[2]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    //Alternative Second Corner
                case 8:
                    //Automatically Make A Move On TR
                    container[2]->setShape(X);
                    //SetColor.......
                    container[2]->setColors(0.0, 1.0, 0.0);
                    break;
            }
                break;
                
                //BR
            case 8:
                //Check Second Corner
                switch(SECOND_CORNER)
            {
                    //Ideal Second Corner TR
                case 2:
                    //Check If BL Is Not Chosen By Human(Ideal 3rd Corner)
                    if(container[6]->getShapeType() != O)
                    {
                        //If So Make A Move On BL
                        container[6]->setShape(X);
                        //SetColor.......
                        container[6]->setColors(0.0, 1.0, 0.0);
                    }
                    //Alternative Corner TL
                    else
                    {
                        //Make Move On TL
                        container[0]->setShape(X);
                        //SetColor.......
                        container[0]->setColors(0.0, 1.0, 0.0);
                    }
                    break;
                    
                    //Alternative Second Corner
                case 6:
                    //Automatically Make A Move On TL
                    container[0]->setShape(X);
                    //SetColor.......
                    container[0]->setColors(0.0, 1.0, 0.0);
                    break;
            }
                break;
        }
    }
    ExamineBoard(container);
}









