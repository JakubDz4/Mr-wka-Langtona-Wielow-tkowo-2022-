export module M_Opcje;
import <iostream>;

export struct Opcje
{
    size_t screen_w = 640;
    size_t screen_h = 480;
    std::string nazwa_pliku = "alg1";
    size_t liczba_kr_w = 100;
    int typ_siatki = 1; ///czy cala biala czarna losowa etc
    size_t real_screen_w;
    size_t real_screen_h;

    void opcje_print()
    {
        system("cls");
        std::cout << "[1] Szerokosc okna: " << screen_w << std::endl;
        std::cout << "[2] Wysokosc okna: " << screen_h << std::endl;
        std::cout << "[3] Plik z instrukcjami: " << nazwa_pliku << std::endl;
        std::cout << "[4] Liczba kratek w wierszu: " << liczba_kr_w << std::endl;
        std::cout << "[5] Typ siatki: " << typ_siatki << std::endl;
        std::cout << "[6] Wroc" << std::endl;
    }

    void opcje()
    {
        int x = 1;
        while (x)
        {
            opcje_print();
            std::cin >> x;
            switch (x)
            {
            case 1:
            {
                size_t set;
                std::cin >> set;
                screen_w = set;
                break;
            }
            case 2:
            {
                size_t set;
                std::cin >> set;
                screen_h = set;
                break;
            }
            case 3:
            {
                std::string set;
                std::cin >> set;
                nazwa_pliku = set;
                break;
            }
            case 4:
            {
                size_t set;
                std::cin >> set;
                liczba_kr_w = set;
                break;
            }
            case 5:
            {
                int set;
                std::cin >> set;
                typ_siatki = set;
                break;
            }
            default:
            {
                x = 0;
                break;
            }
            }
        }
    }

    void init()
    {
        real_screen_w = screen_w - screen_w % liczba_kr_w;
        real_screen_h = screen_h - screen_h % liczba_kr_w;
    }
};