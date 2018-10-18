//Interactive.cpp includes all interactive elements of the game and their dependencies: Moving the mouse, pressing a key, valid mouse positions etc.

bool valid_mouse_x(int x){
//checks for valid cursor positions
    if(x>55 && x<946)
        return true;
    return false;
}
bool valid_mouse_y(int y){
    if(y>40 && y<725)
        return true;
    return false;
}

void updateMouse(int x, int y)
{   //updates mouse according to window rules (don't draw object inside menu screen for example)
    if(valid_mouse_x(x) && valid_mouse_y(y)){
            g_cursor_x = x;
            g_cursor_y = y;
    }
    else
        if(valid_mouse_x(x) && !valid_mouse_y(y))
            g_cursor_x = x;
        else
            if(!valid_mouse_x(x) && valid_mouse_y(y))
                g_cursor_y = y;
}


void mouse_passive(int x, int y)
{       //handles mouse passive events (dragging the mouse without clicking anything for example)    
        //only update mouse position if it doesn't hit borders
	updateMouse(x,y);
        //std::cerr << "\t cursor at (" << g_cursor_x << ", " << 1000-g_cursor_y << ")" << std::endl;
}


void mouse_click(int button, int state, int x, int y)
{       //handles mouse onclick events
        
	if (button==GLUT_LEFT_BUTTON)
	{          
		//std::cerr << "\t left mouse button pressed!" << std::endl;
                
                if(state == GLUT_DOWN){
                    
                    //Left-clicking creates a playerbullet, assign data and add to bullet vector    
                    Playerbullet bullet;
                    bullet.setX(g_cursor_x);
                    bullet.setY(1000-g_cursor_y+50);
                    PBulletvector.push_back(bullet);
                }
        
		if (state==GLUT_UP)
		{
			//std::cerr << "\t button released...click finished" << std::endl;
		}
	}
	else
	if (button==GLUT_RIGHT_BUTTON)
	{
		//std::cerr << "\t right mouse button pressed!" << std::endl;
	}
}

void motion_function(int x, int y)
{   //handles mouse whileClicked events (same as passive, keep moving the player plane even if left click is pressed)
    updateMouse(x,y);
}


void keyboard(unsigned char key, int, int)
{       // handles keyboard onPress eventss
	//std::cerr << "\t you pressed the " << key << " key" << std::endl;

	switch (key)
	{
		case 'q': exit(1); // quit!
	}
}