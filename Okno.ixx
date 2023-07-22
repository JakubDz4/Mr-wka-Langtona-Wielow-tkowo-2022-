module;
#include<SDL.h>
export module M_Okno;
import M_Siatka;
import M_Algorytm;
import M_Mrowka;
import M_File;
import M_Regex;
import M_Opcje;
import <thread>;

static std::binary_semaphore semafor(1);

export class Okno
{
    Siatka* S1;
    Opcje kontener_opcje;
    std::vector<Algorytm> alg;
    std::vector<Mrowka> mrowka;
    std::vector<std::thread> thr;
    kolor4i kol_nast_mr;
    
    SDL_Window* window;
    SDL_Event event;
    SDL_Renderer* renderer; 

public:

    Okno()
    {
        S1 = new Siatka();
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError());
            exit(0);
        }
    }

    ~Okno()
    {
        if(S1!=nullptr)
        delete S1;
        if(renderer!=nullptr)
        SDL_DestroyRenderer(renderer);
        if (window != nullptr)
        SDL_DestroyWindow(window);

        SDL_Quit();
    }

    bool init()
    {
        kontener_opcje.init();

        kol_nast_mr.r = 255;

        const size_t kratka_w = kontener_opcje.real_screen_w / kontener_opcje.liczba_kr_w;
        const size_t kratka_h = kontener_opcje.real_screen_h / kontener_opcje.liczba_kr_w;

        window = SDL_CreateWindow("PK4_Projekt_Jakub_Dzadz_Mrowka_langtona", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            kontener_opcje.real_screen_w + kratka_w + kratka_w, kontener_opcje.real_screen_h, SDL_WINDOW_RESIZABLE);

        if (NULL == window)
        {
            std::cout << "blad" << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        S1->set(kontener_opcje.real_screen_w, kontener_opcje.real_screen_h, kratka_w, kratka_h);

        S1->init(kontener_opcje.typ_siatki);

        std::vector<std::string> vec = get_instr(get_path(kontener_opcje.nazwa_pliku));
        for (int i = 0; i < vec.size(); i++)
            alg.push_back(Algorytm(vec[i]));
        if (!alg.size())
        {
            std::cout << "brak wybranego algorytmu!";
            return false;
        }
        return true;
    }

    void run_mrow(int el)
    {
        mrowka[el].move(semafor);
    }

    void render_all(SDL_Renderer* renderer,const int &tmp, const int &tmp2, kolor4i &kol_opcji_mr)
    {
        S1->show(renderer);
        for (auto& mr : mrowka)
            mr.show(renderer);

        SDL_Rect rect;
        rect.x = tmp;
        rect.y = 0;
        rect.w = tmp2;
        rect.h = kontener_opcje.real_screen_h;

        SDL_Rect rect2;
        rect2.x = tmp;
        rect2.y = tmp2;
        rect2.w = tmp2;
        rect2.h = tmp2;

        SDL_SetRenderDrawColor(renderer, kol_nast_mr.r, kol_nast_mr.g, kol_nast_mr.b, kol_nast_mr.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, kol_opcji_mr.r, kol_opcji_mr.g, kol_opcji_mr.b, kol_opcji_mr.a);
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);
    }

    void run()
    {
        const int tmp = kontener_opcje.real_screen_w + (kontener_opcje.real_screen_w / kontener_opcje.liczba_kr_w) / 2;
        const int tmp2 = kontener_opcje.real_screen_w / kontener_opcje.liczba_kr_w;
        unsigned char option = 0;
        int winx, winy, alg_num=0;
        float scalex = 1, scaley = 1;

        SDL_GetWindowSize(window, &winx, &winy);

        kolor4i kol_opcji_mr(255, 0, 0, 255);
        while (true)
        {
            ///event handler
            if (SDL_PollEvent(&event))
            {
                if (SDL_QUIT == event.type)
                {
                    break;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_a:
                        kol_opcji_mr.option(option, -255);
                        option--;
                        kol_opcji_mr.option(option, 255);
                        break;

                    case SDLK_d:
                        kol_opcji_mr.option(option, -255);
                        option++;
                        kol_opcji_mr.option(option, 255);
                        break;

                    case SDLK_w:
                        kol_nast_mr.option(option, 10);
                        break;

                    case SDLK_s:
                        kol_nast_mr.option(option, -10);
                        break;
                    default:
                        alg_num++;
                        if (alg_num == alg.size())
                            alg_num = 0;
                    }
                    kol_opcji_mr.a = 255;
                    std::cout << (int)kol_nast_mr.r <<" " << (int)kol_nast_mr.g << " " << (int)kol_nast_mr.b << " " << (int)kol_nast_mr.a << std::endl;
                }
                else if (SDL_MOUSEBUTTONDOWN == event.type)
                {
                    int xMouse, yMouse;
                    SDL_GetMouseState(&xMouse, &yMouse);
                    xMouse/= scalex;
                    yMouse/= scaley;

                    for (int i = 0; i < S1->pole.size(); i++)
                    {
                        for (int j = 0; j < S1->pole[i].size(); j++)
                        {
                            if(S1->pole[i][j].x< xMouse && S1->pole[i][j].x + S1->pole[i][j].w > xMouse &&
                                S1->pole[i][j].y < yMouse && S1->pole[i][j].y + S1->pole[i][j].h > yMouse)
                            {
                                mrowka.push_back(Mrowka(&alg[alg_num], &S1->pole[i][j], S1, kol_nast_mr.r, kol_nast_mr.g, kol_nast_mr.b, kol_nast_mr.a));
                                thr.resize(mrowka.size());
                            }
                        }
                    }

                }
                else if (event.window.event == SDL_WINDOWEVENT_RESIZED) 
                {
                    int newx, newy;
                    SDL_GetWindowSize(window, &newx, &newy);
                    scalex = static_cast<float>(newx) / static_cast<float>(winx);
                    scaley = static_cast<float>(newy) / static_cast<float>(winy);
                    SDL_RenderSetScale(renderer, scalex, scaley);

                }
            }
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            for (int i = 0; i < thr.size(); i++)
                thr[i] = std::thread(&Okno::run_mrow, this, i);     //(Mrowka::move, mrowka[i]);//(&Okno::run_mrow, this);

            for (auto& t : thr) 
                t.join();

            render_all(renderer, tmp, tmp2, kol_opcji_mr);

            SDL_Delay(2);
        }
    }

    void menu()
    {
        while (true)
        {
            int x;
            system("cls");
            std::cout << "[1] Uruchom" << std::endl;
            std::cout << "[2] Opcje" << std::endl;
            std::cout << "[3] Wyjscie" << std::endl;
            std::cin >> x;
            if (x == 1)
            {
                if(init())
                run();
                break;
            }
            else if (x == 2)
            {
                kontener_opcje.opcje();
            }
            else break;
        }
    }
};