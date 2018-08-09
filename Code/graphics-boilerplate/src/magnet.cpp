#include "main.h"
#include "magnet.h"

Magnet::Magnet(float x, float y, color_t color)
{
    side=1;
    this->position = glm::vec3(x, y, 0);
    speed = 0;
     static GLfloat vertex_buffer_data[] = {
     0.2, 0.4, 0,
    -0.2, 0.4, 0,
     -0.2,-0.4,0,

      0.2, 0.4, 0,
     -0.2,-0.4,0,
      0.2,-0.4,0

    };



    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
     Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::tick() {

}


bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}


