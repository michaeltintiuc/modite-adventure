find_package(Python3 REQUIRED COMPONENTS Interpreter)

file(MAKE_DIRECTORY "${generated}")
set(resource_manager "${generated}/BResourceManager.cpp")
set(resource_header "${generated}/Resources.h")
add_custom_command(
        OUTPUT "${resource_manager}" "${resource_header}"
        COMMAND Python3::Interpreter "${PROJECT_SOURCE_DIR}/scripts/embed-resources.py"
        "${PROJECT_SOURCE_DIR}/src/Resources.zip" "${engine}/BResourceManager.cpp" "${generated}"
        DEPENDS "${PROJECT_SOURCE_DIR}/src/Resources.zip" "${PROJECT_SOURCE_DIR}/scripts/embed-resources.py" "${engine}/BResourceManager.cpp"
        VERBATIM
)
