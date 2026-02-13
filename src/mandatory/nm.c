/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:42:27 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 17:50:45 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_nm(t_ft_nm *nm)
{
	int	i;

	fprintf(stderr, "MANDATORY NM CALLED\n");
	if (nm->options.valid > 0 || nm->options.bad > 0)
		return (nm_help_message(nm), exit(EXIT_FAILURE));
	i = -1;
	nm_cycle(nm);
}
