#include "api/api.h"
#include "internal/os/util.h"
#include <cstdio>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prior, LPSTR cmd, int show)
#else
int main(int argc, const char* argv[])
#endif
{
    // initialize library
    init_lib();
    
    // initialize engine
    if (guiEngineInit(GUI_TYPE_OPENGL2, GUI_MAIN_THREAD) == 0)
    {
        // build GUI here
        if (!createMainWindow("GUI Demo", 100, 100, 800, 600, 12456, 1))
        {
            fprintf(stderr, "ERROR ! Cannot create main window !");
            exit(-1);
        }

        // start the engine
        guiEngineStart();
        // stop the engine
        guiEngineStop();
    }
    else
    {
        fprintf(stderr, "ERROR ! Cannot initialize OpenGL GUI !");
        exit(-1);
    }

    return 0;
}