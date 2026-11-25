set(engine "${PROJECT_SOURCE_DIR}/creative-engine/src")
set(generated "${PROJECT_BINARY_DIR}/windows-generated")
include("${CMAKE_CURRENT_LIST_DIR}/ModiteEmbeddedResources.cmake")

function(configure_windows_engine_file source output)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${source}")
    file(READ "${source}" content)
    # Read arguments individually so C++ semicolons stay inside each replacement.
    set(index 2)
    while(index LESS ARGC)
        set(original "${ARGV${index}}")
        math(EXPR index "${index} + 1")
        set(replacement "${ARGV${index}}")
        math(EXPR index "${index} + 1")
        string(FIND "${content}" "${original}" offset)
        if(offset EQUAL -1)
            message(FATAL_ERROR "Unsupported Creative Engine source in ${source}: ${original}")
        endif()
        string(REPLACE "${original}" "${replacement}" content "${content}")
    endwhile()
    file(GENERATE OUTPUT "${output}" CONTENT "${content}")
endfunction()

set(desktop_display "${engine}/Display/DesktopDisplay/DesktopDisplay.cpp")
set(desktop_controls "${engine}/Controls/DesktopControls/DesktopControls.cpp")
configure_windows_engine_file("${desktop_display}" "${generated}/DesktopDisplay.cpp"
        "  SDL_Init(SDL_INIT_VIDEO)" "  SDL_SetMainReady();\n  SDL_Init(SDL_INIT_VIDEO)")
include("${CMAKE_CURRENT_LIST_DIR}/ModiteGamepadControls.cmake")
configure_gamepad_controls("${desktop_controls}" "${generated}/DesktopControls.cpp"
        WindowsGamepad.h ReadWindowsGamepad)
configure_windows_engine_file("${engine}/BStore/DesktopStore/DesktopStore.h" "${generated}/DesktopStore.h"
        "#include <dirent.h>" "#include <dirent.h>\n#include <direct.h>"
        [=[char *homeDir = getenv("HOME")]=]
        [=[const char *homeDir = getenv("USERPROFILE")]=]
        [=[strcpy(mTargetDir, homeDir)]=] [=[strcpy(mTargetDir, homeDir ? homeDir : ".")]=]
        "mkdir(mTargetDir, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH)"
        "_mkdir(mTargetDir)"
        [=[fopen(name, "r")]=] [=[fopen(name, "rb")]=]
        [=[fopen(name, "w")]=] [=[fopen(name, "wb")]=]
        [=[if (!fp || fwrite(aValue, aSize, 1, fp) != aSize) {]=]
        "if (!fp) return EFalse;\n    if (fwrite(aValue, 1, aSize, fp) != aSize) {")

list(REMOVE_ITEM CREATIVE_ENGINE_SOURCE_FILES "${engine}/BResourceManager.cpp"
        "${desktop_display}" "${desktop_controls}")
list(APPEND CREATIVE_ENGINE_SOURCE_FILES "${resource_manager}" "${resource_header}"
        "${generated}/DesktopDisplay.cpp" "${generated}/DesktopControls.cpp"
        "${generated}/DesktopStore.h")

target_include_directories(Modite BEFORE PRIVATE "${generated}" "${CMAKE_CURRENT_LIST_DIR}/windows")
target_compile_definitions(Modite PRIVATE SDL_MAIN_HANDLED BUILDING_STATIC MODITE_GAMEPAD_RUMBLE)
target_sources(Modite PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/windows/LibXmpCompat.c"
        "${CMAKE_CURRENT_LIST_DIR}/windows/WindowsGamepad.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/windows/WindowsGamepad.h")
target_link_libraries(Modite PRIVATE winpthread)
target_compile_options(Modite PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:-include${CMAKE_CURRENT_LIST_DIR}/windows/Compat.h>"
        "$<$<COMPILE_LANGUAGE:CXX>:-include${generated}/DesktopStore.h>")
set_source_files_properties("${engine}/BApplication.cpp" PROPERTIES COMPILE_OPTIONS "-include;time.h")
target_link_options(Modite PRIVATE -static)
add_custom_command(TARGET Modite POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>"
                "$<TARGET_FILE_DIR:Modite>"
        VERBATIM)

install(TARGETS Modite RUNTIME DESTINATION ".")
install(FILES "$<TARGET_FILE:SDL2::SDL2>" DESTINATION ".")
