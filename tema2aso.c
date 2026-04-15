#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	SC_HANDLE hManagerServicii;
	LPBYTE lpBufferDate = NULL;
	DWORD nrServiciiGasite = 0;
	DWORD octetiNecesari = 0;
	DWORD punctReluare = 0;

	hManagerServicii = OpenSCManagerW(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);

	if (hManagerServicii == NULL)
	{
		printf("eroare la deschidere manager: %ld\n", GetLastError());
		return 1;
	}
	printf("start\n");

	EnumServicesStatusExW(
		hManagerServicii,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		NULL,
		0,
		&octetiNecesari,
		&nrServiciiGasite,
		&punctReluare,
		NULL
	);

	lpBufferDate = (LPBYTE)malloc(octetiNecesari);
	if (lpBufferDate == NULL) {
		CloseServiceHandle(hManagerServicii);
		return 1;
	}

	if (EnumServicesStatusExW(
		hManagerServicii,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		lpBufferDate,
		octetiNecesari,
		&octetiNecesari,
		&nrServiciiGasite,
		&punctReluare,
		NULL))
	{
		ENUM_SERVICE_STATUS_PROCESSW* listaServicii = (ENUM_SERVICE_STATUS_PROCESSW*)lpBufferDate;

		printf("s-au gasit % lu servicii: \n\n", nrServiciiGasite);

		for (DWORD i = 0; i < nrServiciiGasite; i++)
		{
			if (listaServicii[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING)
			{
				wprintf(L"%s\n", listaServicii[i].lpDisplayName);
			}
		}
	}
	else
	{
		printf("eroare la enumerare: %ld\n", GetLastError());
	}
	free(lpBufferDate);
	CloseServiceHandle(hManagerServicii);
	printf("\nfinal");
	_getch();

	return 0;
}