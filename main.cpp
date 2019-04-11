#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <fstream>
#include "ShaderProgram.hpp"
#include "GoxelObject.hpp"
#include <dlfcn.h>

int main() {
  sf::ContextSettings settings;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
  glewInit();

  window.setVerticalSyncEnabled(true);
  window.setActive(true);

  GoxelObject goxelObject {"something.obj", 0.03f};

  ShaderProgram shaderProgram{};
  shaderProgram.attachShader("vBasic", GL_VERTEX_SHADER).attachShader("fBasic", GL_FRAGMENT_SHADER).finish();

  bool running = true;
  while (running) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        running = false;
      } else if (event.type == sf::Event::Resized) {
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }

    glClearColor(0.1, 0.3, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.activate();
    goxelObject.drawBuffers();

    window.display();
  }

  return 0;
}