#include "vocabulary.hpp"

class t_text: public t_command_base {
	t_vocabulary voc;

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
		// TODO finish settings

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
