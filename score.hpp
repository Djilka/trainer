
class t_score {
	t_count s_min = 0, s_max = 100;
	t_scores score;
public:
	void add(t_dict *dict)
	{
		int s = !dict->count ? 0 : dict->mean * 100 / dict->count;
		s = s < s_min ? s_min : s >= s_max ? s_max - 1 : s;
		score[s].push_back(dict);
	}

	void sort_score(tm_token token)
	{
		for (int i = s_min; i < s_max; i++) {
			sort(score[i].begin(), score[i].end(),
				[&token](tp_dict i, tp_dict j)
				{
					return token[i->word] < token[j->word];
				});
		}
	}

	void init(t_dicts dicts, tm_token token)
	{
		for (int i = 0; i < dicts.size(); i++)
			add(&dicts[i]);
		sort_score(token);
	}

	void update(tm_token token)
	{
		for (int i = s_min; i < s_max; i++) {
			tpi_dicts it = score[i].begin();
			while (it != score[i].end()) {
				int s = !(*it)->count ? 0 : (*it)->mean * 100 / (*it)->count;
				s = s < s_min ? s_min : s >= s_max ? s_max - 1 : s;
				if (s != i) {
					score[s].push_back(*it);
					it = score[i].erase(it);
				} else
					it++;
			}
		}
		sort_score(token);
	}

	tp_dicts train(int count)
	{
		tp_dicts dicts;
		for (int i = s_min + 1; i < s_max && count; i++) {
			for (int j = 0; j < score[i].size() && count; j++) {
				dicts.push_back(score[i][j]);
				count--;
			}
		}
		return dicts;
	}

	tp_dicts learn(int count)
	{
		tp_dicts dicts;
		for (int j = 0; j < score[s_min].size() && count; j++) {
			dicts.push_back(score[0][j]);
			count--;
		}
		return dicts;
	}
};