
class t_text {
	typedef void (*t_fun)();
public:
	typedef map<t_string, t_fun> t_map;
private:
	typedef pair<t_string, t_fun> t_pair;
	typedef t_map::iterator t_iter;

	static
	void view()
	{
		cout << "view:\n";

	}

	static
	void add()
	{
		cout << "add:\n";

	}

	static
	void merge()
	{
		cout << "merge:\n";

	}

	static
	void remove()
	{
		cout << "remove:\n";

	}

	static
	void train()
	{
		cout << "train:\n";

	}

	static
	void setting()
	{
		cout << "setting:\n";

	}

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

	static bool is_exit;
	static t_map cmd_fun;
public:
	t_text()
	{
		cmd_fun["exit"] = &this->exit;
		cmd_fun["setting"] = &this->setting;
		cmd_fun["help"] = &this->help;
		cmd_fun["view"] = &this->view;
		cmd_fun["add"] = &this->add;
		cmd_fun["merge"] = &this->merge;
		cmd_fun["remove"] = &this->remove;
		cmd_fun["train"] = &this->train;
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

bool t_text::is_exit = false;
t_text::t_map t_text::cmd_fun;
