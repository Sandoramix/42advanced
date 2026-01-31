
#ifndef LIBASM_H
# define LIBASM_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <errno.h>


typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s1);

// BONUS
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *list);

typedef int	(*t_cmp_fn)(const void *a, const void *b);
void	ft_list_sort(t_list **begin_list, t_cmp_fn cmp);

#endif