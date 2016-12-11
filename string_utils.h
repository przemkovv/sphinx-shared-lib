#pragma once

#include <string>

namespace boost::program_options {
class variable_value;
}

namespace Sphinx {

std::string escape_control_characters(const std::string &input);

} // namespace Sphinx

namespace std {

std::ostream &operator<<(std::ostream &out,
                         const boost::program_options::variable_value &v);

} // namespace std
