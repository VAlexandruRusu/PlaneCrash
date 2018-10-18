//GlobalVariables.cpp contains all the global data used in the project

//macros
#define         g_level_first 1
#define         g_level_boss_1 2

// last cursor click
int g_cursor_x = 0;
int g_cursor_y = 0;

//list handles
unsigned int g_the_border = 0;
unsigned int g_the_menu = 0;
unsigned int g_the_game_lower_margin = 0;
int Windowhandle; //window is the handle of glutCreateWindow(), used in glutDestroyWindow(window);

//game-related data
int             g_lives = 3;
int             g_state = g_level_first;
float           g_bullet_offset = 10.0f;
float           g_enemy_offset  = 2.0f;
float           g_enemy_offset_increment = 0.1f;
float           g_bonus_lives_offset = 5.0f;
unsigned int    g_score_total = 0;
int             g_score_increment_e1 = 25;
int             g_boss_1_wing_count = 0;
bool            g_boss_1_init = false;
float           g_boss_1_xcord_offset = 40.0f;

//player-related data
bool            p_invincibility = false;

//Data structures to hold attacks, planes and other game-related interactions
//vectors will hold all bullets/enemy planes
std::vector<Playerbullet> PBulletvector;
std::vector<Enemyplane>   EPlanevector;
std::stack<PlayerLives>   PLivesstack;
Boss1 heliboss = Boss1(0,0.3f,0.015f,10);

//Pseudo-uniform random distribution 
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(1,2); // guaranteed unbiased
std::uniform_int_distribution<int> unixcord(55,943); // guaranteed unbiased