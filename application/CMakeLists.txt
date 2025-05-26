include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

SET(SRCS
    src/main.cpp
    src/application.cpp
    src/scene_model.cpp
    src/window_view.cpp
    src/event_manager.cpp
    src/keyboard_controller.cpp
    src/mouse_controller.cpp
    src/command_line.cpp
    src/object_parser.cpp
    src/exception_handling.cpp
)

add_executable(application ${SRCS})
target_compile_features(application INTERFACE cxx_std_20)
target_link_libraries(application PRIVATE SFML::Graphics Renderer Observer3)
