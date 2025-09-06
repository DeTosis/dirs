#define DIRS_IMPLEMENTATION
#define DIRS_STRIP_PREFIXES
#include "dirs.h"

int main(void)
{
    /*
        To enumerate all items in the directory you can use
        dirs_contents dirs_get_contents(const char* path, dirs_content_type type);

        content type could be 
        DIRS_ALL: for directories and files, 
        DIRS_FILES: files only, and 
        DIRS_DIRECTORY: directories only;

        or dirs_contents get_contents(const char* path, dirs_content_type type);
        if you strip prefixes.

        Return value of this function is a struct, containing char** for contents
        and a contents_count - ammount of elements 
    */
    // dirs_contents c = get_contents(".", DIRS_DIRECTORY);
    // for (int i = 0; i < c.contents_count; i++)
    // {
    //     printf("%s\n", c.values[i]);
    // }

    /*
        To get the ammount of items in the directory you can use 
        int dirs_get_contents_count(const char* path, dirs_content_type type);

        or int get_contents_count(const char* path, dirs_content_type type);
        with stripped prefixes

        content_type is described earlier.
    */
    //printf("%d", get_contents_count(".", DIRS_ALL));

    /*
        int dirs_get_contents_count_by_ext(const char* path, const char* ext) or 
        int get_contents_count_by_ext(const char* path, const char* ext) returns
        the number of items in a directory based by extencion provided
    */
    //printf("%d", get_contents_count_by_ext(".", ".c"));

    /*
        dirs_contents dirs_get_contents_by_ext(const char* path, const char* ext) or 
        dirs_contents get_contents_by_ext(const char* path, const char* ext) returns 
        dirs_contents struct of files filtered by extencion and  
        contents_count - ammount of elements  
    */
    // dirs_contents c = get_contents_by_ext(".", ".c");
    // for (int i = 0; i < c.contents_count; i++)
    // {
    //     printf("%s\n", c.values[i]);
    // }

    /*
        int dirs_create_directory(const char* path) and int dirs_create_file(const char* file_name)
        should be self explanatory at this point, stripped versions: 
        int create_directory(const char* path) and int create_file(const char* file_name). 
    */
    // create_directory(".\\build");
    // create_file(".\\build\\test.txt");

    /*
        int dirs_remove_directory(const char* path) and int dirs_remove_file(const char* file_name)
        removes directories and files.

        be aware that dirs_remove_directory removes directory recursivly, removeing all subfolders and files
        before. 

        stripped: remove_directory(const char* path) remove_file(const char* file_name)
    */
    // remove_directory(".\\build");
    // remove_file(".\\a");

    /*
        char* dirs_read_entire_file(const char* path) reads file provided in a buffer, returns NULL
        in case of any error
        stripped: char* read_entire_file(const char* path)
    
        NOTE: read_entire_file nullterminates buffer;
    */
    // char* c = read_entire_file("a.txt");
    // printf("%s", c);

    /*
        int dirs_write_entire_file(const char* path, const char* buffer); writes entire file from the buffer,
        NOTE: file is overwritten, contents are cleared
        stripped: int write_entire_file(const char* path, const char* buffer);
    */
    //write_entire_file("a.txt", "a");

    /*
        int dirs_append_file_start(const char* path, const char* buffer) and
        int dirs_append_file_end(const char* path, const char* buffer)
    
        append file contents respectivly to ther names 
        stripped: int append_file_start(const char* path, const char* buffer) and
        int append_file_end(const char* path, const char* buffer)
    */
    //append_file_start("a.txt", "[s]");
    //append_file_end("a.txt", "[e]");

    return (0);
}