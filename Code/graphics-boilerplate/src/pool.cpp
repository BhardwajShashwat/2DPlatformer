#include "pool.h"
#include "main.h"

Pool::Pool(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);

    static GLfloat vertex_buffer_data[1080] = {0.0f};
            int n = 120;
            float angle = (2*M_PI)/n;

            for(int i=n/2; i<n; i++)
            {
                vertex_buffer_data[9*i] = 0.0f;
                vertex_buffer_data[9*i + 1] = 0.0f;
                vertex_buffer_data[9*i + 2] = 0.0f;
                vertex_buffer_data[9*i + 3] = cos(i*angle)*1;
                vertex_buffer_data[9*i + 4] = sin(i*angle)*1;
                vertex_buffer_data[9*i + 5] = 0.0f;
                vertex_buffer_data[9*i + 6] = cos((i+1)*angle)*1;
                vertex_buffer_data[9*i + 7] = sin((i+1)*angle)*1;
                vertex_buffer_data[9*i + 8] = 0.0f;

            }


    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
     Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pool::tick() {}


bounding_box_t Pool::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}



