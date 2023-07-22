export module M_Regex;
import <iostream>;
import <regex>;
import <fstream>;

export std::vector<std::string> get_instr(std::string path)
{
	std::ifstream plik;
	plik.open(path);
	std::string s,tmp;
	if (!plik.good())
	{
		std::cout << "brak pliku: " << path << std::endl;
		exit(0);
	}
	while (!plik.eof())
	{
		getline(plik, tmp);
		s += tmp+"\n";
	}

	plik.close();

	std::vector<std::string> vec;
	std::regex reg("(\\d \\d -?\\d\\d?\\d?\\s(-?\\d -?\\d\\s){4})+||#");
	std::smatch m;
	for (auto i = std::sregex_iterator(s.begin(), s.end(), reg); i != std::sregex_iterator(); i++)
	{
		if((*i)[0]!="" && (*i)[0]!="#")
		vec.push_back((*i)[0]);
	}

	return vec;
}