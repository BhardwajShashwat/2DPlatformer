#include "main.h"
#ifndef SPIKE_H
#define SPIKE_H


class Spike
{
public:
    Spike() {}
    Spike(float x, float y, color_t color);
    double speed;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SPIKE_H
