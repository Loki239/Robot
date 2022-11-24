## PhysSolver

2022, 10-1, Атовмян Артем, Плотникова Анастасия

C++

Тестовый сервер находится [здесь](https://r2d.buran.center/).

### Описание:

В данный момент программа умеет рассчитывать тривиальную баллистику.

![workingprogramm](/workingprogramm1)

### План работы:

- [ ] Изучение необходимых алгоритмов и структур языка С++ (10 часов)
   - [x] Конструктор класса map (5 часов)
   - [ ] ООП (классы и структуры) (5 часов)

  Команде разработчиков потребовались более глубинные знания языка
  
- [ ] Установка движка symengine, необходимого для парсинга синтаксических структур (15 часов)
   - [ ] разбор авторской документации (5 часов)
   - [ ] установка движка, тест функционала (5 часов)
   - [ ] разработка улучшений для конкретного проекта (5 часов)
   
  Symengine - новый современный проект на Github, который позволит облегчить операции с переменными и даст возможность осуществить парсинг арифметических синтаксических структур 
  
- [ ] Реализация способа хранения типов, значений переменных, связь с формулами. (10 часов)
    + [x] основной механизм (5 часов)
    + [ ] подключение справочных вычислительных материалов (формул) (5 часов)
    
  Программа начнет рассчитывать все неизвестные величины, которые она может рассчитать, пользуясь подключенным набором вычислительных материалов.
      
- [ ] Модель движения тела, брошенного под углом к горизонту (10 часов)
    - [ ] консольная программа расчета требуемых параметров (5 часов)
    - [ ] визуализация движения тела (5 часов)
    
  Программа начнет рассчитывать неизвестные параметры движения тела, брошенного под углом к горизонту, принимая минимальные данные от пользователя.
  
- [ ] Кинематические задачи (10 часов)
    + [ ] равноускоренное (в т.ч. равномерное) движение вдоль прямой (5 часов)
    + [ ] равноускоренное движение в плоскости (5 часов)
    
  Программа начнет решать кинетические задачи, в частности, главную задачу кинематики: находить все параметры движения тела в данный момент времени при заданном начальном состоянии.

- [ ] Закон сохранения энергии (15 часов)
    + [ ] математический маятник (5 часов)
    + [ ] пружинный маятник (5 часов)
    + [ ] произвольный случай для одного тела (полные данные о начальном и конечном состоянии) (5 часов)

  Программа научится решать простые задачи на законы сохранения и изменения энергии.
  
- [ ] Электрические цепи (15 часов)
    + [ ] простые электрические цепи (5 часов)
    + [ ] электрические цепи с ВАХ (5 часов)
    + [ ] законы Кирхгофа (5 часов)

  Программа научится решать простые задачи на электрические цепи.
  
- [ ] Блок с теоретическим материалом и описанием функционала программы (20 часов)
    + [ ] список поддерживаемых формул (5 часов)
    + [ ] список поддерживаемых задач, примеры (5 часов)
    + [ ] теоретические материалы по темам (5 часов)
    + [ ] вызов списка основных формул в процессе решения задачи (5 часов)
    
  Программа научится вызывать список основных формул, необходимых для решения задачи. Пользователь получит доступ к теоретическим материалам и инструкцию по использованию программы.
  Создание сервера.
  
- [ ] Web-сайт (20 часов)
    + [ ] подключение к серверу (5 часов)
    + [ ] блок решения задач (5 часов)
    + [ ] блок с теоретическими материалами (5 часов)
    + [ ] cетевые команды (5 часов)
    
  Финальная стадия. Пользователь получит возможность взаимодействовать непосредственно с сайтом, используя полный функционал программы. Выпуск готового продукта.
