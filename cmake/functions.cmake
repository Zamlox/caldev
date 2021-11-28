function (get_build_type bin_dir value)
    string(REPLACE "/" ";" FOLDERS ${bin_dir})
    list(LENGTH FOLDERS LEN_FOLDERS)
    math(EXPR INDEX "${LEN_FOLDERS} - 1")
    list(GET FOLDERS ${INDEX} LAST_FOLDER)
    string(TOLOWER ${LAST_FOLDER} LOWER_LAST_FOLDER)
    # Debug
    string(FIND ${LOWER_LAST_FOLDER} "debug" FOUND)
    if(NOT FOUND EQUAL -1)
        set(${value} "Debug" PARENT_SCOPE)
    else()
        # Release
        string(FIND ${LOWER_LAST_FOLDER} "release" FOUND)
        if(NOT FOUND EQUAL -1)
            set(${value} "Release" PARENT_SCOPE)
        endif()
    endif()
endfunction()

function (get_platform_type bin_dir value)
    string(REPLACE "/" ";" FOLDERS ${bin_dir})
    list(LENGTH FOLDERS LEN_FOLDERS)
    math(EXPR INDEX "${LEN_FOLDERS} - 1")
    list(GET FOLDERS ${INDEX} LAST_FOLDER)
    string(TOLOWER ${LAST_FOLDER} LOWER_LAST_FOLDER)
    # Debug
    string(FIND ${LOWER_LAST_FOLDER} "32" FOUND)
    if(NOT FOUND EQUAL -1)
        set(${value} "32" PARENT_SCOPE)
    else()
        set(${value} "64" PARENT_SCOPE)
    endif()
endfunction()