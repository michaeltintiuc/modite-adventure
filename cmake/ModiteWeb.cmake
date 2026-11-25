set(engine "${PROJECT_SOURCE_DIR}/creative-engine/src")
if (NOT EXISTS "${engine}/BResourceManager.cpp")
    message(FATAL_ERROR "Creative Engine is missing. Clone its develop branch into creative-engine.")
endif ()

set(generated "${PROJECT_BINARY_DIR}/web-generated")
include("${CMAKE_CURRENT_LIST_DIR}/ModiteEmbeddedResources.cmake")

file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS
        "${engine}/*.cpp" "${engine}/*.c" "${engine}/*.h")
set(desktop_controls "${engine}/Controls/DesktopControls/DesktopControls.cpp")
list(REMOVE_ITEM engine_sources "${engine}/BResourceManager.cpp" "${desktop_controls}")

include("${CMAKE_CURRENT_LIST_DIR}/ModiteGamepadControls.cmake")
set(web_controls "${generated}/DesktopControls.cpp")
configure_gamepad_controls("${desktop_controls}" "${web_controls}" WebGamepad.h ReadWebGamepad)
list(APPEND engine_sources "${web_controls}")
# The engine calls time() without including its header.
set_source_files_properties("${engine}/BApplication.cpp" PROPERTIES COMPILE_OPTIONS "-include;time.h")
target_sources(Modite PRIVATE ${engine_sources} "${resource_manager}" "${resource_header}"
        "${CMAKE_CURRENT_LIST_DIR}/WebGamepad.cpp" "${CMAKE_CURRENT_LIST_DIR}/WebGamepad.h")
set_target_properties(Modite PROPERTIES
        OUTPUT_NAME index
        SUFFIX ".html"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/html"
)

target_compile_definitions(Modite PRIVATE
        __MODUS_TARGET_DESKTOP_CONTROLS__=true
        LIBXMP_CORE_PLAYER
        MODITE_GAMEPAD_RUMBLE
)
target_compile_options(Modite PRIVATE --use-port=sdl2)
set(web_shell "${CMAKE_CURRENT_LIST_DIR}/web-shell.html")
set(web_saves "${CMAKE_CURRENT_LIST_DIR}/web-saves.js")
set_property(TARGET Modite APPEND PROPERTY LINK_DEPENDS "${web_shell}" "${web_saves}")
# Level loading puts a 255-by-255 integer matrix on the stack.
target_link_options(Modite PRIVATE --use-port=sdl2 -sALLOW_MEMORY_GROWTH
        -sSTACK_SIZE=4194304 --shell-file "${web_shell}"
        -lidbfs.js --pre-js "${web_saves}")

target_include_directories(Modite BEFORE PRIVATE "${generated}")
target_include_directories(Modite PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
        "${engine}" "${engine}/BStore" "${engine}/BStore/DesktopStore"
        "${engine}/Audio" "${engine}/Audio/mixer" "${engine}/Audio/SDL2Audio"
        "${engine}/Audio/LDKAudio" "${engine}/Display" "${engine}/Display/DesktopDisplay"
        "${engine}/Display/LDKDisplay" "${engine}/Controls" "${engine}/Controls/DesktopControls"
        "${engine}/Controls/LDKControls" "${engine}/Widgets" "${engine}/libxmp"
        "${engine}/libxmp/loaders"
)

add_custom_target(run-web
        COMMAND Python3::Interpreter "${PROJECT_SOURCE_DIR}/scripts/preview-web.py"
                "$<TARGET_FILE_DIR:Modite>"
        DEPENDS Modite
        USES_TERMINAL
        VERBATIM
)
