#ifndef COMPONENT_H_
# define COMPONENT_H_

# include "AttributeRegistrer.hpp"
# include "AttributeContainer.hpp"

class Component
{
public:
  Component() : _attribute_registerer()
  {}
  virtual ~Component()
  {}

  template <typename T,
  	    typename ...Args>
  void		registerAttribute(T &value)
  {
    AttributeContainer<T> *attr;

    attr = new AttributeContainer<T>(value);
    this->parseExecuter<T, Args...>(*attr);
  }

  AttributeRegistrer::iterator	begin()
  { return this->_attribute_registerer.begin(); }

  AttributeRegistrer::iterator	end()
  { return this->_attribute_registerer.end(); }

  AttributeRegistrer::Storage	&getAttributes()
  { return this->_attribute_registerer.getAttributes(); }

private:
  template <typename T,
  	    typename X,
  	    typename Y,
  	    typename ...Args>
  void		parseExecuter(AttributeContainer<T> &attribute_container)
  {
    attribute_container.template addAttributeExecuter<T, X, Y>();
    this->parseExecuter<T, Args...>(attribute_container);
  }

  template <typename T>
  void		parseExecuter(AttributeContainer<T> &attribute_container)
  {
    this->_attribute_registerer.addAttribute(&attribute_container);
  }

private:
  AttributeRegistrer	_attribute_registerer;
};

#endif /* !COMPONENT_H_ */
