#ifndef ATTRIBUTEREGISTRER_H_
# define ATTRIBUTEREGISTRER_H_

# include <vector>
# include <map>
# include <string>
# include <functional>
# include "Attribute.hpp"

class AttributeRegistrer
{
public:
  typedef std::vector<Attribute *> Storage;
  typedef Storage::iterator iterator;

public:
  AttributeRegistrer()
  {}
  virtual	~AttributeRegistrer()
  {
    for (auto attr : this->_attributes)
      { delete attr; }
  }

  void		addAttribute(Attribute *attribute)
  {
    this->_attributes.push_back(attribute);
  }

  iterator	begin()
  { return this->_attributes.begin(); }

  iterator	end()
  { return this->_attributes.end(); }

  Storage	&getAttributes()
  { return this->_attributes; }

private:
  Storage	_attributes;
};

#endif /* !ATTRIBUTEREGISTRER_H_ */
