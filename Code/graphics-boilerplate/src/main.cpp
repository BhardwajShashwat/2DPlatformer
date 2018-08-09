#include "main.h"
#include "timer.h"
#include "ball.h"
#include "pool.h"
#include "ground.h"
#include "spike.h"
#include "trampoline.h"
#include "magnet.h"
#include "stdlib.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;


/**************************
* Customizable functions *
**************************/

Ball ball2, bubble[20];// ball1,
Trampoline ball1;
Ground G1;
Spike S;
Pool P;
Magnet M;
int count=0;
int count1=0;
int count2=0;
int score=0;
char scorput[100];
int time1;
int flag=0;
int flag1=0;
int flag2=0;
int flag3=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);

    S.draw(VP);


    G1.draw(VP);
    P.draw(VP);
    M.draw(VP);
    for(int i=0;i<20;i++)bubble[i].draw(VP);
    ball2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int w  = glfwGetKey(window, GLFW_KEY_W);
    int s  = glfwGetKey(window, GLFW_KEY_S);
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int d  = glfwGetKey(window, GLFW_KEY_D);
    int z  = glfwGetKey(window, GLFW_KEY_Z);
    int x  = glfwGetKey(window, GLFW_KEY_X);
    if(z)
    {
        screen_zoom*=1.04;
        reset_screen();
    }

    if(x)
    {
        screen_zoom/=1.04;
        reset_screen();
    }

    if(w)
    {
        screen_center_y += 0.1;
        reset_screen();
    }

    if(a)
    {
        screen_center_x -= 0.1;
        reset_screen();
    }
    if(s)
    {
        screen_center_y -= 0.1;
        reset_screen();
    }

    if(d)
    {
        screen_center_x += 0.1;
        reset_screen();
    }

    if(detect_collision(ball1.bounding_box(), ball2.bounding_box()))
        ball2.speedy==0;

    if (left) {
        // Do something
        if(detect_collision(ball1.bounding_box(), ball2.bounding_box())){
        if(ball2.position[0]<ball1.position[0] || ball2.position[1]>ball1.position[1])
            ball2.set_position(ball2.position[0]-0.1,ball2.position[1]);
        }
        else
        ball2.set_position(ball2.position[0]-0.1,ball2.position[1]);

    }

    if (right) {
        if(detect_collision(ball1.bounding_box(), ball2.bounding_box())){
            if(ball2.position[0]>ball1.position[0] || ball2.position[1]>ball1.position[1])
                ball2.set_position(ball2.position[0]+0.1,ball2.position[1]);
        }
        else
        ball2.set_position(ball2.position[0]+0.1,ball2.position[1]);

    }
    if(up){
        if(ball2.speedy==0)
        ball2.speedy=0.2;
    }
}

void tick_elements() {
    count++;
    if(count%180==0)
    {
        M.position.x*=-1;
        M.side=(M.side+1)%2;
    }

    if(ball2.position.y>3.4 || ball2.position.y<2.6 )
    {
        ball2.speed=0;
        ball2.acceleration=0;
    }
    else
    {
        if(M.side==0)
        {
            ball2.speed=-0.05;
            ball2.acceleration=-0.08;
        }
        else if(M.side==1)
            {
            ball2.speed=0.05;
            ball2.acceleration=0.08;
            }
    }

    ball1.tick();
    ball2.tick();
    S.tick();

    if(S.position.x>3.5){S.speed=-S.speed;}
    if (detect_collision(ball1.bounding_box(), S.bounding_box()))S.speed=-S.speed;
    if (detect_collision(ball1.bounding_box(), ball2.bounding_box())) {
        //ball1.speed = -ball1.speed;
        //ball2.speed = -ball2.speed;
       //ball2.speedy=0;
        if(ball2.position[1]>ball1.position[1] && ball2.speedy<=0)
        {
            if(abs(ball2.position[0]-ball1.position[0])<0.4)
            {
                ball2.speedy=0.3;
            }
        }
        ball2.speed = 0;
    }
    for(int i=0;i<10;i++)
    {
        bubble[i].tick();
        if (detect_collision(bubble[i].bounding_box(), ball2.bounding_box()))
        {
            if(ball2.position[1]>bubble[i].position[1])
            {
                if(ball2.speedy<0)
                {
                    ball2.speedy=0.15;
                    bubble[i]=Ball(-4,float(rand()%4)/2,COLOR_GREEN,1);
                    bubble[i].speed=0.02+float(rand()%4)/200;
                    score+=10;
                }
            }
        }
        if(bubble[i].position[0]>4)
        {
            bubble[i]=Ball(-4,float(rand()%4)/2,COLOR_GREEN,1);
            bubble[i].speed=0.02+float(rand()%4)/200;
        }
    }
    for(int i=10;i<15;i++)
    {
        bubble[i].tick();
        if (detect_collision(bubble[i].bounding_box(), ball2.bounding_box()))
        {
            if(ball2.position[1]>bubble[i].position[1])
            {
                if(ball2.speedy<0)
                {
                    ball2.speedy=0.15;
                    bubble[i]=Ball(-4,float(rand()%2)/2+2,COLOR_GREEN1,1);
                    bubble[i].speed=0.02+float(rand()%4)/200;
                    score+=15;
                }
            }
        }
        if(bubble[i].position[0]>4)
        {
            bubble[i]=Ball(-4,float(rand()%2)/2+2,COLOR_GREEN1,1);
            bubble[i].speed=0.02+float(rand()%4)/200;
        }
    }

    for(int i=15;i<20;i++)
    {
        bubble[i].tick();
        if (detect_collision(bubble[i].bounding_box(), ball2.bounding_box()))
        {
            if(ball2.position[1]>bubble[i].position[1])
            {
                if(ball2.speedy<0)
                {
                    ball2.speedy=0.15;
                    bubble[i]=Ball(-4,float(rand()%2)/2+3,COLOR_GREEN2,1);
                    bubble[i].speed=0.02+float(rand()%4)/200;
                    score+=20;
                }
            }
        }
        if(bubble[i].position[0]>4)
        {
            bubble[i]=Ball(-4,float(rand()%2)/2+3,COLOR_GREEN2,1);
            bubble[i].speed=0.02+float(rand()%4)/200;
        }
    }


    if (detect_collision(S.bounding_box(), ball2.bounding_box())){
        score-=80;
        ball2       = Ball(-2, -1, COLOR_RED,0);
        ball2.speed=0;
        S           = Spike(3, -1, COLOR_RED1);
        S.speed=0.01;
    }

    int j;
    if(score>180 && flag==0)
    {
        count1=count;
        S.speed*=0.3;
        for(j=0;j<20;j++)
        {
            bubble[j].speed*=0.3;
        }
        flag=1;
    }

    if(count1>0 && count-count1>240 && flag1==0)
    {
        flag1=1;
        S.speed/=0.3;
        for(j=0;j<20;j++)
        {
            bubble[j].speed/=0.3;
        }
    }

    if(score>360 && flag2==0)
    {
        for(j=0;j<20;j++)
        {
            bubble[j].balloon=0;
            if(bubble[j].position.x<-0.75)bubble[j].speed=0.05;
            if(bubble[j].position.x>0.75)bubble[j].speed=-0.05;
        }
        flag2=1;
    }

    if(flag3==0 && flag2==1)
    {
        count2=0;
       for(j=0;j<20;j++)
       {
           if(bubble[j].position.x>-0.75 && bubble[j].position.x<0.75 && bubble[j].position.y<-0.75)
           {
               bubble[j].speed=0;
               count2++;
           }
        }

       if(count2==20)flag3=1;
    }

    sprintf(scorput, "Score: %d", score);
    glfwSetWindowTitle(window,scorput);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    //ball1       = Ball(2, -1, COLOR_RED,0);
    ball1       = Trampoline(2, -1, COLOR_BLACK);
    ball2       = Ball(-2, -1, COLOR_RED,0);
    S           = Spike(3, -1, COLOR_RED1);

    S.speed=0.01;
    int i;
    for( i=0;i<10;i++)
    {
        bubble[i]=Ball(rand()%8-4,float(rand()%4)/2,COLOR_GREEN,1);
        bubble[i].speed=0.02+float(rand()%4)/200;
    }

    for(i=10;i<15;i++)
    {
        bubble[i]=Ball(rand()%8-4,float(rand()%2)/2+2,COLOR_GREEN1,1);
        bubble[i].speed=0.02+float(rand()%4)/200;
    }

    for(i=15;i<20;i++)
    {
        bubble[i]=Ball(rand()%8-4,float(rand()%2)/2+3,COLOR_GREEN2,1);
        bubble[i].speed=0.02+float(rand()%4)/200;
    }

    G1          = Ground(COLOR_BROWN);
    P           = Pool(0, -1.23, COLOR_BLUE);
    M           = Magnet(-4,3,COLOR_RED1);
    M.side=0;
    //ball2.speed = -ball2.speed;
    ball2.speed = 0;
    //ball1.speed = 0;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) ;
}

bool detect_collision1(bounding_box_t a, bounding_box_t b) {
    return  (abs(a.x-b.x)>a.width)  ;
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
