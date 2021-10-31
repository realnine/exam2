gcc -Wall -Wextra -Werror main.c -D REAL 
chmod 775 ./a.out
./a.out > org.txt
rm a.out

gcc -Wall -Wextra -Werror main.c ft_printf.c
chmod 775 ./a.out
./a.out > cpy.txt
rm a.out

#diff -d org.txt cpy.txt