/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:32:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/06 08:01:57 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_UTILS_H
# define NM_UTILS_H

# include <stddef.h>
# include <sys/stat.h>
# include <elf.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct stat	t_stat;

/**
Options provided by the user to the program.
The options are:
@param DEBUG_SYMS(1) `-a` | `--debug-syms`
@param EXTERN_ONLY(2) `-g` | `--extern-only`
@param UNDEFINED_ONLY(4) `-u` | `--undefined-only`
@param REVERSE_SORT(8) `-r` | `--reverse-sort`
@param NO_SORT(16) `-p` | `--no-sort`
@param HELP(32) `-h` | `--help`
 */
typedef enum e_nm_option
{
	NMFLAG_NONE = 0,
	NMFLAG_DEBUG_SYMS = 1 << 0,
	NMFLAG_EXTERN_ONLY = 1 << 1,
	NMFLAG_UNDEFINED_ONLY = 1 << 2,
	NMFLAG_REVERSE_SORT = 1 << 3,
	NMFLAG_NO_SORT = 1 << 4,
	NMFLAG_HELP = 1 << 5
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

typedef enum e_nm_symbol_type
{
	SYMBOL_TYPE_UNDEFINED = 'U',
	SYMBOL_TYPE_COMMON = 'C',
	SYMBOL_TYPE_ABSOLUTE = 'A',
	SYMBOL_TYPE_BSS = 'B',
	SYMBOL_TYPE_TEXT = 'T',
	SYMBOL_TYPE_DATA = 'D',
	SYMBOL_TYPE_READONLY = 'R',
	SYMBOL_TYPE_DEBUG = 'N',
}	t_nm_symbol_type;

typedef struct s_nm_symbol
{
	bool				is_local;
	bool				is_hidden;
	bool				is_weak;
	bool				is_debug;
	bool				is_unique;

	char				*name;
	uint64_t			offset;

	t_nm_symbol_type	type;
	uint8_t				st_type;

}	t_nm_symbol;

/**
 * Structure that holds the information about the target file
 * to be processed by the program.
 * It is used by the `nm_cycle` function.
 * @param fd File descriptor of the target file
 * @param mapping Memory mapping of the target file (mmap)
 * @param stat Structure that holds the information about the target file
 * @param format Format of the target file
 * (`ELFCLASS32`, `ELFCLASS64` or `ELFCLASSNONE`)
 */
typedef struct s_nm_target
{
	char			*path;

	int				fd;
	t_stat			stat;
	int				format;

	unsigned char	*mapping;

	int				symbol_count;

}	t_nm_target;

#endif