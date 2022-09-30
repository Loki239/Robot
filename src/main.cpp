#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include <valarray>
#include <iostream>

// Ширина окна
static const int WINDOW_SIZE_X = 800;
// Высота окна
static const int WINDOW_SIZE_Y = 800;

// цвет фона
static sf::Color bgColor;
// значение цвета по умолчанию
float color[3] = {0.12f, 0.12f, 0.13f};

// преобразование целочисленного вектора в вещественный
static sf::Vector2f toFloat(sf::Vector2i v) {
    return {(float) v.x, (float) v.y};
}

// преобразование вещественного вектора в целочисленный
static sf::Vector2i toInt(sf::Vector2f v) {
    return {(int) v.x, (int) v.y};
}

// поворот вектора на угол
static sf::Vector2f rotated(sf::Vector2f v, float a) {
    return {
            v.x * std::cos(a) - v.y * std::sin(a),
            v.x * std::sin(a) + v.y * std::cos(a)
    };
}

// длина вектора
static float length(sf::Vector2f f) {
    return std::sqrt(f.x * f.x + f.y * f.y);
}

// нормирование вектора
static sf::Vector2f norm(sf::Vector2f v) {
    float ln = length(v);
    return {v.x / ln, v.y / ln};
}

// векторное умножение двумерных векторов
static float cross(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.y - a.y * b.x;
}

// расстояние от прямой, образованной первыми двумя точками, до третьей
static float distance(sf::Vector2f pointA, sf::Vector2f pointB, sf::Vector2f pointC) {
    float a = pointA.y - pointB.y;
    float b = pointB.x - pointA.x;
    float c = pointA.x * pointB.y - pointB.x * pointA.y;

    return std::abs(a * pointC.x + b * pointC.y + c) / std::sqrt(a * a + b * b);
}

// сумма векторов
static sf::Vector2f sum(sf::Vector2f a, sf::Vector2f b) {
    return {a.x + b.x, a.y + b.y};
}

// разность векторов
static sf::Vector2f subtract(sf::Vector2f a, sf::Vector2f b) {
    return {a.x - b.x, a.y - b.y};
}

// сумма векторов
static sf::Vector2i sum(sf::Vector2i a, sf::Vector2i b) {
    return {a.x + b.x, a.y + b.y};
}

// разность векторов
static sf::Vector2i subtract(sf::Vector2i a, sf::Vector2i b) {
    return {a.x - b.x, a.y - b.y};
}

// умножение вектора на число
static sf::Vector2f mul(sf::Vector2f a, float b) {
    return {a.x * b, a.y * b};
}


// знак переменной
static float sign(float a) {
    if (a > 0)
        return -1;
    else if (a < 0)
        return 1;
    else
        return 0;
}

// задать цвет фона по вещественному массиву компонент
static void setColor(float *pDouble) {
    bgColor.r = static_cast<sf::Uint8>(pDouble[0] * 255.f);
    bgColor.g = static_cast<sf::Uint8>(pDouble[1] * 255.f);
    bgColor.b = static_cast<sf::Uint8>(pDouble[2] * 255.f);
}

// нарисовать точку
void renderPoint() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();
    // рисуем точку
    pDrawList->AddCircleFilled(
            sf::Vector2i(400, 400),
            3,
            ImColor(100, 200, 150),
            20
    );
}

// нарисовать линию
void renderLine() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // опорные точки линии
    sf::Vector2i pointA = {450, 550};
    sf::Vector2i pointB = {550, 450};

    // получаем максимальную длину отрезка на экране, как длину диагонали экрана
    double maxDistance = std::sqrt(WINDOW_SIZE_X * WINDOW_SIZE_X + WINDOW_SIZE_Y * WINDOW_SIZE_Y);

    // получаем новые точки для рисования, которые гарантируют, что линия
    // будет нарисована до границ экрана
    sf::Vector2i renderPointA = sf::Vector2i(
            pointA.x + (int) ((pointA.x - pointB.x) * maxDistance),
            pointA.y + (int) ((pointA.y - pointB.y) * maxDistance)
    );
    sf::Vector2i renderPointB = sf::Vector2i(
            pointA.x - (int) ((pointA.x - pointB.x) * maxDistance),
            pointA.y - (int) ((pointA.y - pointB.y) * maxDistance)
    );

    // рисуем линию
    pDrawList->AddLine(
            renderPointA,
            renderPointB,
            ImColor(200, 150, 100),
            0.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(200, 100, 150),
            1.5f
    );
}

// рисование треугольников
void renderTriangles() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();
    // опорные точки треугольника
    sf::Vector2i pointA = {430, 530};
    sf::Vector2i pointB = {530, 400};
    sf::Vector2i pointC = {450, 450};

    // рисуем отрезок
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(200, 150, 150),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointB,
            pointC,
            ImColor(200, 150, 150),
            1.5f
    );
    // рисуем отрезок
    pDrawList->AddLine(
            pointC,
            pointA,
            ImColor(200, 150, 150),
            1.5f
    );


    // опорные точки треугольника
    pointA = {430, 300};
    pointB = {530, 310};
    pointC = {350, 250};


    // рисуем треугольник
    pDrawList->AddTriangleFilled(
            pointA,
            pointB,
            pointC,
            ImColor(150, 200, 150)
    );

}

// рисуем круг и окружность
void renderCircles() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();
    // опорная точка окружности
    sf::Vector2i pointA = {230, 300};

    // рисуем окружность
    pDrawList->AddCircle(
            pointA,
            30,
            ImColor(150, 200, 150)
    );

    // опорная точка круга
    pointA = {230, 450};

    // рисуем окружность
    pDrawList->AddCircleFilled(
            pointA,
            30,
            ImColor(150, 150, 200)
    );
}

// рисуем параллельный прямоугольник
void renderParallelRect() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // опорные точки параллельного четырёхугольника
    sf::Vector2i pointA = {50, 50};
    sf::Vector2i pointC = {200, 150};

    // вспомогательные точки параллельного четырёхугольника
    sf::Vector2i pointB = {pointA.x, pointC.y};
    sf::Vector2i pointD = {pointC.x, pointA.y};

    // рисуем отрезок
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(200, 150, 100),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointB,
            pointC,
            ImColor(200, 150, 100),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointC,
            pointD,
            ImColor(200, 150, 100),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointD,
            pointA,
            ImColor(200, 150, 100),
            1.5f
    );
}

// рисуем прямоугольник
void renderRect() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // первая вершина
    sf::Vector2i pointA = {300, 100};
    // вторая вершина
    sf::Vector2i pointB = {500, 200};
    // точка на противоположной стороне
    sf::Vector2i pointP = {300, 50};

    // рассчитываем векторы для векторного умножения
    sf::Vector2i AB = subtract(pointB, pointA);
    sf::Vector2i AP = subtract(pointP, pointA);

    // определяем направление смещения(добавляем минус, т.к. ось y СК экрана смотрит вниз.
    float direction = -sign(cross(toFloat(AB), toFloat(AP)));

    // рассчитываем расстояние от прямой до точки
    float dist = distance(toFloat(pointA), toFloat(pointB), toFloat(pointP));

    // получаем единичный вектор направления смещения
    sf::Vector2f n = norm(rotated(toFloat(AB), ((float) M_PI / 2.f * direction)));

    // получаем вектор смещения
    sf::Vector2i offset = toInt(mul(n, dist));

    // находим координаты вторых двух вершин прямоугольника
    sf::Vector2i pointC = sum(pointB, offset);
    sf::Vector2i pointD = sum(pointA, offset);

    // рисуем отрезок
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(100, 150, 200),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointB,
            pointC,
            ImColor(100, 150, 200),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointC,
            pointD,
            ImColor(100, 150, 200),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointD,
            pointA,
            ImColor(100, 150, 200),
            1.5f
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointA,
            3,
            ImColor(200, 100, 150)
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointB,
            3,
            ImColor(200, 100, 150)
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointP,
            3,
            ImColor(200, 100, 150)
    );
}

// рисуем параллелограмм
void renderParallel() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // первая вершина
    sf::Vector2i pointA = {650, 150};
    // вторая вершина
    sf::Vector2i pointB = {600, 50};
    // третья вершина
    sf::Vector2i pointC = {700, 100};

    // определяем вектор смещения
    sf::Vector2i AB = subtract(pointA, pointB);
    sf::Vector2i pointD = sum(pointC, AB);

    // рисуем отрезок
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(150, 100, 200),
            1.5f
    );
    // рисуем отрезок
    pDrawList->AddLine(
            pointB,
            pointC,
            ImColor(150, 100, 200),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointC,
            pointD,
            ImColor(150, 100, 200),
            1.5f
    );

    // рисуем отрезок
    pDrawList->AddLine(
            pointD,
            pointA,
            ImColor(150, 100, 200),
            1.5f
    );


    // рисуем опорные точки

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointA,
            3,
            ImColor(200, 100, 150)
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointB,
            3,
            ImColor(200, 100, 150)
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointC,
            3,
            ImColor(200, 100, 150)
    );

}

// рисуем угол
void renderCorner() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // вершина угла
    sf::Vector2i pointA = {150, 400};
    // опорные точки
    sf::Vector2i pointB = {50, 300};
    sf::Vector2i pointC = {80, 500};

    // определяем вектор смещения
    sf::Vector2i AB = subtract(pointB, pointA);
    sf::Vector2i AC = subtract(pointC, pointA);


    // получаем максимальную длину отрезка на экране, как длину диагонали экрана
    double maxDistance = std::sqrt(WINDOW_SIZE_X * WINDOW_SIZE_X + WINDOW_SIZE_Y * WINDOW_SIZE_Y);

    // получаем новые точки для рисования, которые гарантируют, что линия
    // будет нарисована до границ экрана
    sf::Vector2i renderPointB = sum(pointA, toInt(mul(toFloat(AB), maxDistance)));
    sf::Vector2i renderPointC = sum(pointA, toInt(mul(toFloat(AC), maxDistance)));


    // рисуем линию
    pDrawList->AddLine(
            pointA,
            renderPointB,
            ImColor(200, 150, 100),
            0.5f
    );


    // рисуем линию
    pDrawList->AddLine(
            pointA,
            renderPointC,
            ImColor(200, 150, 100),
            0.5f
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointA,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            pointB,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            pointC,
            3,
            ImColor(200, 100, 150)
    );
}

// рисуем полосу
void renderBand() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // первая точка
    sf::Vector2i pointA = {400, 700};
    // вторая точка
    sf::Vector2i pointB = {700, 500};
    // отрезок AB
    sf::Vector2i AB = subtract(pointB, pointA);
    // толщина линии
    float width = 40.f;

    // вектор направления для откладывания ширины
    sf::Vector2f wd = norm(rotated(toFloat(AB), M_PI / 2));
    sf::Vector2i widthDirection = toInt(mul(wd, width / 2));


    // получаем максимальную длину отрезка на экране, как длину диагонали экрана
    double maxDistance = std::sqrt(WINDOW_SIZE_X * WINDOW_SIZE_X + WINDOW_SIZE_Y * WINDOW_SIZE_Y);

    sf::Vector2i lineDirection = toInt(mul(norm(toFloat(AB)), maxDistance));

    // получаем опорные точки для откладывания направления
    sf::Vector2i basePointA = sum(pointA, widthDirection);
    sf::Vector2i basePointB = subtract(pointA, widthDirection);

    // получаем точки рисования
    sf::Vector2i renderPointA = sum(basePointA, lineDirection);
    sf::Vector2i renderPointB = sum(basePointB, lineDirection);
    sf::Vector2i renderPointC = subtract(basePointB, lineDirection);
    sf::Vector2i renderPointD = subtract(basePointA, lineDirection);

    // рисуем линию
    pDrawList->AddLine(
            renderPointB,
            renderPointC,
            ImColor(150, 200, 100),
            0.5f
    );

    // рисуем линию
    pDrawList->AddLine(
            renderPointD,
            renderPointA,
            ImColor(150, 200, 100),
            0.5f
    );



    // рисуем точку
    pDrawList->AddCircleFilled(
            pointA,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            pointB,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            basePointA,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            basePointB,
            3,
            ImColor(200, 100, 150)
    );
}

// рисуем широкий луч
void renderWideBeam() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // первая точка
    sf::Vector2i pointA = {100, 600};
    // опорные точки
    sf::Vector2i pointB = {150, 650};
    // отрезок AB
    sf::Vector2i AB = subtract(pointB, pointA);


    // получаем максимальную длину отрезка на экране, как длину диагонали экрана
    double maxDistance = std::sqrt(WINDOW_SIZE_X * WINDOW_SIZE_X + WINDOW_SIZE_Y * WINDOW_SIZE_Y);

    // создаём вектор направления для рисования условно бесконечной полосы
    sf::Vector2i lineDirection = toInt(mul(norm(rotated(toFloat(AB), M_PI / 2)), maxDistance));

    // получаем точки рисования
    sf::Vector2i renderPointC = sum(pointA, lineDirection);
    sf::Vector2i renderPointD = sum(pointB, lineDirection);

    // рисуем линию
    pDrawList->AddLine(
            pointA,
            pointB,
            ImColor(150, 200, 100),
            0.5f
    );

    // рисуем линию
    pDrawList->AddLine(
            pointA,
            renderPointC,
            ImColor(150, 200, 100),
            0.5f
    );

    // рисуем линию
    pDrawList->AddLine(
            pointB,
            renderPointD,
            ImColor(150, 200, 100),
            0.5f
    );

    // рисуем точку
    pDrawList->AddCircleFilled(
            pointA,
            3,
            ImColor(200, 100, 150)
    );
    // рисуем точку
    pDrawList->AddCircleFilled(
            pointB,
            3,
            ImColor(200, 100, 150)
    );

}


// рисуем многоугольник
void renderPolygon() {
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    // список вершин
    ImVec2 lst[5] = {
            ImVec2(200, 550),
            ImVec2(250, 550),
            ImVec2(290, 600),
            ImVec2(190, 700),
            ImVec2(160, 700),
    };

    // рисуем закрашенный многоугольник
    pDrawList->AddConvexPolyFilled(
            lst,
            5,
            ImColor(150, 150, 200)
    );

    // рисуем многоугольник линиями
    pDrawList->AddPolyline(
            lst,
            5,
            ImColor(200, 200, 200),
            ImDrawListFlags_AntiAliasedLines,
            2.5
    );

    // рисуем опорные точки
    for (ImVec2 pos: lst) {
        // рисуем точку
        pDrawList->AddCircleFilled(
                pos,
                3,
                ImColor(200, 100, 150)
        );
    }

}


// рисование задачи на невидимом окне во всё окно приложения
void RenderTask() {
    // задаём левый верхний край невидимого окна
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    // задаём правый нижний край невидимого окна
    ImGui::SetNextWindowSize(ImVec2(WINDOW_SIZE_X, WINDOW_SIZE_Y));
    // создаём невидимое окно
    ImGui::Begin("Overlay", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);


    // нарисовать точку
    renderPoint();
    // нарисовать линию
    renderLine();
    // рисование треугольников
    renderTriangles();
    // рисуем круг и окружность
    renderCircles();
    // рисуем параллельный прямоугольник
    renderParallelRect();
    // рисуем прямоугольник
    renderRect();
    // рисуем параллелограмм
    renderParallel();
    // рисуем угол
    renderCorner();
    // рисуем полосу
    renderBand();
    // рисуем широкий луч
    renderWideBeam();
    // рисуем многоугольник
    renderPolygon();


    // заканчиваем рисование окна
    ImGui::End();

}


// главный метод
int main() {
    // создаём окно для рисования
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Geometry Project 10");
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

        // рисование задания
        RenderTask();

        // очищаем окно
        window.clear(bgColor);
        // рисуем по окну средствами imgui+sfml
        ImGui::SFML::Render(window);
        // отображаем изменения на окне
        window.display();
    }

    // завершаем работу imgui+sfml
    ImGui::SFML::Shutdown();

    return 0;
}