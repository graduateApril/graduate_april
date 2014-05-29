/*
* pursuit
* Created Time:  2014年05月18日 星期日 17时45分54秒
* File Name: example.cpp
*/
#include "dict.cpp"
using namespace std;

int dict_parse_func(char* tokens[],
        unsigned int token_num, 
        int* key, 
        int* value)
{
    if (token_num != 2) {
        std::cout << "token_num is not equal to 2";
        return -1;
    }
    *key = atoi(tokens[0]);
    *value = atoi(tokens[1]);
    return 0;
}

int main()
{
    Dict<int, int>* dict = new Dict<int, int>("data.sign", 10, dict_parse_func);
    dict->load_dict();
    int value = 0;
    dict->seek(1, &value);
    cout << value << endl;
    while (cin >> value) {
        if (dict->reload_dict() == 0) {
            dict->swap_dict();
            cout << "swap_dict success" << endl;
        }
        dict->seek(1, &value);
        cout << value << endl;
    }
}
    
