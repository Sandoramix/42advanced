
#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

// BONUS
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *list);

typedef int	(*t_cmp_fn)(const void *a, const void *b);
void	ft_list_sort(t_list **begin_list, t_cmp_fn cmp);

#endif