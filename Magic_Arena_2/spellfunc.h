
//-----------------Spells functions------------------
void InitSpell(spell_t *spell, int dmg, int mCost, int color, char symbol, char *spellName, effect_t effect, int timeOfEffect, type_t type);
void ChooseSpells(player_t * player);
void ChooseSpellToCast(player_t *player, listOfMobs_t *listOfMobs, WINDOW * logWin);
void CastSpell(int x, int y, listOfMobs_t *listOfMobs, log_t *log);

void CastSpell(int x, int y, listOfMobs_t *listOfMobs, log_t *log)
{
	//Вызвать поиск моба, если он стоит на координатах, на которые кастуем,то
	//вычесть из хп дмг наложить еффект
	//вычесть ману у игрока 
	//запихнуть в лог каст спелла
}

//Дописать штуки с спеловой функцией
void InitSpell(spell_t *spell, int dmg, int mCost, int color, char symbol, char *spellName, effect_t effect, int timeOfEffect, type_t type)
{
	spell -> spellName[0] = '\0';
	spell -> dmg    	=	dmg + ThrowDice(2, 4);
	spell -> mCost  	=	mCost + ThrowDice(1, 4);
	spell -> color  	=	color;
	spell -> symbol 	=	symbol;
	spell -> eff 	 	=	effect;
	spell -> timeOfEff 	=	timeOfEffect + ThrowDice(1, 3);
	spell -> type 		=   type;
	Copy(spell -> spellName, spellName);
}

void ChooseSpells(player_t * player)
{
	int i = 0, spell;
	while(i < NUMBER_OF_PLR_SPELLS)
	{
		mvprintw(0, 0, "You can choose %d spells. Choose your %d spell\n",NUMBER_OF_SPELLS, i + 1);
		printw("1 - Fire bolt\n2 - Ice bolt\n3 - Teleportation\n4 - Health resotration\n");
		scanw("%1d", &spell);
		switch(spell)
		{
			case 1: 
				InitSpell(&player -> spell[i], BOLT_SPELL_DMG, BOLT_SPELL_COST,  FIRE_SPELL_COLOR, FIRE_SPELL_SYMBOL,  "Fire bolt", 	 burning,  BURNING_TIME, bolt);
				printw("You choose fire bolt spell");
			break;
			case 2: 
				InitSpell(&player -> spell[i], BOLT_SPELL_DMG, BOLT_SPELL_COST,  ICE_SPELL_COLOR,  ICE_SPELL_SYMBOL,   "Ice bolt",  	 stuning,  STUNING_TIME, bolt);
				printw("You choose ice bolt spell");
			break;
			case 3: 
				InitSpell(&player -> spell[i], 0, 			   TELE_SPELL_COST,  TELE_SPELL_COLOR, TELE_SPELL_SYMBOL,  "Teleportation",  none, 	  0, yourself);
				printw("You choose teleportation spell");
			break;
			case 4: 
				InitSpell(&player -> spell[i], HEAL_AMOUNT,    HEAL_SPELL_COST,  HEAL_SPELL_COLOR, HEAL_SPELL_SYMBOL,  	"Restoration", 	 healing, 0, yourself);
				printw("You choose resotration spell");
			break;
			case 5: 
				InitSpell(&player -> spell[i], BOLT_SPELL_DMG+5, BOLT_SPELL_COST+5,  HEAL_SPELL_COLOR, HEAL_SPELL_SYMBOL, "Magic missle", none,	  0, bolt);
				printw("You choose resotration spell");
			break;
		}
		i++;
	}
	printw("\nSmart choose.\nPress any button to start\n");
	getch();
}
