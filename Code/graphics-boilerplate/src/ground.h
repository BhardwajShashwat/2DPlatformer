#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(color_t color);
    void draw(glm::mat4 VP);

private:
    VAO *object;
};

#endif // GROUND_H