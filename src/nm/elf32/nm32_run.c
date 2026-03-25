/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:58:07 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/25 07:56:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

bool	nm32_retrieve_symbols(t_nm_target *t, t_nm32_meta *meta)
{
	size_t		i;

	i = 0;
	while (i < meta->ehdr->e_shnum)
	{
		if (meta->shdr[i].sh_type == SHT_SYMTAB)
		{
			return (nm32_get_symbols(meta, &meta->shdr[i],
					(Elf32_Sym *)(t->mapping + meta->shdr[i].sh_offset)));
		}
		i++;
	}
	return (false);
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
		nm_print_symbol_line(symbol, 8);
		i++;
	}
}

/**
 * Run the 32-bit ELF parser.
 * @param nm Pointer to the main structure
 * @param t Pointer to the target structure
 * @param ehdr Pointer to the ELF header
 * @return -1 if the file was not parsed successfully
 * @return count of symbols if the file was parsed successfully
 */
int	nm32_run(t_nm *nm, t_nm_target *t, Elf32_Ehdr *ehdr)
{
	t_nm32_meta	meta;

	meta = (t_nm32_meta){
		.target = t,
		.ehdr = ehdr,
		.shdr = (Elf32_Shdr *)(t->mapping + ehdr->e_shoff),
		.sym_count = 0, .symbols = NULL, .strtab = NULL, .shstrtab = NULL
	};
	t->symbol_count = 0;
	meta.shstrtab = (char *)meta.target->mapping
		+ meta.shdr[meta.ehdr->e_shstrndx].sh_offset;
	if (!nm32_retrieve_symbols(t, &meta))
		return (-1);
	if (!(nm->options.value & NMFLAG_NO_SORT))
		nm_sort_symbols(meta.symbols, meta.sym_count,
			nm->options.value & NMFLAG_REVERSE_SORT);
	nm32_hide_symbols(nm->options.value, &meta);
	nm32_print_symbols(&meta);
	free(meta.symbols);
	t->symbol_count = meta.sym_count;
	return (meta.sym_count);
}
