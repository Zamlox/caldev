from ctypes import *
import platform
import time

GUI_ENGINE_OPENGL=0
GUI_ENGINE_THREAD_BKG=1

def load_caldev():
    if platform.system() == 'Windows':
        return cdll.LoadLibrary("..\\..\\..\\bazel-bin\\caldev.dll")
    else:
        if platform.system == 'Linux':
            return cdll.LoadLibrary("../../../bazel-bin/libcaldev.so")
    return

def test_gui():
    caldev = load_caldev()
    if caldev is not None:
        caldev.guiEngineInit(GUI_ENGINE_OPENGL, GUI_ENGINE_THREAD_BKG)
        caldev.guiEngineStart()
        caldev.createMainWindow("Python", 100, 100, 700, 400, 12345, 1)
        time.sleep(5)
        caldev.guiEngineStop()
    return

if __name__ == '__main__':
    test_gui()