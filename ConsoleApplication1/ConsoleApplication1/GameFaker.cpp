// GameFaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;

struct point3D
{
	int x;
	int y;
	int z;
};

//server
int main()
{
	//pipe
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\gamePipe");
	HANDLE hPipe;

	//create pipe
	hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

	//handle bad pipe creation
	if (!hPipe || hPipe == INVALID_HANDLE_VALUE) 
	{
		cout << "failed to make pipe" << endl;
		cout << endl << endl << GetLastError() << endl;
		system("pause");
		return 1;
	}

	//Connect to consumer
	bool successfulConnection = ConnectNamedPipe(hPipe, NULL);

	//handle bad connection
	if (!successfulConnection) 
	{
		cout << "bad connection" << endl << endl;
		cout << GetLastError() << endl;
		system("pause");
		return 2;
	}

	double data[1];
	DWORD bytesWritten;

	cout << "Inpug fake game ID (should be unique)" << endl;
	cout << "GameID: ";
	cin >> data[0];

	//write data
	bool succcessfulWrite = WriteFile(
		hPipe,
		data,
		sizeof(data),
		&bytesWritten,
		NULL);
	///////////////////////////////
	//	logic with written data	//
	/////////////////////////////
	if (succcessfulWrite) {
		cout << "sent " << bytesWritten << endl;
	} else {
		cout << "failed to send data" << endl;
	}

	bool stop = false;

	while (!stop)
	{
		//Data to write
		double data[2];
		DWORD bytesWritten;

		cout << "Input number of players and radios to read" << endl;
		cout << "players: " << endl;
		cin >> data[0];
		cout << "radios: ";
		cin >> data[1];

		//write data
		bool succcessfulWrite = WriteFile(
			hPipe,
			data,
			sizeof(data),
			&bytesWritten,
			NULL);
		///////////////////////////////
		//	logic with written data	//
		/////////////////////////////
		if (succcessfulWrite)
		{
			cout << "sent players and radios" << bytesWritten << endl;
		}
		else
		{
			cout << "failed to send data" << endl;
		}
		////////////////
		//	EndLogic //
		//////////////

		for (unsigned int i = 0; i < data[0]; i++) {
			cout << "Radio " << i << " data:" << endl;
			cout << "x, y, z, voiceLevel(volume of voice), frequency, volume(of radio), on, broadcasting" << endl;
			double radioData[8];
			for (unsigned int j = 0; j < 8; j++) {
				cin >> radioData[j];
			}

			//write data
			bool succcessfulWrite = WriteFile(
				hPipe,
				radioData,
				sizeof(radioData),
				&bytesWritten,
				NULL);
			///////////////////////////////
			//	logic with written data	//
			/////////////////////////////
			if (succcessfulWrite) {
				cout << "sent radio" << bytesWritten << endl;
			} else {
				cout << "failed to send data" << endl;
			}
		}

		for (unsigned int i = 0; i < data[1]; i++) {
			cout << "Player " << i << " data: " << endl;
			cout << "x, y, z, voiceLevel (voice volume), selectedRadio, gameID" << endl;
			double playerData[6];

			for (unsigned int j = 0; j < 6; j++) {
				cin >> playerData[j];
			}

			//write data
			bool succcessfulWrite = WriteFile(
				hPipe,
				playerData,
				sizeof(playerData),
				&bytesWritten,
				NULL);
			///////////////////////////////
			//	logic with written data	//
			/////////////////////////////
			if (succcessfulWrite) {
				cout << "sent radio" << bytesWritten << endl;
			} else {
				cout << "failed to send data" << endl;
			}
		}

		cout << "stop? 1 = yes, 0 = no" << endl;
		cin >> stop;
	}

	//close pipe
	CloseHandle(hPipe);

	system("pause");
    return 0;
}

