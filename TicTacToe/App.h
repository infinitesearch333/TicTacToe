#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
//Add-on By Sergio Rosendo
#include"Square.h"
#include "TicTacToe.h"
#include<string>
#include<vector>
#include<cmath>
using std :: vector;
using std :: string;

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
    
    //Add-on By Sergio Rosendo
    vector<Square*> container;
    TicTacToe game;
    void MenuScreen();
    void GameScreen();
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    
    //Add-on By Sergio Rosendo
    void containerInit();
    void idle();
    
};

#endif
