/*
* pursuit
* Created Time:  2014年05月17日 星期六 20时34分50秒
* File Name: dict.cpp
*/
#include "dict.h"
#include <sys/stat.h>

template <typename KeyType, typename ValueType>
Dict<KeyType, ValueType>::Dict(
        const char* dict_file,
        uint32_t dict_size,
        DICT_PARSE_FUNC dict_parse_func):
    _dict_parse_func(dict_parse_func),
    _last_reload_time(0UL),
    _dict_idx(0)
{
    if (dict_file == NULL) {
        _dict_file.clear();
    } else {
        _dict_file = dict_file;
    }
    
    _hash_size = 2 * dict_size;
}


template <typename KeyType, typename ValueType>
Dict<KeyType, ValueType>::~Dict()
{
    _dict_parse_func = NULL;
    _dict_file.clear();
}

template <typename KeyType, typename ValueType>
int Dict<KeyType, ValueType>::load_dict()
{
    int ret = reload_dict();
    if (ret == 0) {
        swap_dict();
    }
    return ret;
}

template <typename KeyType, typename ValueType>
void Dict<KeyType, ValueType>::swap_dict()
{
   _dict_idx = 1 - _dict_idx;
}


template <typename KeyType, typename ValueType>
int Dict<KeyType, ValueType>::reload_dict()
{
    struct stat st;
    if (stat(_dict_file.c_str(), &st) == -1) {
        std::cout << "could not retrieve info from " << _dict_file;
        return -1;
    }
    
    if (!S_ISREG(st.st_mode)) {
        std::cout <<" the file is not an ordinary file " << _dict_file;
        return -1;
    }
    
    if (st.st_mtime == _last_reload_time) {
        return -2;
    }
    
    if (_dict_file.empty()) {
        std::cout << "dict_file is empty";
        return -1;
    }
    
    if (_dict_parse_func == NULL) {
        std::cout << "dict_parse_func is NULL";
        return -1;
    }
    
    hash_map<KeyType, ValueType>& bg_dict = _dicts[1 - _dict_idx];
    bg_dict.clear();
    
    FILE* fp = fopen(_dict_file.c_str(), "r");
    if (fp == NULL) {
        std::cout << "open dict_file error" << _dict_file;
        return -1;
    }
    
    uint32_t total_count = 0;
    char line[DICT_MAX_LINE_LEN];
    int parse_token_num = 0;
    char* tokens[DICT_MAX_LINE_LEN];
    
    KeyType key;
    ValueType value;
    
    while (fgets(line, sizeof line, fp)) {
        size_t line_len = strlen(line);
        if (line_len == 0) {
            continue;
        }

        parse_token_num = get_tokens_ptr(tokens, line, DICT_MAX_LINE_LEN);
        if (parse_token_num < 0) {
            continue;
        }

        if (_dict_parse_func(tokens, parse_token_num, &key, &value) < 0) {
            std::cout << "parse error " << line;
            continue;
        }
        bg_dict[key] = value;
        total_count++;
    }

    fclose(fp);
    fp = NULL;
    
    if (total_count == 0) {
        std::cout <<"load total_count is zero";
        return -1;
    }

    _last_reload_time = st.st_mtime;

    std::cout << "load success ";
    
    return 0;
}
    
template <typename KeyType, typename ValueType>
int Dict<KeyType, ValueType>::seek(
        const KeyType& key, 
        ValueType* value)
{
    if (value == NULL || _dicts[_dict_idx].empty()) {
        std::cout << "invalid param or dict empty";
        return -1;
    }
    
    *value = _dicts[_dict_idx][key];
    return 0;
}

template <typename KeyType, typename ValueType>
int Dict<KeyType, ValueType>::get_tokens_ptr(
        char* token[],
        char* buf,
        uint32_t max_num)
{
    if (token == NULL || buf == NULL || max_num == 0) {
        std::cout << "invalid input parmeters";
        return -1;
    }
    
    char delim = '\t';
    char *p_begin = buf;
    char *p_end = NULL;
    uint32_t token_num = 0;
    
    while (p_begin && token_num < max_num) {
        token[token_num++] = p_begin;
        p_end = strchr(p_begin, delim);
        if (!p_end) {
            break;
        }
        *p_end = '\0';
        p_begin = p_end + 1;
    }
    
    if (p_begin) {
        p_end = strchr(p_begin, '\n');
        p_end && (*p_end = '\0');
        
        p_end = strchr(p_begin, '\r');
        p_end && (*p_end = '\0');
    }

    return token_num;
}
