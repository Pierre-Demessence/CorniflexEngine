#ifndef ATTRIBUTE_H_
# define ATTRIBUTE_H_

# include <functional>
# include <vector>

# include "IAttributeExecuter.hpp"
# include "AttributeExecuterTyped.hpp"
# include "Caster.hpp"
# include "PassByValue.hpp"

template <typename>
class AttributeExecuter;

template <typename>
class AttributeContainer;

class Attribute
{
public:
  Attribute()
  {}

  virtual ~Attribute()
  {
    for (auto attr_executer : this->_attribute_executers)
      { delete attr_executer; }
  }

  void	addAttributeExecuter(IAttributeExecuter *attr_exec)
  {
    this->_attribute_executers.push_back(attr_exec);
  }

  template <
    typename ValueType,
    class OpType,
    typename ExecuterType
    >
  void	addAttributeExecuter()
  {
    this->_attribute_executers.push_back(new AttributeExecuterTyped<ValueType, OpType, ExecuterType>());
  }

  template <typename T>
  void	apply(T &obj)
  {
    static const std::type_info &type_info = typeid(T);

    for (auto it = this->_attribute_executers.begin(); it != this->_attribute_executers.end(); ++it)
      {
	if (type_info == (*it)->getTypeInfo())
	  {
	    Caster::cast<AttributeExecuter<T> *>(*it)->priv_apply(*this, obj);
	  }
      }
  }

  /*
  ** Attribute::set, Attribute::get has an undefined behavior if 'T' is incorrect
  ** An exception will be raised in debug mode.
  */
  void	set(const Attribute &value)
  {
    this->copy(value);
  }

  template <typename T>
  void	set(const AttributeContainer<T> &value)
  {
    this->copy(value);
  }

  template <typename T>
  T	&get()
  {
    AttributeContainer<T> *tmp;

    tmp = Caster::cast<AttributeContainer<T> *>(this);
    return tmp->getValue();
  }

private:
  template <typename T>
  void	inner_set(T value)
  {
    Caster::cast<
      AttributeContainer<
	typename std::remove_cv<
	  typename std::remove_reference<T>::type>::type> *>
      (this)->getValue() = value;
  }

protected:
  virtual void	copy(const Attribute &attr) = 0;

protected:
  std::vector<IAttributeExecuter *>	_attribute_executers;
};

#endif /* !ATTRIBUTE_H_ */
