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

typedef void *(t_generate_file)(const char*);

int main(int argc, const char * argv[]) {
    
    char path[1000];
    char fullpath[1000];
    char* name;
    char realname[1000];
    size_t namesize;
    if(argc < 2)
    {
        printf("Please provide the path to the LV2 plugin folder\n");
        return 1;
    }
    snprintf(path, 1000, "%s", argv[1]);
    name = basename(path);
    if(!name)
    {
        printf("Please provide the path to the LV2 plugin folder\n");
        return 1;
    }
    namesize = strnlen(name, 1000);
    if(namesize < 4)
    {
        printf("The LV2 plugin folder is invalid\n");
        return 1;
    }
    memcpy(realname, name, namesize-4);
    printf("looking for %s in %s\n", realname, path);
    snprintf(fullpath, 1000, "%s/%s.dylib", argv[1], realname);
    void* handle = dlopen(fullpath, RTLD_LAZY);
    if(handle)
    {
        char* error = NULL;
        t_generate_file* method = (t_generate_file *)dlsym(handle, "lv2_generate_ttl");
        if(method)
        {
            (*method)(realname);
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
