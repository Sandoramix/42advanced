/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:46:56 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 15:13:49 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_option_enum	identify_short_option(const char opt)
{
	const t_option_info	*options = get_known_options();
	const char			opt_str[2] = {opt, 0};
	size_t				i;

	i = 0;
	while (options[i].short_name)
	{
		if (!ft_strcmp(options[i].short_name, opt_str))
			return (options[i].value);
		i++;
	}
	return (NMFLAG_NONE);
}

static t_option_enum	identify_extended_option(const char *opt)
{
	const t_option_info	*options = get_known_options();
	size_t				i;

	if (!opt || opt[0] != '-' || opt[1] != '-' || !opt[2])
		return (NMFLAG_NONE);
	i = 0;
	opt = &opt[2];
	while (options[i].long_name)
	{
		if (!ft_strcmp(options[i].long_name, opt))
			return (options[i].value);
		i++;
	}
	return (NMFLAG_NONE);
}

t_option_enum	nm_identify_option(const char *opt)
{
	t_option_enum		result;
	t_option_enum		opt_flag;
	size_t				i;

	result = NMFLAG_NONE;
	if (!opt || opt[0] != '-')
		return (NMFLAG_NONE);
	result = identify_extended_option(opt);
	if (result != NMFLAG_NONE)
		return (result);
	i = 1;
	if (opt[1] == '-')
		i = 2;
	while (opt[i])
	{
		opt_flag = identify_short_option(opt[i]);
		if (opt_flag == NMFLAG_NONE)
			return (NMFLAG_NONE);
		result |= opt_flag;
		i++;
	}
	return (result);
}
