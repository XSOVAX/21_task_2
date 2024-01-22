## <font color="tomato">Модель данных для посёлка</font>

Используя структуры данных, создайте подробную модель посёлка. Что известно:
* Посёлок состоит из участков, и у каждого участка есть свой номер.
* На любом участке может стоять жилой дом, а также могут быть и другие сооружения:
  * гараж,
  * сарай (бытовка),
  * баня.

Далее:
* У каждого здания есть информация о площади, которую оно занимает на участке.
* В доме может быть 1–3 этажа, на этаже — 2–4 комнаты:
  * спальня,
  * кухня,
  * ванная,
  * детская,
  * гостиная.

* У каждого этажа есть информация о количестве комнат и высоте потолка на этаже.
* У каждой комнаты есть информация о занимаемой площади.
* В доме и бане может быть печь с трубой.

Для всех упомянутых сущностей нуж 

Структуры должны быть:
* связными и легко расширяемыми,
* без дублирующих конструкций.

Пользователь заполняет данные о посёлке: вводит общее количество участков, а потом детализирует каждый.

Сначала указывается количество построек на участке, 
а затем — информация, какие это постройки, 
сколько этажей в доме, 
какие комнаты на этажах.

После ввода данных можно рассчитать суммарный параметр, 
например процент земли, занимаемой постройками, от общей площади посёлка. 
Главное в этой задаче не операция подсчёта, а структуры данных.

Перечислять комнаты и типы зданий нужно следующим образом:

```c++
enum room_type { living, children }
```

Затем нужно использовать полученный тип внутри структуры. 
Алгоритм заполнения каждого объекта одинаковый:
* создать объект нужного типа,
* ввести с клавиатуры значения,
* добавить объект в вектор при помощи push_back.

## <font color="tomato">Реализация</font>

Родительский компонент содержит необходимую информацию о своих дочерних элементах. 
При этом дочерние элементы ничего не знают о своих родительских компонентах.

Меню реализовано как интерфейс с набором команд, которые необходимо вводить вручную. 
В меню каждого компонента можно добавлять новые дочерние элементы, изменять и получать информацию о них. 

Программа легко масштабируема.
