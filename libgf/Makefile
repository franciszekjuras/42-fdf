NAME = libgf.a

FILES = \
	gf_basics gf_color gf_core gf_line\
	gf_int_pxput

OFILES = $(FILES:%=%.o)

CFLAGS = -Wall -Wextra

OPTIM = -O3

INC = -I. -I..

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $@ $?

$(OFILES): %.o: %.c
	gcc $(CFLAGS) $(OPTIM) $(INC) -c $< -o $@

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
