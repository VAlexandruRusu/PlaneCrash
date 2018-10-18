//GameLogic.cpp is used for calling and modifying the graphics declared in graphics.cpp (translate, scale, matrix proj etc) and update these graphics according to a set of rules.  Utilizes data from GlobalVariables.cpp

void draw_player_plane()
{   //draws a complete player plane graphic
    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
        glTranslatef(g_cursor_x,1000-g_cursor_y,0.0f); 
        //100x100 for testing, 500x500 for changing design
        glScalef(100.0f, 100.0f, 1.0f);
        draw_player_plane_graphic();
        //left half complete, now mirror (scale by x = -1 and draw to complete design)
        glScalef(-1.0f, 1.0f,1.0f);
        draw_player_plane_graphic();
        draw_player_plane_hitbox();
    glPopMatrix();
}

void draw_player_lclick_attacks()
{
    //draws a complete player lclick attack from the PBulletvector declared in GlobalVariables.cpp
    glColor3f(1.0f, 1.0f, 1.0f); 
    for (std::vector<Playerbullet>::iterator it = PBulletvector.begin() ; it != PBulletvector.end(); ++it){
    //loop through the vector of playerbullets using the iterator 'it', then display each bullet
        glPushMatrix();
            // it itself is just a reference, to get the actual value use (*it).operation or it->operation
            glTranslatef( (*it).getX(),(*it).getY(),0.0f); 
            glScalef(10.0f, 20.0f, 1.0f);
            draw_player_lclick_attacks_graphic();
        glPopMatrix();
    }    
}

void update_player_lclick_attack()
{
    //Updates all the lclick attacks that the player has made (stored in PBulletvector) at each of the Planes.cpp playerbullettimer call
    bool erased = false;    //will need to know if collision happened to not increment bullet offset
    for (std::vector<Playerbullet>::iterator it = PBulletvector.begin() ; it != PBulletvector.end(); ++it){
    //loop through the vector of playerbullets using the iterator 'it'
        if( (*it).getY() > 960 ){
            //no need for out of bounds bullets, erase
            PBulletvector.erase (it);
            --it;
        }
        else{//go through enemy planes vector searching for a collision
            for(std::vector<Enemyplane>::iterator EPit = EPlanevector.begin(); EPit!= EPlanevector.end(); ++EPit){
                //guaranteed to be in correct order since the first plane spawned will always be the one that gets deleted
                if( (*it).getX() >= (*EPit).getLDXCorner() && (*it).getX() <= (*EPit).getLDXCorner()+70 && (*it).getY() >= (*EPit).getY() && (*it).getY() <= (*EPit).getY()+125 ){
                    //on collision erase
                   PBulletvector.erase (it);
                    --it; 
                    EPlanevector.erase (EPit);
                    --EPit;
                    erased = true;
                    //update score
                    g_score_total += g_score_increment_e1;
                }
            }
            //otherwise simply update the new bullet location by incrementing with the global offset from GlobalVariables
            if(erased == false)
                 (*it).setY( (*it).getY()+g_bullet_offset );
        }
    }
}

void draw_enemy_planes() 
{   
   //draws a complete graphic of all the enemy planes. The planes are stored in EPlanevector.
   glColor3f(1.0f, 1.0f, 1.0f); 
    for(std::vector<Enemyplane>::iterator it = EPlanevector.begin(); it!= EPlanevector.end(); ++it){
        //loop through vector, for each plane display the graphic
        glPushMatrix();
            glTranslatef( (*it).getX(), (*it).getY(),0.0f); 
            glScalef(80.0f, -80.0f, 1.0f);
            draw_enemy_planes_graphic();
            //left half complete, now mirror (scale by x = -1 and draw to complete design)
            glScalef(-1.0f, 1.0f,1.0f);
            draw_enemy_planes_graphic();
            draw_enemy_planes_hitbox();
        glPopMatrix(); 
    }
}

void update_enemy_planes()
{
    //Updates all enemy planes location when called by the enemymovetimer located in Planes.cpp
    for (std::vector<Enemyplane>::iterator it = EPlanevector.begin(); it!= EPlanevector.end(); ++it){
    //loop through the vector of playerbullets using the iterator 'it', then update each bullet Y coord
        if( (*it).getY() < 285 ){
            //planes that reach the end get erased and the player loses a life
            EPlanevector.erase (it);
            --it;
            g_lives--;
        }
        else//update the plane location
            (*it).setY( (*it).getY()-g_enemy_offset-g_enemy_offset_increment );
    }
}

void spawn_enemy_plane()
{
    //spawns an enemy plane whenever called by enemyspawntimer located in Planes.cpp
    int xcord = unixcord(rng); //get a random xcord to place the plane according to the global variable set in GlobalVariables.cpp
    //Create a new plane, set xcord, set Y, push into vector. This plane will be updated by update_enemy_planes and drawn by draw_enemy_planes
    Enemyplane plane;
    plane.setCords(xcord,900);
    EPlanevector.push_back(plane);
    //std::cerr<<"Plane spawned at: "<<plane.getX()<<","<<plane.getY()<<std::endl;
    //std::cerr<<"CORNER COORDS: LDCORNER: "<<plane.getLDXCorner()<<","<<plane.getLDYCorner()<<std::endl;
}

void checkPlaneEnemyCollision()
{
    for(std::vector<Enemyplane>::iterator EPit = EPlanevector.begin(); EPit!= EPlanevector.end(); ++EPit){
                if( !(g_cursor_x < (*EPit).getLDXCorner()-20 || g_cursor_x > (*EPit).getRUXCorner()+20 || 1000-g_cursor_y > (*EPit).getRUYCorner()+30 || 1000-g_cursor_y < (*EPit).getLDYCorner()-30)  ){
                    //check collision in terms of the player plane corners compared to the enemy plane corners
                    EPlanevector.erase(EPit);
                    --EPit;
                   g_lives--;
                }
                    
    }
}

void spawn_player_bonus_life()
{
       int xcord = unixcord(rng);
       PlayerLives life;
       life.setCords(xcord,975);
       PLivesstack.push(life);
}

void draw_player_bonus_lives()
{   //draws a complete player bonus life graphic
    if(!PLivesstack.empty()){
        //safety check
        PlayerLives life = PLivesstack.top();
        glColor3f(0.556863f,   0.137255f,  0.137255f); 
        glPushMatrix();
            glTranslatef(life.getX(),life.getY(),0.0f); 
            glScalef(50.0f, 50.0f, 1.0f);
            draw_player_plane_graphic();
            //left half complete, now mirror (scale by x = -1 and draw to complete design)
            glScalef(-1.0f, 1.0f,1.0f);
            draw_player_plane_graphic();
            draw_player_plane_hitbox();
        glPopMatrix();
    }
}

void update_player_bonus_lives()
{
    //Updates all enemy planes location when called by the enemymovetimer located in Planes.cpp
    if(!PLivesstack.empty()){
        PlayerLives life = PLivesstack.top();
        PLivesstack.pop();
        life.setY(life.getY()-g_bonus_lives_offset);
        if(life.getY() >= 245)
        PLivesstack.push(life);
    }
}

void checkPlaneBonusLifeCollision()
{       //checks for collision between player and bonus lives
        if(!PLivesstack.empty()){
            //safety check
            PlayerLives life = PLivesstack.top();
            if( !(g_cursor_x < life.getLDXCorner()-20 || g_cursor_x > life.getRUXCorner()+20 || 1000-g_cursor_y > life.getRUYCorner()+30 || 1000-g_cursor_y < life.getLDYCorner()-30)  ){
                PLivesstack.pop();
                g_lives++;
            }
        }
}



