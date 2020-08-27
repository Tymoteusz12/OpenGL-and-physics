#include <vector>
namespace arrays {

    glm::vec3 spotLightVecProperties[] = {
            glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f)
    };

    const float spotLightFloatProperties[] = {
        1.0f, 0.0f, 0.0f, glm::cos(glm::radians(45.0f)), glm::cos(glm::radians(45.0f))
    };

    const vector <const char*> faces
    {
        "textures/cubemaps/skybox/skybox2/1.png",
        "textures/cubemaps/skybox/skybox2/3.png",
        "textures/cubemaps/skybox/skybox2/5.png",
        "textures/cubemaps/skybox/skybox2/6.png",
        "textures/cubemaps/skybox/skybox2/2.png",
        "textures/cubemaps/skybox/skybox2/4.png"
    };

    const float skyboxVertices[] = {

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

       -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
    };

}