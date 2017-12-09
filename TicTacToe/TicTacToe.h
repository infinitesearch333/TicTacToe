#ifndef TicTacToe_h
#define TicTacToe_h
#include"Square.h"
#include<cstdlib>
#include<vector>
using std :: vector;

//Enum Helps Determine Game Type...HH = Human VS Human...HC = Human VS Computer...U = Undetermined
enum gameType{U = 0, HH = 1, HC = 2};

class TicTacToe
{
private:
    //Game State Variables
    bool gameStart;
    bool gameEnd;
    gameType typeOfGame;    //Type Of Game Selected
    shape gameOutcome;      //Winner? Draw/X OR O
    int clickCount;         //9 Max
    
    //Winning Indices
    //Will Be Extracted By glutIdle() Function To Obtain A Flashing Effect When There Is A Winner
    int winningIndex1;
    int winningIndex2;
    int winningIndex3;
    
    //Corners...Used For Corner Game Strategy Used By AI
    int FIRST_CORNER;
    int SECOND_CORNER;
    
    //Private Functions:
    shape playerUp();   //Determines Who Is Up By Looking At Click Count
    //Examine The Board For A Winner/Draw
    void ExamineBoard(vector<Square *>& container);
    //Column/Row Examiner..Called By ExamineBoard(...)
    void ExamineColumnRows(int start, int end, int offset, vector<Square *>& container);
    //Check For Winning Moves For Either Computer OR Human
    bool ComputerExamineBoard(vector<Square *>& container);
    //Called By ComputerExamineBoard(...)
    bool SearchXsANDOs(int start, int end, int offset, vector<Square *>& container);

public:
    //Default Constructor
    TicTacToe();
    //Necessary Setters
    void setGameStart();                //Called Once After Game Type Has Been Selected
    void setGameType(gameType type);    //Called Once In Menu Screen
    
    //Decision Makers
    void ComputerDecision(vector<Square *>& container);
    //Returns True If Human Move Is Valid
    bool HumanDecision(int index, vector<Square *>& container);
    
    //Necessary Getters
    bool getGameStartStatus();
    bool getGameEndStatus();
    shape getGameOutcome();
    gameType geTypeOfGame();
    
    int getWinningIndex1();
    int getWinningIndex2();
    int getWinningIndex3();
    
};

#endif
    
    
    
