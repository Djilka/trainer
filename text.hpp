#include "vocabulary.hpp"
#include "translation.hpp"

#include "path.hpp"

class t_text: public t_command_base {
	static t_vocabulary voc;
	static t_string dir;

	static
	void view()
	{
		cout << "view:\n";
		t_path path;
		t_strings names = path.names(dir);
		for (t_string name : names)
			cout << name << "\n";
	}

	static
	void init()
	{
		cout << "init:\n";

	}

	static
	void load()
	{
		cout << "load:\n";

	}

	static
	void save()
	{
		cout << "save:\n";

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
		cmd_fun["init"] = &this->init;
		cmd_fun["load"] = &this->load;
		cmd_fun["save"] = &this->save;
		cmd_fun["merge"] = &this->merge;
		cmd_fun["remove"] = &this->remove;
		cmd_fun["train"] = &this->train;
	}
};

t_string t_text::dir = "./voc";
t_vocabulary t_text::voc;
