REBOL [
]

face!: make object! [
    type: 'face         ;'
    offset: 20x20
    size: 100x100
    span: none
    pane: none
    text: none
    color: 200.200.200
    image: none
    effect: none
    data: none
    edge: none
    font: none
    para: none
    feel: none
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
edge!: make object! [
    color: 200.200.200
    image: none
    effect: none
    size: 2x2
]
font!: make object! [
    name: "arial"
    style: none
    size: 12
    color: 0.0.0
    offset: 2x2
    space: 0x0
    align: 'center      ;'
    valign: 'middle     ;'
    shadow: none
    path: none
]
para!: make object! [
    origin: 2x2
    margin: 2x2
    indent: 0x0
    tabs: 40
    wrap?: true
    scroll: 0x0
]
feel!: make object! [
    redraw: none
    detect: none
    over: none
    engage: none
]

system/error: make system/error [
    caldev-errors: make object! [
        code: 2000
        type: "Caldev error"
        err-style-def: [ "Expected style name after:" :arg1 ]
    ]
]

context [
	pairs:  copy []
	texts:  copy []
	colors: copy []
	files:  copy []
	blocks: none
	images: copy []
	chars:  copy []
	logics: copy []
	decimals:   copy []
	times:  copy []
	functions:  copy []
	keywords:   [ style ]
    make-blocks: does [ blocks: [ edge [] font [] para [] feel [] effect [] ] ]
    make-blocks ; create blocks
    default: compose [
        text        ""
        size        20x20
        win-size    100x100
        bk-color    (none)
        fr-color    0.0.0
    ]
    styles: copy compose [
        window      (make face! [
            type:   'window     ;'
            size:   default/win-size
        ])
        title       (make face! [
            type:   'title    ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold ]
                size:    24
                align:   'center
                valign:  'middle
            ]
        ])
        h1          (make face! [
            type:   'h1   ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold ]
                size:    20
                align:   'left
                valign:  'top
            ]
        ])
        h2          (make face! [
            type:   'h2     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold ]
                size:    16
                align:   'left
                valign:  'top
            ]
        ])
        h3          (make face! [
            type:   'h3     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold ]
                size:    14
                align:   'left
                valign:  'top
            ]
        ])
        h4          (make face! [
            type:   'h4     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold ]
                size:    12
                align:   'left
                valign:  'top
            ]
        ])
        h5          (make face! [
            type:   'h5     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:   [ bold italic ]
                size:    12
                align:   'left
                valign:  'top
            ]
        ])
        banner      (make face! [
            type:   'banner     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold ]
                size:   24
                color:  250.215.0
                align:  'center
                valign: 'middle
                shadow: 3x3
            ]
        ])
        vh1         (make face! [
            type:   'vh1        ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold ]
                size:   20
                color:  255.255.255
                align:  'center
                valign: 'middle
                shadow: 3x3
            ]
        ])
        vh2         (make face! [
            type:   'vh2        ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold ]
                size:   16
                color:  255.255.255
                align:  'center
                valign: 'middle
                shadow: 2x2
            ]
        ])
        vh3         (make face! [
            type:   'vh3        ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold italic ]
                size:   16
                color:  255.255.255
                align:  'center
                valign: 'middle
                shadow: 2x2
            ]
        ])
        text        (make face! [
            type:   'text       ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                size:   12
                align:  'left
                valign: 'top
            ]
        ])
        tt          (make face! [
            type:   'tt     ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                name:   "courier new"
                size:   12
                align:  'left
                valign: 'top
            ]
        ])
        code        (make face! [
            type:   'code       ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                name:   "courier new"
                style:  [ bold ]
                size:   12
                align:  'left
                valign: 'top
            ]
        ])
        vtext       (make face! [
            type:   'vtext      ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                size:   12
                color:  255.255.255
                align:  'left
                valign: 'top
                shadow: 1x1
            ]
        ])
        txt         (make face! [
            type:   'txt        ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                size:   12
                align:  'left
                valign: 'top
            ]
        ])
        label       (make face! [
            type:   'label      ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold ]
                size:   12
                color:  255.255.255
                align:  'left
                valign: 'middle
                shadow: 1x1
            ]
        ])
        lbl         (make face! [
            type:   'lbl        ;'
            text:   default/text
            size:   default/size
            color:  default/bk-color
            font:   make font! [
                style:  [ bold ]
                size:   12
                align:  'left
                valign: 'middle
            ]
        ])
        field       (make face! [
            type:   'field      ;'
            size:   200x24
            color:  240.240.240
            edge:   make edge! [
                color:  110.120.130
                image:  none
                effect: 'ibevel     ;'
                size:   2x2
            ]
            font:   make font! [
                size:   12
                color:  0.0.0
                align:  'left
                valign: 'top
            ]
        ])
        info        (make face! [
            type:   'info       ;'
            size:   200x24
            color:  240.240.240
            edge:   make edge! [
                color:  110.120.130
                image:  none
                effect: 'ibevel     ;'
                size:   2x2
            ]
            font:   make font! [
                size:   12
                align:  'left       ;'
                valign: 'top        ;'
            ]
        ])
        area        (make face! [
            type:   'area       ;'
            size:   400x150
            color:  240.240.240
            edge:   make edge! [
                color:  110.120.130
                image:  none
                effect: 'ibevel     ;'
                size:   2x2
            ]
        ])
        button      (make face! [
            type:   'button     ;'
            size:   100x24
            color:  44.80.132
            effect: [
                gradient 0x1 66.120.192 44.80.132
            ]
            edge:   make edge! [
                color:  110.120.130
                image:  none
                effect: 'bevel      ;'
                size:   2x2
            ]
            font:   make font! [
                size:   12
                style:  'bold       ;'
                color:  255.255.255
                align:  'center     ;'
                valign: 'middle     ;'
                shadow: 1x1
            ]
        ])
        checkbox    (make face! [
            type:   'checkbox       ;'
            size:   16x16
            color:  240.240.240
            edge:   make edge! [
                color:  110.120.130
                image:  none
                effect: 'ibevel     ;'
                size:   2x2
            ]
        ])
        radio       (make face! [
            type:   'radio      ;'
            size:   13x13
            color:  240.240.240
            effect: [ anti-alias ]
        ])
        image       (make face! [
            type:   'image      ;'
            effect: [ fit ]
            edge:   make edge! [
                color:  0.0.0
                image:  none
                effect: none
                size:   0x0
            ]
            font:   make font! [
                style:  'bold       ;'
                size:   16
                color:  255.255.255
                align:  'center     ;'
                valign: 'middle     ;'
                shadow: 2x2
            ]
        ])
        combo       (make face! [
            type:   'combo      ;'
        ])
    ]
    is-new-style: false
    face: none
    text-type:  styles/label/type
    field-type: styles/field/type
    fill-in: [
        title   [ make-text-style face ]
        h1      [ make-text-style face ]
        h2      [ make-text-style face ]
        h3      [ make-text-style face ]
        h4      [ make-text-style face ]
        h5      [ make-text-style face ]
        banner  [ make-text-style face ]
        vh1     [ make-text-style face ]
        vh2     [ make-text-style face ]
        vh3     [ make-text-style face ]
        text    [ make-text-style face ]
        tt      [ make-text-style face ]
        code    [ make-text-style face ]
        vtext   [ make-text-style face ]
        txt     [ make-text-style face ]
        label   [ make-text-style face ]
        lbl     [ make-text-style face ]
        window [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/offset: pairs/1 ]
            if (length? pairs) >= 2 [ face/size: pairs/2 ]
            if (length? colors) >= 2 [ face/color: colors/2 ]
            unless empty? colors [ face/font/color: colors/1 ]
            make-font-from-blocks face styles/window/font
            make-edge-from-blocks face styles/window/edge
            make-para-from-blocks face styles/window/para
        ]
        field [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/field/font
            make-edge-from-blocks face styles/field/edge
            make-para-from-blocks face styles/filed/para
        ]
        info [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/info/font
            make-edge-from-blocks face styles/info/edge
            make-para-from-blocks face styles/info/para
            face/type:    field-type
        ]
        area [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/area/font
            make-edge-from-blocks face styles/area/edge
            make-para-from-blocks face styles/area/para
        ]
        button [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/button/font
            make-edge-from-blocks face styles/button/edge
            make-para-from-blocks face styles/button/para
        ]
        checkbox [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/checkbox/font
            make-edge-from-blocks face styles/checkbox/edge
            make-para-from-blocks face styles/checkbox/para
        ]
        radio [
            unless empty? texts [ face/text: texts/1 ]
            unless empty? pairs [ face/size: pairs/1 ]
            unless empty? colors [ face/color: colors/1 ]
            make-font-from-blocks face styles/radio/font
            make-edge-from-blocks face styles/radio/edge
            make-para-from-blocks face styles/radio/para
        ]
        image [
            if blocks/effect [ face/effect: blocks/effect ]
            make-font-from-blocks face styles/image/font
            make-edge-from-blocks face styles/image/edge
            make-para-from-blocks face styles/image/para
        ]
        combo [
        ]
    ]

    make-font-from-blocks: func [
        face    [ object! ]
        font    [ object! none! ]
        /local b
    ][
        face/font: either b: blocks/font [ make font b ][ make font [] ]
    ]
    make-edge-from-blocks: func [
        face    [ object! ]
        edge    [ object! none! ]
        /local b
    ][
        face/edge: either b: blocks/edge [ make edge b ][ make edge [] ]
    ]
    make-para-from-blocks: func [
        face    [ object! ]
        para    [ object! none! ]
        /local b
    ][
        face/para: either b: blocks/para [ make para b ][ make para [] ]
    ]
    make-text-style: func [
        face    [ object! ]
        /local b
    ][
        unless is-new-style [ face/type: text-type ]
        unless empty? texts [ face/text: texts/1 ]
        unless empty? pairs [ face/size: pairs/1 ]
        if (length? colors) >= 2 [ face/color: colors/2 ]
        make-font-from-blocks face face/font
        make-edge-from-blocks face face/edge
        make-para-from-blocks face face/para
        unless empty? colors [ face/font/color: colors/1 ]
    ]

    clear-facets: does [
        clear pairs
        clear texts
        clear colors
        clear files
    	make-blocks
        clear images
        clear chars
        clear logics
        clear decimals
        clear times
        clear functions
    ]

    is-allowed-type: func [ val ][
        any [
            (type? val) = pair!
            (type? val) = integer!
            (type? val) = string!
            (type? val) = tuple!
            (type? val) = block!
            (type? val) = file!
            (type? val) = url!
            (type? val) = image!
            (type? val) = char!
            (type? val) = logic!
            (type? val) = decimal!
            (type? val) = time!
        ]
    ]

    collect-facets: func [
        sf  [ block! ]
        ef  [ block! ]
        /local values val t pos is-keyword
    ][
        while [ sf <> ef ][
            val: first sf
            unless is-keyword: find keywords val [
                unless is-allowed-type val [
                    either error? try [ reduce t: copy/part sf 1 ][
                        make error! rejoin ["ERROR !!! Token not allowed: " t ]
                        halt
                    ][ val: first reduce t ]
                ]
            ]
            switch/default type?/word val [
                pair!       [append pairs val]
                integer!    [append pairs val]
                string!     [append texts val]
                tuple!      [append colors val]
                block!      [append/only functions val]
                file!       [append files val]
                url!        [append files val]
                image!      [append images val]
                char!       [append chars val]
                logic!      [append logics val]
                decimal!    [append decimals val]
                time!       [append times val]
                word!       [
                    unless is-keyword [
                        either blocks/:val [ blocks/:val: first next sf ][
                            ; TODO: handle other cases of words
                            ; ...
                        ]
                    ]
                ]
			][
                print ["ERROR !!! Unknown parameter" val]
                halt
            ]
            sf: next sf
        ]
    ]

    next-style: func [ b [ block! ] /local pos ][
        if empty? b [ return tail b ]
        either b/1 = 'style [ b ][       ;'
            pos: b
            while [ not tail? pos ][
                if any [
                    find styles first pos
                    pos/1 = 'style  ;'
                ][ break ]
                pos: next pos
            ]
            pos
        ]
    ]

    style-object: func [ style [ word! ] /local pos ][
        either pos: find styles style [ first next pos ][ pos ]
    ]

    create-face: func [
        "Clone 'so' and fill in fields from facets"
        so  [ object! ]
    ][
        ;face: copy/deep/types so object!
        face: make so []
        ; fill in fields based on style type
        switch/default so/type
            fill-in
            [
                ; TODO: take into account custom widget creation
                ; ...
                print ["ERROR !!! Unknown style" face/type "!"]
                halt
            ]
        face
    ]

    parse-layout: func [
        layout-rule    [ block! ]
        /local result rule val style-o ss se face pos oss
    ][
        result: copy []
        style-o: none
        clear-facets
        rule: layout-rule

        ss: rule
        se: next-style next rule
        forever [
            oss: ss
            val: first ss
            either val = 'style [       ;'
                is-new-style: true
                ss: next ss
                either not tail? ss [
                    unless pos: find styles first ss [
                        append styles first ss
                    ]
                    ss: next ss
                    se: next-style next ss
                    style-o: style-object first ss
                    collect-facets next ss se
                    ; create face object from facets
                    face: create-face style-o
                    ; append face object to styles
                    either pos [ pos/2: face ][ append styles face ]
                    is-new-style: false
                ][
                    make error! compose [ caldev-errors err-style-def (oss) ]
                ]
            ][
                collect-facets next ss se
                style-o: style-object first ss
                ; create face object from facets
                face: create-face style-o
                ; append face object to result
                append result face
            ]
            ; prepare facets for next style
            clear-facets

            ; get next style
            ss: se if ss = tail rule [ break ]
            se: next-style next ss
        ]
        result
    ]

    ;res: parse-layout [ style mytext text red green mytext "MyText" 120x40 style mytext text white green mytext "AnotherText" ]
    res: parse-layout [ style ]
    probe res
    ;st: now/time/precise loop 10000 [ parse-layout [ button "Hello World" ] ] print now/time/precise - st
]