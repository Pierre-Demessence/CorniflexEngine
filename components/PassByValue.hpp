#ifndef PASSBYVALUE_H_
# define PASSBYVALUE_H_

# include <type_traits>

template <typename T>
struct PassByValue :
  std::integral_constant<bool, std::is_scalar<T>::value || std::is_array<T>::value>
{};

#endif /* !PASSBYVALUE_H_ */
