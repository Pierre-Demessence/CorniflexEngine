#ifndef ATTRIBUTEEXECUTERTYPED_H_
# define ATTRIBUTEEXECUTERTYPED_H_

# include "AttributeExecuter.hpp"
# include "Caster.hpp"

template <typename>
class AttributeContainer;

template <typename ValueType, typename OpType, typename ExecuterType>
class AttributeExecuterTyped : public AttributeExecuter<ExecuterType>
{
public:
  AttributeExecuterTyped() : AttributeExecuter<ExecuterType>() {}
  virtual	~AttributeExecuterTyped() {}
  void	priv_apply(Attribute &attr, ExecuterType &obj)
  {
    OpType::apply(obj, Caster::cast<AttributeContainer<ValueType> *>(&attr)->getValue());
  }
};

#endif /* !ATTRIBUTEEXECUTERTYPED_H_ */
