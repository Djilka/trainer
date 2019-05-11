
class t_text: public t_command_base {
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
public:
	t_text()
	{
		cmd_fun["setting"] = &this->setting;
		cmd_fun["view"] = &this->view;
		cmd_fun["add"] = &this->add;
		cmd_fun["merge"] = &this->merge;
		cmd_fun["remove"] = &this->remove;
		cmd_fun["train"] = &this->train;
	}
};
