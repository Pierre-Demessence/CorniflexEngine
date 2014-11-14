NAME	=	libCorniflex.a
SRC	=	./src/
BIN	=	./bin/
TEST	=	./test/

all:		$(BIN)$(NAME)

$(BIN)$(NAME):
		make -C $(SRC)
		cp $(SRC)$(NAME) $(BIN)$(NAME)

clean:
		make clean -C $(SRC)
		make clean -C $(TEST)

fclean:
		make fclean -C $(SRC)
		make fclean -C $(TEST)
		$(RM) $(BIN)$(NAME)

re:		fclean all

test:		$(BIN)$(NAME)
		make run -C $(TEST)

debug:		$(BIN)$(NAME)
		make debug -C $(TEST)

doc:
		doxygen doxygen.cfg

.PHONY:		all clean fclean re test debug doc
