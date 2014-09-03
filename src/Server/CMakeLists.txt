SET(TARGET Server)

FIND_PACKAGE(Qt4 REQUIRED QtCore QtNetwork)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

SET(SOURCES
    main.cpp
    ClientConnection.cpp
    Server.cpp
)

SET(HEADERS
    ClientConnection.h
    Server.h
)

ADD_EXECUTABLE(
    ${TARGET}
    ${SOURCES}
    ${HEADERS}
)

TARGET_LINK_LIBRARIES(
    ${TARGET}
    ${QT_LIBRARIES}
    Core
)
