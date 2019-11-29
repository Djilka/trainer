#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class t_path_base {
public:
	t_strings names(t_string dir_path)
	{
		t_strings name;
		for(auto& p: fs::directory_iterator(dir_path))
			name.push_back(p.path().filename());
		return name;
	}

	void create(t_string dir_path)
	{
		fs::create_directory(dir_path);
	}

	void remove(t_string dir_path)
	{
		fs::remove_all(dir_path);
	}

	bool exist(t_string dir_path)
	{
		return fs::exists(dir_path);
	}
};

class t_path : public t_path_base {
public:
	t_path(){}
	~t_path(){}

	void free_dir(t_string dir_path)
	{
		remove(dir_path);
		create(dir_path);
	}
};
