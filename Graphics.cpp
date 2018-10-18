//Graphics.cpp is concerned with the drawing of all the game's graphics (planes, bullets, circles, triangles, borders, menus) AND methods that help create these graphics (circles, text). Includes graphics stored as lists.


//PART 1: Graphics-Creation Methods (text, arcs etc)

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments) 
{       //draws an arc 
	float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	
	float x = r * cosf(start_angle);//we now start at the start angle
	float y = r * sinf(start_angle); 
    
	glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
	for(int ii = 0; ii < num_segments; ii++)
	{ 
		glVertex2f(x + cx, y + cy);

		float tx = -y; 
		float ty = x; 

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
}

void draw_text(const char* text)
{       //method used to draw text on the world
	size_t len = strlen(text);
        
	for (size_t i=0;i<len;i++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }
}

//PART 2: Actual game graphics

void draw_player_plane_graphic()
{   //draws left half of the player plane graphic
    
        static float vertex[15][2] = 
        {
            {    0.0f, 0.40f   },
            {   -0.05f,0.30f   },
            {   -0.06f,0.2f    },
            {   -0.15f,0.15f   },
            {   -0.18f,0.05f   },
            {   -0.30f,-0.1f   },
            {   -0.30f,-0.15f  },
            {   -0.18f,-0.25f  },
            {   -0.23f, -0.4f  },
            {   -0.23f, -0.45f },
            {   -0.15f, -0.50f },
            {   -0.10f, -0.45f },
            {   -0.10f, -0.40f },
            {   -0.05f, -0.45f },
            {    0.0f,  -0.40f }
              
        };
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<15;i++){
                glVertex2fv(vertex[i]);
            }
        glEnd();
}

void draw_player_plane_hitbox()
{   //draws a hitbox around the player plane (debug purposes)
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.30f,0.40f);
        glVertex2f(0.30f,0.40f);
        glVertex2f(0.30f,-0.50f);
        glVertex2f(-0.30f,-0.50f);
    glEnd();
}

void draw_player_lclick_attacks_graphic()
{       //draws the lclick attack graphic of the player's plane
    
        static float vertex[3][2] = 
        {
            {-1.0f,0.0f},
            {0.0f,1.0f},
            {1.0f,0.0f}
        };
        glBegin(GL_LINE_LOOP);
            for(int i=0;i<3;i++)
                    glVertex2fv(vertex[i]);
        glEnd();
}

void draw_enemy_planes_graphic()
{   //draws left half of the enemy planes graphic
     
    glBegin(GL_LINE_STRIP);
        
        static float vertex[25][2] = 
        {
            {    0.0f, 0.43f   },
            {   -0.05f,0.30f   },
            {   -0.06f,0.2f    },
            {   -0.09f,0.25f   },
            {   -0.12f,0.25f   },
            {   -0.12f,0.18f   },
            {   -0.20f,0.12f  },
            {   -0.20f,0.08f  },
            {   -0.12f,0.08f  },
            {   -0.15f,-0.03f },
            {   -0.15f, -0.05f },
            {   -0.36f, -0.18f },
            {   -0.36f, -0.32f },
            {   -0.15f, -0.28f },
            {   -0.15f, -0.30f },
            {   -0.215f, -0.35f },
            {   -0.28f,  -0.38f },
            {   -0.28f,  -0.45f },
            {   -0.215f,  -0.48f },
            {   -0.15f,  -0.48f },
            {   -0.15f,  -0.56f },
            {   -0.06f,  -0.72f },
            {   -0.06f,  -0.78f    },
            {   -0.15f,  -0.86f    },
            {   0.0f,    -0.86f    },
               
        };
        int rows =  sizeof vertex / sizeof vertex[0];
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<rows;i++){
                glVertex2fv(vertex[i]);
            }
        glEnd();
    glEnd();
}

void draw_enemy_planes_hitbox()
{   //draws a hitbox around the enemy planes (debug purposes)
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.36f,0.40f);
        glVertex2f(0.36f,0.40f);
        glVertex2f(0.36f,-0.86f);
        glVertex2f(-0.36f,-0.86f);
    glEnd();
}

//PART 3: Perifery game graphics (menus, borders)

unsigned int make_border(int state)
{       //list-based implementation of creating the game border. OBS: The method is called in Planes.cpp, assigned to the lsit global variable from GlobalVariables.cpp, then once aggain called in Planes.cpp's display method
	static float vertex[4][2] =
		{
			{-1.0f, -1.0f},
			{ 1.0f, -1.0f},
			{ 1.0f, 1.0f},
                        {-1.0f, 1.0f}
		};

	// request a single display list handle
	unsigned int handle = glGenLists(1); 

	glNewList(handle, GL_COMPILE);
        //draw a line loop (no inner obj color) or polygon (inner obj color) depending on state
        if(state == 0)
            glBegin(GL_LINE_LOOP);
        else
            glBegin(GL_POLYGON);
		for (size_t i=0;i<4;i++)
			glVertex2fv(vertex[i]);
            glEnd();
	glEndList();
	return handle;
}

void draw_borders()
{       //draws the game border 
        glColor3f(0.0f, 1.0f, 1.0f); 
        glMatrixMode(GL_MODELVIEW);
    
	glPushMatrix();
		glTranslatef(500.0f, 500.0f, 0.0f);
		glScalef(499.0f, 499.0f, 1.0f);
		// execute a pre-compiled display list
		glCallList(g_the_border);

	glPopMatrix(); 
        
        //draw the bottom interface border 
        glColor3f(1.0f, 0.0f, 0.0f); 
        glPushMatrix();
		glTranslatef(500.0f, 112.0f, 0.0f);
		glScalef(498.5f, 110.0f, 1.0f);
		// execute a pre-compiled display list
		glCallList(g_the_game_lower_margin);
	glPopMatrix(); 
}

void draw_menu()
{       
        //draw the game border situated inside the bottom interface border
        glColor3f(0.0f, 0.0f, 0.0f); 
        glPushMatrix();
		glTranslatef(500.0f, 115.0f, 0.0f);
		glScalef(420.0f, 85.0f, 1.0f);
		// execute a pre-compiled display list
		glCallList(g_the_menu);
	glPopMatrix(); 
        
        //draw the lives string situated inside the game border
        glColor3f(0.0f, 1.0f, 1.0f); 
        glPushMatrix();
                glTranslatef(150.0f,95.0f,0.0f);
                glScalef(0.4f,0.4f,1.0f);
                draw_text("Lives:");
        glPopMatrix();
        
        //draw the lives as planes
        for(int i = 1; i<=g_lives;i++){
            glPushMatrix();
                if(i>6){
                    //if too many lives on row switch rows
                    int reps = g_lives - i;
                    glTranslatef(250.0f + reps*50.0f,60.0f,0.0f);
                }else
                    glTranslatef(250.0f + i*50.0f,115.0f,0.0f);
                glScalef(50.0f,50.0f,1.0f);
                draw_player_plane_graphic();
                glScalef(-1.0f,1.0f,1.0f);
                draw_player_plane_graphic();
            glPopMatrix();
        }
       //draw score text 
       glPushMatrix();
                glTranslatef(570.0f,95.0f,0.0f);
                glScalef(0.4f,0.4f,1.0f);
                draw_text("Score:");
       glPopMatrix();
       //draw the score 
       glPushMatrix();
                glTranslatef(720.0f,95.0f,0.0f);
                glScalef(0.4f,0.4f,1.0f);
                //cast int to const char*, then draw
                std::string s = std::to_string(g_score_total);
                char const *pchar = s.c_str();
                draw_text(pchar);
        glPopMatrix();
        
        
        
}





