#include "Texture.h"

Texture::Texture() : m_id(0), m_fichierImage("")
{

}

Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage)
{

}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

bool Texture::charger()
{
    SDL_Surface *imageSDL = IMG_Load(m_fichierImage.c_str());

    if(imageSDL == 0)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return false;
    }

    SDL_Surface *imageInversee = inverserPixels(imageSDL);
    SDL_FreeSurface(imageSDL);

    if(glIsTexture(m_id) == GL_TRUE)
    {
        glDeleteTextures(1, &m_id);
    }

    glGenTextures(1, &m_id);

    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum formatInterne(0);
    GLenum format(0);

    if(imageInversee->format->BytesPerPixel == 3)
    {
        formatInterne = GL_RGB;

        if(imageInversee->format->Rmask == 0xff)
            format = GL_RGB;

        else
            format = GL_BGR;
    }

    else if(imageInversee->format->BytesPerPixel == 4)
    {
        formatInterne = GL_RGBA;

        if(imageInversee->format->Rmask == 0xff)
            format = GL_RGBA;

        else
            format = GL_BGRA;
    }

    else
    {
        std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
        SDL_FreeSurface(imageInversee);

        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(imageInversee);
    return true;
}


GLuint Texture::getID() const
{
    return m_id;
}


void Texture::setFichierImage(const std::string &fichierImage)
{
    m_fichierImage = fichierImage;
}

SDL_Surface* Texture::inverserPixels(SDL_Surface *imageSource) const
{
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
                                                         imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);

    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;

    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }

    return imageInversee;
}


Texture& Texture::operator=(Texture const &textureACopier)
{
    m_fichierImage = textureACopier.m_fichierImage;
    charger();

    return *this;
}
