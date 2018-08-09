#include "main.h"
#ifndef POOL_H
#define POOL_H


class Pool
{
public:
    Pool() {}
    Pool(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int balloon;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // POOL_H
