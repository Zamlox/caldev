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
        either (id-win: create-main-window "Rebol2 Main Window" 100 100 600 700 10100 1) > 0 [

            window: make face! [
                type: 'window   ;'
                offset: 30x30
                size: 300x300
                color: 128.234.34.255
                text: "Test Window"
                font: make face!/font [
                    name: "arial"
                    size: 20
                    color: 200.200.200.255
                    align: 'right
                    valign: 'top
                ]
                parent: id-win
            ]
            create-widget mold window

            label: make face! [
                type: 'label        ;'
                offset: 10x10
                size: 350x240
                color: 200.38.100.255
                text: rejoin ["a" newline "Text sample aaaa bbbbb cccc dddd  eee eee e e e efffff f f f ff f ffffff mmmmmmm kkkk kk kkk k  aaaa kk" newline "Groovie !" ]
                ;text: rejoin ["a" newline "Text sample" newline "b !" ]
                font: make face!/font [
                    name: "arial"
                    size: 20
                    color: 200.200.200.255
                    align: 'right
                    valign: 'top
                ]
                para: make face!/para [
                    origin: 2x2
                    margin: 2x2
                    indent: 0x0
                    tabs: 40
                    wrap?: true
                    scroll: 0x0
                ]
                parent: id-win
            ]
            create-widget mold label

            print "Wait for 10 seconds..."
            wait 100
        ][ alert "Something wrong happened while creating main window !" quit/return -1 ]
        gui-stop
    ]

    test-main-window
]

