#include <limits>

#include "raytracer.hpp"
#include "scene/scene.hpp"

#include "math/math.hpp"

#include "rendering/shader/blinnphongshader.hpp"

constexpr ColorRGB BACKGROUND_COLOR = ColorRGB(0, 0, 0);
constexpr ColorRGB AMBIENT_COLOR = ColorRGB(.2, .2, .2);

constexpr float REFLECT_PAREMETER = .3;

constexpr float FIX_SELF_SHADOW_PARAMETER = .00001;


RayTracer::RayTracer(Scene &inputScene) :
    scene_{inputScene} {

}

void RayTracer::trace(Ray &inputRay, ColorRGB &color) {
    color = BACKGROUND_COLOR;
    _trace(inputRay, 0, color);
}

void RayTracer::_trace(Ray &inputRay, int depth, ColorRGB &color) {
    if (depth == 5) {
        return;
    }

    auto t_cache = std::numeric_limits<float>::infinity();
    bool intersect_flag = false;

    std::unique_ptr<LocalGeometry> local;
    Material material;

    for(std::size_t i = 0; i != scene_.SceneObjectNumber(); ++i) {
        if (scene_.getSceneObject(i).intersect(inputRay, local, t_cache)) {
            material = scene_.getSceneObject(i).material();
            intersect_flag = true;
        }
    }

    if (intersect_flag) {
        LocalGeometry& localref = *local;
        color = AMBIENT_COLOR;

        for (std::size_t i = 0; i != scene_.lightNumber(); ++i) {
            Ray lightray;
            ColorRGB lightcolor;
            scene_.getLight(i).generateLightRay(localref, lightray, lightcolor);

    //      Shadowing
            bool shadowed = false;

            // Prevent self shadowing
            auto fixedLightray = lightray;

            fixedLightray.setOrigin(lightray.origin() + localref.normal() * FIX_SELF_SHADOW_PARAMETER);
            for (std::size_t j = 0; j != scene_.SceneObjectNumber(); ++j) {
                if (scene_.getSceneObject(j).intersect(fixedLightray)) {
                    shadowed = true;
                }
            }

            if (!shadowed) {
                std::unique_ptr<Shader> shader {new BlinnPhongShader};
                color += shader->shading(localref, inputRay, lightray, lightcolor, material.IlluminationInfo_);
            }

        }

        Ray reflexRay {localref.position() + localref.normal() * FIX_SELF_SHADOW_PARAMETER,
                    localref.normal() + localref.normal() - inputRay.direction()};

        auto color_reflex = BACKGROUND_COLOR;
        _trace(reflexRay, depth + 1, color_reflex);
        color += color_reflex * REFLECT_PAREMETER;
    }
}
