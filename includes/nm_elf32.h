/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_elf32.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:39:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 17:38:04 by odudniak         ###   ########.fr       */
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

	Elf32_Shdr	*strtab;

	size_t		sym_count;
	t_nm_symbol	*symbols;

}	t_nm32_meta;

char	nm32_get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *shdr);
bool	nm32_get_symbols(t_nm32_meta *meta,
			Elf32_Shdr *sym_hdr, Elf32_Sym *sym);

#endif