#include <unistd.h> // read
#include <stdlib.h> // malloc free

char *bufcat(char *stor, char c)
{
	char *new;
	int len;
	
	len = 0;
	while (stor[len])
		len++;
	if (!(new = malloc(len + 2)))
		return (NULL);
	len = -1;
	while (stor[++len])
		new[len] = stor[len];
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
	
}

int get_next_line(char **line)
{
	char *stor;
	char buf[1];
	char *tmp;

	if (!(stor = malloc(1)))
		return (-1);
	*stor = '\0';
	while (read(0, buf, 1) > 0)
	{
		if (buf[0] == '\n')
		{	
			*line = stor;
			return (1);
		}
		tmp = stor;
		stor = bufcat(stor, buf[0]);
		free(tmp);
		if (!stor)
			return (-1);
	}
	*line = stor;
	//system("leaks a.out > leak_res; cat leak_res | grep leaked && rm leak_res ");
	return (0);
}