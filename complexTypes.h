namespace complexTypes {

    struct modelProperties {
        float mass;
        float radius;
        float peryhelium;
        float aphelium;
        glm::vec3 position;
        glm::vec3 vMax;
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