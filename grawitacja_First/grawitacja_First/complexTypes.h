namespace complexTypes {

    struct modelProperties {
        float mass = 0.0f;
        float radius = 0.0f;
        float peryhelium = 0.0f;
        float aphelium = 0.0f;
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 vMax = glm::vec3(0.0f);
    };

    modelProperties sun = {
        100.0
    };
    struct lastPosition
    {
        glm::vec3 cameraPosition = glm::vec3(1.0f);
        glm::vec3 cameraFront = glm::vec3(1.0f);
    };

}