
#pragma once

#include <memory>          // for shared_ptr, __shared_ptr_access
#include <spdlog/spdlog.h> // for logger, get, stdout_color_st, spdlog_ex
#include <string>          // for string

namespace Sphinx {

typedef std::shared_ptr<spdlog::logger> Logger;

inline auto make_logger(const std::string &name)
{
  try {
    return spdlog::stdout_color_st(name);
  }
  catch (spdlog::spdlog_ex &) {
    return spdlog::get(name);
  }
}

inline auto make_logger(const std::string &name,
                        const spdlog::level::level_enum &level)
{
  try {
    auto logger = spdlog::stdout_color_st(name);
    logger->set_level(level);
    return logger;
  }
  catch (spdlog::spdlog_ex &) {
    auto logger = spdlog::get(name);
    logger->set_level(level);
    return logger;
  }
}

} // namespace Sphinx
