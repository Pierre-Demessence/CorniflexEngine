#ifndef ATTRIBUTEEXECUTERLEFTREDIRECT_H_
# define ATTRIBUTEEXECUTERLEFTREDIRECT_H_

# include "AttributeExecuter.hpp"

struct AttributeExecuterLeftRedirect
{
  template <typename T, typename Y>
  static void	apply(T &obj, Y &value)
  {
    obj << value;
  }
};

#endif /* !ATTRIBUTEEXECUTERLEFTREDIRECT_H_ */
