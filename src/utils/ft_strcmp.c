/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:29:55 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 14:56:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1p;
	unsigned char	*s2p;

	s1p = (unsigned char *)s1;
	s2p = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (INT_MIN);
	while (s2p[i] && s1p[i] && s2p[i] == s1p[i])
		i++;
	return (s1p[i] - s2p[i]);
}
