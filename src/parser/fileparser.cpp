#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <stack>

#include "glm/gtc/matrix_transform.hpp"

#include "fileparser.hpp"

#include "../scene/scene.hpp"
#include "../scene/light/pointlight.hpp"

#include "../scene/primitives/sphere.hpp"
#include "../scene/primitives/triangle.hpp"

#include "../rendering/shader/blinnphongshader.hpp"
#include "../rendering/material.hpp"

using glm::vec3;
using glm::mat4;

namespace FileParserDetails {
void rightmultiply(const mat4 & M, std::stack<mat4> &matrixStack) {
    mat4 &T = matrixStack.top();
    T = T * M;
}
}


// Function to read the input data values
// Use is optional, but should be very helpful in parsing.
template <typename T, std::size_t N>
bool FileParser::readvals(std::stringstream &s, std::array<T, N> &values) {
  T tmp;
  for (int i = 0; i != N; ++i) {
    s >> tmp;
    values[i] = tmp;
    if (s.fail()) {
      std::cout << "Failed reading value " << i << " will skip\n";
      return false;
    }
  }
  return true;
}

void FileParser::addCamera(Scene& scene, const std::array<float, 10>& input_values) {
    vec3 lookfrom(input_values[0], input_values[1] , input_values[2]);

    vec3 lookat(input_values[3], input_values[4], input_values[5]);

    vec3 updir(input_values[6], input_values[7], input_values[8]);

    auto fov = input_values[9];

    std::shared_ptr<Camera> cameraPtr(
                new Camera(lookfrom,
                           lookat - lookfrom,
                           updir,
                           fov));

    scene.addCamera(cameraPtr);
}


void FileParser::readfile(const std::string &filename) {
    std::ifstream input;
    input.open(filename);
    if (input.is_open()) {
        parse(input);
    } else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        std::exit(-1);
    }
}

void FileParser::parse(std::ifstream &input) {
    std::string line, cmd;

    Scene scene(640, 480);

    std::string filename = "test.png";

    std::stack<mat4> matrixStack;
    matrixStack.push(mat4(1.0));  // identity

    std::vector<vec3> vertices;
    Material tmpMaterial;

    for (std::size_t linenum = 1; std::getline(input, line); ++linenum) {
        bool valid_flag = true;

        // Ruled out comment and blank lines
        if ((line.find_first_not_of(" \t\r\n") != std::string::npos) && (line[0] != '#')) {

            std::stringstream s(line);
            s >> cmd;

            if (cmd == "output") {
                std::array<std::string, 1> input_values;
                valid_flag = readvals(s, input_values);

                filename = input_values[0];

            } else if (cmd == "camera") {
                std::array<float, 10> input_values;
                valid_flag = readvals(s, input_values);

                addCamera(scene, input_values);

            } else if (cmd == "size") {
                std::array<int, 2> input_values;
                valid_flag = readvals(s, input_values);
                scene.setSize(input_values[0], input_values[1]);

            } else if (cmd == "vertex") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);
                vec3 vertex(input_values[0], input_values[1], input_values[2]);
                vertices.push_back(vertex);

            } else if (cmd == "tri") {
                std::array<int, 3> input_values;
                valid_flag = readvals(s, input_values);

                auto a = input_values[0];
                auto b = input_values[1];
                auto c = input_values[2];

                std::shared_ptr<Primitive> triangle(new Triangle(vertices[a], vertices[b], vertices[c]));
                std::shared_ptr<SceneObject> object(new SceneObject(tmpMaterial));
                object->addPrimitive(triangle);
                object->setTransform(matrixStack.top());
                scene.addSceneObject(object);

            } else if (cmd == "sphere") {
                std::array<float, 4> input_values;
                valid_flag = readvals(s, input_values);

                vec3 center(input_values[0], input_values[1], input_values[2]);
                auto r = input_values[3];

                std::shared_ptr<Primitive> sphere(new Sphere(r, center));
                std::shared_ptr<SceneObject> object(new SceneObject(tmpMaterial));
                object->addPrimitive(sphere);
                object->setTransform(matrixStack.top());
                scene.addSceneObject(object);

            } else if (cmd == "maxverts") {
                // ignore this line
                valid_flag = true;

            } else if (cmd == "emission") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);

                ColorRGB emission(input_values[0], input_values[1], input_values[2]);
                tmpMaterial.IlluminationInfo_.setEmissionComponent(emission);


            }  else if (cmd == "ambient") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);

                ColorRGB ambient(input_values[0], input_values[1], input_values[2]);
                tmpMaterial.IlluminationInfo_.setAmbientComponent(ambient);

            } else if (cmd == "diffuse") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);

                ColorRGB diffuse(input_values[0], input_values[1], input_values[2]);
                tmpMaterial.IlluminationInfo_.setDiffuseComponent(diffuse);

            } else if (cmd == "specular") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);

                ColorRGB specular(input_values[0], input_values[1], input_values[2]);
                tmpMaterial.IlluminationInfo_.setSpecularComponent(specular);

            } else if (cmd == "shininess") {
                std::array<float, 1> input_values;
                valid_flag = readvals(s, input_values);

                float shininess = input_values[0];
                tmpMaterial.IlluminationInfo_.setShininess(shininess);

            } else if (cmd == "point") {
                std::array<float, 6> input_values;
                valid_flag = readvals(s, input_values);

                vec3 position(input_values[0], input_values[1], input_values[2]);
                ColorRGB color(input_values[3], input_values[4], input_values[5]);

                std::shared_ptr<Light> point_light(new PointLight(position, color));
                scene.addLight(point_light);

            } else if (cmd == "pushTransform") {
                matrixStack.push(matrixStack.top());
            } else if (cmd == "popTransform") {
                if (matrixStack.size() <= 1) {
                    throw std::runtime_error("Stack has no elements.  Cannot Pop");
                } else {
                    matrixStack.pop();
                }
            } else if (cmd == "translate") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);
                vec3 transVec(input_values[0], input_values[1], input_values[2]);
                mat4 translate = glm::translate(mat4(), transVec);
                FileParserDetails::rightmultiply(translate, matrixStack);

            } else if (cmd == "rotate") {
                std::array<float, 4> input_values;
                valid_flag = readvals(s, input_values);
                vec3 axis(input_values[0], input_values[1], input_values[2]);
                auto angle = input_values[3];

                mat4 rotation = glm::rotate(mat4(), Math::radian(angle), axis);
                FileParserDetails::rightmultiply(rotation, matrixStack);


            } else if (cmd == "scale") {
                std::array<float, 3> input_values;
                valid_flag = readvals(s, input_values);
                vec3 scaleVec(input_values[0], input_values[1], input_values[2]);
                mat4 scale = glm::scale(mat4(), scaleVec);
                FileParserDetails::rightmultiply(scale, matrixStack);

            }  else {
                std::cerr << "Unknown command \"" << cmd << "\" at line " << linenum << std::endl;
                valid_flag = false;
            }
        }
    }

    std::cout << "Parsing Complete" << std::endl;
    std::cout << "the output file will be: " << filename << std::endl;


    try {
        scene.render(filename);
    } catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }



}
