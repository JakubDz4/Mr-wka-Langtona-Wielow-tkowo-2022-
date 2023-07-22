export module M_File;
import <filesystem>;
import <iostream>;

namespace fs = std::filesystem;

export std::string get_path(std::string name)
{
	fs::path p = fs::current_path();

	for (const fs::directory_entry& dir_entry : fs::recursive_directory_iterator(p))
	{
		if (fs::path(dir_entry).stem() == name)
		{
			return fs::path(dir_entry).parent_path().string() + "\\" + fs::path(dir_entry).filename().string();;
		}
	}
}