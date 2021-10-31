gcc -Wall -Wextra -Werror inter2.c -o inter

echo padinto | cat -e > expect.res
echo df6ewg4 | cat -e >> expect.res
echo nothig | cat -e >> expect.res
echo "" | cat -e >> expect.res

./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" \
| cat -e > my.res

./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd \
| cat -e >> my.res

./inter "nothing" "This sentence hides nothing" \
| cat -e >> my.res

./inter | cat -e >> my.res

diff expect.res my.res

rm expect.res my.res inter