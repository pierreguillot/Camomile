//
//  main.c
//  LV2FileMaker
//
//  Created by Guillot Pierre on 6/30/18.
//  Copyright © 2018 Pierre Guillot. All rights reserved.
//

#include <stdio.h>
#include <dlfcn.h>
#include <libgen.h>
#include <string.h>

#define MAX_STRING_LENGTH 1000

#ifdef __APPLE__
#define LIB_EXT "dylib"
#elif _WIN32
#define LIB_EXT "dll"
#else
#define LIB_EXT "so"
#endif

typedef void *(t_generate_file)(const char*);

int main(int argc, const char * argv[]) {
    if(argc < 3)
    {
        printf("Please provide the path to the LV2 plugin and the name of the plugin\n");
        return 1;
    }
    printf("looking for %s in %s\n", argv[2], argv[1]);
    void* handle = dlopen(argv[1], RTLD_LAZY);
    if(handle)
    {
        char* error = NULL;
        t_generate_file* method = (t_generate_file *)dlsym(handle, "lv2_generate_ttl");
        if(method)
        {
            (*method)(argv[2]);
        }
        else if((error = dlerror()) != NULL)
        {
            printf("error: %s", error);
        }
        dlclose(handle);
    }
    else
    {

    }
    return 0;
}
