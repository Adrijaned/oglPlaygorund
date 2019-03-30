#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <fstream>
#include "ShaderProgram.hpp"
#include <dlfcn.h>

int main() {
  sf::ContextSettings settings;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
  glewInit();

  window.setVerticalSyncEnabled(true);
  window.setActive(true);

  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      -0.25f, 0.5f, 0.0f,};
  float vertices2[] = {
      0.0f, 0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      0.25f, -0.5f, 0.0f,
  };
  unsigned int indices[] = {
      0, 1, 2,
      0, 2, 3
  };
  GLuint VAO[2];  // Vertex array object - stores configuration (VBO and stuff)
  glGenVertexArrays(2, VAO);
  GLuint VBO[2];  // Vertex buffer object - generic buffer, contains the vertices
  glGenBuffers(2, VBO);
  GLuint EBO;  // Element buffer object - stores the indices with order for accessing the vertices
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  ShaderProgram shaderProgram{}, yellowShaderProgram{};
  shaderProgram.attachShader("vBasic", GL_VERTEX_SHADER).attachShader("fBasic", GL_FRAGMENT_SHADER).finish();
  yellowShaderProgram.attachShader("vBasic", GL_VERTEX_SHADER).attachShader("fYellow", GL_FRAGMENT_SHADER).finish();

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
    glBindVertexArray(VAO[0]);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO[1]);
    yellowShaderProgram.activate();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    window.display();
  }

  return 0;
}