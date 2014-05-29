/*
* pursuit
* Created Time:  2014年05月17日 星期六 20时16分52秒
* File Name: dict.h
*/

#ifndef DICT_H
#define DICT_H

#include <ctime>
#include <ext/hash_map>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdint.h>
using namespace __gnu_cxx;


const uint32_t DICT_MAX_PATH_LEN = 1024;
const uint32_t DICT_MAX_LINE_LEN = 1024 * 4;

template<typename KeyType, typename ValueType>
class Dict {
public:
    typedef int (*DICT_PARSE_FUNC)(
            char* tokens[],
            uint32_t token_num,
            KeyType* key,
            ValueType* value);
    Dict(const char* dict_file,
            uint32_t dict_size,
            DICT_PARSE_FUNC dict_parse_func);
    
    ~Dict();
    int load_dict();
    int reload_dict();
    int seek(const KeyType& key, ValueType* value);
    void swap_dict();
private:
    int get_tokens_ptr(char* token[], char* buf, uint32_t max_num);
private:
    std::string _dict_file;
    uint32_t _dict_line_num;
    uint32_t _hash_size;
    time_t _last_reload_time;
    
    DICT_PARSE_FUNC _dict_parse_func;
    uint32_t _dict_idx;

    hash_map<KeyType, ValueType> _dicts[2];
};
        

#endif
