#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);

    /*static GLfloat vertex_buffer_data[1080] = {0.0f};
            int n = 120;
            float angle = (2*M_PI)/n;

            for(int i=0; i<n; i++)
            {
                vertex_buffer_data[9*i] = 0.0f;
                vertex_buffer_data[9*i + 1] = 0.0f;
                vertex_buffer_data[9*i + 2] = 0.0f;
                vertex_buffer_data[9*i + 3] = cos(i*angle)/4;
                vertex_buffer_data[9*i + 4] = sin(i*angle)/4;
                vertex_buffer_data[9*i + 5] = 0.0f;
                vertex_buffer_data[9*i + 6] = cos((i+1)*angle)/4;
                vertex_buffer_data[9*i + 7] = sin((i+1)*angle)/4;
                vertex_buffer_data[9*i + 8] = 0.0f;

            }*/
    static const GLfloat vertex_buffer_data[] = {
            -0.25, 0.25, 0,
            0.25,  0.25, 0,
            0.25,  0.2, 0,

          -0.25, 0.25, 0,
            -0.25, 0.2, 0,
            0.25, 0.2, 0,

        -0.25, -0.25, 0,
        0.25,  -0.25, 0,
        0.25,  -0.2, 0,

      -0.25, -0.25, 0,
        -0.25, -0.2, 0,
        0.25, -0.2, 0,

        -0.2, 0.2,0,
        -0.15,0.2,0,
        0.15,-0.2,0,

        -0.15,0.2,0,
        0.15,-0.2,0,
        0.2,-0.2,0,

        0.2, 0.2,0,
        0.15,0.2,0,
        -0.15,-0.2,0,

        0.15,0.2,0,
        -0.15,-0.2,0,
        -0.2,-0.2,0.
};

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
     Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::tick() {}


bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}


