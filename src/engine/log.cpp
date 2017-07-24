/*
 MIT License
 
 Copyright (c) 2017 Elias Farhan
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <engine/log.h>

int Log::begin()
{
    char buffer[PATH_LIMIT];
    char filename[PATH_LIMIT];
    
    internal_handlers = new std::list<void(*)(int, const char*)>();
    
    // Create log/ directory if it doesn't exist yet.
    utils_data_path(buffer, PATH_LIMIT, "log");
    
    if (!utils_makedir(buffer))
    {
        printf("Warning: Failed to create config directory: %s...\n", buffer);
    }
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    utils_snprintf(filename, PATH_LIMIT, "log/%d-%d-%d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    utils_data_path(buffer, PATH_LIMIT, filename);
    
    internal_file = fopen(buffer, "a");
    
    if (internal_file != NULL)
    {
        utils_snprintf(buffer, PATH_LIMIT, "[ -- %d:%d:%d -- ]\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
        fwrite(buffer, 1, strlen(buffer), internal_file);
    }
    
    return internal_file != NULL;
}

void Log::handler(void(*handler)(int level, const char* message))
{
    internal_handlers->push_back(handler);
}

void Log::clear(void)
{
    internal_handlers->clear();
}

void Log::internal_log(int level, const char* message)
{
    for (auto it = internal_handlers->begin();
         it != internal_handlers->end();
         it++)
    {
        auto func = *it;
        func(level, message);
    }
    
    if (internal_file != NULL)
    {
        fwrite(message, 1, strlen(message), internal_file);
        fwrite("\n", 1, 1, internal_file);
        
        // Should we flush? I don't really know... Let's say we only do so
        // for critical errors.
        if (level == LOG_ERROR)
        {
            fflush(internal_file);
        }
    }
}

void Log::info(const char* format, ...)
{
    va_list args;
    char buffer[LOG_BUFSIZE];
    
    va_start(args, format);
    vsnprintf(buffer, LOG_BUFSIZE, format, args);
    va_end(args);
    
    internal_log(LOG_INFO, buffer);
}

void Log::error(const char* format, ...)
{
    va_list args;
    char buffer[LOG_BUFSIZE];
    
    va_start(args, format);
    vsnprintf(buffer, LOG_BUFSIZE, format, args);
    va_end(args);
    
    internal_log(LOG_ERROR, buffer);
}

void Log::debug(const char* format, ...)
{
#ifdef _DEBUG
    va_list args;
    char buffer[LOG_BUFSIZE];
    
    va_start(args, format);
    vsnprintf(buffer, LOG_BUFSIZE, format, args);
    va_end(args);
    
    internal_log(LOG_DEBUG, buffer);
#else
    (void)format;
#endif
}

void Log::finish()
{
    if (internal_file != NULL)
    {
        fclose(internal_file);
    }
    
    delete internal_handlers;
}
