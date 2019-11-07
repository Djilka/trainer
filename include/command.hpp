#include "command_base.hpp"
#include "text.hpp"

class t_command: public t_command_base {
	static
	void text()
	{
		cout << "text:\n";
		t_text text;
		text.run();
	}

	static
	void setting()
	{
		cout << "setting:\n";

	}
public:
	t_command()
	{
		cmd_fun["text"] = &this->text;
		cmd_fun["setting"] = &this->setting;
	}
};
