/*
    All what you need to start working with this library is copy 
    dirs.h file in your project.

    This library is not a production ready and has it own problems
    most of wich is known by author, so use it on your own risk

    Define an implementation and optionally DIRS_STRIP_PREFIXES for 
    ease of use. 
*/
#define DIRS_IMPLEMENTATION
#define DIRS_STRIP_PREFIXES
#include "dirs.h"

int main(void)
{
    /*
        To enumerate all items in the directory you can use
        dirs_contents dirs_get_contents(const char* path, dirs_content_type type);

        content type could be DIRS_ALL: for directories and files, 
        DIRS_FILES: files only and DIRS_DIRECTORY: directories only

        or dirs_contents get_contents(const char* path, dirs_content_type type);
        if you strip prefixes.

        Return value of this function is a struct, containing char** for contents
        and a contents_count - ammount of elements 
    */
    dirs_contents c = get_contents(".", DIRS_DIRECTORY);
    for (int i = 0; i < c.contents_count; i++)
    {
        printf("%s\n", c.values[i]);
    }

    /*
        To get the ammount of items in the directory you can use 
        int dirs_get_contents_count(const char* path, dirs_content_type type);

        or int get_contents_count(const char* path, dirs_content_type type);
        with stripped prefixes
    */

    printf("%s", get_contents_count(".", DIRS_ALL));

    return (0);
}