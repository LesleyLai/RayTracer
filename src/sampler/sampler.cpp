#include <iostream>

#include "sampler.hpp"

Sampler::Sampler(int width, int height) :
    width_{width},
    height_{height} {

}

std::vector<Sample> Sampler::generateSampleSet() {
     std::vector<Sample> result;

     for (int x = 0; x != width_; ++x) {
       for (int y = 0; y != height_; ++y) {
         Sample sample{
           (x + 0.5f),
           (y + 0.5f)
         };
         result.push_back(sample);
       }
     }

     return result;
}
