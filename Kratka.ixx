module;
#include<SDL.h>
export module M_Kratka;
export import <iostream>;
import Kolor_wyglad;

export class Kratka
{
    size_t x;
    size_t y;
    size_t w;
    size_t h;
    int type;
    kolor4i kolor;

public:

    Kratka(size_t _x, size_t _y, size_t _w, size_t _h, int _t) :x(_x), y(_y), w(_w), h(_h), type(_t), kolor(type)
    {
    }

    void ustaw_kolor(kolor4i& k)
    {
        kolor.set(k);
        if (type)
            kolor.a = 128;
        else kolor.a = 255;
    }

    void show(SDL_Renderer* rend)
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;

        SDL_SetRenderDrawColor(rend, kolor.r, kolor.g, kolor.b, kolor.a);
        SDL_RenderFillRect(rend, &rect);
    }

    friend class Mrowka;
    friend class Okno;
};