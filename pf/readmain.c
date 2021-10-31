#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd1;
	int fd2;
	char buf[1];

	fd1 = open("./my.res", O_RDONLY);
	fd2 = open("./org.res", O_RDONLY);

	while (read(fd1, buf, 1) > 0)
	{
		printf("%c", buf[0]);
		if (buf[0] == '\n')
		{
			while (read(fd2, buf, 1) > 0)
			{
				printf("%c", buf[0]);
				if (buf[0] == '\n')
					break ;
			}
		}
	}
	return 0;
}
