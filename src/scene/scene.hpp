#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include "../film.hpp"
#include "../sampler/sampler.hpp"
#include "../camera.hpp"

#include "sceneobject.hpp"
#include "light.hpp"

class Scene {
public:
    Scene(size_t width, size_t height);

    /**
     * @brief The main render function
     */
    void render(std::string filename, int maxDepth);


    /*! \brief Returns the total number of primitives in the scene.
     *  \returns Total number of primitives in the scene.
     */
    size_t SceneObjectNumber() const;



    /*! \brief Adds a new SceneObject to the scene.
     *  \param object The SceneObject to add.
     */
    void addSceneObject(std::shared_ptr<SceneObject> object);

    /*! \brief Adds a new Light to the scene.
     *  \param light The Light to add.
     */
    void addLight(std::shared_ptr<Light> light);

    /*! \brief Adds a new Camera to the scene and set this camera to main camera.
     *  \param camera The Camera to add.
     */
    void addCamera(std::shared_ptr<Camera> camera);


    /*! \brief Retrive the specified scene object.
     *  \param index The index to use to access the Scene::sceneObjects_ vector.
     *  \returns A reference to the objects in the scene objects vector at the specified index.
     */
    const SceneObject& getSceneObject(std::size_t index) const;

    /*! \brief Retrive the specified light.
     *  \param index The index to use to access the Scene::lights_ vector.
     *  \returns A reference to the light in the light vector at the specified index.
     */
    const Light& getLight(std::size_t index) const;

    /// \brief Return number of lights
    std::size_t lightNumber() const;

    void setSize(int width, int height);

private:
    size_t width_;
    size_t height_;

    Film film_;

    std::vector<std::shared_ptr<Camera>> cameras_;
    std::shared_ptr<Camera> main_camera_;


    std::vector<std::shared_ptr<SceneObject>> sceneObjects_;
    std::vector<std::shared_ptr<Light>> lights_;
};

#endif // SCENE_HPP
