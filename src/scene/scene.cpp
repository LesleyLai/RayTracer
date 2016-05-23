#include <chrono>
#include <iostream>

#include "../ray.hpp"
#include "scene.hpp"

Scene::Scene(size_t width, size_t height) :
    width_{width},
    height_{height},
    rayTracer_{*this},
    film_{width, height} {
}

void Scene::render(std::string filename) {
    auto startTime = std::chrono::system_clock::now();

    Sampler sampler(width_, height_);
    auto samples = sampler.generateSampleSet();

    Ray ray;
    ColorRGB color;

    for (auto sample : samples) {
        auto now = std::chrono::system_clock::now();
        auto deltatime = now - startTime;
        if (deltatime > std::chrono::seconds(30)) {
            startTime = now;
            std::cout << (sample.x * sample.y / width_ / height_ * 100) << "% complete" << std::endl;
        }

        if (main_camera_ == nullptr) throw std::runtime_error("Cannot find a camera in the scene");
        main_camera_->generateRay(glm::vec2(width_, height_), sample, ray);

        rayTracer_.trace(ray, color);

        film_.commit(sample.x, sample.y, color);
    }

    film_.writeImage(filename);
}


size_t Scene::SceneObjectNumber() const {
    return sceneObjects_.size();
}

void Scene::addSceneObject(std::shared_ptr<SceneObject> object) {
    if (!object) {
        return;
    }
    sceneObjects_.emplace_back(std::move(object));
}

void Scene::addLight(std::shared_ptr<Light> light) {
    if (!light) {
        return;
    }
    lights_.emplace_back(std::move(light));
}

void Scene::addCamera(std::shared_ptr<Camera> camera) {
    if (!camera) {
        return;
    }
    main_camera_ = camera;
    cameras_.push_back(camera);
}


const SceneObject &Scene::getSceneObject(std::size_t index) const {
    assert(index >= 0 && index < sceneObjects_.size());
    const std::shared_ptr<SceneObject>& internalObject = sceneObjects_[index];
    return *internalObject.get();
}

const Light &Scene::getLight(std::size_t index) const {
    assert(index >= 0 && index < lights_.size());
    const std::shared_ptr<Light>& internalLight = lights_[index];
    return *internalLight.get();
}

std::size_t Scene::lightNumber() const {
    return lights_.size();
}

void Scene::setSize(int width, int height) {
    width_ = width;
    height_ = height;
    film_.setResolution(width, height);
}



