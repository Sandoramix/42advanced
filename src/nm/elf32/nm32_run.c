/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:58:07 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 17:39:38 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	nm32_get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
	Elf32_Shdr	*section;

	if (sym->st_shndx == SHN_UNDEF)
		return ('U');
	if (sym->st_shndx == SHN_ABS)
		return ('A');
	section = &shdr[sym->st_shndx];
	if (section->sh_type == SHT_NOBITS)
		return ('B');
	if (section->sh_flags & SHF_EXECINSTR)
		return ('T');
	if (section->sh_flags & SHF_WRITE)
		return ('D');
	return ('R');
}

bool	nm32_get_symbols(t_nm32_meta *meta, Elf32_Shdr *sym_hdr, Elf32_Sym *sym)
{
	const size_t	sym_len = sym_hdr->sh_size / sym_hdr->sh_entsize;
	size_t			i;
	char			*name;
	char			type;
	t_nm_symbol		symbol;

	meta->strtab = (Elf32_Shdr *)
		(meta->target->mapping + (meta->shdr[sym_hdr->sh_link]).sh_offset);
	i = -1;
	while (++i < sym_len)
	{
		type = nm32_get_symbol_type(&sym[i], meta->shdr);
		name = (char *)meta->strtab + sym[i].st_name;
		symbol = (t_nm_symbol){
			.name = name, .type = type, .offset = sym[i].st_value
		};
		if (!elf_add_symbol(&meta->symbols, &meta->sym_count, symbol))
			return (false);
	}
	return (true);
}

/**
 * Run the 32-bit ELF parser.
 * @param nm Pointer to the main structure
 * @param t Pointer to the target structure
 * @param ehdr Pointer to the ELF header
 * @return true if the file was parsed successfully and symbols were added
 * @return false otherwise
 */
bool	nm_run_32(t_nm *nm, t_nm_target *t, Elf32_Ehdr *ehdr)
{
	t_nm32_meta	meta;
	size_t		i;

	(void)nm;
	fprintf(stderr, "ELF32 FORMAT\n");
	meta = (t_nm32_meta){
		.target = t,
		.ehdr = ehdr,
		.shdr = (Elf32_Shdr *)(t->mapping + ehdr->e_shoff),
		.sym_count = 0, .symbols = NULL, .strtab = NULL
	};
	i = 0;
	while (i < meta.ehdr->e_shnum)
	{
		if (meta.shdr[i].sh_type == SHT_SYMTAB)
		{
			return (nm32_get_symbols(&meta, &meta.shdr[i],
					(Elf32_Sym *)(t->mapping + meta.shdr[i].sh_offset)));
		}
		i++;
	}
	return (false);
}
