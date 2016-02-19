#include "panel.h"
#include <windows.h>
#include "defines.h"
#include "header.h"
#include "windowsfunc.h"
#include "mobfunc.h"
#include "spellfunc.h"
#include "playerFunc.h"

int main(int argc, int* argv[])
{
    int i;                                                  //НЕ ЗАБЫТЬ УДАЛИТЬ, КОГДА ЗАКОНЧИШЬ ТЕСТИТЬ
    char c;                                              
    object_t        map[MAP_WIN_HEIGHT][MAP_WIN_WIDTH];     //map - Карта, содержит симолы стен и земли.
    player_t        player;
    listOfMobs_t   *listOfMobs;                             //Список мобов
    log_t          *log;                                    //Лог, по типу стека, вывод происходит с конца
    mob_t          *mob;                                    //НЕ ЗАБЫТЬ УДАЛИТЬ, КОГДА ЗАКОНЧИШЬ ТЕСТИТЬ
    WINDOW         *mapWin, *logWin, *infWin;
    PANEL          *window[3];                              //Панели использую для удобства, что бы все обновлять одной функцией
    srand(time(NULL));  

    initscr();                                              //////////////////////////////////////////////////////////
    noecho();                                               //////////////////////////////////////////////////////////
    start_color();                                          ///Вход в режим ncurses, noecho() для того что бы нажатые клавиши не выводились
    InitColorPairs();                                       ///Инициализация цветов.
    cbreak();                                               //////////////////////////////////////////////////////////
    refresh();                                              //////////////////////////////////////////////////////////

    listOfMobs  = CreateList();                              
    log         = CreateLog();                                      
  //  InitPlayer(&player);                                  

    mapWin = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 0, INF_WIN_WIDTH);   //Создание основного окна карты и самой карты
    InitMapWindow(mapWin, MAP_WIN_HEIGHT, MAP_WIN_WIDTH);               //И инициализация 
    InitMap(map, MAP_WIN_HEIGHT, MAP_WIN_WIDTH);

    logWin = newwin(LOG_WIN_HEIGHT, LOG_WIN_WIDTH, MAP_WIN_HEIGHT, 0 ); //Создание окна лога и инициализация
    InitLogWindow(logWin);               
    
    infWin = newwin(INF_WIN_HEIGHT, INF_WIN_WIDTH, 0, 0);               //Создание окна с инофрмацией и инициализация
    InitInfWindow(infWin, INF_WIN_HEIGHT, INF_WIN_WIDTH);

    window[MAP_WIN] = new_panel(mapWin);                                //Создание панелей
    window[LOG_WIN] = new_panel(logWin);
    window[INF_WIN] = new_panel(infWin);
    update_panels();
    doupdate();

    PutInLog(log, "dasdasdsd");                                         //тест работы лога типа, убери потом
    PutInLog(log, "second string!");
    PrintLog(logWin, log);

    // AddMob(listOfMobs, 5, 5);
    // mob = listOfMobs -> head;  

    // for(i = 0; i < 29; i++)                                          //Проверка генерации имен мобов, вывод в окно информации
    // {
        
    //     AddMob(listOfMobs, 5, i);
    //     mvwprintw(infWin, i, 1, "%s %d %d ", mob -> name, mob->hP, mob->dmg);
    //     wattron(infWin, COLOR_PAIR(mob->color));
    //     wprintw(infWin,"%c",mob->symbol);
    //     wattroff(infWin, COLOR_PAIR(mob->color));
    //     doupdate();
    //     mob = mob -> next;
    // }
    for(i = 176; i < 224; i++)
    {

        wprintw(infWin, "%c ", i);
    }
    GenerateDungeon(map, 1000);
    PrintMap(mapWin, map);
    update_panels();
    doupdate();
    // player.x = 5, player.y = 5;
    // player.symbol = PLAYER_SYMBOL;
    // while(c = getch())
    // {   
    //      PrintMap(mapWin, map, MAP_WIN_HEIGHT, MAP_WIN_WIDTH);
    //     switch(c)
    //     {
    //         case 'w': 
    //             movePlayerTo(-1, 0, &player, listOfMobs, mapWin, logWin, infWin);
    //             break;
    //         case 'a': 
    //             movePlayerTo(0, -1, &player, listOfMobs, mapWin, logWin, infWin);
    //             break;
    //         case 's': 
    //             movePlayerTo(1, 0,  &player, listOfMobs, mapWin, logWin, infWin);
    //             break;    
    //         case 'd': 
    //             movePlayerTo(0, 1,  &player, listOfMobs, mapWin, logWin, infWin);
    //             break;
    //         case 'p': 
    //             endwin();
    //             return 0;
    //         case 'c': 
    //             CastSpell(&player, listOfMobs, logWin);
    //             break;
    //     }
    //     update_panels();
    //     doupdate();
    // }
    getch();
    endwin();
    return 0;
}

