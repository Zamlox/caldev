REBOL [
    Title:      "Binding for rebosdk library"
    Purpose:    "Allow calling functions from rebosdk library"
    file:       %lib.r
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
        platform:       ['win 'linux 'macOS]
        type:           [module]
        domain:         [graphics external-library]
        tested-under:   [
            View 2.7.8.3.1
            View 2.7.8.4.3
            View 2.7.8.2.5
        ]
        support:        none
        license:        'MIT
    ]
    Notes: {
        rebosdk library can be found at: https://github.com/Zamlox/rebosdk
    }
]


; adjust library path as needed

lib-path: either System/version/4 = 3 [
    to-rebol-file "..\..\bazel-bin"         ; windows
][  to-rebol-file "../../bazel-bin" ]       ; linux, macOS


; load libray

lib: either System/version/4 = 3 [ %rebosdk32.dll ][ %librebosdk32.so ]

if not attempt [ rebosdk-lib: load/library lib-path/:lib ] [ alert rejoin ["Cannot locate library " lib " !"] quit ]


; constants

GUIType: [          ; must match Api::GuiType 
    OpenGL      0
    DirectX     1
]


; helper functions

func-rebosdk: func [ specs identifier ][
    make routine! specs rebosdk-lib identifier
]


; library functions

rebosdk-funcs: [
    init-gui [ 
        "Initialize GUI engine"
        type [ integer! ] "A GUIType value"
    ] "initGUI"

    stop-GUI [
        "Stop GUI engine"
    ] "stopGUI"
    
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

foreach [ name spec lib-func ] rebosdk-funcs [
    set name func-rebosdk spec lib-func
]
