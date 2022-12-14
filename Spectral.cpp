#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <string>
#include <sstream>

#include<cmath>

using namespace glm;
using namespace std;
#include<vector>
// Function for intializing window





GLfloat lineVertices[10] ;

  unsigned int VBO1, VAO1, EBO1;  

void windowIntializeConfig(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

}


vec3 temp1 = vec3(1.0f,0.0f,0.0f);
glm::mat4 view = glm::mat4(1.0f);
float x,y,z;
float theta1=0.0f;
float theta2=0.0f;
int tx=0;
float phi1=0.0f;
float phi2=0.0f;
const float radius = 5.0f;
float camX = sin(phi1) *cos(theta1)*radius ;
float camZ = cos(theta1)*cos(phi1) *radius;
float camY = radius*sin(theta1);
float camX1= sin(theta2) *radius ;
float camZ1 = cos(theta2) *radius;

float camY1 = sin(theta2) *radius ;

unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube()
{
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

glm::vec3 specularColor=vec3(1.0f,1.0f,1.0f);
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
  
       if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
            tx=1;
        
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            tx=0;
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
           { specularColor= vec3(	0.992157f,0.941176f,0.807843f);
           }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
           { specularColor= vec3(0.393548f,0.271906f,	0.166721f);
           }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
           { specularColor= vec3(0.774597f,0.774597f,0.774597f);
           }
          if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
           { specularColor= vec3(	0.256777f,	0.137622f,		0.086014f);
           }
           if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
           { specularColor= vec3(0.628281f,	0.555802f,	0.366065f);
           } 


    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            
            
           phi1+=0.01;
        camX = sin(phi1) *cos(theta1)*radius ;
camZ = cos(theta1)*cos(phi1) *radius;
camY = radius*sin(theta1);
            
      
            
        }
       
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        
            
            phi1-=0.01;
             camX = sin(phi1) *cos(theta1)*radius ;
 camZ = cos(theta1)*cos(phi1) *radius;
 camY = radius*sin(theta1);
        
         
           
        
        }    
       
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
       { 
        
      
         theta1-=0.01;
            camX = sin(phi1) *cos(theta1)*radius ;
 camZ = cos(theta1)*cos(phi1) *radius;
 camY = radius*sin(theta1);
      
        
      
       }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)

         {
            
           

            theta1+=0.01;
            camX = sin(phi1) *cos(theta1)*radius ;
 camZ = cos(theta1)*cos(phi1) *radius;
 camY = radius*sin(theta1);
            
         }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            
            
            phi2+=0.01;
            camY1 = sin(phi2) * radius;
            camZ1 = cos(phi2)  * radius;
            camX1=0.0f;
            
      
            
        }
       
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        
            
            phi2-=0.01;
            camY1 = sin(phi2) * radius;
            camZ1 = cos(phi2)  * radius;
            camX1=0.0f;
        
         
           
        
        }    
       
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
       { 
        
      
         theta2-=0.01;
            camX1 = sin(theta2) * radius;
            camZ1 = cos(theta2)  * radius;
            camY1=0.0f;
      
        
      
       }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

         {
            
           

            theta2+=0.01;
            camX1 = sin(theta2) *radius;
            camZ1 = cos(theta2)  * radius;
            camY1=0.0f;
            
         }
       
    
    
}

void framebuffer_size(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

//Shaders

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 COD;\n"
    "layout (location = 1) in vec2 uv;\n"
    "layout (location = 2) in vec3 normal;\n"
    "out vec3 COD1;\n"
    "out vec3 FragPos;\n"
    "out vec3 Normal;\n"

    "out vec2 fragUV;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 model;\n"
    "void main()\n"
    "{\n"
    "FragPos =COD;\n"
    "Normal = normalize(normal);\n"
    "fragUV=uv;\n"
    "COD1=COD*0.2;\n"
    "   gl_Position = model*projection*view*vec4(COD1, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "precision mediump float;\n"
    "out vec4 outColor;\n"
   "uniform vec3 color;\n"
    "void main()\n"
    "{\n"
   
    "outColor =vec4(color,1.0f);\n"
    "}\n\0";




int main()
{

 


    windowIntializeConfig();

    //Window creation
    GLFWwindow* window = glfwCreateWindow(600, 600, "Assignment-8", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size);


    if (glewInit() != GLEW_OK)
    { 
        std :: cout << "Failed to initialize GLEW" << std :: endl; 
        return -1;
     }



   
    // Compiling Shaders

    unsigned int vtxShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtxShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vtxShader);
 
    int success;
    char log[512];
    glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vtxShader, 512, NULL, log);
        std::cout << "vertex shader compilation failed\n" << log << std::endl;
    }
 
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragShader);
  
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, log);
        std::cout << "frag shader compilation failed\n" << log << std::endl;
    }
    // Linking Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vtxShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
  
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cout << "Shader Link Failed\n" << log << std::endl;
    }
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);

ifstream xyz("XYZ.csv");
    if (!xyz.is_open()) throw runtime_error("Could not open file");

    vector<float> XYZ[3];
    string line;
    float value;
    while (getline(xyz, line))
    {
        stringstream ss(line);
        int column = 0;
        while (ss >> value) {
            XYZ[column].push_back(value);
            if (ss.peek() == ',') ss.ignore();
            column++;
        }
    }

   ifstream Mac("MacbethColorchecker.csv");
    if (!Mac.is_open()) throw runtime_error("Could not open file");

   vector<float> checker[24];

 string line1;
    float value1;
    while (getline(Mac, line))
    {
        stringstream ss(line);
        int column = 0;
        while (ss >> value1) {
            checker[column].push_back(value1);
            if (ss.peek() == ',') ss.ignore();
            column++;
        }
    }

float xw = 0.3127f, yw = 0.3291f,  zw = 1-xw-yw;
float xr= 0.67f, yr=0.33f, xg=0.21f,yg=0.71f ,xb=0.15f,yb=0.06f;   
float YW = 65.0f, XW = (xw*YW)/yw, ZW=(zw*YW)/yw;

mat3 ve = mat3(xr,xg,xb,yr,yg,yb,1-xr-yr,1-xg-yg,1-xb-yb);
mat3 re =inverse(ve);
 
float Cr =re[0][0]*XW + re[0][1]*YW + re[0][2]*ZW;
float Cg = re[1][0]*XW + re[1][1]*YW + re[1][2]*ZW;
float Cb= re[2][0]*XW + re[2][1]*YW + re[2][2]*ZW;

mat3 ve2 = mat3(xr*Cr,xg*Cg,xb*Cb,yr*Cr,yg*Cg,yb*Cb,(1-xr-yr)*Cr,(1-xg-yg)*Cg,(1-xb-yb)*Cb);
mat3 re2 = inverse(ve2);



float tempx=0,tempy=0,tempz=0;

vector <float> Xvals;
vector <float> Yvals;
vector <float> Zvals;
for(int j=0;j<24;j++)
{
    tempx=0;
    tempy=0;
    tempz=0;
for(int i=0;i<XYZ[0].size();i++)
{
    tempx+= XYZ[0][i]*checker[j][i];
    tempy+= XYZ[1][i]*checker[j][i];
    tempz+= XYZ[2][i]*checker[j][i];
    
}
Xvals.push_back(tempx);
Yvals.push_back(tempy);
Zvals.push_back(tempz);
}



glEnable(GL_DEPTH_TEST); 
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.3f, 0.5f, 0.3f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glUseProgram(shaderProgram);
    


       view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projectionMatrix = mat4(1.0f);
        projectionMatrix =glm::perspective(glm::radians(45.0f),1.0f,0.1f,100.0f);
        glm :: vec3 viewpos = vec3(camX, camY, camZ);
        glm :: vec3 lightPos= vec3(camX1, camY1, camZ1);
        glm :: vec3 lightColor=vec3(1.0f, 1.0f, 1.0f);
       
         
        unsigned int viewLoc= glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        unsigned int projLoc= glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glm::mat4 model = glm::mat4(1.0f);
        int count=0;
        for (int row = 0; row < 4; ++row)
        {

            for (int col = 0; col < 6; ++col)
            {
               float R = re2[0][0]*Xvals[count]+ re2[0][1]*Yvals[count] + re2[0][2]*Zvals[count];
float G = re2[1][0]*Xvals[count]+ re2[1][1]*Yvals[count] + re2[1][2]*Zvals[count];
float B = re2[2][0]*Xvals[count] + re2[2][1]*Yvals[count] + re2[2][2]*Zvals[count];
                vec3 color = vec3(R*3.5,G*3.5,B*3.5);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                    (float)(col - (6 / 2)) * 0.3f + (0.15f),
                    -(float)(row - (4 / 2)) * 0.3f ,
                    0.0f
                ));
                count += 1;
                unsigned int modelLoc= glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
         unsigned int colorLoc= glGetUniformLocation(shaderProgram, "color");
        glUniform3fv(colorLoc, 1, glm::value_ptr(color));
                renderCube();
            }
        }
        
       
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}


