SET(TARGET Client)

FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtNetwork)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

SET(SOURCES
    main.cpp
    MainWindow.cpp
    Connection.cpp
    NumbersGenerator.cpp
)

SET(HEADERS
    MainWindow.h
    Connection.h
    NumbersGenerator.h
)

SET(UI_FILES
    MainWindow.ui
)

QT4_WRAP_UI(UI_HEADERS ${UI_FILES})

ADD_EXECUTABLE(
    ${TARGET}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
)

TARGET_LINK_LIBRARIES(
    ${TARGET}
    ${QT_LIBRARIES}
    Core
)
