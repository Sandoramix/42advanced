/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:22:14 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 17:38:01 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * Opens the file from the given path and returns the metadata about it.
 * @param filename the path of the file to open
 * @param fd pointer to the file descriptor which will be set to the opened file
 * @returns the metadata about the file
 */
t_stat	nm_get_file_stat(const char *filename, int *fd)
{
	int		target_fd;
	t_stat	file_stat;

	file_stat = (t_stat){0};
	target_fd = open(filename, O_RDONLY);
	if (target_fd == -1)
	{
		*fd = -1;
		return (file_stat);
	}
	if (fstat(target_fd, &file_stat) == -1)
	{
		close(target_fd);
		*fd = -1;
		file_stat = (t_stat){0};
		return (perror("Error getting file metadata"), file_stat);
	}
	*fd = target_fd;
	return (file_stat);
}

bool	nm_retrieve_file_mapping(t_nm *nm, t_stat *stat, int fd,
	void **target_mapping)
{
	*target_mapping = mmap(NULL, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (*target_mapping == MAP_FAILED)
	{
		close(fd);
		perror("Error mapping file");
		exit(EXIT_FAILURE);
		return (false);
	}
	if (*target_mapping == NULL)
	{
		close(fd);
		nm_set_file_error(nm);
		write(STDERR_FILENO, "File mapping returned NULL\n", 27);
		return (false);
	}
	return (true);
}

void	nm_cleanup_file_mapping(t_stat *stat, int fd, void **target_mapping)
{
	if (*target_mapping && *target_mapping != MAP_FAILED)
		munmap(*target_mapping, stat->st_size);
	*target_mapping = NULL;
	if (fd != -1)
		close(fd);
}
