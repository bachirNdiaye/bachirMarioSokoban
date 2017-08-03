#ifndef OS_H
#define OS_H

#define WINDOWS // <-- PUT THE OS HERE

#ifdef LINUX
#define CLEAR() system("clear");
#define PAUSE() printf("Appuyez sur une touche pour quitter...\n");\
				getchar();
#define SLEEP(n) sleep(n);
#endif

#ifdef MAC_OS
#define CLEAR() system("clear");
#define PAUSE() printf("Appuyez sur une touche pour quitter...\n");\
				getchar();
#define SLEEP(n) sleep(n);
#endif

#ifdef WINDOWS
#include <windows.h>
#define CLEAR() system("cls");
#define PAUSE() system("pause");
#define SLEEP(n) Sleep(n*1000);
#endif

#endif