#include "ground.h"
#include "main.h"

Ground::Ground(color_t color) {
        static const GLfloat vertex_buffer_data[] = {
        -4, -1.23, 0, // vertex 1
        4,  -1.23, 0, // vertex 2
        -4,  -5, 0, // vertex 3

        4,  -1.23, 0, // vertex 2
        4, -5, 0, // vertex 4
        -4, -5, 0 // vertex 3
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
