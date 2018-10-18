#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <stddef.h>
#include <iostream>

//Data structures 
#include <string.h>
#include <math.h>
#include <queue>
#include <deque>
#include <map>
#include <vector>
#include <unistd.h>
#include <thread>
#include <random>
#include <stack>

//Objects
#include "Playerbullet.cpp"
#include "Enemyplane.cpp"
#include "PlayerLives.cpp"
#include "Boss1.cpp"

//Game universal data
#include "GlobalVariables.cpp"

//Game graphics data
#include "Graphics.cpp"

#include "GameLogicTimers.cpp"

//Game logic data
#include "GameLogic.cpp"

//Game interaction data
#include "Interactive.cpp"

//Game timers data
#include "Timers.cpp"



void display()
{         
        
        //In order to account for window resize we must always check the window height/width
        //float screenheight = glutGet(GLUT_WINDOW_HEIGHT);
       // float screenwidth  = glutGet(GLUT_WINDOW_WIDTH);
    
        //first time set up the color buffer with blue and line width 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(2.0f);
    
        draw_borders();
        draw_menu();
        draw_player_plane();
        draw_player_lclick_attacks();
        draw_player_bonus_lives();
        switch(g_state){
            case g_level_first:
                //first state of game: only default enemy planes are drawn
                draw_enemy_planes();
            break;
            case g_level_boss_1:
                //second state: draw all planes remaining, then draw the first boss.
                draw_enemy_planes();
                draw_enemy_boss_1();
            break;
        }
	glutSwapBuffers(); 
        
}

void checkgamecondition()
{
    if(g_lives<1){
        
        std::cout<<"You lost"<<std::endl;
        glutDestroyWindow(Windowhandle);
        exit(1);
    }
}


//THE GAME TIMER CONTROLS THE REDISPLAY

void firstbosstimer(int extra)
{  //The timer that controls the first boss's actions: movements, attacks 
    if(g_state == g_level_boss_1)
    {//updates boss data 
       // update_enemy_boss_1();
       // std::cerr<<"BOSS DATA:"<<std::endl;
       // std::cerr<<"X, Y CORDS:"<<heliboss.getXcord()<<","<<heliboss.getYcord()<<std::endl;
       // std::cerr<<"LEFT DOWN X, Y CORDS:"<<heliboss.getLDXCorner()<<","<<heliboss.getLDYCorner()<<std::endl;
       // std::cerr<<"RIGHT UP X, Y CORDS:"<<heliboss.getRUXCorner()<<","<<heliboss.getRUYCorner()<<std::endl;
        
       moveFirstBoss();
    }
    glutTimerFunc(1000.0/4, firstbosstimer, g_state);
}

void firstbosswingtimer(int extra)
{   
    //controls first boss's wing movement by updating point coordinates every new frame (g_boss_1_wing_count is used because this is called in gametimer which has 1/60 control, which is too fast, so go in 3*1/60 = 1/20 speed)
    if(g_boss_1_wing_count == 2){
        heliboss.setWing1x(cos(heliboss.getTheta())*0.015f);
        heliboss.setWing1y(sin(heliboss.getTheta())*0.015f);
        heliboss.setWing2x(cos(heliboss.getTheta())*0.3f);
        heliboss.setWing2y(sin(heliboss.getTheta())*0.3f);
        heliboss.setTheta(heliboss.getTheta()+4);
        g_boss_1_wing_count=0;
    }
    else
        g_boss_1_wing_count++;
}

void LevelBoss1Control()
{
    //The boss1 state control method checks for correct state, activates the boss's wing timer (independent of anything else), spawns the boss if not spawned, activates the boss actions timer and checks for collisions
    if(g_state == g_level_boss_1){
        glutTimerFunc(0, firstbosswingtimer, g_state);
        if(g_boss_1_init == false){
            spawn_enemy_boss_1();
            g_boss_1_init = true;
            glutTimerFunc(1000.0/60, firstbosstimer, g_state);
        }
        checkPlayerBoss1Collision();
    }
}

void gametimer(int extra)
{   //every 1/60 seconds
    checkgamecondition();
    //if game isn't over first check for all player bullet collisions with enemies (update_player_lclick_attack), then update all game data to new coords
    update_player_lclick_attack();
    update_enemy_planes();
    update_player_bonus_lives();
    //after updating do checks for collisions
    checkPlaneEnemyCollision();
    checkPlaneBonusLifeCollision();
    
    
    
    
    
    //update game status (correctly determine g_state), then call all state methods 
    updateGameStatus();
    //will only act if g_state is at the correct value
    LevelBoss1Control();
   
    
    
    glutPostRedisplay();
    glutTimerFunc(1000.0/60, gametimer, 0);
}





void init()
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	glClearColor(0.560784, 0.560784, 0.737255, 0.0f); 
        
        
        
        //initial mouse positions
	g_cursor_x =  500; 
        g_cursor_y =  700;
        
        //start compiling list
        g_the_border            =   make_border(0);
        g_the_menu              =   make_border(1);
        g_the_game_lower_margin =   make_border(1);
}

int main(int argc, char* argv[])
{

        std::cout<<"Press 'q' to quit. To move the object, simply drag your mouse across the world."<<std::endl;
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); 
	glutInitWindowSize(1000, 1000); 
	glutInitWindowPosition(50, 0); 
        Windowhandle = glutCreateWindow("PlaneCrash"); 
	glutDisplayFunc(display); 
        //Hides cursor (leave it off for debugging)
        glutSetCursor(GLUT_CURSOR_NONE);
	// handlers for keyboard input
	glutKeyboardFunc(keyboard); 
	
	// mouse event handlers - passive, active & whenActive
	glutPassiveMotionFunc(mouse_passive); 
        glutMouseFunc(mouse_click); 
        glutMotionFunc(motion_function);
        
	init(); 
        
        //gametimer updates every 1/60, controls the coords of things that will be displayed
        glutTimerFunc(0, gametimer, 0);
        //the other timers must be independent of it due to various reasons
        glutTimerFunc(0, enemyspawntimer, 0);
        glutTimerFunc(0, playerlivesspawntimer, 0);
        glutTimerFunc(0, enemyplanespeeduptimer, 0);
        
	glutMainLoop(); 
        
	return 0; 
}
