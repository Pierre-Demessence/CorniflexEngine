#ifndef IATTRIBUTEEXECUTER_H_
# define IATTRIBUTEEXECUTER_H_

# include <typeinfo>

class IAttributeExecuter
{
public:
  virtual ~IAttributeExecuter()
  {}
  virtual const std::type_info &getTypeInfo() const = 0;
};

#endif /* !IATTRIBUTEEXECUTER_H_ */
