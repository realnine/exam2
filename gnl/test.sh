gnl=gnl2.c

gcc -Wall -Werror -Wextra ${gnl} main2.c

#./a.out < test.txt

./a.out < ${gnl} | cat -e > my.res
cat -e < ${gnl} > exp.res
diff my.res exp.res
rm *.res a.out