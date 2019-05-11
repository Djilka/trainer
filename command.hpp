#include "types.hpp"
// #include ".hpp"

class t_command {
	typedef void (*t_fun)();
public:
	typedef map<t_string, t_fun> t_map;
private:
	typedef pair<t_string, t_fun> t_pair;
	typedef t_map::iterator t_iter;

	static bool is_exit;
	static t_map cmd_fun;

	static
	void exit()
	{
		is_exit = true;
	}

	static
	void help()
	{
		cout << "help:\n";
		for (t_iter it = cmd_fun.begin(); it != cmd_fun.end(); ++it)
			cout << "\t" << it->first << '\n';
	}

	static
	void text()
	{
		cout << "text:\n";

	}

	static
	void setting()
	{
		cout << "setting:\n";

	}
public:
	t_command()
	{
		cmd_fun["exit"] = &this->exit;
		cmd_fun["text"] = &this->text;
		cmd_fun["setting"] = &this->setting;
		cmd_fun["help"] = &this->help;
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
	}
};

bool t_command::is_exit = false;
t_command::t_map t_command::cmd_fun;
