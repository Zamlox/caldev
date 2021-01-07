#include "api/api.h"
#include "internal/os/util.h"

int main(int argc, const char* argv[])
{
    if (initGUI(Api::GUI_OPENGL2) != -1)
    {
        if (!createMainWindow("GUI Demo", 100, 100, 800, 600, 12456, 1))
        {
            fprintf(stderr, "ERROR ! Cannot create main window !");
            exit(-1);
        }

        while(true)
        {
            Os::Util::instance().msleep(10);
        }
        
        stopGUI();
    }
    else
    {
        fprintf(stderr, "ERROR ! Cannot initialize OpenGL GUI !");
        exit(-1);
    }

    return 0;
}