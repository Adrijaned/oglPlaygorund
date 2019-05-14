#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <fstream>
#include "ShaderProgram.hpp"
#include "GoxelObjObject.hpp"
#include "Camera.hpp"
#include <dlfcn.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
  sf::ContextSettings settings;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  settings.depthBits = 32;
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
  window.setMouseCursorVisible(false);
  glewInit();
  glEnable(GL_DEPTH_TEST);

  window.setVerticalSyncEnabled(true);
  window.setActive(true);

  GoxelObjObject goxelObject{"something.obj"};

  ShaderProgram shaderProgram{};
  shaderProgram.attachShader("vBasic", GL_VERTEX_SHADER).attachShader("fBasic", GL_FRAGMENT_SHADER).finish();
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
  glm::mat4 projectionMatrix = glm::perspective(glm::quarter_pi<float>(), 4.0f / 3.0f, 0.1f, 100.0f);
  shaderProgram.activate().setUniform("projection", projectionMatrix);
  Camera camera;

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
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          running = false;
        }
      }
    }

    {
      using namespace sf;
      if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        camera.move(Camera::FORWARD, 0.01f);
      }
      if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        camera.move(Camera::LEFT, 0.01f);
      }
      if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
        camera.move(Camera::BACKWARD, 0.01f);
      }
      if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
        camera.move(Camera::RIGHT, 0.01f);
      }
    }

    camera.changeYaw((((int) sf::Mouse::getPosition(window).x) - (int) window.getSize().x / 2) / 100.0f); // NOLINT(bugprone-integer-division)
    camera.changePitch(- ((int) sf::Mouse::getPosition(window).y - (int) window.getSize().y / 2) / 100.0f); // NOLINT(bugprone-integer-division)
    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);

    glClearColor(0.1, 0.3, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
    shaderProgram.activate();
    shaderProgram.setUniform("transform", trans).setUniform("view", camera.getView());
    goxelObject.drawBuffers();

    window.display();
  }

  return 0;
}