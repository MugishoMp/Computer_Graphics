#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <glm/gtx/string_cast.hpp>

#include <iostream>


int main() {

    // create a vertex 
    // w=1 means we have a point
    // if w=0 that means that it is a direction
    // subtracting two points from each other gives us a direction
    // point - point = vector
    // point + point = nonsense
    // direction + direction = direction
    // direction + point = point
    glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f);

    // transformation
    glm::mat4 model(1.0f); // identity matrix

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0, 2.0, 2.0f));
    // which axis do we want to rotate about: glm::vec3(0, 1, 0)
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));

    // translate, then rotate and finaly scale
    // order of operations matters, we think right to left!
    model = scale * rotate * translate;

    std::cout << glm::to_string(model[0]) << std::endl;
    std::cout << glm::to_string(model[1]) << std::endl;
    std::cout << glm::to_string(model[2]) << std::endl;
    std::cout << glm::to_string(model[3]) << std::endl;

    glm::vec4 worldspace_vertex = (model * vertex);

    std::cout << '\n' << "our vertex in world space\n";
    std::cout << glm::to_string(worldspace_vertex) << std::endl;

    return 0;
}