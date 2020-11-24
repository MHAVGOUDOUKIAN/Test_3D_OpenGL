#include "Cristal.h"

using namespace glm;

Cristal::Cristal(std::string const vertexShader, std::string const fragmentShader): m_shader(vertexShader, fragmentShader), m_textureCristal("Cristal.tga"), m_vboID(0),
m_tailleVerticesBytes(99 * sizeof(float)), m_tailleCoordTextureBytes(66 * sizeof(float)), m_vaoID(0)
{
    m_shader.charger();

    m_textureCristal.charger();

       float verticesTmp[] = {-0.5, 0, -0.5,   0.5, 0, -0.5,   0, 1, 0,      // Triangle 1
                           0.5, 0, -0.5,   0.5, 0, 0.5,  0, 1, 0,         // Triangle 2
                           0.5, 0, 0.5,   -0.5, 0, 0.5,   0, 1, 0,        // Triangle 3
                           -0.5, 0, 0.5,   -0.5, 0, -0.5,   0, 1, 0,      // Triangle 4

                           -0.5, 0, -0.5,   0.5, 0, -0.5,   0, -1, 0,     // Triangle 5
                           0.5, 0, -0.5,   0.5, 0, 0.5,  0, -1, 0,        // Triangle 6
                           0.5, 0, 0.5,   -0.5, 0, 0.5,   0, -1, 0,       // Triangle 7
                           -0.5, 0, 0.5,   -0.5, 0, -0.5,   0, -1, 0};    // Triangle 8

    float coordTextureTmp[] = {0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 1
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 2
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 3
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 4
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 5
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 6
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 7
                            0, 0,   0.5, 0,   0.5, 0.5};     // Triangle 8

    for(int i(0); i<72; i++)
    {
        m_vertices[i]=verticesTmp[i];
    }

    for(int i(0); i<48; i++)
    {
        m_textures[i]=coordTextureTmp[i];
    }
}

Cristal::~Cristal()
{
    glDeleteBuffers(1, &m_vboID);

    glDeleteVertexArrays(1, &m_vaoID);
}

void Cristal::charger()
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

void Cristal::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D, m_textureCristal.getID());

                glDrawArrays(GL_TRIANGLES, 0, 24);

            glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

    glUseProgram(0);
}
