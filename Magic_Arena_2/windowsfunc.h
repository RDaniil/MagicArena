//-----------------------------Map functions------------------------------------
void InitMapWindow(WINDOW * mapWin, int height, int width);
void InitMap(object_t map[][MAP_WIDTH]);
void PrintMap(WINDOW * mapWin, object_t map[][MAP_WIDTH], camera_t *cam, int playerY, int playerX);
void InitColorPairs();
void GenerateDungeon(object_t map[][MAP_WIDTH], int numOfWalls);
int  IsNearWall(object_t map[][MAP_WIDTH], int y, int x);

//-----------------------------Log functions------------------------------------
void InitLogWindow(WINDOW *logWin);
void PutInLog(log_t *log, char *stringToPrint);
void PrintLog(WINDOW *logWin, log_t *log);
logString_t *CreateString(char *stringToPrint);
log_t *CreateLog();

//-----------------------------Inf functions------------------------------------
void InitInfWindow(WINDOW *infWin);

//-----------------------------Map functions------------------------------------
void InitMapWindow(WINDOW * mapWin, int height, int width)
{
	box(mapWin, 0 , 0);		
	wrefresh(mapWin);
}

//Добавляя новые пары не забудь, что дефайны идут по возрастанию с еденицыы
void InitColorPairs()
{
	init_pair(ZOMBIE_COLOR, 	CLR_RED, 		CLR_BLACK); 
	init_pair(CORPSE_COLOR, 	CLR_YELLOW, 	CLR_BLACK);
	init_pair(GHOUL_COLOR, 		CLR_YELLOW, 	CLR_BLACK);
	init_pair(SKELETON_COLOR, 	CLR_LGHTWHITE, 	CLR_BLACK);
	init_pair(DRAUGR_COLOR, 	CLR_GRAY, 		CLR_BLACK);
	init_pair(REVENANT_COLOR, 	CLR_CYAN, 		CLR_BLACK);
	init_pair(BURNING_COLOR, 	CLR_RED, 		CLR_LGHTRED	);
	init_pair(FIRE_SPELL_COLOR, CLR_RED, 		CLR_LGHTRED);
	init_pair(ICE_SPELL_COLOR, 	CLR_LGHTCYAN, 	CLR_CYAN);
	init_pair(HEAL_SPELL_COLOR, CLR_GREEN, 		CLR_LGHTGREEN);
	init_pair(TELE_SPELL_COLOR, CLR_CYAN, 		CLR_BLACK);
	init_pair(PLAYER_COLOR, 	CLR_VIOLET, 	CLR_BLACK);
	init_pair(DOOMBRINGER_COLOR,CLR_BLACK, 		CLR_WHITE);
	init_pair(SIMPLE_TEXT_COLOR,CLR_WHITE, 		CLR_BLACK); 
	init_pair(GROUND_COLOR,		CLR_GRAY, 		CLR_BLACK);
	init_pair(WALL_COLOR,		CLR_LGHTRED, 	CLR_LGHTYELLOW);
	init_pair(MGC_MISSLE_COLOR,	CLR_LGHTVIOLET, CLR_BLACK);
	init_pair(RED_TEXT_COLOR,	CLR_RED	, 		CLR_BLACK);//последний дефайн имеет номер 18
}

int IsNearWall(object_t map[][MAP_WIDTH], int y, int x)//Не забудь, что ожешь выйти за границы массива, ИСПАРВЬ
{	
	// if(((y < MAP_WIN_HEIGHT - 1) && (y > 1)) && ((x < MAP_WIN_WIDTH - 1) && (x > 1)))
	// if(((map[y+1][x] != WALL) && (map[y-1][x] != WALL)) && ((map[y][x+1] != WALL) && (map[y][x-1] != WALL)) && ((map[y+1][x+1] != WALL) && (map[y-1][x-1] != WALL)) && ((map[y-1][x+1] != WALL) && (map[y+1][x-1] != WALL)))
	// 	return 0;	//Рядом нет стены
	// else 
	// 	return 1;	//Рядом есть стена

}

void GenerateDungeon(object_t map[][MAP_WIDTH], int numOfWalls)
{
	int i, j;
		for(i = 0; i < MAP_HEIGHT; i++)
	 	{
	 		for(j = 0; j < MAP_WIDTH; j++)
	 		{
	 			if(rand() % 20 == 6)
	 			{
	 				map[i][j].symbol = WALL_SYMBOL;
	 			 	map[i][j].color  = WALL_COLOR;
	 			 	map[i][j].isPassable  = IMPASSABLE;
	 			 	map[i][j].desc[0] = '\0';
	 			 	strcpy(map[i][j].desc, "Huge Wall");
	 			}		
	 		}
	 	}
	//  int density, x, y, dirX, dirY, j, i;
	// 	density = 5 + rand() % 5;
	// 	x = (rand() % MAP_WIDTH) - 5;
	// 	y = (rand() % MAP_HEIGHT) - 5;
	// for(j = 0; j < numOfWalls; j++)
	// {	
	// 	while(IsNearWall(map, y, x))
	// 	{
	// 		density = 3 + rand() % 2; 	
	// 		x = rand() % (MAP_WIDTH - density);
	// 		y = rand() % (MAP_HEIGHT - density);
	// 	}
	// 	dirY = rand() % 2;
	// 	if(dirY)
	// 		dirX = 0;
	// 	else
	// 		dirX = 1;
	// 	for(i = 0; i < density; i++)
	// 	{	
	// 		if((map[y + dirY][x + dirX] != WALL) && (IsNearWall(map, y + dirY, x + dirX)== 0))
	// 		{
	// 			map[y][x] = WALL;
	// 		}
	// 		else
	// 			break;
	// 		y += dirY;
	// 		x += dirX;
	// 	}
	//  }

}

void InitMap(object_t map[][MAP_WIDTH])
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
				map[i][j].symbol = GROUND_SYMBOL;
				map[i][j].isPassable  = PASSABLE;
				map[i][j].color  = GROUND_COLOR;
				map[i][j].desc[0] = '\0';
				strcpy(map[i][j].desc, "Just ground");
		}
	}
}

void PrintMap(WINDOW * mapWin, object_t map[][MAP_WIDTH], camera_t *cam, int playerY, int playerX)
{
	int i, j, k = 0, l = 0;
	cam -> x = (playerX - (cam -> w / 2));
    cam -> y = (playerY - (cam -> h / 2));
    if(cam -> x < 0) cam -> x = 0;
    if(cam -> y < 0) cam -> y = 0;
    if(cam -> x + cam -> w >= MAP_WIDTH) 
    	cam -> x = MAP_WIDTH - cam -> w;
    if(cam -> y + cam -> h >= MAP_HEIGHT)
    	cam -> y = MAP_HEIGHT - cam -> h;
    for(i = cam -> y, k = 0; i < (cam -> y + cam -> h); i++, k++)
    {
        for(j = cam -> x, l = 0; j < (cam -> x + cam -> w); j++, l++)
        {
			wattron(mapWin, COLOR_PAIR(map[i][j].color));
			mvwaddch(mapWin, k, l, map[i][j].symbol);
			wattroff(mapWin, COLOR_PAIR(map[i][j].color));
		}
	}
	wrefresh(mapWin);
}

//-----------------------------Log functions----------------------------------
void InitLogWindow(WINDOW * logWin)
{
	wborder(logWin, ' ',' ', ACS_HLINE, ' ', ACS_HLINE, ACS_HLINE, ' ', ' ');		
	wrefresh(logWin);
}

log_t *CreateLog()
{
	log_t *node;
	node = (log_t*)malloc(sizeof(log_t));
	node -> head = NULL;
	node -> tail = NULL;
	return node;
}

logString_t *CreateString(char *stringToPrint) 	// Элементы лога - строки, которые тут создаются
{
	logString_t *newString;
	newString = (logString_t*)malloc(sizeof(logString_t));
	newString -> logString[0] = '\0';
	strcat(newString -> logString, stringToPrint);
	newString -> next = NULL;
	newString -> prev = NULL;
	return (logString_t*)newString;
}

void PutInLog(log_t *log, char *stringToPrint) 	// Работает как стек
{
	logString_t *pHead;
	logString_t *newString;
	newString = CreateString(stringToPrint);
	if(log -> head == NULL)
	{
		log -> head = newString;
	}
	else
	{
		pHead = (logString_t*)(log -> head);
		while(pHead -> next != NULL)
		{
			pHead = (logString_t*)(pHead -> next);
		}
		pHead -> next = newString;
		newString -> prev = pHead;
	}
	log -> tail = newString;
}

void PrintLog(WINDOW *logWin, log_t *log)
{
	int i;
	logString_t *logString;
	logString = (logString_t*)(log -> tail);
	for (i = 0; i < LOG_WIN_HEIGHT - 2; i++)	//-2 что бы не наезжало на рамку по-вертикали
	{
			mvwprintw(logWin, i + 1, 0, "\n");	//Что бы очистить строку в окне, на которой будем печатать новую строку
			mvwprintw(logWin, i + 1, 0, "%s", logString -> logString); //"i + 1"-Что бы печать не наезжала на рамку
			if(logString -> prev != NULL)
				logString = logString -> prev;
			else
				return;
	}
}

//-----------------------------Inf functions----------------------------------

void InitInfWindow(WINDOW *infWin)
{
	wborder(infWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, '+', '+', '+', '+');	
	wrefresh(infWin);
}

void PrintInf(WINDOW *infWin, player_t *player)
{
	int i;
	mvwprintw(infWin, 1, 1, "%s", player->name);
	mvwprintw(infWin, 2, 1, "Hp: %d/%d", player->hP, PLAYER_HP);
	mvwprintw(infWin, 3, 1, "Mp: %d/%d", player->mP, PLAYER_MP);
	mvwprintw(infWin, 5, 1, "Spells:");
	// for(i = 0; i < NUMBER_OF_SPELLS; i++)
	// {
	// 	mvwprintw(infWin, i+6, 1, "%s", player->spell[i].spellName);
	// }
}