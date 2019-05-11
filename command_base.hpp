#include "types.hpp"

class t_command_base {
protected:
	typedef void (*t_fun)();
public:
	typedef map<t_string, t_fun> t_map;
protected:
	typedef pair<t_string, t_fun> t_pair;
	typedef t_map::iterator t_iter;

	static
	void exit()
	{
		is_exit = true;
	}

	void help()
	{
		cout << "help:\n";
		for (t_iter it = cmd_fun.begin(); it != cmd_fun.end(); ++it)
			cout << "\t" << it->first << '\n';
	}

	static bool is_exit;
	t_map cmd_fun;
public:
	t_command_base()
	{
		cmd_fun["exit"] = &this->exit;
	}

	void run()
	{
		is_exit = false;
		t_string cmd;

		while (!is_exit) {
			cout << "#";
			cin >> cmd;

			t_iter it= cmd_fun.find(cmd);
			if (it != cmd_fun.end())
				it->second();
			else
				help();
		}
		is_exit = false;
	}
};

bool t_command_base::is_exit = false;
