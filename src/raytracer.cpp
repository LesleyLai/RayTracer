#include <limits>

#include "raytracer.hpp"
#include "scene/scene.hpp"

#include "math/math.hpp"

#include "rendering/shader/blinnphongshader.hpp"

constexpr ColorRGB BACKGROUND_COLOR = ColorRGB(0, 0, 0);
constexpr ColorRGB AMBIENT_COLOR = ColorRGB(.2, .2, .2);

constexpr float REFLECT_PAREMETER = 1;

constexpr float FIX_SELF_SHADOW_PARAMETER = .00001;


RayTracer::RayTracer(Scene &inputScene, int maxDepth) :
    scene_{inputScene},
    maxDepth_{maxDepth} {

}

void RayTracer::trace(Ray &inputRay, ColorRGB &color) {
    color = BACKGROUND_COLOR;
    _trace(inputRay, 0, color);
}

void RayTracer::_trace(Ray &inputRay, int depth, ColorRGB &color) {
    if (depth == maxDepth_) {
        return;
    }

    bool intersect_flag = false;

    Hit hit(glm::vec3(), std::numeric_limits<float>::infinity());
    Material material;

    for(std::size_t i = 0; i != scene_.SceneObjectNumber(); ++i) {
        if (scene_.getSceneObject(i).intersect(inputRay, hit)) {
            material = scene_.getSceneObject(i).material();
            intersect_flag = true;
        }
    }


    if (intersect_flag) {
        auto hitPosition = inputRay.pointAtT(hit.t());
        color = AMBIENT_COLOR;

        for (std::size_t i = 0; i != scene_.lightNumber(); ++i) {
            Ray lightray;
            ColorRGB lightcolor;

            scene_.getLight(i).generateLightRay(hitPosition, lightray, lightcolor);

            //Shadowing
            bool shadowed = false;

            // Prevent self shadowing
            auto modifiedLightray = lightray;

            modifiedLightray.setOrigin(lightray.origin()
                                       + hit.normal() * FIX_SELF_SHADOW_PARAMETER);

            for (std::size_t j = 0; j != scene_.SceneObjectNumber(); ++j) {
                if (scene_.getSceneObject(j).intersect(modifiedLightray)) {
                    shadowed = true;
                }
            }

            std::unique_ptr<Shader> shader {new BlinnPhongShader};
            color = shader->shading(hit,
                                    inputRay,
                                    lightray,
                                    lightcolor,
                                    material.IlluminationInfo_,
                                    shadowed);

        }

        Ray reflexRay {hitPosition + hit.normal() * FIX_SELF_SHADOW_PARAMETER,
                    hit.normal() + hit.normal() - inputRay.direction()};

        auto color_reflex = BACKGROUND_COLOR;
        _trace(reflexRay, depth + 1, color_reflex);
        color += color_reflex * REFLECT_PAREMETER;

    }
}
