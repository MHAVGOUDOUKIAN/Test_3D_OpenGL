#include "Caisse.h"

using namespace glm;

Caisse::Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture):
Cube(taille, vertexShader, fragmentShader), m_texture(texture), m_tailleCoordTextureBytes(72 * sizeof(float))
{
    m_texture.charger();

    float coordTextureTmp[] = {0.5, 0,   0, 0,   0, 1,
                               0.5, 0,   0.5, 1,   0, 1,

                               0.5, 0,   1, 0,   1, 1,
                               0.5, 0,   0.5, 1,   1, 1,

                               0.5, 0,   1, 0,   1, 1,
                               0.5, 0,   0.5, 1,   1,1,

                               0, 0,   0.5, 0,   0.5, 1,
                               0, 0,   0, 1,   0.5, 1,

                               0.5, 0,   1, 0,   1, 1,
                               0.5, 0,   0.5, 1,   1, 1,

                               0.5, 0,   1, 0,   1, 1,
                               0.5, 0,   0.5, 1,   1, 1};

    for(int i(0); i < 72 ; i++)
    {
        m_coordTexture[i]=coordTextureTmp[i];
    }
}

Caisse::~Caisse()
{

}

void Caisse::charger()
{
    ////GENERATION DU VBO
    if(glIsBuffer(m_vboID)== GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    glGenBuffers(1, &m_vboID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCoordTextureBytes, 0, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCoordTextureBytes, m_coordTexture);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ////CREATION DU VAO
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
    glDeleteVertexArrays(1, &m_vaoID);

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

void Caisse::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D, m_texture.getID());

                glDrawArrays(GL_TRIANGLES, 0, 36);

            glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

    glUseProgram(0);
}


