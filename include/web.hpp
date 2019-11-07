#include "exec.hpp"

class t_web {
public:
	static
	void load(t_string dir, t_strings words)
	{
		t_exec exec;
		for (string word : words)
			exec.wget(dir, word);
	}
};
