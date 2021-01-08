REBOL [
    Title:      "Binding for caldev library"
    Purpose:    "Allow calling functions from caldev library"
    file:       %caldev.r
    author:     "Iosif Haidu"
    email:      [iosif.haidu@gmail.com]
    date:       30-12-2020
    version:    0.0.1
    needs:      []
    History: [
        0.0.1 [31-12-2020 "Started"]
    ]
    Category:   [library graphics]
    library:    [
        level:          'intermediate
        platform:       ['win 'linux]
        type:           [module]
        domain:         [graphics external-library]
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


; adjust library path as needed

lib-path: either System/version/4 = 3 [
    to-rebol-file "..\..\bazel-bin"         ; windows
][  to-rebol-file "../../bazel-bin" ]       ; linux, macOS


; load libray

lib: either System/version/4 = 3 [ %caldev32.dll ][ %libcaldev32.so ]

if not attempt [ caldev-lib: load/library lib-path/:lib ] [ alert rejoin ["Cannot locate library " lib " !"] quit ]


; constants

GUIType: [          ; must match Api::GuiType 
    OpenGL      0
    DirectX     1
]

GuiEngineExecutionType: [
    Main-Thread     0
    Bkg-Thread      1
]


; helper functions

func-caldev: func [ specs identifier ][
    make routine! specs caldev-lib identifier
]


; library functions

caldev-funcs: [
    gui-init [ 
        "Initialize GUI engine"
        type    [ integer! ] "A GUIType value"
        thread  [ integer! ] "Thread type to run GUI engine"
    ] "guiEngineInit"

    gui-start [
        "Start GUI engine"
    ] "guiEngineStart"

    gui-stop [
        "Stop GUI engine"
    ] "guiEngineStop"
    
    create-main-window [
        "Create main window"
        title   [ string! ]     "window title"
        x       [ integer! ]    "X coordinate of top-left corner of window content"
        y       [ integer! ]    "y coordinate of top-left corner of window content"
        width   [ integer! ]    "window width"
        height  [ integer! ]    "window height"
        color   [ integer! ]    "background color"
        visible [ integer! ]    "window visibility"
        return: [ integer! ]    "0 if successful, -1 otherwise"
    ] "createMainWindow"

    hide-main-window [
        "Hide main window"
    ] "hideMainWindow"

    show-main-window [
        "Show main window"
    ] "showMainWindow"
]


; get functions

foreach [ name spec lib-func ] caldev-funcs [
    set name func-caldev spec lib-func
]
