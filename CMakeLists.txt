cmake_minimum_required(VERSION 3.12)
project(Modite)

option(DEBUG_MODE "Enable Debug Mode" OFF)

set(MODITE_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/resources
    ${PROJECT_SOURCE_DIR}/src/LoadGameState
    ${PROJECT_SOURCE_DIR}/src/GameState
    ${PROJECT_SOURCE_DIR}/src/GameState/environment
    ${PROJECT_SOURCE_DIR}/src/GameState/player
    ${PROJECT_SOURCE_DIR}/src/GameState/inventory
    ${PROJECT_SOURCE_DIR}/src/GameState/enemies
    ${PROJECT_SOURCE_DIR}/src/GameState/enemies/final-boss
    ${PROJECT_SOURCE_DIR}/src/GameState/enemies/grunts
    ${PROJECT_SOURCE_DIR}/src/GameState/enemies/mid-bosses
    ${PROJECT_SOURCE_DIR}/src/GameState/enemies/wizard
    ${PROJECT_SOURCE_DIR}/src/GameState/status
    ${PROJECT_SOURCE_DIR}/src/GameMenuState
    ${PROJECT_SOURCE_DIR}/src/DebugMenuState
    ${PROJECT_SOURCE_DIR}/src/GameOverState
    ${PROJECT_SOURCE_DIR}/src/VictoryState
    ${PROJECT_SOURCE_DIR}/src/MainMenuState
    ${PROJECT_SOURCE_DIR}/src/MainOptionsState
    ${PROJECT_SOURCE_DIR}/src/SplashState
    ${PROJECT_SOURCE_DIR}/src/CreditsState
    ${PROJECT_SOURCE_DIR}/src/ResetState
    ${PROJECT_BINARY_DIR}/usr/local/include
)


file(GLOB_RECURSE MODITE_SRC CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h"
)
add_executable(Modite ${MODITE_SRC})
set_target_properties(Modite PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)
target_include_directories(Modite PRIVATE ${MODITE_INCLUDE_DIRS})
target_compile_definitions(Modite PRIVATE
    CE_SDL2_WINDOW_TITLE="Modite Adventure :: by Modus Create"
    __MODUS_TARGET_SDL2_AUDIO__=true
    __MODUS_TARGET_DESKTOP_DISPLAY__=true
)
if(DEBUG_MODE)
    target_compile_definitions(Modite PRIVATE DEBUG_MODE=true)
endif()

if(EMSCRIPTEN)
    include(cmake/ModiteWeb.cmake)
else()
    option(TARGET_HANDHELDS "Target hand-held devices" OFF)
    option(TARGET_GAMESHELL "Target GameShell" OFF)

    # The singular spelling was accepted by the original GameShell configuration.
    if(TARGET_HANDHELDS OR TARGET_HANDHELD)
        target_compile_definitions(Modite PRIVATE __MODUS_TARGET_HANDHELDS__=true)
        if(TARGET_GAMESHELL)
            target_compile_definitions(Modite PRIVATE __MODUS_TARGET_GAMESHELL__=true)
        endif()
    endif()

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-implicit-exception-spec-mismatch")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-implicit-exception-spec-mismatch")
    include(ProcessorCount)
    if(WIN32)
        if(NOT MINGW)
            message(FATAL_ERROR "Use LLVM-MinGW or another MinGW toolchain for the Windows desktop build.")
        endif()
        # Use the SDK's imported SDL targets, including its runtime DLL location.
        set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
        find_package(SDL2 CONFIG REQUIRED)
        set(SDL2_LIBRARY SDL2::SDL2)
    endif()
    include("${PROJECT_SOURCE_DIR}/creative-engine/CreativeEngine.cmake")

    if((TARGET_HANDHELDS OR TARGET_HANDHELD) AND TARGET_GAMESHELL)
        # Creative Engine enables desktop controls in its directory definitions.
        get_property(engine_definitions DIRECTORY PROPERTY COMPILE_DEFINITIONS)
        list(FILTER engine_definitions EXCLUDE REGEX "^__MODUS_TARGET_DESKTOP_CONTROLS__(=|$)")
        set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS "${engine_definitions}")
    else()
        target_compile_definitions(Modite PRIVATE __MODUS_TARGET_DESKTOP_CONTROLS__=true)
    endif()

    if(WIN32)
        include(cmake/ModiteWindows.cmake)
    elseif(EXISTS "${PROJECT_SOURCE_DIR}/src/resources")
        set(RESOURCES_BIN_FILE "Resources.bin")
        compile_rcomp_and_resources()
    else()
        set(RESOURCES_BIN_FILE "${PROJECT_SOURCE_DIR}/src/Resources.bin")
    endif()

    target_sources(Modite PRIVATE "${RESOURCES_BIN_FILE}" ${CREATIVE_ENGINE_SOURCE_FILES})
    target_include_directories(Modite PRIVATE ${CREATIVE_ENGINE_INCLUDE_DIRS})
    target_link_libraries(Modite PRIVATE ${CREATIVE_ENGINE_LINK_LIBRARIES})

    ProcessorCount(N)
    if(NOT N EQUAL 0)
        set(${PROJECT_NAME}_FLAGS -j${N})
        set(${PROJECT_NAME}_BUILD_FLAGS -j${N})
        set(${PROJECT_NAME}_args ${${PROJECT_NAME}_args} PARALLEL_LEVEL ${N})
    endif()
    build_command($(MAKE) --silent)

    if(APPLE)
        set_target_properties(Modite PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME YES
            CODE_SIGN_INJECT_BASE_ENTITLEMENTS NO
        )
        install(TARGETS Modite DESTINATION ".")
    endif()
endif()
