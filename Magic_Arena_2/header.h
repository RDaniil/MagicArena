void 			Copy(char *s1, char *s2);
int 			Len(char *s);
int 			ThrowDice(int dices, int edges);

typedef enum {burning, healing, stuning, bleeding, none} effect_t;
typedef enum {bolt = 0, ball, yourself} type_t;

typedef struct 
{
	int x, y, h, w;
}camera_t;

//Строка в логе(эл-т стека)
typedef struct 
{
	char					logString[LOG_WIN_WIDTH - 2]; //-2, что бы не вылезало на рамку окна 
	struct logString_t		*next, *prev;
}logString_t;
//Сам лог(стек)
typedef struct 
{
	struct logString_t		*head, *tail;
}log_t;
//Структура моба(эл-т списка мобов)
typedef struct 
{
	int 			x, y, hP, dmg, color, effects[NUMBER_OF_EFFECTS];
	char 			symbol, name[30];
	effect_t 		eff;
	struct mob_t 	*next, *prev;
}mob_t;
//Структура списка 
typedef struct 
{
	mob_t 			*head, *tail;
	int 			numOfMobs;
}listOfMobs_t;
//Структура заклинания
typedef struct 
{
	int 			dmg, mCost, color, timeOfEff;
	char 			symbol, spellName[20];
	effect_t 		eff;
	type_t			type;
	void 			(*CastSpell)(int, int, listOfMobs_t*, log_t*); //Два инта - координаты на которые кастуем
}spell_t;
//Структура объекта, используется на карте
typedef struct 
{
	unsigned char 	symbol; 				//Дабы влезали "интересные" сивмолы
	int 			color, isPassible; 
	char 			desc[20];				//Описание объекта
}object_t;
//Структура игрока
typedef struct 
{
	int 			x, y, hP, mP, color, effects[NUMBER_OF_EFFECTS];
	char 			symbol, name[10];
	spell_t 		spell[NUMBER_OF_PLR_SPELLS];
}player_t;

int ThrowDice(int dices, int edges)	
{
	int result = 0, i, j;
	for(i = 0; i < dices; i++)
	{
		result += rand() % edges;	
	}
	return result;
}

void Copy(char *s1, char *s2)		
{
	int i = Len(s1), j = 0;
	while((s1[i] = s2[j]) != '\0')
		i++, j++;

}

int Len(char *s)
{
	int len = 0,i;  
	for(i = 0; s[i] != '\0'; i++) 
	{
		len++;
	}
	return len;
}