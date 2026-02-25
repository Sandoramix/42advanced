/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:32:51 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/25 14:25:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm32_identify_symbol(Elf32_Sym *sym, Elf32_Shdr *shdr,
	t_nm_symbol *symbol)
{
	Elf32_Shdr			*section;

	if (ELF32_ST_TYPE(sym->st_info) == STT_FILE
		|| ELF32_ST_TYPE(sym->st_info) == STT_SECTION)
		symbol->is_debug = true;
	if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL)
		symbol->is_local = true;
	else if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		symbol->is_weak = true;
	symbol->type = SYMBOL_TYPE_READONLY;
	if (sym->st_shndx == SHN_UNDEF)
		symbol->type = SYMBOL_TYPE_UNDEFINED;
	else if (sym->st_shndx == SHN_ABS)
		symbol->type = SYMBOL_TYPE_ABSOLUTE;
	else
	{
		section = &shdr[sym->st_shndx];
		if (section->sh_type == SHT_NOBITS)
			symbol->type = SYMBOL_TYPE_BSS;
		else if (section->sh_flags & SHF_EXECINSTR)
			symbol->type = SYMBOL_TYPE_TEXT;
		else if (section->sh_flags & SHF_WRITE)
			symbol->type = SYMBOL_TYPE_DATA;
	}
}

bool	nm32_get_symbols(t_nm32_meta *meta, Elf32_Shdr *sym_hdr, Elf32_Sym *sym)
{
	const size_t	sym_len = sym_hdr->sh_size / sym_hdr->sh_entsize;
	size_t			i;
	t_nm_symbol		symbol;
	Elf32_Shdr		*section;

	meta->strtab = (char *)meta->target->mapping
		+ (meta->shdr[sym_hdr->sh_link]).sh_offset;
	i = 0;
	while (++i < sym_len)
	{
		symbol = (t_nm_symbol){
			.name = (char *)meta->strtab + sym[i].st_name,
			.offset = sym[i].st_value, .is_local = false,
			.is_hidden = false, .is_weak = false, .is_debug = false
		};
		nm32_identify_symbol(&sym[i], meta->shdr, &symbol);
		if (sym[i].st_info == STT_SECTION)
		{
			section = &meta->shdr[sym[i].st_shndx];
			symbol.name = meta->strtab + section->sh_name;
		}
		if (!elf_add_symbol(&meta->symbols, &meta->sym_count, symbol))
			return (false);
	}
	return (true);
}

void	nm32_print_symbols(t_nm32_meta *meta)
{
	size_t		i;
	t_nm_symbol	*symbol;

	i = 0;
	while (i < meta->sym_count)
	{
		symbol = &meta->symbols[i];
		if (symbol->is_hidden)
		{
			i++;
			continue ;
		}
		if (symbol->type == SYMBOL_TYPE_UNDEFINED)
			fprintf(stderr, "%8c", ' ');
		else
			fprintf(stderr, "%08lx", symbol->offset);
		fprintf(stderr, " %c %s\n",
			nm_symbol_chr(symbol->type, symbol->is_local, symbol->is_weak),
			symbol->name);
		i++;
	}
}

void	nm32_hide_symbols(t_option_enum options, t_nm32_meta *meta)
{
	size_t			i;
	t_option_enum	opt;
	t_nm_symbol		*sym;

	opt = options;
	i = 0;
	while (i < meta->sym_count)
	{
		sym = &meta->symbols[i];
		if ((opt & NMFLAG_EXTERN_ONLY) && sym->is_local)
			sym->is_hidden = true;
		if ((opt & NMFLAG_UNDEFINED_ONLY) && sym->type != SYMBOL_TYPE_UNDEFINED)
			sym->is_hidden = true;
		if (!(opt & NMFLAG_DEBUG_SYMS) && sym->is_debug)
			sym->is_hidden = true;
		i++;
	}
}

void	nm32_sort_symbols(t_nm32_meta *meta, bool reverse)
{
	t_nm_symbol		tmp;
	size_t			i;
	size_t			j;
	int				cmp;

	i = 0;
	while (i < meta->sym_count)
	{
		j = i + 1;
		while (j < meta->sym_count)
		{
			cmp = ft_strcoll(meta->symbols[i].name, meta->symbols[j].name);
			if ((!reverse && cmp > 0) || (reverse && cmp < 0))
			{
				tmp = meta->symbols[i];
				meta->symbols[i] = meta->symbols[j];
				meta->symbols[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
