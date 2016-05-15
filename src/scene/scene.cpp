#include "scene.hpp"

Scene::Scene(size_t width, size_t height) :
    width_{width},
    height_{height},
    film_{width_, height_} {
}

void Scene::render() {
    Sampler sampler(width_, height_);
    auto samples = sampler.generateSampleSet();

    //Ray ray;
    ColorRGB color;

    for (auto sample : samples) {
        //if (main_camera_ == nullptr) throw std::runtime_error("Cannot find a camera in the scene");
        //main_camera_->generateRay(sample, ray);

        color = ColorRGB(sample.x / width_, sample.x / height_, sample.y / height_);
        //rayTracer_.trace(ray, color);

        film_.commit(sample.x, sample.y, color);
    }

    film_.writeImage();
}


