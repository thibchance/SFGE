#include <utility/file_utility.h>
namespace sfge
{
bool FileExists(std::string & filename)
{
	fs::path p = filename;
	return fs::exists(p);
}
}
