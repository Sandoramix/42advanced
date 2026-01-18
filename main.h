
#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>


// MANDATORY FN NAMES
# define FT_STRLEN "ft_strlen"
# define FT_STRCPY "ft_strcpy"
# define FT_STRCMP "ft_strcmp"
# define FT_WRITE "ft_write"
# define FT_READ "ft_read"
# define FT_STRDUP "ft_strdup"

// BONUS FN NAMES
# define FT_ATOI_BASE "ft_atoi_base"
# define FT_LIST_PUSH_FRONT "ft_list_push_front"
# define FT_LIST_SIZE "ft_list_size"
# define FT_LIST_SORT "ft_list_sort"
# define FT_LIST_REMOVE_IF "ft_list_remove_if"

bool	test_strlen(void);
bool	test_strcpy(void);
bool	test_strcmp(void);
bool	test_write(void);
bool	test_read(void);
bool	test_strdup(void);

bool	test_atoi_base(void);
bool	test_list_push_front(void);
bool	test_list_size(void);
bool	test_list_sort(void);
bool	test_list_remove_if(void);

typedef bool	(*t_fn_ref)(void);

#endif