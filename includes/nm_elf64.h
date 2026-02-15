/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_elf64.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:39:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 18:04:09 by odudniak         ###   ########.fr       */
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

char	nm64_get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr);
bool	nm64_get_symbols(t_nm64_meta *meta,
			Elf64_Shdr *sym_hdr, Elf64_Sym *sym);

#endif