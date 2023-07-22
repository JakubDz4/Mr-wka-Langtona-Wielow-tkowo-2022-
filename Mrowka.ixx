module;
#include<SDL.h>
export module M_Mrowka;
import M_Kratka;
import M_Algorytm;
import M_Siatka;
export import <semaphore>;

export class Mrowka//:public Kratka
{
	Siatka* siatka;
	Kratka* pozycja;
	int x, y, kier=0;
	Algorytm* mrowka_alg;
	kolor4i kolor;
	const int limx = siatka->w - siatka->kr_w;
	const int limy = siatka->h - siatka->kr_h;

public:

	Mrowka(Algorytm* alg, Kratka* poz, Siatka* siat, char r = 255, char g = 0, char b = 0, char a = 255) :kolor(r, g, b, a), mrowka_alg(alg),
		pozycja(poz), siatka(siat)
	{
		x = pozycja->x;
		y = pozycja->y;
		pozycja->ustaw_kolor(kolor);
	};

	void move(std::binary_semaphore& semafor)
	{
		mrowka_alg->zwroc_move(pozycja->type, kier);
		
		x += mrowka_alg->get_x() * siatka->kr_w;
		y += mrowka_alg->get_y() * siatka->kr_h;
	
		if (x > limx)
			x %= siatka->w;
		else if (x < 0)
			x = limx;

		if (y > limy)
			y %= siatka->h;
		else if (y < 0)
			y = limy;

		bool find_el = false;

		for (int i=0;i<siatka->pole.size();i++)
		{
			for (int j = 0; j < siatka->pole[i].size(); j++)
			{
				if (siatka->pole[i][j].x == x && siatka->pole[i][j].y == y)
				{
					semafor.acquire();
					find_el = true;
					pozycja->ustaw_kolor(kolor);
					pozycja = &siatka->pole[i][j];
					semafor.release();
					break;
				}
			}
			if (find_el)
			{
				break;
			}
		}


	}

	void show(SDL_Renderer* rend)
	{
		SDL_Rect rect;
		rect.x = pozycja->x;
		rect.y = pozycja->y;
		rect.w = pozycja->w;
		rect.h = pozycja->h;

		SDL_SetRenderDrawColor(rend, kolor.r, kolor.g, kolor.b, kolor.a);
		SDL_RenderFillRect(rend, &rect);
	}
};