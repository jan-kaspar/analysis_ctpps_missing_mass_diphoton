int LoadInputFiles(const string &input_fn, int min_idx, int max_idx, vector<string> &input_files)
{
	input_files.clear();

	// load file
	FILE *f_in = fopen(input_fn.c_str(), "r");
	if (f_in == NULL)
	{
		printf("ERROR in LoadInputFiles > file '%s' can't be loaded.\n", input_fn.c_str());
		return 1;
	}

	vector<string> input_files_full;
	while (!feof(f_in))
	{
		char buf[300];
		int ret = fscanf(f_in, "%s", buf);

		if (ret == 1)
			input_files_full.push_back(buf);
	}

	fclose(f_in);

	// adjust limits
	if (min_idx < 0)
		min_idx = 0;

	signed int size = input_files_full.size();
	if (max_idx < 0 || max_idx >= size)
		max_idx = input_files_full.size() - 1;

	// copy selected range
	for (int i = min_idx; i <= max_idx; i++)
		input_files.push_back(input_files_full[i]);

	return 0;
}
