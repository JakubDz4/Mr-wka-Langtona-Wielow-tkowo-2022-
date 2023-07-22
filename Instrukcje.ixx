export module M_Instrukcje;
import <vector>;

/// <summary>
/// plik: 
/// $ type new_type obr
/// # x , y dla kierunek = 0 
/// # x , y dla kierunek = 1 
/// # x , y dla kierunek = 2 
/// # x , y dla kierunek = 3 
/// # - zaczyna sie nowy alg
/// </summary>


export struct vec2d
{
	int x, y;
	vec2d(int _x, int _y) : x(_x), y(_y) {}

	void set(int a, int b)
	{
		x = a;
		y = b;
	}
};

export struct Instrukcje
{
	std::vector<vec2d> vec;
	int obr, type, new_type;
	Instrukcje( int t, int nt, int o): obr(o), type(t), new_type(nt) {}
};