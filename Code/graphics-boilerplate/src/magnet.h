#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet
{
public:
    Magnet() {}
        Magnet(float x, float y, color_t color);
        double speed;
        int side;
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void tick();
        bounding_box_t bounding_box();
    private:
        VAO *object;
};

#endif // MAGNET_H
