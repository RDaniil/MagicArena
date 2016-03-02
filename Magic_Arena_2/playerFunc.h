//-----------------------------Player functions------------------------------------
void movePlayerTo(int y, int x, player_t *plr, listOfMobs_t *listOfMobs, object_t map[MAP_HEIGHT][MAP_WIDTH], log_t *log);
void PrintPlayer(player_t * p, WINDOW* mapWin, camera_t *c);
void InitPlayer(player_t * player, char *name);
void Look(player_t *player, listOfMobs_t *mob, log_t *log, WINDOW * logWin, object_t map[MAP_HEIGHT][MAP_WIDTH], int camX, int camY);

void Look(player_t *player, listOfMobs_t *mob, log_t *log, WINDOW * logWin, object_t map[MAP_HEIGHT][MAP_WIDTH], int camX, int camY)
{
	char input;
	int x = player -> x - camX , y = player -> y - camY;
	while(input != ENTER_SMB)
	{
		move(y, x + INF_WIN_WIDTH);    //Перемещение курсора на позиции x, y.Ширину окна прибавляем т.к. окно карты находится справа от окна информации
        input = getch();
        switch(input)
        {       
            case 'w': case 'W':
                if(y > 0)
                y--;
            break;  
            case 's': case 'S':
                if(y < MAP_WIN_HEIGHT - 1)
                y++;
            break;
            case 'a': case 'A':
                if(x > 0)
                x--;
            break;
            case 'd': case 'D':
                if(x < MAP_WIN_WIDTH - 1)
                x++;
            break;
            case ESCAPE_SMB: 
                move(0, 0); 
                return;
            break;
        }   
        PutInLog(log, map[camY + y][camX + x].desc);
        PrintLog(logWin, log);
        update_panels();
        doupdate();
        //if(FindMobAt(x, y) != NULL)
        //Вывести его описание  
    } 
}

void movePlayerTo(int dY, int dX, player_t *plr, listOfMobs_t *listOfMobs, object_t map[MAP_HEIGHT][MAP_WIDTH], log_t *log)
{
    int destinationX = plr -> x + dX, destinationY = plr -> y + dY;
    if((destinationX >= 0 && destinationX < MAP_WIDTH) && (destinationY >= 0 && destinationY < MAP_HEIGHT))
    {
    //if(!IsMobHere(x, y, listOfMobs))
    //{
        if(map[destinationY][destinationX].isPassable)
        {
            plr -> x += dX;
            plr -> y += dY;
            return;
        }
    //}
    }
    PutInLog(log, "Ouch! I can't go this way.");
}

void PrintPlayer(player_t * p, WINDOW* mapWin, camera_t *c)
{
	int x, y;
	if(c -> x >= 0)
        x = p -> x - c -> x, y = p -> y;
    if(c -> y >= 0)
        x = p -> x , y = (p -> y - c -> y);
    if(c -> y >= 0 && c -> x >= 0)
        x = (p -> x - c -> x) , y = (p -> y - c -> y);
    if(c -> x <= 0 && c -> y <= 0)
        x = p -> x, y = p -> y;
	mvwaddch(mapWin, y, x, p -> symbol);
}

void InitPlayer(player_t * player, char *name)
{
	int i;
	player -> x 	 = rand() % MAP_WIDTH;
	player -> y 	 = rand() % MAP_HEIGHT;
	player -> hP 	 = PLAYER_HP;
	player -> mP 	 = PLAYER_MP;
	player -> symbol = PLAYER_SYMBOL;
	player -> color  = PLAYER_COLOR;
	for (i = 0; i < NUMBER_OF_EFFECTS; i++)
		player -> effects[i] = 0;
	//ChooseSpells(player);
	player -> name[0] = '\0';
	strcat(player -> name, name);
}

