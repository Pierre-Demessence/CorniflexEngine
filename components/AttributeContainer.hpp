#ifndef ATTRIBUTECONTAINER_H_
# define ATTRIBUTECONTAINER_H_

# include "Attribute.hpp"

template <typename T>
class AttributeContainer : public Attribute
{
public:
  AttributeContainer(T &value) : Attribute(), _value(value)
  {}

  virtual	~AttributeContainer()
  {}

  T		&getValue()
  {
    return this->_value;
  }

  const T	&getValue() const
  {
    return this->_value;
  }

  void		copy(const Attribute &attr)
  {
    this->_value = Caster::cast<const AttributeContainer<T> *>(&attr)->getValue();
  }

protected:
  T	&_value;
};

#endif /* !ATTRIBUTECONTAINER_H_ */
