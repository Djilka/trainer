
class t_trainer {
protected:
	t_type_test type = tt_up;
public:
	void run(t_dict *dict)
	{
		t_string str;

		cout << dict->get(type) << ": ";
		cin >> str;

		bool res = dict->check(str, type);
		dict->update(res);

		if (res)
			cout << "right" << "\n\n";
		else {
			cout << "wrong!\ncorrect:\n";
			dict->print(cout);
			cout << "\n";
		}
	}
};

class t_pool : public t_trainer {
public:
	void test(tp_dicts dicts)
	{
		for (tpi_dicts id = dicts.begin() ; id != dicts.end(); ++id)
			run(*id);
	}

	void test_type(t_type_test t)
	{
		type = t;
	}
};
