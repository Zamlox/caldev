REBOL [
    Title:      "GUI engine tests"
    Purpose:    "Unit tests for GUI engine"
    file:       %test-gui.r
    author:     "Iosif Haidu"
    email:      [iosif.haidu@gmail.com]
    date:       30-12-2020
    version:    0.0.1
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
    build-widget: func [
        descr   [ block! ]
        /local widget
    ][
        widget: make face! descr
        create-widget mold widget
        widget
    ]

    id-win: none
    test-main-window: does [
        caldev-init
        gui-init GUIType/OpenGL GuiEngineExecutionType/Bkg-Thread
        gui-start
        main-x: 100
        main-y: 100
        main-width: 1400
        main-height: 700
        either (id-win: create-main-window "Rebol2 Main Window" main-x main-y main-width main-height -2147483646 1) > 0 [

            fontD: make face!/font [
                name: "arial"
                size: 20
                color: 255.255.255.255
                align: 'right
                valign: 'top
            ]


            build-widget [
                type: 'window   ;'
                offset: 30x30
                size: 600x300
                color: 128.234.34.255
                text: "Window 1"
                font: make face!/font [
                    name: "arial"
                    size: 20
                    color: 200.200.200.255
                    align: 'right
                    valign: 'top
                ]
                parent: id-win
            ]
            build-widget [
                type: 'window   ;'
                offset: 130x130
                size: 600x300
                color: 28.34.34.155
                text: "Window 2"
                font: make face!/font [
                    name: "arial"
                    size: 20
                    color: 200.200.200.255
                    align: 'right
                    valign: 'top
                ]
                parent: id-win
            ]

            label: build-widget [
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

            area-start-x: label/size/x + 20
            area-height: 200
            area: make face! [
                type: 'area        ;'
                offset: as-pair area-start-x 10
                size: as-pair main-width - area-start-x area-height
                color: 100.138.100.170
                text: rejoin ["a" newline "Text sample aaaa bbbbb cccc dddd  eee eee e e e efffff f f f ff f ffffff mmmmmmm kkkk kk kkk k  aaaa kk" newline "Groovie !" ]
                font: make face!/font [
                    name: "arial"
                    size: 20
                    color: 200.200.200.255
                    align: 'right
                    valign: 'top
                ]

                options: [ uppercase ]
                parent: id-win
            ]
            create-widget mold area

            build-widget [
                type: 'field        ;'
                offset: 100x400
                size: 200x0
                color: 100.138.100.170
                text: ""
                font: fontD
                options: [ uppercase hint "Hint text"]
                parent: id-win
            ]
            build-widget [
                type: 'button        ;'
                offset: 100x350
                size: 100x30
                color: 100.138.100.170
                text: "Buttonp"
                font: make fontD [
                    align: 'center
                    valign: 'middle
                ]
                options: none
                parent: id-win
            ]
            build-widget [
                type: 'checkbox        ;'
                offset: 230x350
                size: 100x30
                color: 100.138.100.170
                text: "Checkbox"
                font: make fontD [
                    align: 'right
                    valign: 'middle
                ]
                options: [ checkmark 255.0.0.100 ]
                parent: id-win
            ]
            build-widget [
                type: 'radio        ;'
                offset: 350x350
                size: 100x30
                color: 100.138.100.170
                text: "Radio 1"
                font: make fontD [
                    align: 'right
                    valign: 'middle
                ]
                options: [ group 1 selected ]
                parent: id-win
            ]
            build-widget [
                type: 'radio        ;'
                offset: 490x350
                size: 100x150
                color: 0.0.0.255
                text: "Radio 2"
                font: make fontD [
                    align: 'right
                    valign: 'middle
                ]
                options: [ group 1 ]
                parent: id-win
            ]
            build-widget [
                type: 'image        ;'
                offset: 10x400
                size: 500x80
                color: 0.0.255.255
                image: "D:\Pictures\test.png"
                parent: id-win
            ]
            build-widget [
                type: 'combo        ;'
                offset: 600x350
                size: 100x150
                color: 0.0.0.255
                font: make fontD [
                    align: 'right
                    valign: 'middle
                ]
                options: [ select "Option" ]
                data: ["Option 1" "Option 2" "Option 3"]
                parent: id-win
            ]

            unstash

            print "Wait for 100 seconds..."
            wait 100
        ][ alert "Something wrong happened while creating main window !" quit/return -1 ]
        gui-stop
    ]

    test-main-window
]

