# cmake_minimum_required(VERSION 3.23)
project(ggj-client VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)

# Build into same bin folder as SteamNetworkingSockets
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(LINUX)
    add_executable(ggj-client main.cpp)
    target_link_libraries(ggj-client galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d
            GameNetworkingSockets::shared)
elseif(WINDOWS)
    # Copies game content to the executable folder when CMake file is loaded.
    file(COPY ${CMAKE_SOURCE_DIR}/content/game/content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(ggj-client main.cpp ${CMAKE_SOURCE_DIR}/content/logo/icon.rc)
    target_link_libraries(ggj-client galder-game-jam-library gamedev_base raylib_cpp raylib fmt box2d
            GameNetworkingSockets::shared)
    # target_link_options(ggj-client PRIVATE -mwindows)
else()
    # Not supported :)
endif()