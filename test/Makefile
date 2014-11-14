CXX	=	g++
RM	=	rm -f

CPPFLAGS +=	-Wextra -Wall -Werror
CPPFLAGS +=	-std=c++11
CPPFLAGS +=	-I../include/

LDFLAGS +=

SRCS	=	main.cpp
OBJS	=	$(SRCS:.cpp=.o)

BIN	=	../bin/
LIB	=	libCorniflex.a	
NAME	=	test

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(BIN)$(LIB)

depend:		.depend

.depend:	$(SRCS)
		$(RM) ./.depend
		$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ./.depend

re:		fclean all

run:		$(NAME)
		./$(NAME)

debug:		$(NAME)
		valgrind --track-origins=yes ./$(NAME)

include .depend

.PHONY:		all clean fclean re run debug
