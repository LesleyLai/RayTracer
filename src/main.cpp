#include <iostream>
#include <chrono>

#include "scene/scene.hpp"
#include "scene/light/pointlight.hpp"

#include "scene/primitives/sphere.hpp"

void printTotallyTimeCost(std::chrono::duration<double> elapsedTimes);

int main(int argc, char *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    Scene scene(1024, 768);

    std::shared_ptr<Camera> mainCamera(new Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), 30));
    scene.addCamera(mainCamera);

    std::shared_ptr<Light> light(new PointLight(glm::vec3(3, 3, 3), ColorRGB(1, 0, 0)));
    scene.addLight(light);

    std::shared_ptr<Primitive> sphere(new Sphere(2, glm::vec3(0, 0, 6)));

    Material m;
    std::shared_ptr<SceneObject> obj(new SceneObject(m));
    obj->addPrimitive(sphere);

    scene.addSceneObject(obj);

    scene.render();


    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTimes = endTime - startTime;

    printTotallyTimeCost(elapsedTimes);

    return 0;
}

void printTotallyTimeCost(std::chrono::duration<double> elapsedTimes) {
    std::chrono::seconds oneSecond(1);
    std::chrono::minutes tenminutes(10);

    std::cout << "It takes " ;

    if (elapsedTimes < tenminutes) {
    if (elapsedTimes < oneSecond) {
        std::cout << elapsedTimes.count();
    } else {
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(elapsedTimes).count();
    }
    std::cout << "s to complete the rendering" << std::endl;
    } else {
        std::cout << std::chrono::duration_cast<std::chrono::minutes>(elapsedTimes).count()
                  << "min to complete the rendering" << std::endl;

    }
}
