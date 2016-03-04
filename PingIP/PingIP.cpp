// PingIP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	PingIP()
{
	BOOL			bRet			= FALSE;

	TCHAR			tchReslt[1000]	= {0};
	CMD_RESULT_INFO CmdResultInfo	= {0};
	SYSTEMTIME		SystemTime		= {0};


	__try
	{
		CmdResultInfo.lpResult = tchReslt;
		CmdResultInfo.ulResultBufferSizeCh = _countof(tchReslt);

		if (!CCommandLine::Execute(
			_T("ping 10.0.3.254 -n 1"),
			TRUE,
			FALSE,
			&CmdResultInfo
			))
		{
			MessageBox(NULL, _T("CCommandLine::Execute failed"), _T("error"), MB_OK | MB_ICONERROR);
			__leave;
		}

		if (!CmdResultInfo.bResult)
		{
			GetLocalTime(&SystemTime);

			MessageBox(NULL, _T("CmdResultInfo.bResult failed"), _T("error"), MB_OK | MB_ICONERROR);
			__leave;
		}

		printf("%S", CmdResultInfo.lpResult);

		bRet = TRUE;
	}
	__finally
	{
		CPrintfEx::ReleaseInstance();
	}

	return bRet;
}

BOOL
	SocketConnect(
	__in ULONG ulPort,
	__in LPSTR lpIP
	)
{
	BOOL		bRet			= FALSE;

	int			iResult			= NO_ERROR;
	WSADATA		wsaData			= {0};
	SOCKET		ConnectSocket	= INVALID_SOCKET;
	sockaddr_in clientService	= {0};
	SYSTEMTIME	SystemTime		= {0};


	__try
	{
		do 
		{
			//----------------------
			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (NO_ERROR != iResult)
				__leave;

			//----------------------
			// Create a SOCKET for connecting to server
			ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (INVALID_SOCKET == ConnectSocket) 
				__leave;

			//----------------------
			// The sockaddr_in structure specifies the address family,
			// IP address, and port of the server to be connected to.
			clientService.sin_family = AF_INET;
			clientService.sin_addr.s_addr = inet_addr(lpIP);
			clientService.sin_port = htons(ulPort);

			//----------------------
			// Connect to server.
			iResult = connect(ConnectSocket, (SOCKADDR *) & clientService, sizeof (clientService));
			if (SOCKET_ERROR == iResult) 
			{
				GetLocalTime(&SystemTime);

				MessageBox(NULL, _T("connect failed"), _T("error"), MB_OK | MB_ICONERROR);

				__leave;
			}

			if (INVALID_SOCKET != ConnectSocket)
			{
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
			}

			WSACleanup();

			Sleep(1000);
		} while (TRUE);

		bRet = TRUE;
	}
	__finally
	{
		if (INVALID_SOCKET != ConnectSocket)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		}

		WSACleanup();
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// PingIP();

	SocketConnect(80, "10.0.3.171");

	_getch();

	return 0;
}
