#include <vector>
namespace arrays {

    glm::vec3 spotLightVecProperties[] = {
            glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f)
    };

    float spotLightFloatProperties[] = {
        1.0f, 0.0f, 0.0f, glm::cos(glm::radians(45.0f)), glm::cos(glm::radians(45.0f))
    };

    vector <string> faces
    {
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/1.png",
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/3.png",
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/5.png",
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/6.png",
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/2.png",
        "C:/Users/Tymek/Desktop/cubemaps/skybox (1)/skybox2/4.png"

    };

    float skyboxVertices[] = {

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