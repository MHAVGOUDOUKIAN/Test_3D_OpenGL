#ifndef CRISTAL_H_INCLUDED
#define CRISTAL_H_INCLUDED

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
#include "Texture.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class Cristal
{
    public:
        Cristal(std::string const vertexShader, std::string const fragmentShader);
        ~Cristal();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
        void charger();

    private:
        Shader m_shader;
        Texture m_textureCristal;
        float m_vertices[72];
        float m_textures[48];

        GLuint m_vboID;
        int m_tailleVerticesBytes;
        int m_tailleCoordTextureBytes;
        GLuint m_vaoID;
};

#endif // CRISTAL_H_INCLUDED
