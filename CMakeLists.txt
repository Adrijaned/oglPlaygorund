cmake_minimum_required(VERSION 3.12)
project(oglPlayground)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(GLEW REQUIRED)
add_executable(oglPlayground main.cpp fileUtils.cpp fileUtils.hpp ShaderProgram.cpp ShaderProgram.hpp exceptions/InvalidStateException.hpp GoxelObjObject.cpp GoxelObjObject.hpp exceptions/FileNotFoundException.hpp exceptions/UnknownIdentifierException.hpp exceptions/ParseException.hpp RenderableBufferObject.hpp Camera.cpp Camera.hpp MyCustomChunk.cpp MyCustomChunk.hpp exceptions/InvalidDataException.hpp HandWrittenObject.cpp HandWrittenObject.hpp)
target_compile_options(oglPlayground PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(oglPlayground sfml-graphics sfml-audio ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
