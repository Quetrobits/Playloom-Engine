#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 transform = glm::mat4(1.0f);
transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));