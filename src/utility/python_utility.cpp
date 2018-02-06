#include <utility/python_utility.h>
#include <sstream>

py::object import(const std::string& module, const std::string& path, py::object& globals)
{
    py::dict locals;
    locals["module_name"] = py::cast(module); // have to cast the std::string first
    locals["path"]        = py::cast(path);

    py::eval<py::eval_statements>(            // tell eval we're passing multiple statements
        "import imp\n"
        "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
        globals,
        locals);

    return locals["new_module"];
}

std::string module2class(std::string& module_name)
{

	std::istringstream iss(module_name);
	std::string token;
	std::string class_name;
	while (std::getline(iss, token, '_'))
	{
		if(token.size() > 0)
		{
			char first = token.at(0);
			class_name += std::toupper(first);
			class_name += token.substr(1, token.size());
		}
	}
	return class_name;
}
