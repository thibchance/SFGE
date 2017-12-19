#ifndef SFGE_FILE_UTILITY_H
#define SFGE_FILE_UTILITY_H

#include <experimental/filesystem>
// for convenience
namespace fs = std::experimental::filesystem;

namespace sfge
{
	bool FileExists(std::string& filename);
}

#endif