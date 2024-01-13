#include "util.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void util_str_replace_old(char* target, const char *search, const char *replace) {
    int target_str_len = strlen(target);
    int search_str_len = strlen(search);
    int replace_str_len = strlen(replace);

    // TODO: 
    // - find instance of substring
    // - use pos to replace with new string
    //   realloc if replace is larger than search
    //   strcat or strcpy?
    // - repeat
    // - realloc at the end to match str length (length until \0)

    char *temp = nullptr;
    size_t temp_len = 0;
    char *rolling_pos = target;
    char *remainder_pos = target;
    while(1) {
        rolling_pos = strstr(rolling_pos, search);
        if(rolling_pos == nullptr)
            break; // done
        
        temp_len += (rolling_pos - target);

        temp = realloc(temp, temp_len + replace_str_len);
        memcpy((temp + temp_len), replace, replace_str_len);

        rolling_pos += search_str_len;
        printf("%zu\n", temp_len);
        remainder_pos = rolling_pos;
    }

    if(temp != nullptr) {
        // figure out the remainder of the string, allocate that memory
        // and copy the rest into it
        char* remainder = (target + temp_len + search_str_len);
        int remainder_str_len = strlen(remainder);
        temp = realloc(temp, temp_len + remainder_str_len);

        printf("---original---\n%s\n---------\n", target);
        printf("---replaced---\n%s\n---------\n", temp);
        free(temp);
    }
}

void util_str_replace(char *target, const char *search, const char *replace) {
    int search_str_len = strlen(search);
    int replace_str_len = strlen(search);

    char* rolling_found_pos = target;
    size_t build_str_len = 0;
    char* build_str = nullptr;

    while(true) {
        char* found_pos = strstr(rolling_found_pos, search);

        if(found_pos == nullptr)
            break;
        
        size_t prev_build_str_len = build_str_len;
        size_t prev_str_len = found_pos - rolling_found_pos;
        build_str_len += prev_str_len + replace_str_len;

        printf("build_str_len: %zu\n", build_str_len);

        printf("before realloc\n");
        build_str = realloc(build_str, build_str_len);
        char *prev_build_str_pos = build_str + prev_build_str_len;
        printf("before memcpy 1\n");
        memcpy(prev_build_str_pos, rolling_found_pos, sizeof(char) * prev_str_len);

        if(replace_str_len != 0) {
            prev_build_str_pos += prev_str_len;
            printf("before memcpy 2\n");
            memcpy(prev_build_str_pos, replace, sizeof(char) * replace_str_len);
        }

        printf("end of loop\n");
        
        rolling_found_pos = found_pos + search_str_len;
    }

    if(build_str != nullptr) {
        size_t final_len = strlen(rolling_found_pos) + 1;
        printf("final_len: %zu\n", final_len);
        build_str = realloc(build_str, build_str_len + final_len);
        memcpy(build_str + build_str_len, rolling_found_pos, sizeof(char) * final_len);

        printf("---original---\n%s\n---------\n", target);
        printf("---replaced---\n%s\n---------\n", build_str);
        free(build_str);
    }
}
