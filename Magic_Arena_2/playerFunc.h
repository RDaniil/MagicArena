//-----------------------------Player functions------------------------------------
void movePlayerTo(int y, int x, player_t *plr, listOfMobs_t *mob, WINDOW* map, camera_t *c);
void PrintPlayer(player_t * p, WINDOW* map, camera_t *c);
void InitPlayer(player_t * player, char *name);
void Look(player_t *player, listOfMobs_t *mob, log_t *log, object_t map[MAP_HEIGHT][MAP_WIDTH]);

void Look(player_t *player, listOfMobs_t *mob, log_t *log, object_t map[MAP_HEIGHT][MAP_WIDTH])
{
	char n;
	int x = player->x % MAP_WIDTH, y = player->y % MAP_HEIGHT;
	while(n != ENTER_SMB)
	{
		move(y, x); 			//Перемещение курсора на позиции x, y.
        n = getch();
        switch(n)
        {
            case 'w': case 'W':
                if(y > 0)
                y--;
            break;
            case 's': case 'S':
                if(y < MAP_WIN_HEIGHT)
                y++;
            break;
            case 'a': case 'A':
                if(x > 0)
                x--;
                break;
            case 'd': case 'D':
                if(x < MAP_WIN_WIDTH)
                x++;
            break;
        }
    } 
}

void movePlayerTo(int y, int x, player_t *plr, listOfMobs_t *mob, WINDOW* map, camera_t *c)
{
	plr -> x += x;
	plr -> y += y;
	PrintPlayer(plr, map, c);
}

void PrintPlayer(player_t * p, WINDOW* map, camera_t *c)
{
	int x, y;
	if(c -> x >= 0)
        x = p -> x - c -> x, y= p -> y;
    if(c -> y >= 0)
        x = p -> x , y = (p -> y - c -> y);
    if(c -> y >= 0 && c -> x >= 0)
        x = (p -> x - c -> x) , y = (p -> y - c -> y);
    if(c -> x <= 0 && c -> y <= 0)
        x = p -> x, y = p -> y;
	mvwaddch(map, y, x, p -> symbol);
}

void InitPlayer(player_t * player, char *name)
{
	int i;
	player -> x 	 = 0;
	player -> y 	 = 0;
	player -> hP 	 = PLAYER_HP;
	player -> mP 	 = PLAYER_MP;
	player -> symbol = PLAYER_SYMBOL;
	player -> color  = PLAYER_COLOR;
	for (i = 0; i < NUMBER_OF_EFFECTS; i++)
		player -> effects[i] = 0;
	//ChooseSpells(player);
	player -> name[0] = '\0';
	Copy(player -> name, name);
}

