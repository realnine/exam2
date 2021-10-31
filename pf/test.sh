gcc -Wall -Werror -Wextra pf2.c main2.c -o my_pf
gcc -Wall -Werror -Wextra -D ORG main2.c -o org_pf

./my_pf | cat -e > my.res
./org_pf | cat -e > org.res

gcc readmain2.c

./a.out | cat -e

rm *_pf *.res a.out
