//
// Created by Atovmian Artem on 01.01.2023.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#ifndef TEST_CMAKE_CONVERTATION_H
#define TEST_CMAKE_CONVERTATION_H

/* описание класса перевода в СИ:
 * В контейнерах типа map лежат приставки СИ и наиболее популярные физические величины, по сути на ввод классу дается
 * конструкция из двух частей - приставки СИ и самой величины. Целью класса становится всего лишь разделить строку
 * ввода на 2 и пересчитать величину и значение в международной СИ
 */


// как подключать это чудо в проекте  (for creators): div помогает в разделении на приставку и величину,
// convert_in_class отвечает за перевод "значение + величина + приставка" в СИ ("значение + величина СИ")

namespace std {

    class Сonvertation {
        // private нам не понадобится
    public:

        // прописываем переменной класса значение
        long double val;
        // прописываем переменной класса физическую величину
        string qua;

        // создаем коробку с приставками СИ
        map<string, long double> SI{
                {"T", 10e12},
                {"Г", 10e9},
                {"М", 10e6},
                {"К", 1000},
                {"г", 100},
                {"д", 0.1},
                {"с", 0.01},
                {"м", 0.001},
                {"мк",0.000001},
                {"н", 0.000000001},
                {"п", 0.000000000001},
                {"", 1},

                {"In is not correct", 239}
        };

        // коробка с физическими величинами, чтобы в перспективе переводить из каких-то кринжовых единиц измерения (морские мили)
        map<string, long double> quant {
                {"Гц", 1}, // герцы
                {"Н", 1}, // Ньютоны
                {"кг", 1}, // килограммы
                {"K", 1}, // кельвины
                {"Ом", 1}, // омы
                {"Ф", 1}, // фарады
                {"В", 1}, // вольты
                {"Кл", 1}, // кулоны
                {"Па", 1}, // паскали
                {"А", 1}, // амперы
                {"с", 1},// ceкунды
                {"моль",1},// моли
                {"м", 1}, //  метры
                {"Вт", 1}, // ватты
                {"Дж", 1}// Джоули


        };

        // создаем функцию класса для отделения приставки от величины
        pair<string, string> div (string inp)
        {
            bool correct_in = false;
            int SIZE = inp.size();

            if(quant[inp] != 0)
            {
                // в таком случае у нас в контейнере СИ уже есть такая величина --> переводить не нужно
                return make_pair("", inp);
            }
            for(int i = 1; i < SIZE; i++)
            {
                string a1 = inp.substr(0, i);
                string a2 = inp.substr(i, SIZE-i);
                if(SI[a1] != 0 && quant[a2] != 0)
                {
                    return make_pair(a1,a2);
                    correct_in = true;
                }
            }
            if(!correct_in)
            {
                // эта строка помогает защитить программу от неизвестных ошибок и понять, где проблема, указать
                // пользователю, что он неправильно ввел данные

                cerr << "CONVERTATION ERROR";
                return make_pair("In is not connect", " ");
            }
        }

        pair<long double, string> convert_in_class()
        {
            pair<string, string> f = div(qua);

            string exit_qua = f.second;
            string exit_mult = f.first;
            return make_pair(SI[exit_mult]*val, f.second);
        }



    };

} // std

#endif //TEST_CMAKE_CONVERTATION_H
