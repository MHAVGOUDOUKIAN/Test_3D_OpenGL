#include "Cube.h"

using namespace glm;

Cube::Cube(float taille, std::string const vertexShader, std::string const fragmentShader): m_shader(vertexShader, fragmentShader), m_vboID(0),
m_tailleVerticesBytes(108 * sizeof(float)), m_tailleCouleursBytes(108 * sizeof(float)), m_vaoID(0)
{
    m_shader.charger();

    taille/=2;

        float verticesTmp[] = {-taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,
                            -taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,

                            taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,
                            taille, -taille, taille,   taille, taille,   taille,   taille, taille, -taille,

                            -taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,
                            -taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,

                            -taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,
                            -taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,

                            -taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,
                            -taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,

                            -taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,
                            -taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille};

        float couleursTmp[] = {1.0, 0.0 , 0.0,  1.0, 0.0 , 0.0,  1.0, 0.0 , 0.0,
                            1.0, 0.0 , 0.0,  1.0, 0.0 , 0.0,  1.0, 0.0 , 0.0,

                            0.0, 1.0 , 0.0,  0.0, 1.0 , 0.0,  0.0, 1.0 , 0.0,
                            0.0, 1.0 , 0.0,  0.0, 1.0 , 0.0,  0.0, 1.0 , 0.0,

                            0.0, 0.0 , 1.0,  0.0, 0.0 , 1.0,  0.0, 0.0 , 1.0,
                            0.0, 0.0 , 1.0,  0.0, 0.0 , 1.0,  0.0, 0.0 , 1.0,

                            1.0, 1.0 , 0.0,  1.0, 1.0 , 0.0,  1.0, 1.0 , 0.0,
                            1.0, 1.0 , 0.0,  1.0, 1.0 , 0.0,  1.0, 1.0 , 0.0,

                            0.0, 1.0 , 1.0,  0.0, 1.0 , 1.0,  0.0, 1.0 , 1.0,
                            0.0, 1.0 , 1.0,  0.0, 1.0 , 1.0,  0.0, 1.0 , 1.0,

                            1.0, 0.0 , 1.0,  1.0, 0.0 , 1.0,  1.0, 0.0 , 1.0,
                            1.0, 0.0 , 1.0,  1.0, 0.0 , 1.0,  1.0, 0.0 , 1.0};

        for(int i(0); i<108; i++)
        {
            m_vertices[i]=verticesTmp[i];
            m_couleurs[i]=couleursTmp[i];
        }
}

Cube::~Cube()
{
    glDeleteBuffers(1, &m_vboID);

    glDeleteVertexArrays(1, &m_vaoID);
}

void Cube::charger()
{
    if(glIsBuffer(m_vboID)== GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    ////CREATION DU VBO
    glGenBuffers(1, &m_vboID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_couleurs);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ////CREATION DU VBA
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
    {
          glDeleteVertexArrays(1, &m_vaoID);
    }

    glGenVertexArrays(1, &m_vaoID);

    glBindVertexArray(m_vaoID);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
            glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


}

void Cube::afficher(mat4 &projection, mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"),
            1, GL_FALSE, value_ptr(modelview));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"),
            1, GL_FALSE, value_ptr(projection));

            glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

    glUseProgram(0);
}

void Cube::updateVBO(void *donnees, int tailleBytes, int decalage)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        if(adresseVBO == NULL)
        {
            std::cout<<"Erreur au niveau de la récupération du VBO"<<std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        memcpy((char*)adresseVBO + decalage, donnees, tailleBytes);

        glUnmapBuffer(GL_ARRAY_BUFFER);
        adresseVBO = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
