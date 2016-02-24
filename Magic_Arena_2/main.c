#include "panel.h"
#include <windows.h>
#include "defines.h"
#include "header.h"
#include "windowsfunc.h"
#include "mobfunc.h"
#include "spellfunc.h"
#include "playerFunc.h"
//=============================TODO===============================
//Доделать камеру (она работает на ход вперед) Ну и код неоч
//Разобраться с указателями на функции в структуре "spell_t"
//Думать над основным циклом
//================================================================

int main(int argc, int* argv[])
{
    int i;                                                  //НЕ ЗАБЫТЬ УДАЛИТЬ, КОГДА ЗАКОНЧИШЬ ТЕСТИТЬ
    char c;                   
    camera_t        camera;                
    object_t        map[MAP_HEIGHT][MAP_WIDTH];             //map - Карта, содержит симолы стен, земли и т.д.
    player_t        player;
    listOfMobs_t   *listOfMobs;                             //Список мобов
    log_t          *log;                                    //Лог, по типу стека, вывод происходит с конца
    mob_t          *mob;                                    //НЕ ЗАБЫТЬ УДАЛИТЬ, КОГДА ЗАКОНЧИШЬ ТЕСТИТЬ
    WINDOW         *mapWin, *logWin, *infWin;
    PANEL          *window[3];                              //Панели использую для удобства, что бы все обновлять одной функцией
    srand(time(NULL));  

    //Если что-то будешь менять тут не забудь про размеры окон
    //Размеры консоли устанавливаются точно под размеры всех окон интерфейса.
    //system("mode con cols=65 lines=35");                    


    initscr();                                              ///////////////////////
    noecho();                                               ///////////////////////
    start_color();                                          ///Вход в режим ncurses
    InitColorPairs();                                       ///Инициализация цветов.
    cbreak();                                               ///////////////////////
    refresh();                                              ///////////////////////

    listOfMobs  = CreateList();                              
    log         = CreateLog();      
                              
   InitPlayer(&player, "Kissel");                                  

    camera.x = 0;
    camera.y = 0;
    camera.h = CAMERA_HEIGHT;
    camera.w = CAMERA_WIDTH;

    mapWin = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 0, INF_WIN_WIDTH);   //Создание основного окна карты и самой карты
    InitMapWindow(mapWin, MAP_WIN_HEIGHT, MAP_WIN_WIDTH);               //И инициализация 
    InitMap(map);
    map[0][0].symbol = 'S';
    map[1][1].symbol = 's';
    map[0][0].color = 1;
    map[1][1].color = 1;

    logWin = newwin(LOG_WIN_HEIGHT, LOG_WIN_WIDTH, MAP_WIN_HEIGHT, 0 ); //Создание окна лога и инициализация
    InitLogWindow(logWin);               
    
    infWin = newwin(INF_WIN_HEIGHT, INF_WIN_WIDTH, 0, 0);               //Создание окна с инофрмацией и инициализация
    InitInfWindow(infWin);

    window[MAP_WIN] = new_panel(mapWin);                                //Создание панелей
    window[LOG_WIN] = new_panel(logWin);
    window[INF_WIN] = new_panel(infWin);
    update_panels();
    doupdate();

    PutInLog(log, "1");                                         //тест работы лога типа, убери потом
    PutInLog(log, "2");
    PutInLog(log, "3");                                         //тест работы лога типа, убери потом
    PutInLog(log, "4!");
    PutInLog(log, "5");                                         //тест работы лога типа, убери потом
    PutInLog(log, "6");
    PrintLog(logWin, log);
    //PrintInf(infWin, &player);

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
    // for(i = 176; i < 224; i++)
    // {

    //     wprintw(infWin, "%c ", i);
    // }
    GenerateDungeon(map, 1000);
    PrintMap(mapWin, map, &camera, player.y, player.x);
    update_panels();
    doupdate();
    while(c = getch())
    {   
                PrintLog(logWin, log);
        PrintMap(mapWin, map, &camera, player.y, player.x);
        switch(c)
        {
            case 'w': 
                movePlayerTo(-1, 0, &player, listOfMobs, mapWin, &camera);
                break;
            case 'a': 
                movePlayerTo(0, -1, &player, listOfMobs, mapWin, &camera);
                break;
            case 's': 
                movePlayerTo(1, 0,  &player, listOfMobs, mapWin, &camera);
                break;    
            case 'd': 
                movePlayerTo(0, 1,  &player, listOfMobs, mapWin, &camera);
                break;
            case ESCAPE_SMB: 
                endwin();
                return 0;
                break;
            case 'l': 
                Look(&player, listOfMobs, log, map);
                break;
            default:
                PutInLog(log, "Unkown command");   
            break;
        }
        update_panels();
        doupdate();
    }
    getch();
    endwin();
    return 0;
}

