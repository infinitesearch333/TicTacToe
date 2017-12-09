#include "App.h"
using namespace std;
#include <iostream>
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    // Add-on By Sergio Rosendo
    containerInit();
}

void App::draw() {

    //If Game Has Not Started Call Menu Screen
    if(!game.getGameStartStatus())
        MenuScreen();
    //Else If Game Has Started Call Game Screen
    else
    {
        GameScreen();
    }
    
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    //Check Which Rectangle Was Clicked
    //Only do while game started and is not over
    if((!game.getGameEndStatus()) && (game.getGameStartStatus() == true))
    {
        //Check which rectangle was clicked...
        int foundIndex;
        
        for(int  i = 0; i < container.size(); ++i)
        {
            if(container[i]->contains(mx, my))
            {
                //Mark Index
                foundIndex = i;
                //No further checking needed
                break;
            }
        }
        cout << "Index" << foundIndex << endl;
        //Make Move And Check If Computer Has To Go Next
        if(game.HumanDecision(foundIndex, container) && (game.geTypeOfGame() == HC))
        {
            //Computer Makes Move
            game.ComputerDecision(container);
        }
        
        
    }
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
    //Can Only  Press Menu Keys If The Gae Has Not Started
    if(!game.getGameStartStatus())
    {
        //User Would Like To Play H vs H
        if((key == 'h') || (key == 'H'))
        {
            //Start The Game
            game.setGameStart();
            game.setGameType(HH);
        }
        //User Would Like To Play H vs C
        else if((key == 'c')||(key == 'C'))
        {
            //Start The Game
            game.setGameStart();
            game.setGameType(HC);
            //Let Computer Make First Move
            game.ComputerDecision(container);
        }
        
        redraw();
    }
}

//Add-on By Sergio Rosendo
void App :: idle()
{
    //If the game is over and it is not a draw
    if((game.getGameEndStatus() == true) && (game.getGameOutcome() != U ))
    {
        float red   = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0));
        float green = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0));
        float blue  = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0));
        container[game.getWinningIndex1()]->setColors(red,green,blue);
        container[game.getWinningIndex2()]->setColors(red,green,blue);
        container[game.getWinningIndex3()]->setColors(red,green,blue);
    }
    
    //Else change all symbols to signal draw
    else if(game.getGameEndStatus() && (game.getGameOutcome() == Undetermined ))
    {
        for (int i = 0; i < container.size(); ++i)
        {
            container[i]->setColors(0.658824f, 0.658824f, 0.658824f);
    
        }
    }
}

void App :: containerInit()
{
    //Square 1(Top Left)
    Square *square1 = new Square(-1.0f, 1.0f);
    container.push_back(square1);
    
    //Square 2(Top Middle)
    Square *square2 = new Square(-0.333f, 1.0f);
    container.push_back(square2);
    
    //Square 3(Top Right )
    Square *square3 = new Square(0.333f, 1.0f);
    container.push_back(square3);
    
    //Square 4(Middle Left)
    Square *square4 = new Square(-1.0f, 0.333f);
    container.push_back(square4);
    
    //Square 5(Middle Middle)
    Square *square5 = new Square(-0.333f, 0.333f);
    container.push_back(square5);
    
    //Square 6(Middle Right)
    Square *square6 = new Square(0.333f,  0.333f);
    container.push_back(square6);
    
    //Square 7
    Square *square7 = new Square(-1.0f, -0.333f);
    container.push_back(square7);
    
    //Square 8
    Square *square8 = new Square(-0.333f, -0.333f);
    container.push_back(square8);
    
    //Square 9
    Square *square9 = new Square(0.333f, -0.333f);
    container.push_back(square9);
    
    
}

void App :: MenuScreen()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Draw Letters Using Rectangles
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    //T
    glVertex2f(-0.85f, 0.85f);
    glVertex2f(-0.70f, 0.85f);
    glVertex2f(-0.70f, 0.75f);
    glVertex2f(-0.85f, 0.75f);
    glVertex2f(-0.80f, 0.75f);
    glVertex2f(-0.75f, 0.75f);
    glVertex2f(-0.75f, 0.65f);
    glVertex2f(-0.80f, 0.65f);
    
    //i
    glVertex2f(-0.65f, 0.85f);
    glVertex2f(-0.55f, 0.85f);
    glVertex2f(-0.55f, 0.80f);
    glVertex2f(-0.65f, 0.80f);
    glVertex2f(-0.65f, 0.75f);
    glVertex2f(-0.55f, 0.75f);
    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.65f, 0.65f);
    
    //c
    glVertex2f(-0.50f, 0.85f);
    glVertex2f(-0.35f, 0.85f);
    glVertex2f(-0.35f, 0.80f);
    glVertex2f(-0.50f, 0.80f);
    glVertex2f(-0.50f, 0.80f);
    glVertex2f(-0.45f, 0.80f);
    glVertex2f(-0.45f, 0.70f);
    glVertex2f(-0.50f, 0.70f);
    glVertex2f(-0.50f, 0.70f);
    glVertex2f(-0.35f, 0.70f);
    glVertex2f(-0.35f, 0.65f);
    glVertex2f(-0.50f, 0.65f);
    
    //Pink Letters
    glColor3f(1.0f, 0.43f, 0.78f);
    //T
    glVertex2f(-0.30f, 0.85f);
    glVertex2f(-0.15f, 0.85f);
    glVertex2f(-0.15f, 0.75f);
    glVertex2f(-0.30f, 0.75f);
    glVertex2f(-0.25f, 0.75f);
    glVertex2f(-0.20f, 0.75f);
    glVertex2f(-0.20f, 0.65f);
    glVertex2f(-0.25f, 0.65f);
    
    //a
    glVertex2f(-0.10f, 0.85f);
    glVertex2f(0.05f, 0.85f);
    glVertex2f(0.05f, 0.80f);
    glVertex2f(-0.10f, 0.80f);
    glVertex2f(-0.10f, 0.80f);
    glVertex2f(-0.05f, 0.80f);
    glVertex2f(-0.05f, 0.65f);
    glVertex2f(-0.10f, 0.65f);
    glVertex2f(0.0f, 0.80f);
    glVertex2f(0.05f, 0.80f);
    glVertex2f(0.05f, 0.65f);
    glVertex2f(0.0f, 0.65f);
    glVertex2f(-0.05f, 0.75f);
    glVertex2f(0.0f, 0.75f);
    glVertex2f(0.0f, 0.70f);
    glVertex2f(-0.05f, 0.70f);
    
    //c
    glVertex2f(0.1f, 0.85f);
    glVertex2f(0.25f, 0.85f);
    glVertex2f(0.25f, 0.80f);
    glVertex2f(0.1f, 0.80f);
    glVertex2f(0.1f, 0.80f);
    glVertex2f(0.15f, 0.80f);
    glVertex2f(0.15f, 0.70f);
    glVertex2f(0.1f, 0.70f);
    glVertex2f(0.1f, 0.70f);
    glVertex2f(0.25f, 0.70f);
    glVertex2f(0.25f, 0.65f);
    glVertex2f(0.1f, 0.65f);
    
    //White Letters
    glColor3f(1.0f, 1.0f, 1.0f);
    //T
    glVertex2f(0.30f, 0.85f);
    glVertex2f(0.45f, 0.85f);
    glVertex2f(0.45f, 0.75f);
    glVertex2f(0.30f, 0.75f);
    glVertex2f(0.35f, 0.75f);
    glVertex2f(0.40f, 0.75f);
    glVertex2f(0.40f, 0.65f);
    glVertex2f(0.35f, 0.65f);
    
    //o
    glVertex2f(0.50f, 0.85f);
    glVertex2f(0.65, 0.85f);
    glVertex2f(0.65, 0.75f);
    glVertex2f(0.50f, 0.75f);
    glVertex2f(0.50f, 0.75f);
    glVertex2f(0.55f, 0.75f);
    glVertex2f(0.55f, 0.65f);
    glVertex2f(0.50f, 0.65f);
    glVertex2f(0.60f, 0.85f);
    glVertex2f(0.65f, 0.85f);
    glVertex2f(0.65f, 0.65f);
    glVertex2f(0.60f, 0.65f);
    glVertex2f(0.55f, 0.70f);
    glVertex2f(0.60f, 0.70f);
    glVertex2f(0.60f, 0.65f);
    glVertex2f(0.55f, 0.65f);
    
    //e
    glVertex2f(0.70f, 0.85f);
    glVertex2f(0.85f, 0.85f);
    glVertex2f(0.85f, 0.80f);
    glVertex2f(0.70f, 0.80f);
    glVertex2f(0.70f, 0.80f);
    glVertex2f(0.75f, 0.80f);
    glVertex2f(0.75f, 0.75f);
    glVertex2f(0.70f, 0.75f);
    glVertex2f(0.70f, 0.75f);
    glVertex2f(0.80f, 0.75f);
    glVertex2f(0.80f, 0.70f);
    glVertex2f(0.70f, 0.70f);
    glVertex2f(0.70f, 0.70f);
    glVertex2f(0.75f, 0.70f);
    glVertex2f(0.75f, 0.65f);
    glVertex2f(0.70f, 0.65f);
    glVertex2f(-0.85f, 0.65f);
    glVertex2f(0.85f, 0.65f);
    glVertex2f(0.85f, 0.60f);
    glVertex2f(-0.85f, 0.60f);
    
    glEnd();
    
    //Menu Options
    glRasterPos2f(-0.85f, 0.1f);
    glColor3f(1.0f, 1.0f, 1.0f);
    string firstLine  = "Choose 2nd Player :";
    string seconfLine = "> Human (Press H)";
    string thirdLine  = "> Computer (Press C)";
    
    for(int i = 0; i < firstLine.length(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, firstLine[i]);
    
    glRasterPos2f(-0.25f, -0.05f);
    for(int i = 0; i < seconfLine.length(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, seconfLine[i]);
    
    
    glRasterPos2f(-0.30f, -0.20f);
    for(int i = 0; i < thirdLine.length(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, thirdLine[i]);
    
    //Underlines
    glColor3f(1.0f, 0.43f, 0.78f);
    glBegin(GL_LINES);
    glVertex2f(-0.85f, 0.07f);
    glVertex2f(-0.25f, 0.07f);
    
    glVertex2f(-0.25f, -0.07f);
    glVertex2f(0.26f, -0.07f);
    
    glVertex2f(-0.30f, -0.22f);
    glVertex2f(0.30f, -0.22f);
    
    //Border
    glColor3f(0.5f, 0.8f, 0.2f);
    glVertex2f(-0.90f, 0.90f);
    glVertex2f(0.90f, 0.90f);
    glVertex2f(0.90f, 0.90f);
    glVertex2f(0.90f, -0.90f);
    glVertex2f(0.90f, -0.90f);
    glVertex2f(-0.90f, -0.90f);
    glVertex2f(-0.90f, -0.90f);
    glVertex2f(-0.90f, 0.90f);
    
    glVertex2f(0.90f, 0.55f);
    glVertex2f(-0.90f, 0.55f);
    glEnd();
    
    glFlush();
    glutSwapBuffers();
    
}

void App :: GameScreen()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Draw 3x3 grid
    glColor3f(0.5f, 0.8f, 0.2f);
    glBegin(GL_LINES);
    
    //Horizontal Lines
    glVertex2f(-1.0f, 0.333f);
    glVertex2f(1.0f, 0.333f);
    
    glVertex2f(-1.0f, -0.333f);
    glVertex2f(1.0f, -0.333f);
    
    //Vertical Lines
    glVertex2f(-0.333f, 1.0f);
    glVertex2f(-0.333f, -1.0f);
    
    glVertex2f(0.333f, 1.0f);
    glVertex2f(0.333f, -1.0f);
    
    //Border
    glLineWidth(7.0f);
    glVertex2f(-0.999f, 0.999f);
    glVertex2f(0.999f, 0.999f);
    glVertex2f(0.999f, 0.999f);
    glVertex2f(0.999f, -0.999f);
    glVertex2f(0.999f, -0.999f);
    glVertex2f(-0.999f, -0.999f);
    glVertex2f(-0.999f, -0.999f);
    glVertex2f(-0.999f, 0.999f);
    
    glEnd();
    
    //Draw Shapes
    for (int i = 0; i < container.size(); ++i)
    {
        //Extract color
        glColor3f(container[i]->getRed(), container[i]->getGreen(), container[i]->getBlue());
        
        //Draw X
        if(container[i]->getShapeType() == X)
        {
            glBegin(GL_QUADS);
            
            glVertex2f(container[i]->getCenterX() - 0.2, container[i]->getCenterY() + 0.1);
            glVertex2f(container[i]->getCenterX() - 0.1, container[i]->getCenterY() + 0.2);
            glVertex2f(container[i]->getCenterX() + 0.2, container[i]->getCenterY() - 0.1);
            glVertex2f(container[i]->getCenterX() + 0.1, container[i]->getCenterY() - 0.2);
            
            glVertex2f(container[i]->getCenterX() + 0.2, container[i]->getCenterY() + 0.1);
            glVertex2f(container[i]->getCenterX() + 0.1, container[i]->getCenterY() + 0.2);
            glVertex2f(container[i]->getCenterX() - 0.2, container[i]->getCenterY() - 0.1);
            glVertex2f(container[i]->getCenterX() - 0.1, container[i]->getCenterY() - 0.2);
            
            glEnd();
            
            redraw();
        }
        
        //Draw O
        else if (container[i] -> getShapeType() == O)
        {
            
            //Needed info to both inner and outer circle draw circle
            int numVertices = 1000;
            float radius   = 0.1f;
            float twoPi     = M_PI * 2;
            
            
            //Inner Circle...Black to match background
            glColor3f(0.0f, 0.0f, 0.0f);
            
            glBegin(GL_TRIANGLE_FAN);
            //Center vertex
            glVertex2f(container[i]->getCenterX(), container[i]->getCenterY());
            
            for(int j = 0; j <= numVertices; ++j)
            {
                glVertex2f(container[i]->getCenterX()+radius*cosf(j*twoPi/numVertices), container[i]->getCenterY()+radius*sinf(j*twoPi/numVertices));
                
            }
            glEnd();
            redraw();
            
            //Outer Circle
            radius = 0.2f;
            
            glColor3f(container[i]->getRed(), container[i]->getGreen(), container[i]->getBlue());
            
            glBegin(GL_TRIANGLE_FAN);
            //Center vertex
            glVertex2f(container[i]->getCenterX(), container[i]->getCenterY());
            
            for(int j = 0; j <= numVertices; ++j)
            {
                glVertex2f(container[i]->getCenterX()+radius*cosf(j*twoPi/numVertices), container[i]->getCenterY()+radius*sinf(j*twoPi/numVertices));
                
            }
            glEnd();
            redraw();
        }
        
    }
    
    glFlush();
    glutSwapBuffers();
}
