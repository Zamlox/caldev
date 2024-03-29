REBOL [
]

face-t!: make object! [
    type: 'face         ;'
    offset: 0x0
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

face!: make face-t! [
    edge: make edge! []
    font: make font! []
    para: make para! []
    feel: make feel! []
]

context [
	pairs:  copy []
	texts:  copy []
	colors: copy []
	files:  copy []
	blocks: [ edge [] font [] para [] feel [] ]
	images: copy []
	chars:  copy []
	logics: copy []
	decimals:   copy []
	times:  copy []
	functions:  copy []
    styles: copy compose [
        window      (make face! [type: 'window])    ;'
        title       (make face! [type: 'title])     ;'
        h1          (make face! [type: 'h1])        ;'
        h2          (make face! [type: 'h2])        ;'
        h3          (make face! [type: 'h3])        ;'
        h4          (make face! [type: 'h4])        ;'
        h5          (make face! [type: 'h5])        ;'
        banner      (make face! [type: 'banner])    ;'
        vh1         (make face! [type: 'vh1])       ;'
        vh2         (make face! [type: 'vh2])       ;'
        vh3         (make face! [type: 'vh3])       ;'
        text        (make face! [type: 'text])      ;'
        tt          (make face! [type: 'tt])        ;'
        code        (make face! [type: 'code])      ;'
        vtext       (make face! [type: 'vtext])     ;'
        txt         (make face! [type: 'txt])       ;'
        label       (make face! [type: 'label])     ;'
        lbl         (make face! [type: 'lbl])       ;'
        field       (make face! [type: 'field])     ;'
        area        (make face! [type: 'area])      ;'
        button      (make face! [type: 'button])    ;'
        checkbox    (make face! [type: 'checkbox])  ;'
        radio       (make face! [type: 'radio])     ;'
        image       (make face! [type: 'image])     ;'
        combo       (make face! [type: 'combo])     ;'
    ]
    defaults: [
        text        ""
        size        20x20
        win-size    100x100
        bk-color    200.200.200
        fr-color    0.0.0

        title [
            ; use set words to use the block directly in facet creation (see fill-in)
            font [
                style:   [ bold ]
                size:    24
                align:   center
                valign:  middle
            ]
        ]
        h1 [
            font [
                style:   [ bold ]
                size:    20
                align:   left
                valign:  top
            ]
        ]
        h2 [
            font [
                style:   [ bold ]
                size:    16
                align:   left
                valign:  top
            ]
        ]
        h3 [
            font [
                style:   [ bold ]
                size:    14
                align:   left
                valign:  top
            ]
        ]
        h4 [
            font [
                style:   [ bold ]
                size:    12
                align:   left
                valign:  top
            ]
        ]
        h5 [
            font [
                style:   [ bold italic ]
                size:    12
                align:   left
                valign:  top
            ]
        ]
        banner [
            font [
                style:  [ bold ]
                size:   24
                color:  250.215.0
                align:  center
                valign: middle
                shadow: 3x3
            ]
        ]
        vh1 [
            font [
                style:  [ bold ]
                size:   20
                color:  255.255.255
                align:  center
                valign: middle
                shadow: 3x3
            ]
        ]
        vh2 [
            font [
                style:  [ bold ]
                size:   16
                color:  255.255.255
                align:  center
                valign: middle
                shadow: 2x2
            ]
        ]
        vh3 [
            font [
                style:  [ bold italic ]
                size:   16
                color:  255.255.255
                align:  center
                valign: middle
                shadow: 2x2
            ]
        ]
        text [
            font [
                size:   12
                align:  left
                valign: top
            ]
        ]
        tt [
            font [
                name:   "courier new"
                size:   12
                align:  left
                valign: top
            ]
        ]
        code [
            font [
                name:   "courier new"
                style:  [ bold ]
                size:   12
                align:  left
                valign: top
            ]
        ]
        vtext [
            font [
                size:   12
                color:  255.255.255
                align:  left
                valign: top
                shadow: 1x1
            ]
        ]
        txt [
            font [
                size:   12
                align:  left
                valign: top
            ]
        ]
        label [
            font [
                style:  [ bold ]
                size:   12
                color:  255.255.255
                align:  left
                valign: middle
                shadow: 1x1
            ]
        ]
        lbl [
            font [
                style:  [ bold ]
                size:   12
                align:  left
                valign: middle
            ]
        ]
        field [
            size    200x24
            color   240.240.240
            edge [
                color:  110.120.130
                image:  none
                effect: 'ibevel
                size:   2x2
            ]
        ]
        area [
            size    400x150
            color   240.240.240
            edge [
                color:  110.120.130
                image:  none
                effect: 'ibevel
                size:   2x2
            ]
        ]
        button [
            size    100x24
            color   44.80.132
            effect [
                gradient 0x1 66.120.192 44.80.132
            ]
            edge [
                color:  110.120.130
                image:  none
                effect: 'bevel
                size:   2x2
            ]
            font [
                size:   12
                align:  center
                valign: middle
                shadow: 1x1
            ]
        ]
        checkbox [
            size    16x16
            color   240.240.240
            edge [
                color:  110.120.130
                image:  none
                effect: 'ibevel
                size:   2x2
            ]
        ]
        radio [
            size    13x13
            color   240.240.240
            effect  [ anti-alias ]
        ]
    ]
    text-type:  "label"
    fill-in: [
        title   [ make-text-style result defaults/title/font result/type: text-type ]
        h1      [ make-text-style result defaults/h1/font result/type: text-type ]
        h2      [ make-text-style result defaults/h2/font result/type: text-type ]
        h3      [ make-text-style result defaults/h3/font result/type: text-type ]
        h4      [ make-text-style result defaults/h4/font result/type: text-type ]
        h5      [ make-text-style result defaults/h5/font result/type: text-type ]
        banner  [ make-text-style result defaults/banner/font result/type: text-type ]
        vh1     [ make-text-style result defaults/vh1/font result/type: text-type ]
        vh2     [ make-text-style result defaults/vh2/font result/type: text-type ]
        vh3     [ make-text-style result defaults/vh3/font result/type: text-type ]
        text    [ make-text-style result defaults/text/font result/type: text-type ]
        tt      [ make-text-style result defaults/tt/font result/type: text-type ]
        code    [ make-text-style result defaults/code/font result/type: text-type ]
        vtext   [ make-text-style result defaults/vtext/font result/type: text-type ]
        txt     [ make-text-style result defaults/txt/font result/type: text-type ]
        label   [ make-text-style result defaults/label/font result/type: text-type ]
        lbl     [ make-text-style result defaults/lbl/font result/type: text-type ]
        window [
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/offset:  either empty? pairs [ defaults/size ][ pairs/1 ]
            result/size:    either (length? pairs) < 2 [ defaults/win-size ][ pairs/2 ]
            result/color:   either (length? colors) < 2 [ defaults/bk-color ][ colors/2 ]
            result/font/color:   either empty? colors [ defaults/fr-color ][ colors/1 ]
        ]
        field [
            make-text-style result defaults/txt/font
            result/edge:    make-edge defaults/field/edge
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/size:    either empty? pairs [ defaults/field/size ][ pairs/1 ]
            result/color:   either empty? colors [ defaults/field/color ][ colors/1 ]
        ]
        area [
            make-text-style result defaults/txt/font
            result/edge:    make-edge defaults/area/edge
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/size:    either empty? pairs [ defaults/area/size ][ pairs/1 ]
            result/color:   either empty? colors [ defaults/area/color ][ colors/1 ]
        ]
        button [
            result/edge:    make-edge defaults/button/edge
            result/font:    make-font defaults/button/font
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/size:    either empty? pairs [ defaults/button/size ][ pairs/1 ]
            result/color:   either empty? colors [ defaults/button/color ][ colors/1 ]
        ]
        checkbox [
            result/edge:    make-edge defaults/checkbox/edge
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/size:    either empty? pairs [ defaults/checkbox/size ][ pairs/1 ]
            result/color:   either empty? colors [ defaults/checkbox/color ][ colors/1 ]
        ]
        radio [
            result/text:    either empty? texts [ defaults/text ][ texts/1 ]
            result/size:    either empty? pairs [ defaults/radio/size ][ pairs/1 ]
            result/color:   either empty? colors [ defaults/radio/color ][ colors/1 ]
            result/effect:  defaults/radio/effect
        ]
        image [
        ]
        combo [
        ]
    ]

    make-block-facet: func [
        tpl     [ object! ]
        fields  [ block! ]
    ][ make tpl fields ]
    make-edge: func [ edge [ block! ] ][ make-block-facet edge! edge ]
    make-font: func [ font [ block! ] ][ make-block-facet font! font ]
    make-para: func [ para [ block! ] ][ make-block-facet para! para ]
    make-feel: func [ feel [ block! ] ][ make-block-facet feel! feel ]
    make-text-style: func [
        result  [ object! ]
        font    [ block! ]
    ][
        ; fill in block facets if exist
        result/font: make-font font
        result/font: make-block-facet result/font blocks/font
        result/edge: make-edge []
        result/para: make-para []
        result/feel: make-feel []
        ; fill in other facets
        result/text:    either empty? texts [ defaults/text ][ texts/1 ]
        result/size:    either empty? pairs [ defaults/size ][ pairs/1 ]
        result/color:   either (length? colors) < 2 [ defaults/bk-color ][ colors/2 ]
        unless empty? colors [ result/font/color: colors/1 ]
    ]

    clear-facets: does [
        clear pairs
        clear texts
        clear colors
        clear files
    	blocks: [ edge [] font [] para [] feel [] ]
        clear images
        clear chars
        clear logics
        clear decimals
        clear times
        clear functions
    ]

    is-allowed-type: func [ val ][
        any [
            (type?/word val) = pair!
            (type?/word val) = integer!
            (type?/word val) = string!
            (type?/word val) = tuple!
            (type?/word val) = block!
            (type?/word val) = file!
            (type?/word val) = url!
            (type?/word val) = image!
            (type?/word val) = char!
            (type?/word val) = logic!
            (type?/word val) = decimal!
            (type?/word val) = time!
        ]
    ]

    collect-facets: func [
        sf  [ block! ]
        ef  [ block! ]
        /local values val t pos
    ][
        while [ sf <> ef ][
            val: first sf
            unless is-allowed-type val [
                either error? try [ reduce t: copy/part sf 1 ][
                    make error! rejoin ["ERROR !!! Token not allowed: " t ]
                    halt
                ][ val: first reduce t ]
            ]
            select/default type?/word val [
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
                    either blocks/:val [ blocks/:val: first next sf ][
                        ; TODO: handle other cases of words
                        ; ...
                    ]
                ]
			][
                print ["ERROR !!! Unknown parameter" val]
                halt
            ]
            sf: next sf
        ]
    ]

    next-style: func [ b [ block! ] ][
        if empty? b [ return tail b ]
        either b/1 = 'style [ b ][       ;'
            either find styles first b [ b ][ tail b ]
        ]
    ]

    style-object: func [ style [ word! ] /local pos ][
        either pos: find styles style [ first next pos ][ pos ]
    ]

    create-face: func [
        "Clone 'so' and fill in fields from facets"
        so  [ object! ]
        /local result
    ][
        ;result: copy/deep/types so object!
        result: make face-t! []
        ; fill in fields based on style type
        select/default so/type
            fill-in
            [
                ; TODO: take into account custom widget creation
                ; ...
                print ["ERROR !!! Unknown style" result/type "!"]
                halt
            ]
        result
    ]

    parse-layout: func [
        layout-rule    [ block! ]
        /local result rule val style-o ss se face
    ][
        result: copy []
        style-o: none
        clear-facets
        rule: layout-rule

        ss: rule
        se: next-style next rule
        unless style-o: style-object first ss [
            print ["ERROR !!!" first ss "not a style !"]
            halt
        ]
        forever [
            val: first ss
            either val = 'style [       ;'
                append styles val
                ss: next ss
                collect-facets next ss se
                ; create face object from facets
                face: create-face style-o
                ; append face object to styles
                append styles face
            ][
                collect-facets next ss se
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
            style-o: style-object ss

            ; check if an existing style is redefined
            if all [
                ss/1 = 'style           ;'
                find styles first se
            ][
                ; style already exist, we redefine it silently
                se: next-style next se
            ]
        ]
        result
    ]
]