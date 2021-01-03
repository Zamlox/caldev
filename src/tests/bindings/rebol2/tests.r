REBOL [
    Title:      "Rebol2 tests"
    Purpose:    "Unit tests for Rebol2"
    file:       %tests.r
    author:     "Iosif Haidu"
    email:      [iosif.haidu@gmail.com]
    date:       3-01-2021
    version:    0.0.1
    needs:      [
        %lib.r
    ]
    History: [
        0.0.1 [3-01-2021 "Started"]
    ]
    Category:   [tests library]
    library:    [
        level:          'intermediate
        platform:       ['win 'linux]
        type:           [test]
        domain:         [tests external-library]
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

do %test-gui.r