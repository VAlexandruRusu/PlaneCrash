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

//Game universal data
#include "GlobalVariables.cpp"

//Game graphics data
#include "Graphics.cpp"

//Game logic data
#include "GameLogic.cpp"

//Game interaction data
#include "Interactive.cpp"

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
        draw_enemy_planes();
        draw_player_bonus_lives();
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

void gametimer(int extra)
{   //the timer method will redisplay every 16 milliseconds
    checkgamecondition();
    //will have to check for collisions
    checkPlaneEnemyCollision();
    checkPlaneBonusLifeCollision();
    glutPostRedisplay();
    glutTimerFunc(1000.0/60, gametimer, 0);
}

void playerbullettimer(int extra)
{   //the timer method will redisplay every 16 milliseconds
    update_player_lclick_attack();
   
    glutTimerFunc(1000.0/60, playerbullettimer, 0);
}

void enemymovetimer(int extra)
{   //enemies move in 30 fps
    update_enemy_planes();
    glutTimerFunc(1000.0/60, enemymovetimer, 0);
}

void enemyspawntimer(int extra)
{   //enemies spawn each second (subject to change)
    spawn_enemy_plane();
    glutTimerFunc(500,enemyspawntimer,0);
}

void playerlivesspawntimer(int extra)
{   //spawns player lives on score condition
    if(extra != g_score_total &&  g_score_total%150 == 0){
        //extra stores the score total such that it will only spawn once after the if check (includes 0 case)
        spawn_player_bonus_life();
    }
    glutTimerFunc(14,playerlivesspawntimer,g_score_total);
}

void playerlivesmovetimer(int extra)
{
    update_player_bonus_lives();
    glutTimerFunc(1000.0/60,playerlivesmovetimer,0);
}

void enemyplanespeeduptimer(int extra)
{
        if(extra != g_score_total && g_score_total % 50 == 0){
            g_enemy_offset_increment+=0.1f;
        }
        glutTimerFunc(14,enemyplanespeeduptimer,g_score_total);
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
        
        //different timer methods depending on what is to be displayed
        glutTimerFunc(0, gametimer, 0);
        glutTimerFunc(0, playerbullettimer, 0);
        glutTimerFunc(0, enemymovetimer, 0);
        glutTimerFunc(0, enemyspawntimer, 0);
        glutTimerFunc(0, playerlivesspawntimer, 0);
        glutTimerFunc(0, playerlivesmovetimer, 0);
        glutTimerFunc(0, enemyplanespeeduptimer, 0);
        
	glutMainLoop(); 
        
	return 0; 
}
