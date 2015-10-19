#pragma once
#include <Windows.h>

class ProgressBar {
private:
	DWORD textIteration;
	DWORD visualIteration;
	DWORD constTextIteration;
	DWORD constVisualIteration;
	double sizeArr;
	double progress;
	int itemArr;
	DWORD allReadBytes;
public:
	void clearScreen();
	void PrintProgressBar();
	void UpdateProgressBar(bool, DWORD);
	ProgressBar(double);
	~ProgressBar();
};