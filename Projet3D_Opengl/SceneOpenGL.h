#ifndef SCENEOPENGL_H_INCLUDED
#define SCENEOPENGL_H_INCLUDED

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>
#include "Shader.h"
#include "Cube.h"
#include "Input.h"
#include "Texture.h"
#include "Caisse.h"
#include "Camera.h"
#include "Maison.h"
#include "Cristal.h"
#include "Sol.h"

class SceneOpenGL
{
    public:
        SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
        ~SceneOpenGL();

        bool initialiserFenetre();
        bool initGL();
        void bouclePrincipale();

    private:
        std::string m_titreFenetre;
        int m_largeurFenetre;
        int m_hauteurFenetre;

        SDL_Window* m_fenetre;
        SDL_GLContext m_contextOpenGL;
        SDL_Event m_event;
        Input m_input;

};

#endif // SCENEOPENGL_H_INCLUDED
