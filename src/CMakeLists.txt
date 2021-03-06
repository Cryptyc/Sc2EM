# Source files
file(GLOB SOURCES_EASYBMP "EasyBMP/*.cpp" "EasyBMP/*.h")
file(GLOB SOURCES_SC2BINDINGS "Sc2Bindings/*.cpp" "Sc2Bindings/*.h")
file(GLOB SOURCES_SC2EM "Sc2EM/*.cpp" "Sc2EM/*.h")
file(GLOB SOURCES_EXAMPLEBOT "ExampleBot/*.cpp" "ExampleBot/*.h")

# Include directories
include_directories(SYSTEM
    ${PROJECT_SOURCE_DIR}/src/EasyBMP
    ${PROJECT_SOURCE_DIR}/src/Sc2EM
    ${PROJECT_SOURCE_DIR}/src/Sc2Bindings
    ${PROJECT_SOURCE_DIR}/s2client-api/include
    ${PROJECT_SOURCE_DIR}/s2client-api/contrib/protobuf/src
    ${PROJECT_BINARY_DIR}/s2client-api/generated
)

if (WIN32)
    include_directories(SYSTEM
        ${PROJECT_SOURCE_DIR}/s2client-api/src/sc2utils/
    )
endif ()

# Link directories
link_directories(${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/s2client-api/bin)


# Create the executable.
add_executable(ExampleBot ${SOURCES_EXAMPLEBOT})
add_library(Sc2EM ${SOURCES_SC2EM})
add_library(EasyBMP ${SOURCES_EASYBMP})
add_library(Sc2Bindings ${SOURCES_SC2BINDINGS})

target_link_libraries(ExampleBot
    EasyBMP
)
target_link_libraries(ExampleBot
    Sc2Bindings
)
target_link_libraries(ExampleBot
    Sc2EM
)

target_link_libraries(ExampleBot
    sc2api sc2lib sc2utils sc2protocol civetweb libprotobuf
)


# Set working directory as the project root
set_target_properties(ExampleBot PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")