set_target_properties(Modite PROPERTIES
        OUTPUT_NAME index
        SUFFIX ".html"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/html"
)

set(web_shell "${CMAKE_CURRENT_LIST_DIR}/web-shell.html")
set_property(TARGET Modite APPEND PROPERTY LINK_DEPENDS "${web_shell}")
# Level loading puts a 255-by-255 integer matrix on the stack.
target_link_options(Modite PRIVATE -sALLOW_MEMORY_GROWTH
        -sSTACK_SIZE=4194304 --shell-file "${web_shell}")

add_custom_target(run-web
        COMMAND Python3::Interpreter "${PROJECT_SOURCE_DIR}/scripts/preview-web.py"
                "$<TARGET_FILE_DIR:Modite>"
        DEPENDS Modite
        USES_TERMINAL
        VERBATIM
)
