/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:29:55 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/27 10:17:58 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_nm.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (s1 - s2);
	while (s2p[i] && s1p[i] && s2p[i] == s1p[i])
		i++;
	return (s1p[i] - s2p[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (s1 - s2);
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	is_separator(char c)
{
	return (c == '_' || c == '.');
}

/**
 * String comparison close to strcoll(3) behaviour, for nm symbol sorting.
 * The collation rules in GNU nm (reverse engineered) are:
 * - '_' and '.' are skipped for the primary comparison
 * - the remaining characters are compared case-insensitively
 * - if the stripped versions are identical, the first case difference is used
 *   as tiebreaker: lowercase sorts before uppercase (en_US.UTF-8 behaviour)
 */
int	ft_strcoll(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	int		c1;
	int		c2;
	int		case_diff;

	if (!s1 || !s2)
		return (s1 - s2);
	i = 0;
	j = 0;
	case_diff = 0;
	while (s1[i] || s2[j])
	{
		while (is_separator(s1[i]))
			i++;
		while (is_separator(s2[j]))
			j++;
		if (!s1[i] && !s2[j])
			break ;
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[j]);
		if (c1 != c2)
			return (c1 - c2);
		if (!case_diff && s1[i] != s2[j])
			case_diff = (s1[i] >= 'A' && s1[i] <= 'Z') ? 1 : -1;
		i++;
		j++;
	}
	if (case_diff)
		return (case_diff);
	return (ft_strcmp(s1, s2));
}
