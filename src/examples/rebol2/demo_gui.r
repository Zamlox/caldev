REBOL []

do %../../bindings/rebol2/caldev.r

context [
    caldev-init
    gui-init GUIType/OpenGL GuiEngineExecutionType/Bkg-Thread
    gui-start
    unless (create-main-window "GUI Demo" 250 250 400 400 10100 1) > 0 [
        alert "ERROR !!! Something wrong happened while creating main window !"
        quit/return -1
    ]

    label: make face [
        type: 'label        ;'
        offset: 0x0
        size: 100x100
    ]

    create-widget mold label

    while [true][
        wait .100
    ]

    gui-stop
]