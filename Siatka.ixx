export module M_Siatka;
export import M_Kratka;
export import <vector>;

export class Siatka
{
public:
    size_t w;
    size_t h;
    size_t kr_w;
    size_t kr_h;
    std::vector<std::vector<Kratka>> pole;

public:
    Siatka(){}
    Siatka(size_t _w, size_t _h, size_t _kr_w, size_t _kr_h) :w(_w), h(_h), kr_w(_kr_w), kr_h(_kr_h) {}

    void set(size_t _w, size_t _h, size_t _kr_w, size_t _kr_h)
    {
        w = _w; 
        h = _h; 
        kr_w = _kr_w; 
        kr_h = _kr_h;
    }

    void init(int _typ_siatki)
    {
        for (int i = 0; i < h/kr_h; i++)
        {
            size_t cordY = i * kr_h;
            pole.push_back(std::vector<Kratka>());
            for (size_t j = 0; j < w; j+=kr_w)
            {
                pole[i].push_back(Kratka(j,cordY,kr_w,kr_h, _typ_siatki));
            }
        }
    }

    void show(SDL_Renderer* rend)
    {
        for (std::vector<Kratka> vect1D : pole)
        {
            for (Kratka x : vect1D)
            {
                x.show(rend);
            }
        }
    }
    
};