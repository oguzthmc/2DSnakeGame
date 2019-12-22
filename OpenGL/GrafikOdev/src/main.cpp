/**   
 * @file  		main.cpp
 * @description Yılan hareketi, çizim, kuyruğa eleman ekleme yapıldı. 
 *              Kaplama üzerinde uğraşıldı ama tam yapılamadı.
 * @course  	Bilgisayar Grafiği
 * @assignment  01
 * @authors  	Oğuzhan Tohumcu 2A B181210397  
 *				Abdurrahman Doğan 1A B181210394
*/ 

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<GLFW/glfw3.h>
#include<vector>
#include "shaderprogram.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Daire.hpp"
#include <cmath>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <time.h>

//noktalara ait koordinat bilgileri.
std::vector<Vertex>      vertices;
std::vector<Daire*>    snakeList;
std::vector<unsigned int>   indices;
std::string donusYonu;
glm::mat3 mtxTransform(1);
glm::vec3 position;
float aci=0.0f;
float tersAci=0.0f;


float yariCap=0.1;

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int texture;


void addToTail()
{
    int elementCount = snakeList.size();
    int sayi=rand()%10;
    if(sayi%2==0){   
        donusYonu="arti";
    }
    else{
        donusYonu="eksi";
    }

    if(elementCount==0)
    {
        snakeList.push_back(new Daire(yariCap,donusYonu,vertices,glm::vec3(0.0f,0.0f,0.0f),indices,mtxTransform,9));
        
    }
    else
    {
        Daire* sonDaire = snakeList[elementCount-1];

        glm::vec2 pos = sonDaire->getPosition();

        Daire::DIRECTION dir = sonDaire->getDirection();

        switch(dir)
        {
            case Daire::DIR_RIGHT:
                pos-=glm::vec2(2*yariCap,0.0f);
            break;
            case  Daire::DIR_LEFT:
                pos+=glm::vec2(2*yariCap,0.0f);
                break;
            case  Daire::DIR_UP:
                pos-=glm::vec2(0.0f,2*yariCap);
                break;    
            case  Daire::DIR_DOWN:
                pos+=glm::vec2(0.0f,2*yariCap);
                break;              
        }
        
        Daire* yeniDaire = new Daire(yariCap,donusYonu,vertices,pos,indices,mtxTransform,9);

        yeniDaire->setDirection(dir);

        snakeList.push_back(yeniDaire);
    }
}
void move()
{
    for(auto next:snakeList)
    {
        next->move();
    }

    for(int i=snakeList.size()-1;i>0;i--)
    {
        snakeList[i]->setDirection(snakeList[i-1]->getDirection());
    }      
}

void draw(ShaderProgram& program)
{
    aci+=2;
    tersAci-=2;
    for(auto next:snakeList)
    {
        program.setVec4("uColor",next->getColor());
        if(next->getRotation()=="arti"){
            next->setTransform(aci);
        }
        else{
            next->setTransform(tersAci);
        }
        glm::mat3 transform=next->getTransform();
        program.setMat3("uMtxTransform",&transform);
        
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();   
    if(action==GLFW_PRESS)
    {
        if(snakeList.size()!=0)
        {
            Daire* first = snakeList[0];

            if(key==GLFW_KEY_LEFT)  
            {
                first->setDirection(Daire::DIR_LEFT);
            }
            if(key==GLFW_KEY_RIGHT) 
            {
                first->setDirection(Daire::DIR_RIGHT);
            }    
            if(key==GLFW_KEY_UP)  
            {
                first->setDirection(Daire::DIR_UP);
            }
            if(key==GLFW_KEY_DOWN) 
            {
                first->setDirection(Daire::DIR_DOWN);
            }                
        }
        
        if(key==GLFW_KEY_SPACE)
            addToTail();
           
    }  
           
}

int main(int argc,char** argv)
{
    srand(time(NULL));
    if(!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800,800,"İLk Programım",NULL,NULL);
    if(window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;

        glfwTerminate();

        return -1;
    }    
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    // addToTail();
    
    addToTail();
    addToTail();
    addToTail();
    addToTail();
    addToTail();
    
    int width, height, nrChannels;
 
    unsigned char*data =stbi_load("../images/homer.jpg",&width,&height,&nrChannels,0);

    // std::cout<<width<<","<<height<<std::endl;

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);

    glGenerateMipmap(GL_TEXTURE_2D);
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    stbi_image_free(data);

    //glm::mat3 mtxTransform(1);

    // aci=0.0f;
    // position = glm::vec2(0.0f,0.0f);
    // tersAci = 1.0f;
    

    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uColor");
    program.addUniform("uMtxTransform");

    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1,&VBO);   

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); 

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 

   
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);

        //çizimde kullanılacak olan Vertex array object aktif ediliyor;
        glBindVertexArray(VAO);

        draw(program);
      
        move();

        std::this_thread::sleep_for (std::chrono::milliseconds(200));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}