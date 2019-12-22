/**   
 * @file  		ShaderProgram.hpp
 * @description Shader program fonksiyonları ve değişkenlerinin tanımlandığı kütüphane 
 * @course  	Bilgisayar Grafiği
 * @assignment  01
 * @authors  	Oğuzhan Tohumcu 2A B181210397  
 *				Abdurrahman Doğan 1A B181210394
*/ 

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <map>
#include<glm/mat3x3.hpp>



class ShaderProgram{
    public :
    ShaderProgram();
    ~ShaderProgram();
    void attachShader(const char* filename,unsigned int shaderType);
    void link();
    void use();
    void addUniform(const std::string& varName);
    void setFloat(const std::string& varName,float value);
    void setVec3(const std::string& varName,const glm::vec3& value);
    void setVec4(const std::string& varName,const glm::vec4& value);
    void setMat3(const std::string& varName,const glm::mat3* mtx);
    private:

    std::map<std::string,unsigned int> m_UniformVars;

    unsigned int m_ProgramId;

    std::string getShaderFromFile(const char* fileName);

};

#endif 