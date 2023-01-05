// стандартные библиотеки
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

// графические библиотеки
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

// локальные классы
#include "convertation.h"
#include "rules.h"

// удобные переименования
#define all(x) (x).begin(),(x).end()

using namespace std;
map <string, long double> form { // Структура данных, отвечающая за значение данной физической величины, в противном случае это 0. В теории, сюда можно закинуть рандомные константы для удобства дебага
        {"VO", 0},
        {"t", 0},
        {"t_end", 0},
        {"V_end", 0},
        {"m", 0},
        {"g", 9.81}

};
map <string, bool> known { // Структура данных, отвечающая за то, знаем ли мы данную физическую величину
        {"VO", false},
        {"t",  false},
        {"t_end", false},
        {"V_end", false},
        {"m", false},
        {"g", true}

};

vector <string> claims { // Вектор, хранящий физические формулы
    "F=m*a",
    "F_g=m*g",
    "p=F/s",
    "x=x0+V0*t+a*(t^2)/2",
    "F_arch=po_fluid*g*h"
};



// цвет фона
static sf::Color bgColor;
// значение цвета по умолчанию
float color[3] = {0.12f, 0.12f, 0.13f};

// задать цвет фона по вещественному массиву компонент
static void setColor(float * pDouble){
    bgColor.r = static_cast<sf::Uint8>(pDouble[0] * 255.f);
    bgColor.g = static_cast<sf::Uint8>(pDouble[1] * 255.f);
    bgColor.b = static_cast<sf::Uint8>(pDouble[2] * 255.f);
}
pair <long double, string> convert (long double input_convert, string quantity_convert);

void get_it(vector<string> &var, string equ); // Функция, закладывающая в ПУСТОЙ вектор, переданный по ссылке, величины, известные в формуле
void get_it_short(vector<string> &var, string equ); // Функция, закладывающая в ПУСТОЙ вектор, переданный по ссылке, величины, известные в формуле, ЗАБИВАЯ на степени. Это удобно, т.к. в некоторых формулах нужна лишь переменная, а ее значение мы знаем, тогда знаем значение ее квадрата и т.п.
template<typename T> void out_vec (vector<T>& a); // Функция вывода любого вектора
template<typename T> void out_test (vector<T>& a); // Функция тестового вывода вектора (вывод не распространяется в консоль тестирующей системы, в Сlion подсвечивается красным
inline void get_beauty (string inputt, vector<string>& input);
bool number_test (string s); // Эта функция проверяет,  является ли строка числом. Необходимо для того, чтобы понять, что на самом деле является неизвестным, а что константой
vector<string> find_form(vector<vector <string>> tex, vector<string> claims, vector<string> &input, map<string, bool> &known, map<string, double> &form);
long double convertation_system_value(string input);
bool num (char h);
short num_value(char h);
int main() {

    rules testing;
    testing.start();

    // time
    auto now = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(now);
    cerr << ctime(&end_time) << '\n';

    // пока что отключаем ускоряющие строчки для более удобного дебага
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
     */

    // устанавливаем точность обработки данных
    cout.precision(10);

    /*
    vector<vector<string>> tex; // в этом векторе лежат все данные формул (отсортированные)
    for(int i = 0; i < claims.size(); i++){
        vector <string> var;
        get_it_short(var, claims[i]);
        sort(var.begin(), var.end());
        tex.push_back(var);
        out_test(tex[i]); // ЗДЕСЬ ЛЕЖИТ ТЕСТОВЫЙ ВЫВОД ВЕКТОРА ФОРМУЛ
    } // Вектор заполнился всеми данными формул

    vector <string> input; // Вектор входных данных
    cin.ignore(); // команда, НЕОБХОДИМАЯ для нормальной работы гетлайна
    string input_full;
    getline(cin, input_full); //  Осторожно, ввод необходимо начинать С ПРОБЕЛА и В ОДНУ СТРОКУ. Используется getline, чтобы программа не зависала при каждом использовании из-за неизвестного количества переменных.
    get_beauty(input_full, input); // теперь в векторе input лежат данные задач
    sort(input.begin(), input.end()); // СОРТИРОВКА ВЕКТОРА ВВОДА, ПРИ ИЗМЕНЕНИИ СПОСОБА ВВОДА ТРЕБУЕТСЯ ОБРАТИТЬ ОСОБОЕ ВНИМАНИЕ
    */
    long double vvod;
    cin >> vvod;

    string s;
    cin >> s;

    pair<long double, string> ans = convert(vvod, s);
    cout << ans.first << " " << ans.second;


    return 0;
}


pair <long double, string> convert (long double input_convert, string quantity_convert)
{
    Сonvertation struct_convertation{input_convert,quantity_convert};
    pair<long double, string> an = struct_convertation.convert_in_class();
    cout << an.first << " " << an.second;
}

short num_value(char h)
{
    return int(h-'0');
}

bool num (char h)
{
    int ch = int(h-'0');
    if(ch == 1 || ch == 2 || ch == 3 || ch == 4 || ch == 5 || ch == 6 || ch == 7 || ch == 8 || ch == 9 || ch == 0 || h == '.')
    {
        return true;
    }
    else {
        return false;
    }
}
long double convertation_system_value(string input)
{
    long double value1 = 0;
    long double value2 = 0;
    string quantity;
    bool point = false;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == '.')
        {
            if(point == true)
            {
                cout << "FATAL ERROR";
            }
            point = true;
            continue;
        }
        if(num(input[i]) == true )
        {
            if(point == false){
                value1 *= 10;
                value1 += num_value(input[i]);
                continue;}
            else
            {
                value2 *= 10;
                value2 += num_value(input[i]);
            }
        }
        else {
            quantity += input[i];
        }
    }
    while(value2 > 1)
    {
        value2 /= 10;
    }
    return value1 + value2;
}




void get_it(vector<string> &var, string equ)
{
string period;
for(int i = 0; i < equ.size(); i++)
{
char h;
h = equ[i];
if(h != ')' && h != '(' && h != '=' && h != '*' && h != '-' && h != '/' && h != '+')
{
period += h;
}
else {
    if(number_test(period) == false)
    {
        var.push_back(period);
    }
period.clear();
}
}
if(period.empty())
{

} else
{
    if(number_test(period) == false)
    {
        var.push_back(period);
    }
period.clear();
}
return;
}

void get_it_short(vector<string> &var, string equ)
{
    string period;
    for(int i = 0; i < equ.size(); i++)
    {
        char h;
        h = equ[i];
        if(h != ')' && h != '(' && h != '=' && h != '*' && h != '-' && h != '/' && h != '+' && h!= '^')
        {
            period += h;
        }
        else {
            if(number_test(period) == false)
            {
                var.push_back(period);
            }
            period.clear();
        }
    }
    if(period.empty())
    {

    } else
    {
        if(number_test(period) == false)
        {
            var.push_back(period);
        }
        period.clear();
    }
    return;
}

template<typename T> void out_vec (vector<T>& a){
    for(int i = 0; i < a.size(); ++i){
        cout << a[i] << " ";
    }
    cout << '\n';
}

template<typename T> void out_test (vector<T>& a){
    for(int i = 0; i < a.size(); ++i){
        cerr << a[i] << " ";
    }
    cerr << '\n';
}

inline void get_beauty (string inputt, vector<string> &input)
{
    string gap;
    for(int i = 0; i < inputt.size(); i++)
    {
        if(inputt[i] == ' ')
        {
            input.push_back(gap);
            gap.clear();
        } else
        {
            gap += inputt[i];
        }
    }
    input.push_back(gap);
    gap.clear();
    return;
}

bool number_test (string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9' && s[i] != '.')
        {
            return false;
        }
    }
    return true;
}
vector<string> find_form(vector<vector <string>> tex, vector<string> claims, vector<string> &input, map<string, bool> &known, map<string, double> &form)
{
    vector <string> ret; // Вектор, который будет возвращать наша функция
    int new_value = 0;
    while(true){
      for(int i = 0; i < tex.size(); i++)
      {
          vector <string> interval = tex[i];
          bool flag = true;
          bool destr = false;
          for(int j = 0; j < interval.size(); j++)
          {
              bool flag2 = false;
              for(int l = 0; l < input.size(); l++)
              {
                  if(interval[j] == input[l])
                  {
                      flag2 = true;
                      break;
                  }
              }
              if(flag2 == false)
              {
                  if(flag == true)
                  {
                      flag = false;
                  }
                  else
                  {
                      destr = true;
                      break;
                  }
              }
          }
          if(destr == true) {
              continue;
          }
      }}
      return ret;
}
/*
 string equ;
 cin >> equ;
 string left, right;
 bool flag = true;

 for(int i = 0; i < equ.size(); i++)
 {
     if(equ[i] == '=')
     {
         flag = false;
         continue;
     }
     if(flag == true)
     {
         left = left + equ[i];
     } else
     {
         right = right + equ[i];
     }
 }

*/







// тут лежит SFMLщина
/*
sf::Font font;
if(!font.loadFromFile("/Users/admin/Desktop/nk57-monospace-cd-lt-it.ttf"))
{
    cout << "error";
    system("pause");
}
sf::Text text;
text.setFont(font);
text.setString("Hello WORLD");
text.setFillColor(sf::Color::Red);
text.setCharacterSize(240);
window.draw(text);


// создаём окно для рисования
sf::RenderWindow window(sf::VideoMode(1280, 720), "PhysSolver");
// задаём частоту перерисовки окна
window.setFramerateLimit(60);
// инициализация imgui+sfml
ImGui::SFML::Init(window);

// задаём цвет фона
setColor(color);

// переменная таймера
sf::Clock deltaClock;
// пока окно открыто, запускаем бесконечный цикл
while (window.isOpen()) {
// создаём событие sfml
sf::Event event;
// пока окно принимает события
while (window.pollEvent(event)) {
// отправляем события на обработку sfml
ImGui::SFML::ProcessEvent(event);

// если событие - это закрытие окна
if (event.type == sf::Event::Closed) {
// закрываем окно
window.close();
}
}

// запускаем обновление окна по таймеру с заданной частотой
ImGui::SFML::Update(window, deltaClock.restart());


// создаём окно управления
ImGui::Begin("Control");

// Инструмент выбора цвета
if (ImGui::ColorEdit3("Background color", color)) {
// код вызывается при изменении значения
// задаём цвет фона
setColor(color);
}
// конец рисование окна
ImGui::End();


// очищаем окно
window.clear(bgColor);
// рисуем по окну средствами imgui+sfml
ImGui::SFML::Render(window);
// отображаем изменения на окне
window.display();
}

// завершаем работу imgui+sfml
ImGui::SFML::Shutdown();*/