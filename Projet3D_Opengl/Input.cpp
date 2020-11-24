#include "Input.h"

Input::Input() : m_x(0), m_y(0), m_xRel(0), m_yRel(0), m_terminer(false)
{
    for(int i(0); i < SDL_NUM_SCANCODES; i++)
        m_touches[i] = false;

    for(int i(0); i < 8; i++)
        m_boutonsSouris[i] = false;
}

Input::~Input()
{

}

void Input::updateEvenements()
{
    m_xRel = 0;
    m_yRel = 0;

    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
            case SDL_KEYDOWN:
                m_touches[m_event.key.keysym.scancode] = true;
            break;

            case SDL_KEYUP:
                m_touches[m_event.key.keysym.scancode] = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                m_boutonsSouris[m_event.button.button] = true;
                break;

            case SDL_MOUSEBUTTONUP:
                m_boutonsSouris[m_event.button.button] = false;
                break;

            case SDL_MOUSEMOTION:
                m_x = m_event.motion.x;
                m_y = m_event.motion.y;

                m_xRel = m_event.motion.xrel;
                m_yRel = m_event.motion.yrel;
                break;


            case SDL_WINDOWEVENT:
                if(m_event.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_terminer = true;
                break;


            default:
                break;
        }
    }
}

bool Input::terminer() const
{
    return m_terminer;
}

bool Input::getTouche(const SDL_Scancode touche) const
{
    return m_touches[touche];
}

bool Input::getBoutonSouris(const Uint8 bouton) const
{
    return m_boutonsSouris[bouton];
}

bool Input::mouvementSouris() const
{
    if(m_xRel == 0 && m_yRel == 0)
        return false;

    else
        return true;
}

int Input::getX() const
{
    return m_x;
}

int Input::getY() const
{
    return m_y;
}

int Input::getXRel() const
{
    return m_xRel;
}

int Input::getYRel() const
{
    return m_yRel;
}

void Input::afficherPointeur(bool reponse) const
{
    if(reponse)
        SDL_ShowCursor(SDL_ENABLE);

    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::capturerPointeur(bool reponse) const
{
    if(reponse)
        SDL_SetRelativeMouseMode(SDL_TRUE);

    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
