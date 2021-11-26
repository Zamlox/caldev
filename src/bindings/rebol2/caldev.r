REBOL [
    Title:      "Binding for caldev library"
    Purpose:    "Allow calling functions from caldev library"
    file:       %caldev.r
    author:     "Iosif Haidu"
    email:      [iosif.haidu@gmail.com]
    date:       30-12-2020
    version:    0.0.1
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

base-path: ""
either system/options/args [
    base-path: to-rebol-file system/options/args/1
][
    base-path: ""
]

lib-path: rejoin [ base-path %/Debug ]

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
    caldev-init [
        "Initialize library"
    ] "init_lib"

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

    create-widget [
        "Create widget from molded face. Returns widget id."
        molded-face [ string! ]
        return:     [ integer! ]
    ] "createWidget"

    bufferingBegin [
        "Buffer graphic data"
    ] "bufferingBegin"

    bufferingCommit [
        "Commit buffered data"
    ] "bufferingCommit"
]


; get functions

foreach [ name spec lib-func ] caldev-funcs [
    set name func-caldev spec lib-func
]

face!: make object! [
    type: 'face
    offset: 0x0
    size: 100x100
    span: none
    pane: none
    text: none
    color: 200.200.200
    image: none
    effect: none
    data: none
    edge: make object! [
        color: 200.200.200
        image: none
        effect: none
        size: 2x2
    ]
    font: make object! [
        name: "arial"
        style: none
        size: 12
        color: 0.0.0
        offset: 2x2
        space: 0x0
        align: 'center
        valign: 'center
        shadow: none
        path: none
    ]
    para: make object! [
        origin: 2x2
        margin: 2x2
        indent: 0x0
        tabs: 40
        wrap?: true
        scroll: 0x0
    ]
    feel: make object! [
        redraw: none
        detect: none
        over: none
        engage: none
    ]
    saved-area: none
    rate: none
    show?: true
    options: none
    parent-face: none
    old-offset: none
    old-size: none
    line-list: none
    changes: none
    face-flags: 0
    action: none
    id: none
    parent: none
]

image!: make object! [
    size: 0x0
    channels: 3
    data: none      ; must be binary size.x * size.y * channels : #{000000}
]