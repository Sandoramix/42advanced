/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm64_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:58:34 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/25 18:31:27 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

bool	nm64_retrieve_symbols(t_nm_target *t, t_nm64_meta *meta)
{
	size_t		i;

	i = 0;
	while (i < meta->ehdr->e_shnum)
	{
		if (meta->shdr[i].sh_type == SHT_SYMTAB)
		{

			meta->shstrtab = (char *)meta->target->mapping
				+ meta->shdr[meta->ehdr->e_shstrndx].sh_offset;
			return (nm64_get_symbols(meta, &meta->shdr[i],
					(Elf64_Sym *)(t->mapping + meta->shdr[i].sh_offset)));
		}
		i++;
	}
	return (false);
}

/**
 * Run the 64-bit ELF parser.
 * @param nm Pointer to the main structure
 * @param t Pointer to the target structure
 * @param ehdr Pointer to the ELF header
 * @return true if the file was parsed successfully and symbols were added
 * @return false otherwise
 */
bool	nm64_run(t_nm *nm, t_nm_target *t, Elf64_Ehdr *ehdr)
{
	t_nm64_meta	meta;

	meta = (t_nm64_meta){
		.target = t,
		.ehdr = ehdr,
		.shdr = (Elf64_Shdr *)(t->mapping + ehdr->e_shoff),
		.sym_count = 0, .symbols = NULL, .strtab = NULL
	};
	if (!nm64_retrieve_symbols(t, &meta))
		return (false);
	if (!(nm->options.value & NMFLAG_NO_SORT))
		nm64_sort_symbols(&meta, nm->options.value & NMFLAG_REVERSE_SORT);
	nm64_hide_symbols(nm->options.value, &meta);
	nm64_print_symbols(&meta);
	free(meta.symbols);
	return (true);
}
