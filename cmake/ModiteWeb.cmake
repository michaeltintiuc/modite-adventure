find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(engine "${PROJECT_SOURCE_DIR}/creative-engine/src")
if (NOT EXISTS "${engine}/BResourceManager.cpp")
    message(FATAL_ERROR "Creative Engine is missing. Clone its develop branch into creative-engine.")
endif ()

set(generated "${PROJECT_BINARY_DIR}/web-generated")
file(MAKE_DIRECTORY "${generated}")
set(resource_manager "${generated}/BResourceManager.cpp")
set(resource_header "${generated}/Resources.h")
add_custom_command(
        OUTPUT "${resource_manager}" "${resource_header}"
        COMMAND Python3::Interpreter "${PROJECT_SOURCE_DIR}/scripts/embed-web-resources.py"
        "${PROJECT_SOURCE_DIR}/src/Resources.zip" "${engine}/BResourceManager.cpp" "${generated}"
        DEPENDS src/Resources.zip scripts/embed-web-resources.py "${engine}/BResourceManager.cpp"
        VERBATIM
)

file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS
        "${engine}/*.cpp" "${engine}/*.c" "${engine}/*.h")
set(desktop_controls "${engine}/Controls/DesktopControls/DesktopControls.cpp")
list(REMOVE_ITEM engine_sources "${engine}/BResourceManager.cpp" "${desktop_controls}")

# Keep SDL keyboard events and sample the browser's standard gamepad every poll.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${desktop_controls}")
file(READ "${desktop_controls}" controls_source)
set(include_marker [=[#include "DesktopControls.h"]=])
set(update_marker [=[    // cKeys are journaled if journaling is on!
    dKeys |= TUint16(TUint16(keys) ^ TUint16(TUint16(cKeys) & TUint16(keys)));
    cKeys = keys;
    bKeys = keys;
  }]=])
foreach(marker IN ITEMS include_marker update_marker)
    string(FIND "${controls_source}" "${${marker}}" marker_offset)
    if(marker_offset EQUAL -1)
        message(FATAL_ERROR "Unsupported Creative Engine desktop controls source")
    endif()
endforeach()
string(REPLACE "${include_marker}" [=[#include "DesktopControls.h"
#undef CONTROLLER_SUPPORT
#include "WebGamepad.h"]=] controls_source "${controls_source}")
string(REPLACE "  SDL_Event e;" "  const TUint16 gamepadKeys = ReadWebGamepad();
  SDL_Event e;" controls_source "${controls_source}")
string(REPLACE "  while (SDL_PollEvent(&e)) {" [=[  while (SDL_PollEvent(&e)) {
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.keysym.scancode == SDL_SCANCODE_Q) {
      continue;
    }]=] controls_source "${controls_source}")
string(REPLACE "${update_marker}" [=[    bKeys = keys;
    const TUint16 combined = keys | gamepadKeys;
    dKeys |= combined & ~cKeys;
    cKeys = combined;
  }

  const TUint16 combined = bKeys | gamepadKeys;
  dKeys |= combined & ~cKeys;
  cKeys = combined;]=] controls_source "${controls_source}")
set(web_controls "${generated}/DesktopControls.cpp")
file(GENERATE OUTPUT "${web_controls}" CONTENT "${controls_source}")
list(APPEND engine_sources "${web_controls}")
# The engine calls time() without including its header.
set_source_files_properties("${engine}/BApplication.cpp" PROPERTIES COMPILE_OPTIONS "-include;time.h")
target_sources(Modite PRIVATE ${engine_sources} "${resource_manager}" "${resource_header}"
        "${CMAKE_CURRENT_LIST_DIR}/WebGamepad.h")
set_target_properties(Modite PROPERTIES
        OUTPUT_NAME index
        SUFFIX ".html"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/html"
)

target_compile_definitions(Modite PRIVATE
        __MODUS_TARGET_DESKTOP_CONTROLS__=true
        LIBXMP_CORE_PLAYER
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
