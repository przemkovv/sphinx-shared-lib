
#pragma once

#include <chrono>   // for milliseconds
#include <future>   // for future_status, async, future_status...
#include <optional> // for optional, nullopt
#include <tuple>
#include <type_traits> // for false_type, true_type

namespace Sphinx::Utils {

template <class T>
struct is_optional : std::false_type {
};

template <class T>
struct is_optional<std::optional<T>> : std::true_type {
};
template <class T>
struct remove_optional {
  using type = T;
};

template <class T>
struct remove_optional<std::optional<T>> {
  using type = T;
};

template <auto I = 0, typename Func, typename... Ts>
typename std::enable_if<I == sizeof...(Ts)>::type
for_each_in_tuple(std::tuple<Ts...> &, Func)
{
}

template <auto I = 0, typename Func, typename... Ts>
    typename std::enable_if <
    I<sizeof...(Ts)>::type for_each_in_tuple(std::tuple<Ts...> &tpl, Func func)
{
  func(std::get<I>(tpl));
  for_each_in_tuple<I + 1>(tpl, func);
}

template <typename Task1, typename Task2>
auto while_do(const Task1 &task_while, const Task2 &task_do)
{

  auto future = std::async(std::launch::async, task_while);
  std::future_status status;
  do {
    task_do();
    status = future.wait_for(std::chrono::milliseconds(5));
  } while (status != std::future_status::ready);

  task_do();

  return future.get();
}

} // namespace Sphinx::Utils

namespace Sphinx {

enum class ExitCode
/// Commonly used exit status codes.
/// Based on the definitions in the 4.3BSD <sysexits.h> header file.
{ OK = 0,           /// successful termination
  USAGE = 64,       /// command line usage error
  DATAERR = 65,     /// data format error
  NOINPUT = 66,     /// cannot open input
  NOUSER = 67,      /// addressee unknown
  NOHOST = 68,      /// host name unknown
  UNAVAILABLE = 69, /// service unavailable
  SOFTWARE = 70,    /// internal software error
  OSERR = 71,       /// system error (e.g., can't fork)
  OSFILE = 72,      /// critical OS file missing
  CANTCREAT = 73,   /// can't create (user) output file
  IOERR = 74,       /// input/output error
  TEMPFAIL = 75,    /// temp failure; user is invited to retry
  PROTOCOL = 76,    /// remote error in protocol
  NOPERM = 77,      /// permission denied
  CONFIG = 78       /// configuration error
};

} // namespace Sphinx
