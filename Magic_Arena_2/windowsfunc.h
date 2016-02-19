//-----------------------------Map functions------------------------------------
void InitMapWindow(WINDOW * mapWin, int height, int width);
void InitMap(object_t map[][MAP_WIN_WIDTH], int height, int width);
void PrintMap(WINDOW * mapWin, object_t map[][MAP_WIN_WIDTH]);
void InitColorPairs();
void GenerateDungeon(object_t map[][MAP_WIN_WIDTH], int numOfWalls);
int  IsNearWall(object_t map[][MAP_WIN_WIDTH], int y, int x);


//-----------------------------Log functions------------------------------------
void InitLogWindow(WINDOW *logWin);
void PutInLog(log_t *log, char *stringToPrint);
void PrintLog(WINDOW *logWin, log_t *log);
logString_t *CreateString(char *stringToPrint);
log_t *CreateLog();

//-----------------------------Inf functions------------------------------------
void InitInfWindow(WINDOW *infWin, int height, int width);

//-----------------------------Map functions------------------------------------
void InitMapWindow(WINDOW * mapWin, int height, int width)
{
	box(mapWin, 0 , 0);		
	wrefresh(mapWin);
}

//Добавляя новые пары не забудь, что дефайны идут по возрастанию с еденицыы
void InitColorPairs()
{
	init_pair(ZOMBIE_COLOR, 	4, COLOR_BLACK); 
	init_pair(CORPSE_COLOR, 	6, COLOR_BLACK);
	init_pair(GHOUL_COLOR, 		6, COLOR_BLACK);
	init_pair(SKELETON_COLOR, 	15, COLOR_BLACK);
	init_pair(DRAUGR_COLOR, 	8, COLOR_BLACK);
	init_pair(REVENANT_COLOR, 	3, COLOR_BLACK);
	init_pair(BURNING_COLOR, 	4, 12);
	init_pair(FIRE_SPELL_COLOR, 4, 14);
	init_pair(ICE_SPELL_COLOR, 	11, 3);
	init_pair(HEAL_SPELL_COLOR, 2, 10);
	init_pair(TELE_SPELL_COLOR, 3, COLOR_BLACK);
	init_pair(PLAYER_COLOR, 	5, COLOR_BLACK);
	init_pair(DOOMBRINGER_COLOR,0, 7);
	init_pair(SIMPLE_TEXT_COLOR,7, COLOR_BLACK); 
	init_pair(GROUND_COLOR,		8, COLOR_BLACK);
	init_pair(WALL_COLOR,		12, 14);//последний дефайн имеет номер 16
}

int IsNearWall(object_t map[][MAP_WIN_WIDTH], int y, int x)//Не забудь, что ожешь выйти за границы массива, ИСПАРВЬ
{	
	// if(((y < MAP_WIN_HEIGHT - 1) && (y > 1)) && ((x < MAP_WIN_WIDTH - 1) && (x > 1)))
	// if(((map[y+1][x] != WALL) && (map[y-1][x] != WALL)) && ((map[y][x+1] != WALL) && (map[y][x-1] != WALL)) && ((map[y+1][x+1] != WALL) && (map[y-1][x-1] != WALL)) && ((map[y-1][x+1] != WALL) && (map[y+1][x-1] != WALL)))
	// 	return 0;	//Рядом нет стены
	// else 
	// 	return 1;	//Рядом есть стена

}

void GenerateDungeon(object_t map[][MAP_WIN_WIDTH], int numOfWalls)
{
	int i, j;
		for(i = 0; i < MAP_WIN_HEIGHT; i++)
	 	{
	 		for(j = 0; j < MAP_WIN_WIDTH; j++)
	 		{
	 			 if(rand() % 20 == 6)
	 			 {
	 			 	map[i][j].symbol = WALL_SYMBOL;
	 			 	map[i][j].color  = WALL_COLOR;
	 			 }
	 					
	 		}
	 		
	 	}
	//  int density, x, y, dirX, dirY, j, i;
	// 	density = 5 + rand() % 5;
	// 	x = (rand() % MAP_WIN_WIDTH) - 5;
	// 	y = (rand() % MAP_WIN_HEIGHT) - 5;
	// for(j = 0; j < numOfWalls; j++)
	// {	
	// 	while(IsNearWall(map, y, x))
	// 	{
	// 		density = 3 + rand() % 2; 	
	// 		x = rand() % (MAP_WIN_WIDTH - density);
	// 		y = rand() % (MAP_WIN_HEIGHT - density);
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

void InitMap(object_t map[][MAP_WIN_WIDTH], int height, int width)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
				map[i][j].symbol = GROUND_SYMBOL;
				map[i][j].color  = GROUND_COLOR;
		}
	}
}

void PrintMap(WINDOW * mapWin, object_t map[][MAP_WIN_WIDTH])
{
	int i, j;
	for (i = 0; i < MAP_WIN_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIN_WIDTH; j++)
		{
			wattron(mapWin, COLOR_PAIR(map[i][j].color));
			mvwaddch(mapWin, i, j, map[i][j].symbol);
			wattroff(mapWin, COLOR_PAIR(map[i][j].color));
		}
	}
	wrefresh(mapWin);
}

//-----------------------------Log functions----------------------------------
void InitLogWindow(WINDOW * logWin)
{
	wborder(logWin, '.', '.', ACS_HLINE, ACS_HLINE, '/', 92, 92, '/');		
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

logString_t *CreateString(char *stringToPrint)
{
	logString_t *newString;
	newString = (logString_t*)malloc(sizeof(logString_t));
	newString -> logString[0] = '\0';
	Copy(newString -> logString, stringToPrint);
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
	char stringToPrint[LOG_WIN_WIDTH - 2];		//-2 что бы не наезжало на рамку по-горизонтали
	logString_t *logString;
	logString = (logString_t*)(log -> tail);
	for (i = 0; i < LOG_WIN_HEIGHT - 2; i++)	//-2 что бы не наезжало на рамку по-вертикали
	{
			mvwprintw(logWin, i + 1, 1, "%s", logString -> logString); //"i + 1, 1"-Что бы печать не наезжала на рамку
			if(logString -> prev != NULL)
				logString = logString -> prev;
			else
				return;
	}
}

//-----------------------------Inf functions----------------------------------

void InitInfWindow(WINDOW *infWin, int height, int width)
{
	wborder(infWin, '|', '|', '-', '-', '+', '+', '+', '+');	
	wrefresh(infWin);
}