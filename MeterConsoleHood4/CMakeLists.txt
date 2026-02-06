cmake_minimum_required(VERSION 3.16)

project(MeterConsoleHood4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appMeterConsoleHood4
    main.cpp
    speedtempanddistancectrl.cpp
    speedtempanddistancectrl.h
)

qt_add_qml_module(appMeterConsoleHood4
    URI MeterConsoleHood4
    VERSION 1.0
    QML_FILES
        main.qml
        CustomGauge.qml
        SpeedMeter.qml
        TemperatureGauge.qml
)

target_compile_definitions(appMeterConsoleHood4
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appMeterConsoleHood4
    PRIVATE Qt6::Quick)
