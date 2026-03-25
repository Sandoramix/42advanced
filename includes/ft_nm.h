/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:32 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/25 07:54:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>

# include "nm_utils.h"
# include "nm_elf32.h"
# include "nm_elf64.h"

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
}	t_nm;

void				ft_nm(t_nm *nm);
void				nm_help_message(t_nm *nm);

void				nm_print_symbol_line(t_nm_symbol *symbol, int zeropad);

// ./src/nm
const t_option_info	*get_help_options(void);
void				nm_cycle(t_nm *nm);
void				nm_set_file_error(t_nm *nm);
void				nm_sort_symbols(t_nm_symbol *symbols,
						size_t sym_count, bool reverse);

// ./src/nm/elf32
int					nm32_run(t_nm *nm, t_nm_target *t, Elf32_Ehdr *ehdr);

// ./src/nm/elf64
int					nm64_run(t_nm *nm, t_nm_target *t, Elf64_Ehdr *ehdr);

// ./src/nm/parsing
t_option_enum		nm_identify_option(const char *opt);
char				nm_symbol_chr(const t_nm_symbol *symbol);
t_option_enum		parse_argv(char **argv, int *valid_opts, int *bad_opts);

// ./src/utils
bool				elf_add_symbol(t_nm_symbol **sym_head, size_t *sym_size,
						t_nm_symbol sym);
int					elf_get_format(const char *file_path,
						unsigned char *e_ident);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcoll(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				ft_tolower(char c);
void				nm_cleanup_file_mapping(t_stat *stat, int fd,
						void **target_mapping);
t_stat				nm_get_file_stat(const char *filename, int *fd);
void				nm_print_possible_warnings(t_nm *nm, t_nm_target *t);
bool				nm_retrieve_file_mapping(t_nm *nm, t_stat *stat, int fd,
						void **target_mapping);

#endif