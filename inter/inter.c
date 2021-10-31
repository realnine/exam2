#include <unistd.h>

int main(int argc, char **argv)
{
    int i, j;
    int used[128] = { 0, };
	unsigned char c;

    if (argc == 3)
    {
        i = 2;
        while (i > 0)
        {
            j = 0;
            while (argv[i][j])
            {
				c = argv[i][j];
                if (i == 2 && used[c] == 0)
                    used[c] = 1;
                else if (i == 1 && used[c] == 1)
                {
                    write(1, &c, 1);
                    used[c] = 2;
                }
                j++;
            }
            i--;
        }
    }
    write(1, "\n", 1);
    return (0);
}

/*

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "nothing" "This sentence hides nothing" | cat -e
nothig$
$>./inter | cat -e
$

*/