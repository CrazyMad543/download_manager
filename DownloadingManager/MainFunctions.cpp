#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")
#include <fstream>
#include <iostream>
#include "MainFunctions.h"

using namespace std;

HINTERNET hInternetSession;
HINTERNET hURL;
const DWORD Size = 1024;
char Buffer[Size] = "";
DWORD error;
DWORD readBytes;
BOOL Result = true;

void DownloadFile(char* URL) {
	hInternetSession = InternetOpen("Downloading Manager", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternetSession != NULL) {
		hURL = InternetOpenUrl(hInternetSession, (LPCSTR)URL, NULL, NULL, NULL, NULL);
		if (hURL != NULL){
			ofstream news("downloaded.dat", ios::binary);
			do {
				Result = InternetReadFile(hURL, &Buffer, Size, &readBytes);
				if (Result != true) {
					error = GetLastError();
					cout << "Error" << error;
				}
				news.write(Buffer, Size);
				memset(Buffer, '\0', sizeof(Buffer));
			} while (Result == true && readBytes > 0);
		}
	}
	InternetCloseHandle(hInternetSession);
	InternetCloseHandle(hURL);
}