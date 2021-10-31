# include <stdio.h> // printf
#include <stdlib.h> // free

int get_next_line(char **line);

int main()
{
	char *line;

	while (get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	system("leaks a.out > leak_res; cat leak_res | grep leaked && rm leak_res ");
	return 0;
}
