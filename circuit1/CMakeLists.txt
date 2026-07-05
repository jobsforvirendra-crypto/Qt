cmake_minimum_required(VERSION 3.16)

project(circuit1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Svg)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appcircuit1
    main.cpp
)

qt_add_qml_module(appcircuit1
    URI circuit1
    QML_FILES
        Main.qml
    SOURCES
        core/componentData.h
        models/componentmodels.cpp
        models/componentmodels.h
    QML_FILES
        CircuitCanvas.qml
        ComponentItem.qml
        Toolbox.qml
    RESOURCES
        resources/battery.svg
        resources/capacitor.svg
        resources/resistor.svg
        resources/LED.svg
        SOURCES core/pin.h
        SOURCES core/wireData.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcircuit1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcircuit1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcircuit1
    PRIVATE Qt6::Quick
    Qt6::Svg
)

include(GNUInstallDirs)
install(TARGETS appcircuit1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
