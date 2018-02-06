#ifndef SFGE_PYTHON_UTILIY_H
#define SFGE_PYTHON_UTILIY_H

#include <pybind11/embed.h>// everything needed for embedding
namespace py = pybind11;

py::object import(const std::string& module, const std::string& path, py::object& globals);

std::string module2class(std::string& module_name);

#endif
