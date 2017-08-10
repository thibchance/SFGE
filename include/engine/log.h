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

#ifndef SFGE_LOG_H
#define SFGE_LOG_H

#include <engine/utility.h>
#include <engine/globals.h>

#include <stdarg.h>
#include <stdio.h> // vsnprintf
#include <string.h>
#include <time.h>
#include <list>
#include <iostream>

#define LOG_BUFSIZE 512

class Log: public Singleton
{
private:
    std::list<void(*)(int, const char*)>* internal_handlers;
    FILE* internal_file;
    
    void internal_log(int level, const char* message);
public:
    int begin();
    void handler(void(*)(int level, const char* message));
    void clear(void);
    
    void info(const char* format, ...);
    void error(const char* format, ...);
    void debug(const char* format, ...);
    
    void finish();
};
#endif // SFGE_LOG_H
