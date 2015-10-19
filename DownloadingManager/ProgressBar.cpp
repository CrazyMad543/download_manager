#include "ProgressBar.h"
#include <stdio.h>
#include <windows.h>

ProgressBar::ProgressBar(double N) {
	sizeArr = 20;
	itemArr = 0;
	progress = 0;
	textIteration = N / 100;
	visualIteration = N / 20;
	constVisualIteration = visualIteration;
	constTextIteration = textIteration;
	allReadBytes = 0;
}

void ProgressBar::PrintProgressBar() {
	clearScreen();
	printf("[");
	for (int i(0); i < sizeArr; i++) {
		if (i < itemArr || itemArr == 19) {
			printf("=");
		} 
		else if (i >= itemArr) {
			printf("*");
		}
	}
	printf("] %3.0f%%\n", progress);
}

void ProgressBar::UpdateProgressBar(bool result, DWORD readBytes) {
	if (result) {
		if (allReadBytes >= textIteration) {
			progress += 1;
			textIteration += constTextIteration;
			allReadBytes += readBytes;
			PrintProgressBar();
		}
		else if (allReadBytes >= visualIteration) {
			itemArr++;
			visualIteration += constVisualIteration;
			allReadBytes += readBytes;
			PrintProgressBar();
		}
		else allReadBytes += readBytes;
	}
}

ProgressBar::~ProgressBar() {

}

void ProgressBar::clearScreen() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}