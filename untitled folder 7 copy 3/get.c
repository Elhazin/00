#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdalign.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*read_from_a_file(int fd, char *storage);
int		check_if_there_line(char *storage);
char	*get_until_line(char *storage);
char	*get_after_line(char *storage);
int		where_is_line( char *storage);
int		gnl_strlen(char *str);
char	*gnl_strsub(const char *str, int begin, int end);
#endif

int	where_is_line(char *storage)
{
	int	i;

	i = 0;
	while (storage && storage[i])
	{
		if (storage[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*gnl_strsub(const char *str, int begin, int end)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ptr = malloc(sizeof(char) * (end - begin + 1));
	if (ptr == NULL)
		return (NULL);
	while (begin < end && str[begin])
	{
		ptr[i] = str[begin];
		begin++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_after_line(char *storage)
{
	int		i;
	int		x;
	char	*str;

	if (storage == NULL || storage[0] == '\0')
		return (0);
	i = 0;
	x = where_is_line(storage);
	if (x == 0)
		return (0);
	str = malloc((gnl_strlen(storage) - x) + 1);
	if (str == NULL)
		return (NULL);
	while (storage[x])
		str[i++] = storage[x++];
	str[i] = '\0';
	return (str);
}

char	*get_until_line(char *storage)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!storage[0])
		return (NULL);
	while (storage[x] && storage[x] != '\n')
		x++;
	if (storage[x] == '\n')
		x++;
	return (gnl_strsub(storage, 0, x));
}

int	check_if_there_line(char *storage)
{
	int	i;

	i = 0;
	while (storage && storage[i])
	{
		if (storage[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *storage, char *reading)
{
	int		i;
	int		x;
	char	*str;

	x = gnl_strlen(storage);
	i = 0;
	str = malloc(BUFFER_SIZE + x + 1);
	while (storage && storage[i])
	{
		str[i] = storage[i];
		i++;
	}
	x = 0;
	while (reading && reading[x])
		str[i++] = reading[x++];
	str[i] = '\0';
	free(storage);
	return (str);
}

char	*read_from_a_file(int fd, char *storage)
{
	int		readed;
	char	*reading;

	reading = malloc(BUFFER_SIZE + 1);
	readed = 1;
	while (readed != 0 && !check_if_there_line(storage))
	{
		readed = read(fd, reading, BUFFER_SIZE);
		if (readed == -1)
		{
			free(reading);
			free(storage);
			return (NULL);
		}
		reading[readed] = '\0';
		storage = gnl_strjoin(storage, reading);
	}
	free(reading);
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*to_line;
	static char	*storage;
	char		*to_recover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_from_a_file(fd, storage);
	if (storage == NULL)
		return (NULL);
	to_line = get_until_line(storage);
	to_recover = storage;
	storage = get_after_line(storage);
	free(to_recover);
	return (to_line);
}