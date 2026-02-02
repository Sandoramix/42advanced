#include "./libasm.h"
#include "./libasm_bonus.h"
#include "./main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

// ------------------ PRINT HELPERS ------------------

#define PRINT_OK "\e[92mOK\e[0m"
#define PRINT_FAIL "\e[91mFAILED\e[0m"

#define PRINT_RESULT_EXT(cond, flag, fmt, ...) \
	do \
	{ \
		if (cond) \
			fprintf(stderr, "\t[%s] ", PRINT_OK); \
		else \
		{ \
			fprintf(stderr, "\t[%s] ", PRINT_FAIL); \
			*flag = false; \
		} \
		fprintf(stderr, fmt "\n", ##__VA_ARGS__); \
	} while (0)

#define RUN_SUBTEST(desc, cond, flag, fmt, ...) \
	do \
	{ \
		fprintf(stderr, "[%s]:", desc); \
		PRINT_RESULT_EXT(cond, flag, fmt, ##__VA_ARGS__); \
	} while (0)

// ------------------ TEST FUNCTION TYPE ------------------

typedef bool (*t_test_fn)(void);

typedef struct s_test_entry
{
	const char *name;
	t_test_fn fn;
} t_test_entry;

// ------------------ MANDATORY TESTS ------------------

bool	test_strlen(void)
{
	const char	*strings[] = {"", "test", "longer string", NULL};
	bool		result = true;

	for (int i = 0; strings[i]; i++)
	{
		size_t got = ft_strlen(strings[i]);
		RUN_SUBTEST(strings[i], got == strlen(strings[i]), &result,
			"expected %lu, got %lu", strlen(strings[i]), got);
	}
	size_t got = ft_strlen(NULL);
	RUN_SUBTEST("NULL", got == 0, &result, "expected 0, got %lu", got);
	return result;
}

bool	test_strcpy(void)
{
	const char	*inputs[] = {"", "test", "longer string", NULL};
	char		dst[128];
	bool		result = true;

	for (int i = 0; inputs[i]; i++)
	{
		ft_strcpy(dst, inputs[i]);
		RUN_SUBTEST(inputs[i], strcmp(dst, inputs[i]) == 0, &result,
			"expected \"%s\", got \"%s\"", inputs[i], dst);
	}
	return result;
}

bool	test_strcmp(void)
{
	const char	*inputs[] = {"", "test", "test2", NULL};
	const char	*base = "test";
	bool		result = true;

	for (int i = 0; inputs[i]; i++)
	{
		int got = ft_strcmp(base, inputs[i]);
		int expected = strcmp(base, inputs[i]);
		char desc[64];
		snprintf(desc, sizeof(desc), "\"%s\" vs \"%s\"", base, inputs[i]);
		RUN_SUBTEST(desc, got == expected, &result,
			"expected %d, got %d", expected, got);
	}
	return result;
}

bool	test_write(void)
{
	struct
	{
		int fd;
		const char *buf;
		size_t count;
		ssize_t expected;
	}	tests[] = {
		{.fd = 1, .buf = "test", .count = 4, .expected = 4},
		{.fd = 2, .buf = "err_test", .count = 8, .expected = 8},
		{.fd = 69, .buf = "bad_test", .count = 8, .expected = -1},
	};
	bool	result = true;
	for (int i = 0; i < 3; i++)
	{
		errno = 0;
		ssize_t got = ft_write(tests[i].fd, tests[i].buf, tests[i].count);
		char desc[64];
		snprintf(desc, sizeof(desc), "write(fd=%d)", tests[i].fd);
		RUN_SUBTEST(desc, got == tests[i].expected, &result,
			"expected %zd, got %zd (errno=%d)", tests[i].expected, got, errno);
	}
	return result;
}

bool	test_read(void)
{
	char buf[1024];
	bool	result = true;

	// Interactive read
	fprintf(stderr, "[Manual Input] Enter some text:\n");
	errno = 0;
	ssize_t got = ft_read(STDIN_FILENO, buf, sizeof(buf) - 1);
	if (got >= 0)
		buf[got] = '\0';
	RUN_SUBTEST("read(STDIN_FILENO)", got == (ssize_t)strlen(buf), &result,
		"expected %lu, got %zd", strlen(buf), got);
	// Invalid fd
	errno = 0;
	got = ft_read(666, buf, sizeof(buf));
	RUN_SUBTEST("read(invalid_fd)", got == -1, &result,
		"expected -1, got %zd (errno=%d)", got, errno);
	return result;
}

bool	test_strdup(void)
{
	const char	*inputs[] = {"", "test", "longer string", NULL};
	bool		result = true;
	char		*dup;

	for (int i = 0; inputs[i]; i++)
	{
		dup = ft_strdup(inputs[i]);
		RUN_SUBTEST(inputs[i], dup != NULL, &result, "expected non-NULL");
		if (dup)
		{
			RUN_SUBTEST(inputs[i], strcmp(dup, inputs[i]) == 0, &result,
				"expected \"%s\", got \"%s\"", inputs[i], dup);
			free(dup);
		}
	}
	dup = ft_strdup(NULL);
	RUN_SUBTEST("NULL", dup == NULL, &result, "expected NULL");
	free(dup);
	return result;
}

// ------------------ BONUS LINKED LIST TESTS ------------------

static void	free_list(t_list **list)
{
	t_list	*curr = *list;
	while (curr)
	{
		t_list	*tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	*list = NULL;
}

bool	test_list_push_front(void)
{
	t_list	*list = NULL;
	t_list	**addrs = NULL;
	bool	result = true;

	for (int i = 0; i < 10; i++)
	{
		ft_list_push_front(&list, (void *)(long)i);
		addrs = realloc(addrs, sizeof(t_list *) * (i + 1));
		addrs[i] = list;

		t_list *curr = list;
		bool	ok = true;
		for (int j = 0; j <= i; j++)
		{
			if (!curr || curr != addrs[i - j] || curr->data != (void *)(long)(i - j))
			{
				ok = false;
				break;
			}
			curr = curr->next;
		}
		char desc[64];
		snprintf(desc, sizeof(desc), "push_front iteration %d", i);
		RUN_SUBTEST(desc, ok, &result, "head/data mismatch");
	}
	free(addrs);
	free_list(&list);
	return result;
}

bool	test_list_size(void)
{
	t_list	*list = NULL;
	t_list	*last = NULL;
	bool	result = true;

	for (int i = 0; i < 10; i++)
	{
		t_list *node = calloc(1, sizeof(t_list));
		node->data = (void *)(long)i;
		if (last)
			last->next = node;
		if (!list)
			list = node;
		last = node;

		int size = ft_list_size(list);
		char desc[64];
		snprintf(desc, sizeof(desc), "list_size iteration %d", i);
		RUN_SUBTEST(desc, size == i + 1, &result, "expected %d, got %d",
			i + 1, size);
	}
	free_list(&list);
	return result;
}

// ------------------ TEST REGISTRATION ------------------

static t_test_entry g_tests[] = {
	{"ft_strlen", test_strlen},
	{"ft_strcpy", test_strcpy},
	{"ft_strcmp", test_strcmp},
	{"ft_write", test_write},
	{"ft_read", test_read},
	{"ft_strdup", test_strdup},
	{"ft_list_push_front", test_list_push_front},
	{"ft_list_size", test_list_size},
};

// ------------------ TEST RUNNER ------------------

static bool	run_test(const char *name)
{
	int		total = sizeof(g_tests) / sizeof(g_tests[0]);
	bool	found = false;
	bool	overall = true;

	for (int i = 0; i < total; i++)
	{
		if (!name || strcmp(name, g_tests[i].name) == 0)
		{
			found = true;
			fprintf(stderr, "\n=== Running %s ===\n", g_tests[i].name);
			overall &= g_tests[i].fn();
			fprintf(stderr, "\nPress ENTER to continue...");
			getchar();
		}
	}
	if (!found)
		fprintf(stderr, "Invalid test name: '%s'\n", name);
	return overall;
}

// ------------------ MAIN ------------------

int main(int argc, char **argv)
{
	bool	result;
	if (argc == 1)
		return run_test(NULL) ? 0 : 1;
	result = true;
	for (int i = 1; i < argc; i++)
		result &= run_test(argv[i]);
	return result ? 0 : 1;
}
