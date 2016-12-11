#pragma once

namespace Sphinx {

template <typename Task>
struct on_scope_exit {
  on_scope_exit(const Task &f) : f_(f) {}
  on_scope_exit<Task> &operator=(const on_scope_exit<Task> &) = delete;
  on_scope_exit(const on_scope_exit<Task> &) = delete;
  on_scope_exit(on_scope_exit<Task> &&) = default;

  ~on_scope_exit() { f_(); }
  const Task &f_;
};

template <typename Task>
on_scope_exit<Task> do_on_scope_exit(const Task &f)
{
  return on_scope_exit<Task>(f);
}

#define STRING_JOIN2(arg1, arg2) DO_STRING_JOIN2(arg1, arg2)
#define DO_STRING_JOIN2(arg1, arg2) arg1##arg2
#define SCOPE_EXIT(code)                                                       \
  auto STRING_JOIN2(on_scope_exit_, __LINE__) =                                \
      do_on_scope_exit([&]() { code; })
} // Sphinx
