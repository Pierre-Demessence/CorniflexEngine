#ifndef ATTRIBUTEEXECUTER_H_
# define ATTRIBUTEEXECUTER_H_

# include "IAttributeExecuter.hpp"

class Attribute;

template <typename ExecuterType>
class AttributeExecuter : public IAttributeExecuter
{
public:
  AttributeExecuter() : _type_infos(typeid(ExecuterType))
  {}

  virtual	~AttributeExecuter()
  {}

  virtual const std::type_info &getTypeInfo() const
  {
    return this->_type_infos;
  }

  virtual void	priv_apply(Attribute &attr, ExecuterType &obj) = 0;

protected:
  const std::type_info	&_type_infos;
};

#endif /* !ATTRIBUTEEXECUTER_H_ */
