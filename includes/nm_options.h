/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:18:18 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 15:18:20 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OPTIONS_H
# define NM_OPTIONS_H

/**
Options provided by the user to the program.
The options are:
@param DEBUG_SYMS(1) `-a` | `--debug-syms`
@param EXTERN_ONLY(2) `-g` | `--extern-only`
@param UNDEFINED_ONLY(4) `-u` | `--undefined-only`
@param REVERSE_SORT(8) `-r` | `--reverse-sort`
@param NO_SORT(16) `-p` | `--no-sort`
 */
typedef enum e_nm_option
{
	NMFLAG_NONE = 0,
	NMFLAG_DEBUG_SYMS = 1 << 0,
	NMFLAG_EXTERN_ONLY = 1 << 1,
	NMFLAG_UNDEFINED_ONLY = 1 << 2,
	NMFLAG_REVERSE_SORT = 1 << 3,
	NMFLAG_NO_SORT = 1 << 4
}	t_option_enum;

typedef struct s_option_info
{
	char			*short_name;
	char			*long_name;
	char			*description;
	t_option_enum	value;
}	t_option_info;

/**
 * Structure that holds the options of the program.
 * @param value The actual value of the option
 * @param valid Number of valid options parsed
 * @param bad Number of invalid options parsed
 */
typedef struct s_nm_option
{
	t_option_enum		value;
	int					valid;
	int					bad;
}	t_nm_option;

#endif