
#include "./libasm.h"
#include "./main.h"

# define PRINT_RESULT_EXT(is_valid, error_val, error_template, ...) \
	do { \
		if (is_valid) \
			fprintf(stderr, "\t[\e[92mOK]\e[0m"); \
		else \
		{ \
			fprintf(stderr, "\t[\e[91mFAILED]\e[0m"); \
			*error_val = false; \
		} \
		fprintf(stderr, " (" error_template ")\n", ##__VA_ARGS__); \
	} while (0);
# define PRINT_RESULT(is_valid, error_val) \
	do { \
		if (is_valid) \
			fprintf(stderr, "\t[\e[92mOK]\e[0m\n"); \
		else \
		{ \
			fprintf(stderr, "\t[\e[91mFAILED]\e[0m\n"); \
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
		fprintf(stderr, "[%d]: \"%s\" ->\n", i, strings[i]);
		PRINT_RESULT_EXT(
			strlen(strings[i]) == curr_value, &result,
			"expected %lu, got %lu", strlen(strings[i]), curr_value
		);
	}
	fprintf(stderr, "[%d]: NULL ->\n", i);
	curr_value = ft_strlen(NULL);
	PRINT_RESULT_EXT(
		curr_value == 0, &result,
		"expected 0, got %lu", curr_value
	);
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
		fprintf(stderr, "[%d]: \"%s\" ->\n", i, inputs[i]);
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
		fprintf(stderr, "[%d]: \"%s\" <-> \"%s\" ->\n", i, base, inputs[i]);
		value = ft_strcmp(base, inputs[i]);
		PRINT_RESULT_EXT(value == strcmp(base, inputs[i]), &result,
			"expected %d, got %d", strcmp(base, inputs[i]), value
		);
	}
	return (true);
}

typedef struct s_write_test
{
	int			fd;
	const char	*buf;
	size_t		count;

	ssize_t		expected;
}	t_write_test;

bool	test_write(void)
{
	const t_write_test	tests[] = {
		{1, "test", 4, 4}, {2, "err_test", 8, 8}, {69, "bad_test", 8, -1}
	};
	const int			tot_size = sizeof(tests) / sizeof(tests[0]);
	bool				result;
	ssize_t				curr;
	int					i;

	errno = 0;
	result = true;
	i = -1;
	while (++i < tot_size)
	{
		fprintf(stderr, "[%d]: write(%d, \"%s\", %zu) ->\n", i,
			tests[i].fd, tests[i].buf, tests[i].count
		);
		curr = ft_write(tests[i].fd, tests[i].buf, tests[i].count);
		PRINT_RESULT_EXT(curr == tests[i].expected, &result,
			"expected %zu, got %zd", tests[i].expected, curr
		);
		fprintf(stderr, "\t\tCurrent errno = %d\n", errno);
		perror("\t\tCurrent errno message");
	}
	return (result);
}

bool	test_read(void)
{
	int		curr;
	char	buf[1024];
	bool	result;

	errno = 0;
	result = true;
	fprintf(stderr, "[0]: read(STDIN_FILENO, buf, sizeof(buf))\nManual input:");
	curr = ft_read(STDIN_FILENO, buf, sizeof(buf));
	buf[curr] = '\0';
	fprintf(stderr, "Got \"%s\" - ", buf);
	PRINT_RESULT_EXT(curr == strlen(buf), &result,
		"expected %lu, got %d", strlen(buf), curr
	);
	curr = ft_read(666, buf, sizeof(buf));
	PRINT_RESULT_EXT(curr == -1, &result,
		"expected -1, got %d", curr
	);
	fprintf(stderr, "\terrno = %d", errno);
	perror("\tperror_value");
	return (result);
}

bool	test_strdup(void)
{
	char	*curr;
	const char	*inputs[] = {
		"", "test", "test2", NULL
	};
	bool	result;
	int		i;

	errno = 0;
	result = true;
	i = -1;
	while (inputs[++i])
	{
		fprintf(stderr, "[%d]: ft_strdup(\"%s\") ->\n", i, inputs[i]);
		curr = ft_strdup(inputs[i]);
		PRINT_RESULT_EXT(curr != NULL, &result,
			"expected non-NULL, got \"%s\"", curr
		);
		PRINT_RESULT_EXT(!strcmp(curr, inputs[i]), &result,
			"expected \"%s\", got \"%s\"", inputs[i], curr
		);
		free(curr);
	}
	fprintf(stderr, "[%d]: ft_strdup(NULL) -> ", i);
	curr = ft_strdup(NULL);
	PRINT_RESULT_EXT(curr == NULL, &result,
		"expected NULL, got non-NULL"
	);
	free(curr);
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
	t_list			**all_addresses;
	t_list			*list;
	int				i;
	bool			result;

	result = true;
	list = NULL;
	all_addresses = NULL;
	for (i = 0; i < 10; i++)
	{
		ft_list_push_front(&list, (void *)i);
		all_addresses = realloc(all_addresses, sizeof(t_list *) * (i + 1));
		all_addresses[i] = list;

		bool	is_addr_ok = true;
		bool	is_data_ok = true;
		t_list	*curr = list;
		int j = 0;
		for ( ; j <= i; j++)
		{
			is_addr_ok = all_addresses[i - j] == curr;
			is_data_ok = curr && curr->data == (void *) i - j;
			if (!is_addr_ok || !is_data_ok)
			{
				result = false;
				break;
			}
			curr = curr->next;
		}
		fprintf(stderr, "[%d]: %d nodes\n", i, i + 1);
		PRINT_RESULT_EXT(is_addr_ok && is_data_ok, &result,
			"expected head to be %p (data: %p), got %p (data: %p)\t[ADDR: %s, DATA: %s]. j=%d",
			all_addresses[i], i, list, list ? list->data : NULL, 
			is_addr_ok ? "OK" : "FAILED",
			is_data_ok ? "OK" : "FAILED",
			j
		);
	}
	return (true);
}

bool	test_list_size(void)
{
	t_list	*list;
	t_list	*last;
	t_list	*node;
	bool	result;
	int		curr;

	result = true;
	last = NULL;
	list = NULL;
	for (int i = 0; i < 10; i++){
		node = calloc(1, sizeof(t_list));
		node->data = (void *)i;
		if (last){
			last->next = node;
		}
		if (!list){
			list = node;
		}
		last = node;
		fprintf(stderr, "[%d]: %d nodes\n", i, i + 1);
		curr = ft_list_size(list);
		PRINT_RESULT_EXT(curr == i + 1, &result,
			"expected %d, got %d", i + 1, curr
		);
	}
	return (result);
}

t_cmp_fn	foo(const void *a, const void *b)
{
	return (a - b);
}

bool	test_list_sort(void)
{
	const int		values[] = {5, 4, 2, 1, 0};
	const int		tot_size = sizeof(values) / sizeof(values[0]);
	t_list			*list;
	t_list			*last;
	t_list			*node;
	t_cmp_fn		*function;
	bool			result;

	result = true;
	list = NULL;
	last = NULL;
	int i;
	for (i = 0; i < tot_size; i++)
	{
		node = calloc(1, sizeof(t_list));
		node->data = (void *)values[i];
		if (last)
			last->next = node;
		if (!list)
			list = node;
		last = node;
	}
	function = foo;
	ft_list_sort(&list, function);

	fprintf(stderr, "[0]: {");
	for (int i = 0; i < 10; i++){
		fprintf(stderr, "%d", values[i]);
		if (i < 9)
		fprintf(stderr, ", ");
	}
	fprintf(stderr, "}\n");

	int prev = (int)list->data;
	bool is_ok = true;
	t_list *curr = list;
	for (int i = 0; i < 10; i++){
		int value = (int)curr->data;
		is_ok = value >= prev;
		prev = value;
		curr = curr->next;

	}
	PRINT_RESULT_EXT(is_ok, &result,
		"Expected list to be sorted, got unsorted"
	);
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
			fprintf(stderr, "Press ENTER to continue...");
			getchar();
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
