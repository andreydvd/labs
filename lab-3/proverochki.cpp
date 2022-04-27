#include "proverochki.h"

#include <string>

bool is_digit(char c)//проверка цифра ли
{
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0')
        return true;
    return false;
}

bool is_normal_metric(string text)//проверяем метрику на корректную запись
{
    if (text == "")
        return false;
    for (int i = 0; i < text.length(); ++i){
        if (!is_digit(text[i]) && (text[i] != '-' && text[i] != '.')){
            return false;
        }
    }
    return true;
}


