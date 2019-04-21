#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <fstream>
#include "ShaderProgram.hpp"
#include "GoxelObject.hpp"
#include <dlfcn.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  sf::ContextSettings settings;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  settings.depthBits = 32;
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
  glewInit();
  glEnable(GL_DEPTH_TEST);

  window.setVerticalSyncEnabled(true);
  window.setActive(true);

  GoxelObject goxelObject {"something.obj", 0.03f};

  ShaderProgram shaderProgram{};
  shaderProgram.attachShader("vBasic", GL_VERTEX_SHADER).attachShader("fBasic", GL_FRAGMENT_SHADER).finish();
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
  glm::mat4 projectionMatrix = glm::perspective(glm::quarter_pi<float>(), 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 view = glm::mat4(1.0f);
  // note that we're translating the scene in the reverse direction of where we want to move
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.3f));
  shaderProgram.activate().setUniform("projection", projectionMatrix).setUniform("view", view);

  bool running = true;
  while (running) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        running = false;
      } else if (event.type == sf::Event::Resized) {
        glViewport(0, 0, event.size.width, event.size.height);
        projectionMatrix = glm::perspective(glm::quarter_pi<float>(), ((float) event.size.width) / ((float) event.size.height), 0.1f, 100.0f);
        shaderProgram.activate().setUniform("projection", projectionMatrix);
      }
    }

    glClearColor(0.1, 0.3, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
    shaderProgram.activate();
    shaderProgram.setUniform("transform", trans);
    goxelObject.drawBuffers();

    window.display();
  }

  return 0;
}