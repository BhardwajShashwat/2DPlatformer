#include "ball.h"
#include "main.h"
#include "math.h"

Ball::Ball(float x, float y, color_t color,int balloon) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->balloon  = balloon;
    speed = 0.01;
    speedy=0;
    acceleration=0;
    /*static const GLfloat vertex_buffer_data[] = {
        -0.2, -0.2, 0, // vertex 1
        0.2,  -0.2, 0, // vertex 2
        0.2,  0.2, 0, // vertex 3

        0.2,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0 // vertex 1
    };*/

    static GLfloat vertex_buffer_data[1080] = {0.0f};
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

            }


    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += speed;
    speed=speed+acceleration;


    if(this->balloon==0)
    {
        this->position.y += speedy;
        speedy-=0.01;

        if(this->position.x<-0.75 || this->position.x>0.75)
        {
            if (this->position.y<-1)
            {
                this->position.y= -1;
                speedy=0;
            }
        }
        else
        {

            if (abs(this->position.y+1)>1-this->position.x*this->position.x && this->position.y<-1 )
            {
                this->position.y= sqrt(1-this->position.x*this->position.x)*-1-1;
                speedy=0;
            }

            if(this->position.y<-1 && speedy<0)
            {
                speedy=0.8*speedy;
            }

            if(abs(this->position.x)<0.05 && this->position.y<-2 )
            {
                this->position.y=-2;
                speedy=0;
            }

        }
        if(this->position.x<-4)
        {
            this->position.x=-4;
            speed=0;
            acceleration=0;
        }
        if(this->position.x>4)
        {
            this->position.x=4;
            speed=0;
            acceleration=0;
        }
    }

}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
