include(FetchContent)
FetchContent_Declare(Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(Eigen)

SET(SRCS
  src/renderer.cpp
  src/camera.cpp
  src/color.cpp
  src/object.cpp
  src/screen.cpp
  src/world.cpp
)

add_library(Renderer STATIC ${SRCS})
target_include_directories(Renderer PUBLIC "src")
target_compile_features(Renderer INTERFACE cxx_std_20)
target_link_libraries(Renderer PUBLIC Eigen3::Eigen)
