/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_elf32.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:39:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/27 10:21:27 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_ELF32_H
# define NM_ELF32_H

# include "nm_utils.h"

typedef struct s_nm32_meta
{
	t_nm_target	*target;

	Elf32_Ehdr	*ehdr;
	Elf32_Shdr	*shdr;

	char		*strtab;
	char		*shstrtab;

	size_t		sym_count;
	t_nm_symbol	*symbols;

}	t_nm32_meta;

bool	nm32_get_symbols(t_nm32_meta *meta,
			Elf32_Shdr *sym_hdr, Elf32_Sym *sym);
void	nm32_hide_symbols(t_option_enum options, t_nm32_meta *meta);
void	nm32_identify_symbol(Elf32_Sym *sym,
			Elf32_Shdr *shdr, t_nm_symbol *symbol);
bool	nm32_retrieve_symbols(t_nm_target *t, t_nm32_meta *meta);
void	nm32_sort_symbols(t_nm32_meta *meta, bool reverse);
void	nm32_print_symbols(t_nm32_meta *meta);
#endif