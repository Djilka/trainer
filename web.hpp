#include "exec.hpp"

class t_web {
	t_string dir;
public:
	t_web(t_string path)
	{
		dir = path;
	}

	// TODO : clear tmp dir with pages
	~t_web() { }

	void load_page(t_strings words)
	{
		t_exec exec;
		for (string word : words)
			exec.wget(dir, word);
	}
};
