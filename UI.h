#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#pragma once

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define ESC 27
#define CTRL_S 19
#define DEL 83
#define F11 133

#define HORIZONTAL_LINE 196
#define VERTICAL_LINE 179
#define TOP_RIGHT 191
#define TOP_LEFT 218
#define BOTTOM_RIGHT 217
#define BOTTOM_LEFT 192
#define LT 195
#define RT 180
#define TT 194
#define BT 193
#define PLUS 197
#define BOX 219

#ifndef CONSOLE_H
#define CONSOLE_H

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void rect(int x, int y, int l, int b) {
	gotoxy(x, y);
	printf("%c", TOP_LEFT);
	for (int i = 0; i < l - 2; i++) {
		printf("%c", HORIZONTAL_LINE);
	}
	printf("%c", TOP_RIGHT);
	for (int i = y + 1; i < y + b; i++) {
		gotoxy(x, i);
		printf("%c", VERTICAL_LINE);
		gotoxy(x + l - 1, i);
		printf("%c", VERTICAL_LINE);
	}
	gotoxy(x, y + b);
	printf("%c", BOTTOM_LEFT);
	for (int i = 0; i < l - 2; i++) {
		printf("%c", HORIZONTAL_LINE);
	}
	printf("%c", BOTTOM_RIGHT);
}

#endif

int max_val(int *values) {
	int max = -1;
	for (int i = 0; i < 24; i++) {
		if (max == -1 || max < values[i]) {
			max = values[i];
		}
	}
	return max;
}

int *normalize_data(int *values) {
	int max_element = max_val(values);
	int *normalized_data = (int *)calloc(24, sizeof(int));
	for (int i = 0; i < 24; i++) {
		normalized_data[i] = ((float)values[i] / max_element) * 20;
	}
	return normalized_data;
}

void _print_graph(int width, int height, int *normalized_values, int *actual_values) {
	int startx = 7, starty = 5;
	int i, j;
	for (j = 0; j < height; j++) {
		gotoxy(startx, starty + j); printf("%c", VERTICAL_LINE);
	}
	gotoxy(startx++, starty + j); printf("%c", BOTTOM_LEFT);
	for (i = 0; i < width; i++) {
		gotoxy(startx + i, starty + j); printf("%c", HORIZONTAL_LINE);
	}
	int k = 3;
	for (int index = 0; index < 24; index++) {
		for (int val = 0; val < normalized_values[index]; val++) {
			gotoxy(startx + k, starty + j - 1 - val); printf("%c", BOX);
		}
		gotoxy(startx + k, starty + j + 1); printf("%d", index);
		gotoxy(startx + k, starty + j - 2 - normalized_values[index]); printf("%d", actual_values[index]);
		k += 4;
	}
}

void print_graph(int *values) {
	system("cls");
	gotoxy(45, 1);
	printf("TIMELINE OF PREVIOUS DATA");
	int width = 100, height = 20;
	int *normalized_data = normalize_data(values);
	_print_graph(width, height, normalized_data, values);
	gotoxy(0, 0); _getch();
}

void _print_data(int *data, void (print_method(int a))) {
	gotoxy(40, 0); printf("%20s", "BOOK AN AD!!");
	int hrs = 0, x = 20;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 12; j++) {
			gotoxy(30 * (i + 1), 2 + j * 2); printf("%2d-%2d hrs:", hrs, hrs + 1); print_method(data[hrs]);
			hrs++;
		}
	}
}

void print_boolean(int a) {
	printf("%c", a == 0 ? 251 : 220);
}

void print_free_slot(int *boolean_data) {
	system("cls");
	_print_data(boolean_data, &print_boolean);
	printf("\n");
}

void print_int(int a) {
	printf("%d", a);
}

void print_24hr_data(int *values) {
	system("cls");
	_print_data(values, &print_int);
}

char *read_string(int is_password) {
	char *str = (char *)malloc(40 * sizeof(char)), ch;
	int index = 0;
	int flag = 0;
	do {
		if (is_password) {
			ch = _getch();
			printf("*");
			if ((index + 1) % 4 == 0) {
				printf(" ");
			}
		}
		else {
			ch = _getche();
		}
		if(ch==ESC||ch==ENTER)
            break;
		str[index++] = ch;
		if (is_password && index == 16) {
			flag = 1;
			break;
		}

	} while (ch != ESC && ch != ENTER);
	str[index] = '\0';
	if (flag) return str;
	if (ch == ESC) return NULL;
	return str;
}

char **payment_page(int price) {
	system("cls");
	char *name, *card;
	rect(7, 1, 100, 27);
	gotoxy(50, 2); printf("PAYMENT PORTAL");
	gotoxy(30, 5); printf("NAME:");
	rect(40, 4, 40, 2);
	gotoxy(20, 10); printf("Amount to be payed:");
	rect(40, 9, 40, 2);
	gotoxy(41, 10); printf("%d $", price);
	gotoxy(25, 15); printf("DEBIT CARD:");
	rect(40, 14, 40, 2);
	gotoxy(41, 5); name = read_string(0);
	if (name == NULL) return NULL;
	gotoxy(41, 15); card = read_string(1);
	if (card == NULL) return NULL;
	int ch;
	gotoxy(50, 21); printf("[ENTER] - PAY NOW");
	gotoxy(50, 23); printf("  [ESC] - CANCEL");
	do {
		gotoxy(0, 0);
		ch = _getch();
	} while (ch != ESC && ch != ENTER);
	if (ch == ESC) return NULL;
	char **ans = (char **)calloc(2, sizeof(char *));
	ans[0] = name;
	ans[1] = card;
	return ans;
}

void payment_status(int is_done) {
	rect(25, 25, 65, 2);
	gotoxy(31, 26);
	if (is_done) {
		printf("PAYMENT SUCCESSFUL! THANKS FOR USING OUR SERVICE!");
	}
	else {
		printf("PAYMENT UNSUCCESSFUL! NO DATA/IMPROPER DATA PROVIDED!");
	}
}

int main_menu(int option_count, ...) {
	char **options = (char **)calloc(option_count, sizeof(char *));
	va_list valist;
	va_start(valist, option_count);
	for (int i = 0; i < option_count; i++) {
		options[i] = (char *)malloc(100 * sizeof(char));
		strcpy(options[i], va_arg(valist, char *));
	}
	va_end(valist);
	int option = 0, ch, end_loop = 0;
	do {
		system("cls");
		for (int i = 0; i < option_count; i++) {
			gotoxy(45, 4 + i * 2); printf("%s", options[i]);
		}
		gotoxy(26, 4 + option * 2); printf("=>");
		gotoxy(0, 0);
		ch = _getch();
		switch (ch) {
		case 0:
		case 224:
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				option--;
				if (option < 0) option = option_count - 1;
				break;

			case DOWN_ARROW:
				option++;
				if (option >= option_count) option = 0;
				break;
			}
			break;

		case ENTER:
			return option;
			break;

		case ESC:
			return -1;
			break;
		}
	} while (end_loop != 1);
}
