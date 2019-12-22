/**   
 * @file  		Daire.cpp
 * @description Yılana ait daire oluşturma, dönme, öteleme
 * @course  	Bilgisayar Grafiği
 * @assignment  01
 * @authors  	Oğuzhan Tohumcu 2A B181210397  
 *				Abdurrahman Doğan 1A B181210394
*/ 

#include "Daire.hpp"
#include <glad/glad.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include <vector>
#include<cmath>
#include <iostream>


Daire::Daire(float yariCap,std::string donus,std::vector<Vertex>& vertices,glm::vec2 pos,std::vector<unsigned int>& indices,glm::mat3 transform,int detay)
{
    m_Color=glm::vec4(1.0f,1.0f,1.0f,1.0f);
    m_Yaricap=yariCap;
    m_Direction=DIR_RIGHT;
    m_Position=pos;
    m_Donus=donus;
    mtxTransform=transform;


        int noktaSayisi = 4*detay;
        float angle     = 360.0f/noktaSayisi;
        int triCount    = noktaSayisi-2;
        for(int i=0;i<noktaSayisi;i++)
        {
            Vertex ver;
            float Aci = angle*i;

            ver.pos.x = m_Position.x+(yariCap*glm::cos(glm::radians(Aci)));
            ver.pos.y = m_Position.y+(yariCap*glm::sin(glm::radians(Aci)));
            ver.pos.z = 1.0f;

            vertices.push_back(ver);
        }
        for(int i =0;i<triCount;i++)
        {
            int index = i;
            
            indices.push_back(0);
            indices.push_back(index+1);
            indices.push_back(index+2);
            
        }
}
Daire::DIRECTION Daire::getDirection()
{
    return m_Direction;
}

glm::vec4 Daire::getColor()
{
    return m_Color;
}

void Daire::setDirection(Daire::DIRECTION dir)
{
    m_Direction = dir;
}
void Daire::move()
{
    switch(m_Direction)
    {
        case DIR_LEFT:
            m_Position-= glm::vec2(m_Yaricap*2,0.0f);
        break;
        case DIR_RIGHT:
            m_Position+= glm::vec2(m_Yaricap*2,0.0f);
        break;
        case DIR_UP:
            m_Position+= glm::vec2(0.0f,m_Yaricap*2);
        break;
        case DIR_DOWN:
            m_Position-= glm::vec2(0.0f,m_Yaricap*2);
        break;                        
    }
}
void Daire::setTransform(float angle){

    glm::mat3 mtxRotate = glm::rotate(glm::mat3(1),glm::radians(angle));
    glm::mat3 mtxTranslation=glm::translate(glm::mat3(1),m_Position);
    mtxTransform=mtxTranslation*mtxRotate;
}
std::string Daire::getRotation(){
    return m_Donus;
}  
glm::mat3 Daire::getTransform(){
    return mtxTransform;
}
glm::vec2 Daire::getPosition()
{
    return m_Position;
}


