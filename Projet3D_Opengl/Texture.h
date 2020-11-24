#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
    public:
        Texture();
        Texture(std::string fichierImage);
        ~Texture();
        bool charger();
        GLuint getID() const;
        void setFichierImage(const std::string &fichierImage);
        SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;
        Texture(Texture const &textureACopier);
        Texture& operator=(Texture const &textureACopier);


    private:
        GLuint m_id;
        std::string m_fichierImage;
};

#endif // TEXTURE_H_INCLUDED
