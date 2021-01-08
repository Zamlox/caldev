REBOL []

do %../../bindings/rebol2/caldev.r

context [
    gui-init GUIType/OpenGL GuiEngineExecutionType/Bkg-Thread
    gui-start
    unless (create-main-window "GUI Demo" 250 250 400 400 10100 1) > 0 [
        alert "ERROR !!! Something wrong happened while creating main window !"
        quit/return -1
    ]

    while [true][
        wait .100
    ]

    gui-stop
]