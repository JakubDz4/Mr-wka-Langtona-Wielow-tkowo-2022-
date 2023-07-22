export module M_Algorytm;
import M_Instrukcje;
import <vector>;
import <sstream>;

export class Algorytm
{
	int x, y;
	std::vector<Instrukcje> instr;

public:

	Algorytm(std::string file)
	{
		std::stringstream s;
		s.str(file);
		int data[3];
		while (!s.eof())
		{

			for (int i = 0; i < 3; i++)
				s >> data[i];

			instr.push_back(Instrukcje(data[0], data[1], data[2]));

			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 2; i++)
					s >> data[i];

				instr[instr.size() - 1].vec.push_back(vec2d(data[0], data[1]));
			}

		}
	}

	void check_kier(int &x)
	{
		if (x < 0)
		{
			x = 360 + x;
		}
		else if (x >= 360)
		{
			x %= 360;
		}
	}

	void zwroc_move(int &type, int &kierunek)
	{
		x = 0; y = 0;
		type = instr[type].new_type;
		kierunek += instr[type].obr;
		check_kier(kierunek);
		int num = kierunek / 90;
		x = instr[type].vec[num].x;
		y = instr[type].vec[num].y;
	}

	int get_x()
	{
		return x;
	}

	int get_y()
	{
		return y;
	}
};



