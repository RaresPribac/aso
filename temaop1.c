#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main()
{

    char szCaleRelativa[MAX_PATH];
    HANDLE hFisier;
    DWORD dwOctetiCititi;
    char chBuffer[512];
    BOOL bRezultatCitire;

    printf("Introduceti calea relativa a fisierului (ex: date.txt sau foldernou\\date.txt):\n");
    printf("-> ");

    if (fgets(szCaleRelativa, sizeof(szCaleRelativa), stdin) != NULL)
    {
        size_t nLungime = strlen(szCaleRelativa);
        if (nLungime > 0 && szCaleRelativa[nLungime - 1] == '\n')
        {
            szCaleRelativa[nLungime - 1] = '\0';
        }
    }

    hFisier = CreateFileA(
        szCaleRelativa,         
        GENERIC_READ,           
        FILE_SHARE_READ,        
        NULL,                   
        OPEN_EXISTING,         
        FILE_ATTRIBUTE_NORMAL,  
        NULL                    
    );

    if (hFisier == INVALID_HANDLE_VALUE)
    {
        printf("\n[EROARE] Fisierul '%s' nu exista sau nu poate fi deschis\n", szCaleRelativa);
        printf("Cod eroare Windows: %lu\n", GetLastError());

        printf("\nApasa orice tasta pentru a inchide");
        _getch();
        return 1;
    }

    printf("\nContinutul fisierului '%s'\n", szCaleRelativa);

    while (1)
    {
        bRezultatCitire = ReadFile(
            hFisier,
            chBuffer,
            sizeof(chBuffer) - 1,  
            &dwOctetiCititi,
            NULL
        );

        if (dwOctetiCititi == 0)
        {
            break;
        }

        chBuffer[dwOctetiCititi] = '\0';
        printf("%s", chBuffer);
    }

    printf("\n-----------------------------------------\n");

    CloseHandle(hFisier);

    printf("\nGata, apasa orice tasta");
    _getch();

    return 0;
}