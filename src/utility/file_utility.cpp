#include <utility/file_utility.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace sfge
{
bool FileExists(std::string & filename)
{
#ifdef WIN32
	fs::path p = filename;
	return fs::exists(p);
#else
    std::ifstream infile(filename);
    return infile.good();
#endif
}
bool IsRegularFile(std::string& filename)
{
#ifdef WIN32
    fs::path p = filename;
    return fs::is_regular_file(p);
#else
    struct stat pathStat;
    stat(filename.c_str(), &pathStat);
    return S_ISREG(pathStat.st_mode);
#endif
}
}
