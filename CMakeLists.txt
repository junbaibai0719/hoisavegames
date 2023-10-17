cmake_minimum_required(VERSION 3.16)

project(hoisavegames VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_DECLARATIVE_DEBUG true)
set(QT_QML_DEBUG true)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup()

qt_add_executable(apphoisavegames
    main.cpp
)

qt_add_qml_module(apphoisavegames
    URI hoisavegames
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
        hoisavenode.h hoisavenode.cpp
        hoimodel.h hoimodel.cpp
        message_handler.cpp message_handler.h
        savegamelistener.h savegamelistener.cpp
        hoifileparser.h hoifileparser.cpp
        datetimeformat.h
        line.h line.cpp
)

qt_add_resources(apphoisavegames "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)
file(COPY 7z DESTINATION ${CMAKE_BINARY_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apphoisavegames PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apphoisavegames
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apphoisavegames
    PRIVATE Qt6::Quick  Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS apphoisavegames
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
