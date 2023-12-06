#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <glm/gtx/string_cast.hpp>

#include <iostream>


// 2d.3d points
// vecotrs
// - magnitude
// - normalizing
// - dot (how similar are two vectors / the angle)
// - cross product (new vector that is perpundicuilar to the other vectors)

int main() {
    glm::vec3 A(1.0f, 0.0f, 0.0f);
    glm::vec3 B(0.0f, 1.0f, 0.0f);

    glm::vec3 C = glm::cross(A,B);
    std::cout << "cross product: " << glm::to_string(C) << std::endl;

    // std::cout << glm::length(A) << std::endl;
    // std::cout << glm::length(B) << std::endl;

    // std::cout << "A length: " << glm::length(A) << std::endl;
    // std::cout << "A normalized: " << glm::to_string(glm::normalize(A)) << std::endl;
    // std::cout << "A-hat: " << glm::length(glm::normalize(A)) << std::endl;

    // //Dot product tells us how similar 2 vectors are
    // float dotproduct = glm::dot(glm::normalize(A),glm::normalize(B));
    // std::cout << "dotproduct: " << dotproduct << std::endl;
    // // the angle in degrees
    // std::cout << std::acos(dotproduct) * 180.0/M_PI << std::endl;

    return 0;
}