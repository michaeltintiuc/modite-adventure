# Reuse Creative Engine's SDL keyboard handling and merge the platform gamepad state.
function(configure_gamepad_controls desktop_controls output gamepad_header read_gamepad)
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
    string(REPLACE "${include_marker}" "${include_marker}\n#undef CONTROLLER_SUPPORT\n#include \"${gamepad_header}\""
            controls_source "${controls_source}")
    string(REPLACE "  SDL_Event e;" "  const TUint16 gamepadKeys = ${read_gamepad}();\n  SDL_Event e;"
            controls_source "${controls_source}")
    if(EMSCRIPTEN)
        string(REPLACE "  while (SDL_PollEvent(&e)) {" [=[  while (SDL_PollEvent(&e)) {
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.keysym.scancode == SDL_SCANCODE_Q) {
      continue;
    }]=] controls_source "${controls_source}")
    endif()
    string(REPLACE "${update_marker}" [=[    bKeys = keys;
    const TUint16 combined = keys | gamepadKeys;
    dKeys |= combined & ~cKeys;
    cKeys = combined;
  }

  const TUint16 combined = bKeys | gamepadKeys;
  dKeys |= combined & ~cKeys;
  cKeys = combined;]=] controls_source "${controls_source}")
    file(GENERATE OUTPUT "${output}" CONTENT "${controls_source}")
endfunction()
