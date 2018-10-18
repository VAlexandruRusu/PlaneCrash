//Game timers that work independently of the main game timer due to various reasons

void enemyspawntimer(int extra)
{   //enemies spawn each second (subject to change)
    if(g_state == g_level_first)
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



void enemyplanespeeduptimer(int extra)
{       //speeds up all basic planes to increase difficulty gradually
        if(extra != g_score_total && g_score_total % 50 == 0){
            g_enemy_offset_increment+=0.1f;
        }
        glutTimerFunc(14,enemyplanespeeduptimer,g_score_total);
}

