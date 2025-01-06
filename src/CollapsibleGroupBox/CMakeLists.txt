find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets Gui)

qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)

set(EXE_NAME CollapsibleGroupBox)
qt_add_executable(${EXE_NAME}
    main.cpp
    CollapsibleGroupBox.hpp
)
target_link_libraries(${EXE_NAME}
    PRIVATE
    Qt::Widgets
    Qt::Gui
)

set_target_properties(${EXE_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

if (WIN32)
    # On Windows, call windeployqt create a deployable folder
    # https://doc.qt.io/qt-6/windows-deployment.html
    set_target_properties(${EXE_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )

    # Find windeployqt.exe
    get_target_property(QT_BIN_DIR Qt::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_BIN_DIR}" DIRECTORY)
    find_program(WINDEPLOYQT NAMES windeployqt.exe HINTS "${QT_BIN_DIR}")

    # Add post build command to call windeployqt
    add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND ${WINDEPLOYQT}
        --verbose 1
        "$<IF:$<CONFIG:Debug>,--debug,--release>"
        "$<TARGET_FILE:${EXE_NAME}>"
    )

elseif (APPLE)
    # Post-build steps for macOS
    # https://doc.qt.io/qt-6/macos-deployment.html
    set_target_properties(${EXE_NAME} PROPERTIES
        MACOSX_BUNDLE ON
        MACOSX_BUNDLE_INFO_PLIST ../cmake/MacOSXBundleInfo.plist.in
    )

    # Find macdeployqt
    get_target_property(QT_BIN_DIR Qt::qmake IMPORTED_LOCATION)
    find_program(MACDEPLOYQT NAMES macdeployqt HINTS "${QT_BIN_DIR}")

    # Use macdeployqt to bundle Qt libraries
    add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND ${MACDEPLOYQT}
        "$<TARGET_BUNDLE_DIR:${EXE_NAME}>"
        -verbose=1
        -always-overwrite
        -codesign=-
        "$<IF:$<CONFIG:Release>,-dmg,-use-debug-libs>"
        COMMENT "Bundling Qt libraries"
    )

endif()
