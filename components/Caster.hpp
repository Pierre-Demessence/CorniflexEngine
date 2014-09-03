#ifndef CASTER_H_
# define CASTER_H_

# include <exception>
# include <utility>
# include <string>
# include <typeinfo>

class Caster
{
public:
  class CastException : public std::exception
  {
  public:
    CastException(std::string from, std::string to) throw()
      : exception(), _from(std::move(from)), _to(std::move(to))
    {}
    virtual ~CastException() throw()
    {}

    const char *what() const throw()
    {
      return (std::string("CastException: Cast error from ") + this->_from + " to " + this->_to).c_str();
    }
  private:
    std::string _from;
    std::string _to;
  };
public:
  template <typename T, typename X>
  static T cast(const X &value)
  {
#ifdef _DEBUG
    return safe_cast<T>(value);
#else
    return fast_cast<T>(value);
#endif
  }

  template <typename T, typename X>
  static T fast_cast(const X &value)
  {
    return static_cast<T>(value);
  }

  template <typename T, typename X>
  static T safe_cast(const X &value)
  {
    T tmp = dynamic_cast<T>(value);
    if (!tmp)
      throw CastException(typeid(T).name(), typeid(X).name());
    return tmp;
  }
};

#endif /* !CASTER_H_ */
