// cuando se trata de una DLL, el entrypoint ya no es main
#include <stdio.h>
#include <windows.h>
#include <process.h>

int main() {
    printf("importing\n");
    int pid = _getpid();
    printf("%d\n", pid);
    char msg[20];
    sprintf_s(msg, "pid: %d\n\0", pid);
    printf("%s", msg);
    MessageBoxA(NULL, (LPCSTR)msg, NULL, NULL);
}

__declspec(dllexport) int __cdecl square(int n) {
    return n * n;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        // Se ejecuta cuando se carga la librería
        main();
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        // Se ejecuta cuando se descarga la librería
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}