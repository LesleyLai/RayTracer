#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include "../film.hpp"
#include "../sampler/sampler.hpp"

class Scene {
public:
    Scene(size_t width, size_t height);

    /**
     * @brief The main render function
     */
    void render();
private:
    size_t width_;
    size_t height_;

    Film film_;
};

#endif // SCENE_HPP
