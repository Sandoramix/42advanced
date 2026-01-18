
#include "./libasm.h"
#include "./main.h"



// MANDATORY TESTS--------------------------------------------------------------
bool	test_strlen(void)
{
	const char	*strings[] = {
		"", "test", NULL
	};
	int			i;
	bool		result;
	size_t		curr_value;

	i = -1;
	result = true;
	while (strings[++i])
	{
		curr_value = ft_strlen(strings[i]);
		printf("[%d]: \"%s\" - ", i, strings[i]);
		if (strlen(strings[i]) != curr_value)
		{
			result = false;
			printf("\e[[91mFAILED\e[[0m"
				"(expected %lu, got %lu)\n", strlen(strings[i]), curr_value);
		}
		else
			printf("\e[[92mOK\e[[0m\n");
	}
	return (result);
}

bool	test_strcpy(void)
{
	return (true);
}

bool	test_strcmp(void)
{
	return (true);
}

bool	test_write(void)
{
	return (true);
}

bool	test_read(void)
{
	return (true);
}

bool	test_strdup(void)
{
	return (true);
}



//------------------------------------------------------------------------------

// BONUS TESTS------------------------------------------------------------------

bool	test_atoi_base(void)
{
	return (true);
}

bool	test_list_push_front(void)
{
	return (true);
}

bool	test_list_size(void)
{
	return (true);
}

bool	test_list_sort(void)
{
	return (true);
}

bool	test_list_remove_if(void)
{
	return (true);
}


//------------------------------------------------------------------------------

static const char		*g_all_fn_names[] = {
	FT_STRLEN, FT_STRCPY, FT_STRCMP, FT_WRITE, FT_READ, FT_STRDUP,
	FT_ATOI_BASE, FT_LIST_PUSH_FRONT, FT_LIST_SIZE, FT_LIST_SORT,
	FT_LIST_REMOVE_IF
};

static const t_fn_ref	g_all_fn_refs[] = {
	test_strlen, test_strcpy, test_strcmp, test_write, test_read, test_strdup,
	test_atoi_base, test_list_push_front, test_list_size, test_list_sort,
	test_list_remove_if
};


static int	run_case(char *s)
{
	const int	tot_size = sizeof(g_all_fn_names) / sizeof(g_all_fn_names[0]);
	bool		fail;
	int			i;
	bool		found;

	found = false;
	fail = false;
	i = -1;
	while (g_all_fn_names[++i])
	{
		if (!s || !strcmp(s, g_all_fn_names[i]))
		{
			fail |= !(g_all_fn_refs[i])();
			found = true;
		}
	}
	if (!found)
	{
		write(2, "Invalid argument ", 17);
		write(2, s, strlen(s));
		write(2, " provided. Provide a valid name.\n", 33);
	}
	return (fail);
}

int	main(int argc, char **argv)
{
	int	i;
	int	result;

	if (argc == 1)
		return (run_case(NULL));
	i = 0;
	result = 0;
	while (++i < argc)
	{
		result = run_case(argv[i]);
	}
	return (result);
}
