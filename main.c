
#include "./libasm.h"
#include "./main.h"

# define PRINT_RESULT_EXT(is_valid, error_val, error_template, ...) \
	do { \
		if (is_valid) \
			printf("[\e[92mOK]\e[0m"); \
		else \
		{ \
			printf("[\e[91mFAILED]\e[0m"); \
			*error_val = false; \
		} \
		printf(" (" error_template ")\n", ##__VA_ARGS__); \
	} while (0);
# define PRINT_RESULT(is_valid, error_val) \
	do { \
		if (is_valid) \
			printf("[\e[92mOK]\e[0m\n"); \
		else \
		{ \
			printf("[\e[91mFAILED]\e[0m\n"); \
			*error_val = false; \
		} \
	} while (0);

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
		PRINT_RESULT_EXT(
			strlen(strings[i]) == curr_value, &result,
			"expected %lu, got %lu", strlen(strings[i]), curr_value
		);
	}
	return (result);
}

bool	test_strcpy(void)
{
	char		dst[100] = {0};
	const char	*inputs[] = {
		"", "test", "test2", NULL
	};
	int			i;
	bool		result;

	i = -1;
	result = true;
	while (inputs[++i])
	{
		printf("[%d]: \"%s\" -> ", i, inputs[i]);
		ft_strcpy(dst, inputs[i]);
		PRINT_RESULT_EXT(!strcmp(dst, inputs[i]), &result,
			"expected \"%s\", got \"%s\"", inputs[i], dst
		);
	}

	return (true);
}

bool	test_strcmp(void)
{
	const char	*inputs[] = {
		"", "test", "test2", NULL
	};
	const char	*base = "test";
	int			i;
	bool		result;
	int			value;

	i = -1;
	result = true;
	while (inputs[++i])
	{
		printf("[%d]: \"%s\" <-> \"%s\" - ", i, base, inputs[i]);
		value = ft_strcmp(base, inputs[i]);

		PRINT_RESULT_EXT(value == strcmp(base, inputs[i]), &result,
			"expected %d, got %d", strcmp(base, inputs[i]), value
		);
	}
	return (true);
}

bool	test_write(void)
{
	bool	result;
	ssize_t	curr;

	result = true;
	fprintf(stderr, "[0]: write(1, \"test\", 4) - ");
	curr = ft_write(1, "test", 4);
	PRINT_RESULT_EXT(curr == 4, &result,
		"expected 4, got %zd", ft_write(1, "test", 4)
	);
	fprintf(stderr, "[1]: write(1, \"test\", 5) - ");
	curr = ft_write(1, "test", 5);
	PRINT_RESULT_EXT(curr == 5, &result,
		"expected -1, got %zd", curr
	);
	fprintf(stderr, "[2]: write(69, \"test\", 4) - ");
	curr = ft_write(69, "test", 4);
	PRINT_RESULT_EXT(curr == -1, &result,
		"expected -1, got %zd", curr
	);
	fprintf(stderr, "\terrno = %d", errno);
	perror("\tperror_value");
	return (result);
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
	while (++i < tot_size)
	{
		if (!s || !strcmp(s, g_all_fn_names[i]))
		{
			printf("Running test: %s\n", g_all_fn_names[i]);
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
