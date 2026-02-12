/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 07:43:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/12 08:49:20 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_help_message(void)
{
	write(STDERR_FILENO, NM_HELP_MESSAGE, 15);
}
