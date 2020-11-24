#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#ifdef WIN32
#include <GL/glew.h>

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <iostream>
#include <fstream>
#include <string>

class Shader
{
    public:
        Shader();
        Shader(std::string vertexSource, std::string fragmentSource);
        Shader(Shader const &shaderACopier);
        Shader& operator=(Shader const &shaderACopier);
        ~Shader();
        GLuint getProgramID() const;
        bool charger();
        bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);

    private:
        GLuint m_vertexID;
        GLuint m_fragmentID;
        GLuint m_programID;

        std::string m_vertexSource;
        std::string m_fragmentSource;
};

#endif // SHADER_H_INCLUDED
