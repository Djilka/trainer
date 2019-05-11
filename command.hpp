#include "types.hpp"
// #include ".hpp"

class t_command {
	bool is_exit = false;

	typedef void (*t_fun)();

	void help()
	{
		cout << "help:\n";

	}
public:
	void run()
	{
		is_exit = false;
		t_string cmd;

		while (!is_exit) {
			cout << "#";
			cin >> cmd;

			if (cmd == "exit")
				is_exit = true;
			else if (cmd == "text") {
				//
			} else if (cmd == "setting") {
				//
			} else {
				help();
			}
		}
	}
};
