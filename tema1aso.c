//Să se citească toate subcheile unei chei (la alegere) din Registry și să se afișeze la ieșirea standard. 

#include <stdio.h>
#include <windows.h>

int main()
{
	HKEY hCheieParinte;
	long rezultatStatus;

	rezultatStatus = RegOpenKeyExA(
		HKEY_CURRENT_USER,
		"Software",
		0,
		KEY_READ,
		&hCheieParinte
	);

	if (rezultatStatus != ERROR_SUCCESS) {
		printf("eroare deschidere cheie de registrii.\n");
		return 1;
	}

	char numeSubcheie[256];
	DWORD dimensiuneNume;
	DWORD indexSubcheie = 0;

	printf("Subchei gasite:\n");


	while (1) {
		dimensiuneNume = 256;

		rezultatStatus = RegEnumKeyExA(
			hCheieParinte,
			indexSubcheie,
			numeSubcheie,
			&dimensiuneNume,
			NULL,
			NULL,
			NULL,
			NULL
		);

		if (rezultatStatus==ERROR_NO_MORE_ITEMS) {
			break;
		}

		if (rezultatStatus==ERROR_SUCCESS) {
			printf("%s\n", numeSubcheie);
		}
		else {

			printf("eroare la index %lu\n", indexSubcheie);
			break;
		}

		indexSubcheie++;
	}


	RegCloseKey(hCheieParinte);



	return 0;
}