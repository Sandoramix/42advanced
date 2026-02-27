/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:00:11 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/27 12:00:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
