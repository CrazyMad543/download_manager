#include "MainFunctions.h"
#include <conio.h>
#include <iostream>

using namespace std;

int main() {
	char URL[500];
	cout << "Input URL: "; cin >> URL;
	cout << endl;
	cout << "Please, wait minute..." << endl;
	DownloadFile(URL);
	cout << endl;
	cout << "Complete";
	_getch();
	return 0;
}