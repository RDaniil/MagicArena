//-----------------Player defines-------------------
#define PLAYER_HP 			50 
#define PLAYER_MP			40 
#define PLAYER_SYMBOL		'@'
#define PLAYER_COLOR		8

//-----------------Spell defines--------------------
#define NUMBER_OF_SPELLS 	3
#define NUMBER_OF_EFFECTS	4
#define BOLT_SPELL_DMG		5  
#define SPHERE_SPELL_DMG	20 
#define HEAL_AMOUNT			-5

#define TELE_SPELL_COST		20
#define BOLT_SPELL_COST		5  
#define HEAL_SPELL_COST		15 
#define SPHERE_SPELL_COST	15 

#define FIRE_SPELL_COLOR	9
#define ICE_SPELL_COLOR		10
#define HEAL_SPELL_COLOR	11
#define TELE_SPELL_COLOR	12


#define ICE_SPELL_SYMBOL    '^'
#define FIRE_SPELL_SYMBOL   '*'
#define TELE_SPELL_SYMBOL   '+'
#define HEAL_SPELL_SYMBOL   PLAYER_SYMBOL

#define BURNING_TIME 		5
#define BURNING_DMG 		5
#define STUNING_TIME		3
#define HEALING_TIME		5

//-----------------Windows defines------------------
#define MAP_WIN 			0
#define LOG_WIN 			1
#define INF_WIN 			2

#define MAP_WIN_HEIGHT		30
#define MAP_WIN_WIDTH 		50
// #define MAP_WIN_POS_Y		INF_WIN_WIDTH + 1
// #define MAP_WIN_POS_X		1

#define LOG_WIN_HEIGHT 		5
#define LOG_WIN_WIDTH		35
// #define LOG_WIN_POS_Y		INF_WIN_HEIGHT + 1
// #define LOG_WIN_POS_X		1

#define INF_WIN_HEIGHT		MAP_WIN_HEIGHT
#define INF_WIN_WIDTH 		15
// #define INF_WIN_POS_Y		1
// #define INF_WIN_POS_X		1

#define SIMPLE_TEXT_COLOR	14

//-----------------Objects defines------------------
#define GROUND_SYMBOL				'.'
#define GROUND_COLOR 		14
#define WALL_SYMBOL			177
#define WALL_COLOR 			15


//-----------------Mobs defines---------------------
#define ZOMBIE_SYMBOL		'z'
#define REVENANT_SYMBOL		'R'
#define CORPSE_SYMBOL		'c'
#define GHOUL_SYMBOL		'g'
#define SKELETON_SYMBOL		's'
#define DRAUGR_SYMBOL		'D'
#define DOOMBRINGER_SYMBOL	187 //ромбик	

#define ZOMBIE_HP			7
#define CORPSE_HP			5
#define GHOUL_HP			16
#define SKELETON_HP			13
#define DRAUGR_HP			23
#define REVENANT_HP			26
#define DOOMBRINGER_HP		40

#define ZOMBIE_COLOR		1
#define CORPSE_COLOR		2
#define GHOUL_COLOR			3
#define SKELETON_COLOR		4
#define DRAUGR_COLOR		5
#define REVENANT_COLOR		6
#define BURNING_COLOR		7
#define DOOMBRINGER_COLOR	13

#define ZOMBIE_DMG			5
#define CORPSE_DMG			3
#define GHOUL_DMG			15
#define SKELETON_DMG		12
#define DRAUGR_DMG			20
#define REVENANT_DMG		25
#define DOOMBRINGER_DMG		30

#define NUMBER_OF_MOBS		7

#define TITLE_INCREASE_HP	8
#define TITLE_INCREASE_DMG	5
