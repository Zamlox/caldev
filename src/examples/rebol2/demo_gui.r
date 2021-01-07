REBOL []

do %../../bindings/rebol2/caldev.r

context [
    init-gui GUIType/OpenGL
    unless (create-main-window "GUI Demo" 250 250 400 400 10100 1) > 0 [
        alert "ERROR !!! Something wrong happened while creating main window !"
        quit/return -1
    ]

    while [true][
        wait .100
    ]

    stop-gui
]