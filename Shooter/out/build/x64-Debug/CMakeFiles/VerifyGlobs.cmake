# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.29
cmake_policy(SET CMP0009 NEW)

# PROJECT_SOURCES at CMakeLists.txt:40 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/dev/Netpix/Shooter/src/*.cpp")
set(OLD_GLOB
  "C:/dev/Netpix/Shooter/src/Animation.cpp"
  "C:/dev/Netpix/Shooter/src/Camera.cpp"
  "C:/dev/Netpix/Shooter/src/GameObjects.cpp"
  "C:/dev/Netpix/Shooter/src/NewScene.cpp"
  "C:/dev/Netpix/Shooter/src/Player.cpp"
  "C:/dev/Netpix/Shooter/src/Scene.cpp"
  "C:/dev/Netpix/Shooter/src/ScreenManager.cpp"
  "C:/dev/Netpix/Shooter/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/dev/Netpix/Shooter/out/build/x64-Debug/CMakeFiles/cmake.verify_globs")
endif()