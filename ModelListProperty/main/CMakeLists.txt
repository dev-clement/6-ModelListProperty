find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appModelListProperty
    src/main.cpp
)

qt_add_qml_module(appModelListProperty
    URI ModelListProperty
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/InputDialog.qml
    SOURCES
        src/datasource.cpp inc/datasource.hpp
        src/person.cpp inc/person.hpp
        src/personmodel.cpp inc/personmodel.hpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appModelListProperty PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appModelListProperty
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appModelListProperty PUBLIC inc/)

target_link_libraries(appModelListProperty
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appModelListProperty
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
