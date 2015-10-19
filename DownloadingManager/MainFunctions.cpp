#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")
#include <fstream>
#include <iostream>
#include "ProgressBar.h"
#include "MainFunctions.h"

using namespace std;

HINTERNET hInternetSession;
HINTERNET hURL;
const DWORD size = 1024;
char buffer[size] = "";
DWORD error; 
char sizeFileChar[size] = "";
double sizeFileInt;
DWORD sizeBuff = sizeof(sizeFileChar);
DWORD readBytes;
BOOL result = true;

void DownloadFile(char* URL) {
	hInternetSession = InternetOpen("Downloading Manager", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternetSession != NULL) {
		hURL = InternetOpenUrl(hInternetSession, (LPCSTR)URL, NULL, NULL, NULL, NULL);
		if (hURL != NULL){
			ofstream news("downloaded.dat", ios::binary);
			HttpQueryInfo(hURL, HTTP_QUERY_CONTENT_LENGTH, &sizeFileChar, &sizeBuff, NULL);
			sizeFileInt = atoi(sizeFileChar);
			ProgressBar progressBar(sizeFileInt);
			do {
				result = InternetReadFile(hURL, &buffer, size, &readBytes);
				if (result != true) {
					error = GetLastError();
					cout << "Error " << error;
				}
				progressBar.UpdateProgressBar(result, readBytes);
				news.write(buffer, size);
				memset(buffer, '\0', sizeof(buffer));
			} while (result == true && readBytes > 0);
		}
	}
	InternetCloseHandle(hInternetSession);
	InternetCloseHandle(hURL);
}