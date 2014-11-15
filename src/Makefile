CXX	=	g++
AR	=	ar -rvs
RM	=	rm -f

CPPFLAGS +=	-Wextra -Wall -Werror
CPPFLAGS +=	-std=c++11
CPPFLAGS +=	-I../include/

LDFLAGS +=
LDLIBS +=

SRCS	=	Component.cpp
OBJS	=	$(SRCS:.cpp=.o)

NAME	=	libCorniflex.a

all:		$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(LDFLAGS) $(OBJS) $(LDLIBS)

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

include .depend

.PHONY:		all clean fclean re
