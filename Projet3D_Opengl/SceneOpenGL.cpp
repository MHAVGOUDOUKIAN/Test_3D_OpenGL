#include "SceneOpenGL.h"

using namespace glm;

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contextOpenGL(0), m_input()
{

}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contextOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    m_fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if(m_fenetre == 0)
    {
        std::cout<<SDL_GetError()<<std::endl;
        SDL_Quit();

        return false;
    }

    m_contextOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contextOpenGL == 0)
    {
        std::cout<<SDL_GetError()<<std::endl;
        SDL_DestroyWindow(m_fenetre);

        SDL_Quit();
        return false;
    }
    return true;
}

bool SceneOpenGL::initGL()
{
    #ifdef WIN32


        GLenum initialisationGLEW( glewInit() );

        if(initialisationGLEW != GLEW_OK)
        {

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

            SDL_GL_DeleteContext(m_contextOpenGL);
            SDL_DestroyWindow(m_fenetre);
           SDL_Quit();

            return false;
        }
    #endif // WIN32

        glEnable(GL_DEPTH_TEST);

    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    unsigned int frameRate(1000/150);
    Uint32 debutBoucle(0), finBoucle(0), tpsEcoule(0);
    float angle(0.0);

    mat4 modelview;
    mat4 projection;

    projection = perspective(70.0, (double) m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);

    Camera camera(vec3(4,4,9), vec3(0,0,0), vec3(0,1,0), 0.5, 0.3);
    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);

    Caisse caisse(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Decor.jpg");
    caisse.charger();

    Caisse caisseExplosive(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Decor.jpg");
    caisseExplosive.charger();

    Maison maison ("Shaders/texture.vert", "Shaders/texture.frag");
    maison.charger();

    Cristal cristal("Shaders/texture.vert", "Shaders/texture.frag");
    cristal.charger();

    Sol solHerbeux(30.0, 30.0, 15, 15, "Shaders/texture.vert", "Shaders/texture.frag", "Herbe.jpg");
    solHerbeux.charger();

    Sol solTerreux(10.0, 10.0, 5, 5, "Shaders/texture.vert", "Shaders/texture.frag", "Sol.jpg");
    solTerreux.charger();

    while(!m_input.terminer())
    {
        debutBoucle = SDL_GetTicks();

        m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
        {
            break;
        }
        if(m_input.getBoutonSouris(SDL_BUTTON_LEFT))
        {
             projection = perspective(30.0, (double) m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
        }
        else if(m_input.getBoutonSouris(SDL_BUTTON_RIGHT))
        {
             projection = perspective(70.0, (double) m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
        }


        camera.deplacer(m_input);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.lookAt(modelview);

        ////AFFICHAGE DE LA MAISON////
        mat4 copieModelview = modelview;

            maison.afficher(projection, modelview);

            solHerbeux.afficher(projection, modelview);

            modelview = translate(modelview, vec3(0, 0.01, 0));
            solTerreux.afficher(projection, modelview);

        modelview = copieModelview;

        //// AFFICHAGE DES CAISSES////
        copieModelview = modelview;

            modelview = translate(modelview, vec3(0, 1.01, 3));
            caisse.afficher(projection, modelview);

        modelview = copieModelview;

        copieModelview = modelview;

            modelview = translate(modelview, vec3(2, 1.01, -1));
            caisseExplosive.afficher(projection, modelview);

        modelview = copieModelview;

        copieModelview = modelview;

            modelview = translate(modelview, vec3(-2, 1.01, -1));
            caisse.afficher(projection, modelview);

        modelview = copieModelview;
        //// AFFICHAGE DE LA RELIQUE ////

            angle++;
            if(angle > 360)
            {
                angle -=360;
            }
            modelview = translate(modelview, vec3(0, 3.1, 3));
            modelview = rotate(modelview, angle,vec3(0, 1.0, 0));
            cristal.afficher(projection, modelview);

            modelview = copieModelview;

        SDL_GL_SwapWindow(m_fenetre);

        finBoucle = SDL_GetTicks();
        tpsEcoule = finBoucle - debutBoucle;

        if(tpsEcoule < frameRate)
        {
            SDL_Delay(frameRate - tpsEcoule);
        }
    }
}
