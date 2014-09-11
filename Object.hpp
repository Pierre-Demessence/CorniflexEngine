#ifndef OBJECT_H_
# define OBJECT_H_

# include	<ostream>
# include	<string>

template <typename Value>
class Object
{
protected:
  Value		_value;
  std::string	_strvalue;
public:
  // ----- Constructors ----- //
  Object() = default;
  Object(Value value)
    : _value(value)
  { }

  Object(const Object&) = default;

  // ----- Destructor ----- //
  ~Object() = default;

  // ----- Operators ----- //
  Object&	operator=(const Object&) = default;
  Object&	operator=(const Value &value)
  {
    this->_value = value;
    return (*this);
  }

  Object&	operator+=(const Value &value)
  {
    this->_value += value;
    return (*this);
  }

  // ----- Getters & Setters ----- //
  const Value	&value() const
  {
    return (this->_value);
  }

  Value		&value()
  {
    return (this->_value);
  }



  // ----- Methods ----- //
};

template <typename Value>
std::ostream	&operator<<(std::ostream& os, const Object<Value>& object)
{
  os << object.value();
  return (os);
}

typedef Object<std::string> String;
typedef Object<int> Integer;
typedef Object<float> Float;

#endif /* !OBJECT_H_ */
