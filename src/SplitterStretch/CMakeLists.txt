cmake_minimum_required(VERSION 3.16)
project(SplitterStretch LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(TARGET SplitterStretch)

function(define_qt_executable TARGET)
    qt_add_executable(${TARGET}
        ${ARGN}
    )

    set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )
    target_link_libraries(${TARGET}  PRIVATE
        Qt6::Widgets
    )
    install(TARGETS ${TARGET}
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endfunction()

define_qt_executable(${TARGET}
    main.cpp
)