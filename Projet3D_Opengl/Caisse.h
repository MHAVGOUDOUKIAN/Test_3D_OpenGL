#ifndef CAISSE_H_INCLUDED
#define CAISSE_H_INCLUDED

#include "Cube.h"
#include "Texture.h"

class Caisse : public Cube
{
    public:
        Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
        ~Caisse();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
        void charger();


    private:
        Texture m_texture;
        float m_coordTexture[72];
        int m_tailleCoordTextureBytes;


};

#endif // CAISSE_H_INCLUDED
