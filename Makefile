NAME	=	libcorniflex.a
SRC	=	./src/
BIN	=	./bin/
TEST	=	./test/

INSTALLLIB	=	/usr/lib/
INSTALLINCLUDE	=	/usr/include/corniflex/

all:
		make -C $(SRC) NAME=$(NAME)
		cp $(SRC)$(NAME) $(BIN)$(NAME)

false:

install:	all
		sudo cp -r $(BIN)$(NAME) $(INSTALLLIB)
		sudo mkdir -p $(INSTALLINCLUDE)
		sudo cp -r ./include/* $(INSTALLINCLUDE)
		sudo updatedb

uninstall:
		sudo rm -rf $(INSTALLLIB)$(NAME)
		sudo rm -rf $(INSTALLINCLUDE)
		sudo updatedb

clean:
		make clean -C $(SRC) NAME=$(NAME)
		make clean -C $(TEST) NAME=$(NAME)

fclean:
		make fclean -C $(SRC) NAME=$(NAME)
		make fclean -C $(TEST) NAME=$(NAME)
		$(RM) $(BIN)$(NAME)

re:		fclean all

test:		install
		make run -C $(TEST) LIB=$(NAME)

debug:		install
		make debug -C $(TEST) LIB=$(NAME)

doc:
		doxygen doxygen.cfg

.PHONY:		all install uninstall clean fclean re test debug doc
