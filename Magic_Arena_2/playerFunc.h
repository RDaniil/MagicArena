void movePlayerTo(int y, int x, player_t *plr, listOfMobs_t *mob, WINDOW* map, WINDOW* log, WINDOW* inf);
void PrintPlayer(player_t * plr, WINDOW* map);
void InitPlayer(player_t * player);

void movePlayerTo(int y, int x, player_t *plr, listOfMobs_t *mob, WINDOW* map, WINDOW* log, WINDOW* inf)
{
	plr -> x += x;
	plr -> y += y;
	PrintPlayer(plr, map);
}

void PrintPlayer(player_t * plr, WINDOW* map)
{
	mvwaddch(map, plr -> y, plr -> x, plr -> symbol);
}

void InitPlayer(player_t * player)
{
	int i;
	player -> x 	 = rand() % MAP_WIN_HEIGHT;
	player -> y 	 = rand() % MAP_WIN_WIDTH;
	player -> hP 	 = PLAYER_HP;
	player -> mP 	 = PLAYER_MP;
	player -> symbol = PLAYER_SYMBOL;
	player -> color  = PLAYER_COLOR;
	for (i = 0; i < NUMBER_OF_EFFECTS; i++)
		player -> effects[i] = 0;
	ChooseSpells(player);
	player -> name[0] = 'P';
}

