/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:32 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 17:49:55 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <elf.h>
# include <stdbool.h>
# include <errno.h>

# include "ft_utils.h"
# include "nm_options.h"

typedef struct stat	t_stat;

/**
 * @brief Runtime context of the ft_nm program.
 *
 * This structure centralizes all data required during execution.
 * It is initialized in main() and passed to ft_nm(), in both
 * mandatory and bonus builds.
 *
 * Members:
 *
 * - `progname`
 *     Name used to invoke the program (argv[0]).
 *
 * - `argc`
 *     Number of arguments provided to the program, excluding
 *     the program name.
 *     In `bonus mode`, parsed option arguments are excluded from
 *     this count.
 *
 * - `argv`
 *     Array of arguments passed to the program. The program
 *     name (argv[0]) is not included.
 *     In `bonus mode`, option arguments are removed
 *     after parsing.
 *
 * - `options`
 *     Structure storing parsed option flags and metadata.
 *     This structure is only used in `bonus mode`.
 */
typedef struct s_ft_nm
{
	char		*progname;
	int			argc;
	char		**argv;
	t_nm_option	options;

	bool		bad_file_passed;
}	t_ft_nm;

void				ft_nm(t_ft_nm *nm);
void				nm_cycle(t_ft_nm *nm);

t_option_enum		parse_argv(char **argv, int *valid_opts, int *bad_opts);

t_option_enum		nm_identify_option(const char *opt);

t_stat				nm_getfilestat(const char *filename, int *fd);
void				nm_help_message(t_ft_nm *nm);
int					nm_identify_elf_format(unsigned char *e_indent);

const t_option_info	*get_known_options(void);

#endif