#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class Cube
{
    public:
        Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
        ~Cube();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
        void charger();
        void updateVBO(void *donnees, int tailleBytes, int decalage);

    protected:
        Shader m_shader;
        float m_vertices[108];
        float m_couleurs[108];

        GLuint m_vboID;
        int m_tailleVerticesBytes;
        int m_tailleCouleursBytes;
        GLuint m_vaoID;
};

#endif // CUBE_H_INCLUDED
