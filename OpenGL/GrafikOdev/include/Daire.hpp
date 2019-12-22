/**   
 * @file  		ShaderProgram.hpp
 * @description Yılana ait vertex, direction ve vector fonksiyonları, değişkenleri ve kütüphaneleri tanımlandı.
 *              Bu değişkenler kullanılarak daire çizimini yapan constructor yazıldı.
 * @course  	Bilgisayar Grafiği
 * @assignment  01
 * @authors  	Oğuzhan Tohumcu 2A B181210397  
 *				Abdurrahman Doğan 1A B181210394
*/ 

#ifndef DAIRE_HPP
#define DAIRE_HPP
#include <glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <vector>
#include <string>


struct Vertex{
    glm::vec3 pos;
    glm::vec2 tex;
};

class Daire
{
public:

    enum DIRECTION
    {
        DIR_RIGHT   =  1,
        DIR_LEFT    = -1,
        DIR_UP      =  2,
        DIR_DOWN    = -2

    };
    Daire(float yariCap,std::string donus,std::vector<Vertex>& vertices,glm::vec2 pos,std::vector<unsigned int>& indices,glm::mat3 transform,int detay);

    glm::vec2 getPosition();
    glm::vec4 getColor();
    glm::mat3 getTransform();
    void setTransform(float angle);
    
    DIRECTION getDirection();

    void setDirection(DIRECTION dir);

    void move();
    std::string getRotation();                

private:

    DIRECTION   m_Direction;
    glm::vec2           m_Position;
    float               m_Yaricap;
    std::string         m_Donus;
    glm::vec4           m_Color;
    glm::mat3           mtxTransform;

};


#endif