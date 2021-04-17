REBOL [
    Title:      "GUI engine tests"
    Purpose:    "Unit tests for GUI engine"
    file:       %test-gui.r
    author:     "Iosif Haidu"
    email:      [iosif.haidu@gmail.com]
    date:       30-12-2020
    version:    0.0.1
    needs:      [
        %caldev.r
    ]
    History: [
        0.0.1 [31-12-2020 "Started"]
    ]
    Category:   [tests library graphics]
    library:    [
        level:          'intermediate
        platform:       ['win 'linux]
        type:           [test]
        domain:         [tests graphics external-library]
        tested-under:   [
            View 2.7.8.3.1
            View 2.7.8.4.3
        ]
        support:        none
        license:        'MIT
    ]
    Notes: {
        caldev library can be found at: https://github.com/Zamlox/caldev
    }
]

do %../../../bindings/rebol2/caldev.r

context [
    id-win: none
    test-main-window: does [
        caldev-init
        gui-init GUIType/OpenGL GuiEngineExecutionType/Bkg-Thread
        gui-start
        either (id-win: create-main-window "Rebol2 Main Window" 250 250 400 400 10100 1) > 0 [

            label: make face! [
                type: 'label        ;'
                offset: 0x0
                size: 10x10
                text: "Label:"
                parent: id-win
            ]
            create-widget mold label

            print "Wait for 10 seconds..."
            wait 10
        ][ alert "Something wrong happened while creating main window !" quit/return -1 ]
        gui-stop
    ]

    test-main-window
]

