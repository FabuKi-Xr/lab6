#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void gotoxy(int, int);
void draw_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void erase_ship(int, int);
void draw_bullet(int, int);
void erase_bullet(int, int);
void draw_star(int, int);
void print_star();
char cursor(int, int);
void erase_star(int ,int);
void erase_color(int, int);
int main()
{
	int x = 38, y = 20, direction = 1, bullet_status[6] = { 0 }, off = 0, on = 1, a[6] = { 0 }, b[6] = { 0 }, bullet[6] = { 0 }, i;
	int randX=0, randY=0,score=0,ammo=100;
	char ch = '.';
	setcursor(0);
	draw_ship(x, y);

	//for making random stars
	srand(time(NULL));
	print_star();

	//base interface to show scores and ammos
	setcolor(2, 0);
	gotoxy(0, 0);
	printf("score : %03d\n",score);
	printf("ammo : %03d\n", ammo);
	//main process
	do {

	// keyboard input//
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				direction = 4;
			}
			if (ch == 'd') {
				direction = 5;
			}
			if (ch == 's') {
				direction = 6;
			}
			if (ch == ' '&& ammo>0) {
				for (i = 1;i < 6;i++) {
					if (bullet_status[i] == off) {
						bullet_status[i] = on;
						a[i] = x + 2;
						b[i] = y - 2;
						draw_bullet(a[i], b[i]);
						ammo--;
						gotoxy(0, 1);
						setcolor(2, 0);
						printf("ammo : %03d\n", ammo);
						break;
					}
				}
			}
			fflush(stdin);
		}
	//direction//
		if (direction) {
			if (direction == 4) {
				erase_ship(x, y);
				draw_ship(--x, y);
			}
			if (direction == 5) {
				erase_ship(x, y);
				draw_ship(++x, y);
			}
			if (direction == 6) {
			}
		}
	// star // 
	//screen limit//
		if (x <= 1) { erase_ship(x, y); x = 1; draw_ship(x, y); }
		if (x >= 80) { erase_ship(x, y); x = 80; draw_ship(x, y); }

	//penta bullet//
		for (i = 1;i < 6;i++) {
			if (bullet_status[i] == on) {
				erase_color(0, 0);
				erase_bullet(a[i], b[i]);
				if (b[i] > 1 && b[i] < 24) {
					if (cursor(a[i], b[i] - 1) == '*') {
						Beep(1000,100);
						erase_color(0, 0);
						erase_star(a[i], b[i] - 1);
						erase_bullet(a[i], b[i]); 
						
						do {
							randY = rand() % 4 + 2;
							randX = rand() % 60 + 10;
						} while (cursor(randX, randY) == '*');
						draw_star(randX, randY);
						randX = 0;
						randY = 0;
						score++;
						gotoxy(0, 0);
						setcolor(2, 0);
						printf("score : %03d\n", score);
						bullet_status[i] = false;
					}
					else draw_bullet(a[i], --b[i]);
				}
				else bullet_status[i] = off;
			}
		}
		Sleep(50);
	} while (ch != 'x' );
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(13,11);
	printf(" <-0-> ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0,0);
	printf("       ");
}
void draw_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(9,13);
	printf("A");
}
void erase_bullet(int x, int y) {
	gotoxy(x, y);
	printf(" ");
}
void erase_color(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
	printf("");
}
void draw_star(int x, int y) {
	gotoxy(x, y);
	setcolor(4, 7);
	printf("*");
}
void print_star() {
	int j, i, x[21] = { 0 }, y[21] = {0}, xa = 0, ya = 0, c = 0;
		for (i = 1; i <= 20; i++)
		{
			c = 0;
			xa = rand() % 61 + 10;
			ya = rand() % 4 + 2;
			for (j = 1; j <= i; j++)
			{
				if (x[j] == xa && y[j] == ya)
					c++;
			}
			if (c == 0) {
				x[i] = xa; y[i] = ya;
				draw_star(xa, ya);
				}
			else
				{
					c = 0; i--;
				}
		}
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];
}
void erase_star(int x, int y) {
	gotoxy(x, y);
	setcolor(0,0);
	printf(" ");
}
