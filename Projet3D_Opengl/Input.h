#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL2/SDL.h>

class Input
{
    public:
       Input();
       ~Input();
       void updateEvenements();
       bool terminer() const;
       bool getTouche(const SDL_Scancode touche) const;
       bool getBoutonSouris(const Uint8 bouton) const;
       bool mouvementSouris() const;
       void afficherPointeur(bool reponse) const;
       void capturerPointeur(bool reponse) const;

        int getX() const;
        int getY() const;

        int getXRel() const;
        int getYRel() const;

    private:
        SDL_Event m_event;
        bool m_touches[SDL_NUM_SCANCODES];
        bool m_boutonsSouris[8];

        int m_x;
        int m_y;
        int m_xRel;
        int m_yRel;

        bool m_terminer;
};

#endif // INPUT_H_INCLUDED
