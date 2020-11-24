#include "Maison.h"

using namespace glm;

Maison::Maison(std::string const vertexShader, std::string const fragmentShader): m_shader(vertexShader, fragmentShader), m_textureMur("Mur.jpg"), m_textureToit("Toit.jpg"), m_vboID(0),
m_tailleVerticesBytes(99 * sizeof(float)), m_tailleCoordTextureBytes(66 * sizeof(float)), m_vaoID(0)
{
    m_shader.charger();

    m_textureMur.charger();
    m_textureToit.charger();

    float verticesTmp[] = {-5, 0, -5,   -5, 5, -5,   -5, 5, 5,  // 1er MUR
                           -5, 0, -5,   -5, 5, 5,   -5, 0, 5,

                           -5, 0, -5,   -5, 5, -5,   5, 5, -5,    // 2eme MUR
                           -5, 0, -5,   5, 5, -5,   5, 0, -5,

                           5, 5, -5,   5, 0, -5,   5, 0, 5,  //3eme MUR
                           5, 5, -5,   5, 0, 5,   5, 5, 5,

                           -5, 5, -5,   5, 5, -5,   0, 6, -5, //COMBLES

                           -6, 4.8, 6,   0, 6, 6,   0, 6, -6,  // 1er TOIT
                           -6, 4.8, 6,   0, 6, -6,  -6, 4.8, -6,

                           0, 6, 6,   6, 4.8, 6,   6, 4.8, -6,
                           0, 6, 6,   0, 6, -6,   6, 4.8, -6};

    float coordTextureTmp[] = {0, 0,   0, 1,   1, 1, //Texture 1er MUR
                               0, 0,   1, 1,   1, 0,

                               0, 0,   0, 1,   1, 1, //Texture 2eme MUR
                               0, 0,   1, 1,   1, 0,

                               0, 1,   0, 0,   1, 0, //Texture 3eme MUR
                               0, 1,   1, 0,   1, 1,

                               0, 0,   1, 0,   0.5, 0.5, //Texture COMBLES

                               1, 0,   1, 1,   0, 1, //Texture 1er TOIT
                               1, 0,   0, 1,   0, 0,

                               1, 0,   1, 1,   0, 1, //Texture 2eme TOIT
                               1, 0,   0, 0,   0, 1};

    for(int i(0); i<99; i++)
    {
        m_vertices[i]=verticesTmp[i];
    }

    for(int i(0); i<66; i++)
    {
        m_textures[i]=coordTextureTmp[i];
    }
}

Maison::~Maison()
{
    glDeleteBuffers(1, &m_vboID);

    glDeleteVertexArrays(1, &m_vaoID);
}

void Maison::charger()
{
    //// GENERATION DU VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    glGenBuffers(1, &m_vboID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCoordTextureBytes, 0, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCoordTextureBytes, m_textures);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ////CREATION DU VAO
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_vaoID);
    }

    glGenVertexArrays(1, &m_vaoID);

    glBindVertexArray(m_vaoID);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Maison::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D, m_textureMur.getID());

                glDrawArrays(GL_TRIANGLES, 0, 21);

            glBindTexture(GL_TEXTURE_2D, 0);

            glBindTexture(GL_TEXTURE_2D, m_textureToit.getID());

                glDrawArrays(GL_TRIANGLES, 21, 12);

            glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

    glUseProgram(0);
}
