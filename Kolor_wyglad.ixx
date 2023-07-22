export module Kolor_wyglad;

export struct kolor4i
{
	unsigned char r, g, b, a;

	kolor4i() : r(0), g(0), b(0), a(255) {}

	kolor4i(int _r,int _g, int _b, int _a): r(_r), g(_g), b(_b), a(_a){}

	kolor4i(int dark)
	{
		if (dark)
		{
			r = 0;
			g = 0;
			b = 0;
			a = 128;
		}
		else
		{
			r = 255;
			g = 255;
			b = 255;
			a = 255;
		}
	}

	kolor4i(const kolor4i& k)
	{
		r = k.r;
		g = k.g;
		b = k.b;
		a = k.a;
	}

	void set(const kolor4i& k)
	{
		r = k.r;
		g = k.g;
		b = k.b;
	}
	void set(char _r, char _g, char _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	void option(int x, int val)
	{
		switch (x%4)
		{
			case 0:
				r += val;
				break;

			case 1:
				g += val;
				break;

			case 2:
				b += val;
				break;

			default:
				a += val;
				break;
		}
	}
};