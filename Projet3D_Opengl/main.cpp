#include "SceneOpenGL.h"


int main(int argc, char *argv[])
{

	SceneOpenGL scene("Application OpenGL 3D", 800, 600);

	if(scene.initialiserFenetre() == false)
    return -1;

	if(scene.initGL() == false)
    return -1;

    scene.bouclePrincipale();

    return 0;
}
