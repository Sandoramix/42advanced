/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_elf64.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:39:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/25 12:36:56 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_ELF64_H
# define NM_ELF64_H

# include "nm_utils.h"

typedef struct s_nm64_meta
{
	t_nm_target		*target;

	Elf64_Ehdr		*ehdr;
	Elf64_Shdr		*shdr;

	char			*strtab;

	size_t			sym_count;
	t_nm_symbol		*symbols;

}	t_nm64_meta;

bool	nm64_get_symbols(t_nm64_meta *meta,
			Elf64_Shdr *sym_hdr, Elf64_Sym *sym);
void	nm64_hide_symbols(t_option_enum options, t_nm64_meta *meta);
void	nm64_identify_symbol(Elf64_Sym *sym, Elf64_Shdr *shdr,
			t_nm_symbol *symbol);
bool	nm64_retrieve_symbols(t_nm_target *t, t_nm64_meta *meta);
void	nm64_sort_symbols(t_nm64_meta *meta, bool reverse);
void	nm_64_print_symbols(t_nm64_meta *meta);

#endif