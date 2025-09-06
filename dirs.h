/*
    This is a single header, Windows-specific 
    library created to ease the work with directories in c.

    This library is not a production ready and has it own problems,
    most of wich are known by author, so use it on your own risk

    Usage:
        Add dirs.h to your project
        In one source file define DIRS_IMPLEMENTATION before including it

        You can also define DIRS_STRIP_PREFIXES so you dont
        need to write dirs_ prefix before each function

    This library folows the single-header style popularized by 
    stb: github.com/nothings/stb.

    Usage of this library you can see in dirs.c
*/
#ifndef DIRS_H
#define DIRS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32

#include <windows.h>
#else
printf("Platform not supported, this library targets only Windows");

#endif // _WIN32

#ifdef DIRS_STRIP_PREFIXES
#define get_contents_count dirs_get_contents_count
#define get_contents_count_by_ext dirs_get_contents_count_by_ext

#define get_contents dirs_get_contents
#define get_contents_by_ext dirs_get_contents_by_ext

#define create_directory dirs_create_directory
#define create_file dirs_create_file

#define remove_directory dirs_remove_directory
#define remove_file dirs_remove_file
#endif // DIRS_STRIP_PREFIXES

typedef enum
{
    DIRS_ALL,
    DIRS_DIRECTORY,
    DIRS_FILE
} dirs_content_type;

typedef struct
{
    int contents_count;
    char** values;
} dirs_contents;


// *** DIRS_CORE ***
int dirs_get_contents_count(const char* path, dirs_content_type type);
int dirs_get_contents_count_by_ext(const char* path, const char* ext);

dirs_contents dirs_get_contents(const char* path, dirs_content_type type);
dirs_contents dirs_get_contents_by_ext(const char* path, const char* ext);

int dirs_create_directory(const char* path);
int dirs_create_file(const char* file_name);

int dirs_remove_directory(const char* path);
int dirs_remove_file(const char* file_name);

// *** DIRS_EXTRAS ***
static int dirs_get_path_data(const char* path, WIN32_FIND_DATA* fdFile,
                              HANDLE* hFind);

// *** DIRS_IMPLEMENTATION ***
#ifdef DIRS_IMPLEMENTATION
int dirs_get_contents_count(const char* path, dirs_content_type type)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind;
    dirs_get_path_data(path, &fdFile, &hFind);

    int content_count = 0;
    do
    {
        if (strcmp(fdFile.cFileName, ".") != 0 &&
            strcmp(fdFile.cFileName, "..") != 0)
        {
            if (type == DIRS_ALL)
            {
                content_count++;
                continue;
            }

            if (type == DIRS_DIRECTORY &&
                fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                content_count++;
                continue;
            }
            else if (type == DIRS_FILE &&
                     !(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                content_count++;
                continue;
            }
        }
    } while (FindNextFile(hFind, &fdFile) != 0);

    FindClose(hFind);
    return content_count;
}
int dirs_get_contents_count_by_ext(const char* path, const char* ext)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind;
    dirs_get_path_data(path, &fdFile, &hFind);

    int content_count = 0;
    do
    {
        if (strcmp(fdFile.cFileName, ".") != 0 &&
            strcmp(fdFile.cFileName, "..") != 0)
        {
            if (!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                const char* s_ext = strrchr(fdFile.cFileName, '.');
                if (s_ext == NULL)
                    s_ext = "";

                if (strcmp(s_ext, ext) == 0)
                {
                    content_count++;
                }
                continue;
            }
        }
    } while (FindNextFile(hFind, &fdFile) != 0);

    FindClose(hFind);
    return content_count;
}

dirs_contents dirs_get_contents(const char* path, dirs_content_type type)
{
    dirs_contents c = {0};
    c.contents_count = 0;

    WIN32_FIND_DATA fdFile;
    HANDLE hFind;
    dirs_get_path_data(path, &fdFile, &hFind);

    c.contents_count = dirs_get_contents_count(path, type);
    c.values = malloc(c.contents_count * sizeof(char));

    if (!c.values)
    {
        printf("'c.values' allocation error in function '%s'", __func__);
        free(c.values);
        c.contents_count = 0;
        return c;
    }

    int c_index = 0;
    char s_path[2048];

    do
    {
        if (strcmp(fdFile.cFileName, ".") != 0 &&
            strcmp(fdFile.cFileName, "..") != 0)
        {
            sprintf(s_path, "%s\\%s", path, fdFile.cFileName);
            if (type == DIRS_ALL)
            {
                c.values[c_index++] = strdup(s_path);
                continue;
            }

            if (type == DIRS_DIRECTORY &&
                fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                c.values[c_index++] = strdup(s_path);
                continue;
            }
            else if (type == DIRS_FILE &&
                     !(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                c.values[c_index++] = strdup(s_path);
                continue;
            }
        }
    } while (FindNextFile(hFind, &fdFile) != 0);
    return c;
}
dirs_contents dirs_get_contents_by_ext(const char* path, const char* ext)
{
    dirs_contents c = {0};
    c.contents_count = 0;

    WIN32_FIND_DATA fdFile;
    HANDLE hFind;
    dirs_get_path_data(path, &fdFile, &hFind);

    c.contents_count = dirs_get_contents_count_by_ext(path, ext);
    c.values = malloc(c.contents_count * sizeof(char));
    if (!c.values)
    {
        printf("'c.values' allocation error in function '%s'", __func__);
        free(c.values);
        c.contents_count = 0;
        return c;
    }

    int c_index = 0;
    char s_path[2048];

    do
    {
        if (strcmp(fdFile.cFileName, ".") != 0 &&
            strcmp(fdFile.cFileName, "..") != 0)
        {
            sprintf(s_path, "%s\\%s", path, fdFile.cFileName);
            if (!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                const char* s_ext = strrchr(fdFile.cFileName, '.');
                if (s_ext == NULL)
                    s_ext = "";

                if (strcmp(s_ext, ext) == 0)
                {
                    c.values[c_index++] = strdup(s_path);
                }
                continue;
            }
        }
    } while (FindNextFile(hFind, &fdFile) != 0);
    return c;
}

int dirs_create_directory(const char* path)
{
    DWORD dwAttrib = GetFileAttributes(path);
    if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
    {

        int hresult = _mkdir(path);
        return hresult;
    }
    return 1;
}
int dirs_create_file(const char* file_name)
{
    FILE* fp;
    fp = fopen(file_name, "w");
    if (fp)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        return -1;
    }
}

int dirs_remove_directory(const char* path)
{
    int dir_exists = 0;

    DWORD dwAttrib = GetFileAttributes(path);
    if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        dir_exists = 1;
    }

    if (dir_exists)
    {

        WIN32_FIND_DATA fdFile;
        HANDLE hFind;
        dirs_get_path_data(path, &fdFile, &hFind);

        char s_path[2048];
        do
        {
            if (strcmp(fdFile.cFileName, ".") != 0 &&
                strcmp(fdFile.cFileName, "..") != 0)
            {
                sprintf(s_path, "%s\\%s", path, fdFile.cFileName);
                if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    dirs_remove_directory(s_path);
                    RemoveDirectory(s_path);
                }
                else
                {
                    dirs_remove_file(s_path);
                }
            }
        } while (FindNextFile(hFind, &fdFile) != 0);
    }

    RemoveDirectory(path);
    return 0;
}
int dirs_remove_file(const char* file_name)
{
    int hresult = remove(file_name);
    return hresult;
}

static int dirs_get_path_data(const char* path, WIN32_FIND_DATA* fdFile,
                              HANDLE* hFind)
{
    *hFind = NULL;

    char s_path[2048];
    sprintf(s_path, "%s\\*.*", path);

    if ((*hFind = FindFirstFile(s_path, fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Directory '%s' could not be reached or found", s_path);
        return FALSE;
    }

    return TRUE;
}

#endif //DIRS_IMPLEMENTATION

#endif //DIRS_H

/*
    This project is guarded by MIT license
========================================================================================

    MIT License

    Copyright (c) 2025 Nevostruev Alexander

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
========================================================================================
*/