#include "path.hpp"
#include "vocabulary.hpp"
#include "translation.hpp"


class t_text: public t_command_base {
	static t_vocabulary voc;

	static
	void vocabulary()
	{
		cout << "vocabulary:\n";
		cout << "\t1. save\n";
		cout << "\t2. load\n";
		cout << "\t3. info\n";

		t_string path;
		
		int val = 0;
		cin >> val;
		switch (val) {
		case 1:
			voc.save();
			break;
		case 2:
			cout << "dir: ";
			cin >> path;
			voc.path(path);
			voc.load();
			break;
		case 3:
			voc.info();
			break;
		}
	}

	static
	void word()
	{
		cout << "word:\n";
		cout << "\t1. add\n";
		cout << "\t2. add translation\n";
		cout << "\t3. remove\n";
		cout << "\t4. info\n";

		t_string word;
		t_string tr;
		cin >> word;
		int val = 0;
		cin >> val;
		switch (val) {
		case 1:
			voc.add(t_translation::translate({word}));
			break;
		case 2:
			cin >> tr;
			voc.word_add(word, tr);
			break;
		case 3:
			voc.word_remove(word);
			break;
		case 4:
			voc.word_info(word);
			break;
		}
	}

	static
	void text()
	{
		cout << "text:\n";
		cout << "\t1. parse text\n";
		cout << "\t2. load list's words\n";

		int val = 0;
		cin >> val;

		cout << "path:\n";
		t_string path;
		cin >> path;

		tm_token tokens;

		switch (val) {
		case 1: {
			// load text
			tokens = t_translation::tokens(path);
		} break;
		case 2: {
			// load list's
			t_strings words;
			t_file_r file(path);
			while (file.is_OK()) {
				t_string word;
				file.read(word);
				if (word.size())
					words.push_back(word);
			}
			tokens = token_words(words);
		} break;
		default:
			return;
		}
		voc.add(t_translation::translate(voc.unique(tokens)));
	}

	static
	void train()
	{
		cout << "train:\n";
		cout << "\t1. ru->eng\n";
		cout << "\t2. eng->ru\n";

		int t = 0;
		cin >> t;
		t_type_test type = t == 1 ? tt_up : tt_down;

		cout << "\t1. repeat\n";
		cout << "\t2. learn\n";

		int val = 0;
		cin >> val;
		switch (val) {
		case 1:
			voc.train(count_words, type);
			break;
		case 2:
			voc.learn(count_words, type);
			break;
		default:
			return;
		}
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
		cmd_fun["word"] = &this->word;
		cmd_fun["vocabulary"] = &this->vocabulary;
		cmd_fun["text"] = &this->text;
		cmd_fun["train"] = &this->train;

		voc.path(dir_voc);
		voc.load();
	}

	~t_text()
	{
		voc.save();
	}
};

t_vocabulary t_text::voc;
