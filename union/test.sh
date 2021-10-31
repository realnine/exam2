gcc -Wall -Wextra -Werror union2.c -o union
#===============================================
echo zpadintoqefwjy | cat -e > expect.res
echo df6vewg4thras | cat -e >> expect.res
echo rienct phas | cat -e >> expect.res
echo "" | cat -e >> expect.res
echo "" | cat -e >> expect.res
#===============================================
./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" \
| cat -e > my.res

./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd \
| cat -e >> my.res

./union "rien" "cette phrase ne cache rien" \
| cat -e >> my.res

./union | cat -e >> my.res

./union "rien" | cat -e >> my.res
#===============================================
diff expect.res my.res

rm expect.res my.res union