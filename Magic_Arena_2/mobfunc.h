
//-----------------Mobs functions------------------
listOfMobs_t   *CreateList();
mob_t 		   *CreateMob(int x, int y);
void 			AddMob(listOfMobs_t * listOfMobs, int x, int y);
void 			GenerateInf(mob_t *mob);
void 			DeleteMob(listOfMobs_t * listOfMobs, int x, int y);
void			AddInf(mob_t *mob, int hP, int dmg, int color, char symbol);
//mob_t * find_mob(mob * head, int x, int y);


/////////////////////////////////////////////////////////////////////
////////////////////Нахождение моба по координатам///////////////////
/////////////////////////////////////////////////////////////////////
// mob_t * find_mob(mob_t * head, int x, int y)
// {
//     if(head == NULL)
//         return (NULL);
//     if(head -> x == x && head -> y == y)
//         return(head);
//     else
//         return(find_mob(head -> next, x, y));
// }

listOfMobs_t *CreateList()
{
	listOfMobs_t *node;
	node = (listOfMobs_t*)malloc(sizeof(listOfMobs_t));
	node -> head = NULL;
	node -> tail = NULL;
	node->numOfMobs = 0;
	return node;
}

/////////////////////////////////////////////////////////////////////
/////////////Нахождение моба по координатам и удаление///////////////
/////////////////////////////////////////////////////////////////////
void DeleteMob(listOfMobs_t * listOfMobs, int x, int y)
{
	int pos = 1;
	mob_t *pD, *nD, *D = listOfMobs -> head;
	while((D -> x != x) && (D -> y != y))
	{
		if(D -> next != NULL)
			D = (mob_t*)(D -> next);
		else
		{
			return;
		}
		pos++;
	}
	if(pos == 1)
	{
		listOfMobs -> head = (mob_t*)(D -> next);
		listOfMobs -> head -> prev = NULL;
		free(D);
		listOfMobs->numOfMobs--;
		return;
	}
	else
		if(pos == listOfMobs -> numOfMobs)
		{
			listOfMobs -> tail = (mob_t*)(D -> prev);
			listOfMobs -> tail -> next = NULL;
			free(D);
			listOfMobs->numOfMobs--;
			return;
		}
		else
		{
			pD = (mob_t*)(D -> prev);
			nD = (mob_t*)(D -> next);
			pD-> next = nD;
			nD -> prev = pD;
			free(D);
			listOfMobs->numOfMobs--;
			return;
		}
}
/////////////////////////////////////////////////////////////////////
//Создание моба, присваивание начальных координат,генерация эффекта//
/////////////////////////////////////////////////////////////////////
mob_t * CreateMob(int x, int y)
{
	mob_t * newMob;
	newMob = (mob_t*)malloc(sizeof(mob_t));
	newMob -> x 	 = x;
	newMob -> y      = y;
	if(ThrowDice(1, 10) % 3 == 0)			//Дабы мобов с еффектами было меньше такой плохой код тут
		newMob -> eff = ThrowDice(1, 4);
	else
		newMob -> eff = none;
	GenerateInf(newMob);
	newMob -> next = NULL;
	newMob -> prev = NULL;
	return newMob;
}
/////////////////////////////////////////////////////////////////////
///////////////////Добавление моба в конец списка.///////////////////
/////////////////////////////////////////////////////////////////////
void AddMob(listOfMobs_t * listOfMobs, int x, int y)
{
	mob_t *pHead, *newMob;
	newMob = CreateMob(x, y);
	if(listOfMobs -> head == NULL)
	{
		listOfMobs -> head = newMob;
	}
	else
	{
		pHead = listOfMobs -> head;
		while(pHead -> next != NULL)
		{
			pHead = (mob_t*)(pHead -> next);
		}
		pHead -> next = newMob;
		newMob -> prev = pHead;
	}
	listOfMobs -> tail = newMob;
	listOfMobs->numOfMobs++;
}
/////////////////////////////////////////////////////////////////////
////////////////Добавление сгенерированой информации/////////////////
/////////////////////////////////////////////////////////////////////
void AddInf(mob_t *mob, int hP, int dmg, int color, char symbol)
{
	mob -> hP  = hP;
	mob -> dmg = dmg;
	mob -> color = color;
	mob -> symbol = symbol;
}
/////////////////////////////////////////////////////////////////////
//Генерация имени, урона, хП, присваивание символа на основе имени.//
/////////////////////////////////////////////////////////////////////
//Если будешь добавлять мобов не забудь внимательно просмотреть код ниже, ибо он основан на количестве мобов(Дефайны еще менять придется)
void GenerateInf(mob_t *mob)
{
	int upperCase = 'a' - 'A';
	char *eff[3][3] = {{"Burning ", "Aflame ", "Infernal "}, {"Sparkling ", "Frightful ", "Dreadful "}, {"Bloodthirsty ", "Slaughterous ", "Butcherly "}}; 
	char *name[NUMBER_OF_MOBS] = {"Zombie ", "Corpse ", "Skeleton ", "Ghoul ","Revenant ", "Draugr ", "Doombringer "}; 
	char *title[3]= {"SLAYER", "HUNTER","BERSERK"};
	int symbol, titleNum;
	mob->name[0] = '\0';

	if((mob->eff != healing) && (mob->eff != none))
	switch(mob -> eff) 									//На основе эффекта моба выбор префикса к имени.
	{
		case burning:
		{
			strcat(mob -> name, eff[0][ThrowDice(1, 3)]);
			mob -> color = BURNING_COLOR;
			break;
		}
		case stuning:
		{
			strcat(mob -> name, eff[1][ThrowDice(1, 3)]);
			break;
		}
		case bleeding:
		{
			strcat(mob -> name, eff[2][ThrowDice(1, 3)]);
			break;
		}
	}
	if((ThrowDice(1, 10) + 1) % 3 == 0)				//(ДАНИИЛ СДЕЛАЙ ЧТО-ТО С ЭТИМ ДЕРЬМОМ)
	{
		if((ThrowDice(1, 20) + 1) % 2 == 0)			//Отдельный случай для думбрингера (т.к. он мощный оч) У думбрингера последний номер, поэтому здесь 
			symbol = ThrowDice(1, NUMBER_OF_MOBS);	//все мобы могут выпасть. Ниже выбор идет на 1 меньше, что бы не попался думбрингер(ДАНИИЛ СДЕЛАЙ ЧТО-ТО С ЭТИМ ДЕРЬМОМ)
		else
			symbol = ThrowDice(1, NUMBER_OF_MOBS - 1); //Ревенанты и драугры должны появляться реже(Потому что они сильные), поэтому здесь такой накрасивый код
	}	
	else
		symbol = ThrowDice(1, 4);
	strcat(mob -> name, name[symbol]);		//Случайный выбор имени, затем на основе имени присваивание символа, урона, жизней, цвета
	switch(symbol)
	{
		case 0:
			AddInf(mob, ZOMBIE_HP + ThrowDice(1, 5), ZOMBIE_DMG + ThrowDice(1, 4), (mob->color!=BURNING_COLOR)? ZOMBIE_COLOR: BURNING_COLOR, ZOMBIE_SYMBOL);
			break;
		case 1:
			AddInf(mob, CORPSE_HP + ThrowDice(1, 4), CORPSE_DMG + ThrowDice(1, 3), (mob->color!=BURNING_COLOR)? CORPSE_COLOR: BURNING_COLOR, CORPSE_SYMBOL);
		 	break;
		case 2:
			AddInf(mob, SKELETON_HP + ThrowDice(2, 3), SKELETON_DMG + ThrowDice(2, 3), (mob->color!=BURNING_COLOR)? SKELETON_COLOR: BURNING_COLOR, SKELETON_SYMBOL);
		 	break;
		case 3:
			AddInf(mob, GHOUL_HP + ThrowDice(2, 4), GHOUL_DMG + ThrowDice(2, 5), (mob->color!=BURNING_COLOR)? GHOUL_COLOR: BURNING_COLOR, GHOUL_SYMBOL);
		 	break;
		case 4:
			AddInf(mob, REVENANT_HP + ThrowDice(3, 7), REVENANT_DMG + ThrowDice(3, 6), (mob->color!=BURNING_COLOR)? REVENANT_COLOR: BURNING_COLOR, REVENANT_SYMBOL);
		 	break;
		case 5:
			AddInf(mob, DRAUGR_HP + ThrowDice(4, 3) + ThrowDice(3, 7), DRAUGR_DMG + ThrowDice(3, 6), (mob->color!=BURNING_COLOR)? DRAUGR_COLOR: BURNING_COLOR, DRAUGR_SYMBOL);
		 	break;
		 case 6:
			AddInf(mob, DOOMBRINGER_HP + ThrowDice(5, 6), DOOMBRINGER_DMG + ThrowDice(5, 3), DOOMBRINGER_COLOR, DOOMBRINGER_SYMBOL);
		 	break;
	}

	if(ThrowDice(1, 10) % 7 == 0)				//Что бы мобов с титулами было меньше такой плохой код тут
	{
		titleNum = ThrowDice(1, 3);
		switch(titleNum)
		{
			case 0: 		//Slayer title
				mob->dmg += TITLE_INCREASE_DMG + ThrowDice(2, 4); 
				mob->hP  += TITLE_INCREASE_HP  + ThrowDice(2, 4);
				if(((mob -> symbol != REVENANT_SYMBOL) && (mob -> symbol != DRAUGR_SYMBOL)) && (mob -> symbol != (char)DOOMBRINGER_SYMBOL))
					mob -> symbol -= upperCase;
				strcat(mob -> name, title[titleNum]);
			break;
			case 1:			//Hunter title
				mob->dmg += TITLE_INCREASE_DMG + ThrowDice(3, 4);
				mob->hP -= ThrowDice(1, 4);
				if(((mob -> symbol != REVENANT_SYMBOL) && (mob -> symbol != DRAUGR_SYMBOL)) && (mob -> symbol != (char)DOOMBRINGER_SYMBOL))
					mob -> symbol -= upperCase;
				strcat(mob -> name, title[titleNum]);
			break;
			case 2:			//Berserk title
				mob->dmg += TITLE_INCREASE_DMG + ThrowDice(3, 4);
				mob->hP  += TITLE_INCREASE_HP  + ThrowDice(3, 4);
				if(((mob -> symbol != REVENANT_SYMBOL) && (mob -> symbol != DRAUGR_SYMBOL)) && ((mob -> symbol) != (char)DOOMBRINGER_SYMBOL))
					mob -> symbol -= upperCase;
				strcat(mob -> name, title[titleNum]);
			break;
		}
	}
}

