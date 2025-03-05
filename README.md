# freeBSD_lab2
## Завдання №1
Напишіть програму для визначення моменту, коли time_t закінчиться. Дослідіть, які зміни відбуваються в залежності від 32-бітної та 64-бітної архітектури. Дослідіть сегменти виконуваного файлу.
## Реалізація завдання
- Виводиться розмір типу `time_t` в байтах за допомогою функції `sizeof(time_t)`.
- Перевірка, чи є `time_t` підписаним чи беззнаковим, порівнюючи значення `(time_t)-1` з 0.
- Розрахунок максимално можливого значення `time_t`.
- Пошук максимально допустимого значення `time_t`. Це відбувається в циклі. Програма заменшує значення `max_time` до тих пір, поки функція `ctime(&max_time)` не поверне значення, відмінне від NULL.
- Виведення максимально допустимого значення та відповідної дати.
## Компіляція та виконання програми
### 32-бітна система:
![image](https://github.com/user-attachments/assets/f7a9707c-e251-4e35-8713-890d44b27165)

### 64-бітна система:
![image](https://github.com/user-attachments/assets/18f040c2-9fc7-4b63-8e7a-4b70799efb52)

Отже, як ми можемо бачити з виконання програми різниця полягає в наступному:
+ Розмір `time_t`;
+ Максимално можливе значення `time_t`;
+ Максимально допустима дата.
## Дослідження сегментів виконуваного файлу
[`nm file`](http://silmor.de/qtstuff.proginfo.php) - ця команда виводить символи всередині об'єктного файлу або статистичної бібліотеки. Вона також може показувати символи в динамічних бібліотеках та виконуваних файлах, якщо вони не були очищені. Результат виконання команди:

![image](https://github.com/user-attachments/assets/4222f64f-e53c-4fb6-89af-ed5eccca4b7a)

[`objdump -x file`](http://silmor.de/qtstuff.proginfo.php) - виводить вміст об'єктного файлу, бібліотеки або виконуваного файлу, включаючи динамічні залежності, імпортовані та експортовані імена символів. Результати виконання команди:

![image](https://github.com/user-attachments/assets/8b0f46a7-9ec2-4f01-be2c-ce4fb8aaeb40)

Примітка: Оскільки виконання команди `objdump -x file` тягне за собою багато інформації (у тому числі скрінів), було вирішено прикріпити тільки інформацію про `Program Header`.

## Завдання №2
Розгляньте сегменти у виконуваному файлі.
1. Скомпілюйте програму `hello world`, запустіть `ls -l` для виконуваного файлу, щоб отримати його загальний розмір, і запустіть `size`, щоб отримати розміри сегментів всередині нього.
2. Додайте оголошення глобального масиву із `1000 int`, перекомпілюйте й повторіть вимірювання. Зверніть увагу на відмінності.
3. Тепер додайте початкове значення в оголошення масиву (пам’ятайте, що C не змушує вас вказувати значення для кожного елемента масиву в ініціалізаторі). Це перемістить масив із сегмента `BSS` у сегмент даних. Повторіть вимірювання. Зверніть увагу на різницю.
4. Тепер додайте оголошення великого масиву в локальну функцію. Оголосіть другий великий локальний масив з ініціалізатором. Повторіть вимірювання. Дані розташовуються всередині функцій, залишаючись у виконуваному файлі? Яка різниця, якщо масив ініціалізований чи ні?
5. Які зміни відбуваються з розмірами файлів і сегментів, якщо ви компілюєте для налагодження? Для максимальної оптимізації?
## Реалізація, компіляція та виконання завдання
1. ![image](https://github.com/user-attachments/assets/2cf83e6d-473a-470c-b80a-6bb0072c6f1a)
2. ![image](https://github.com/user-attachments/assets/960a27f1-fec1-4bd0-8587-4be9e0305ad0)
3. ![image](https://github.com/user-attachments/assets/dccbff51-6a21-4601-a3b6-13174fd90129)
4. ![image](https://github.com/user-attachments/assets/9074d4bc-1cbb-457f-bf6a-a1e36e669c0b)
5. ![image](https://github.com/user-attachments/assets/072c8f5b-85cc-417b-8690-be387ae7675c)
## Висновки до завдання №2
1. Виконуваний файл `Hello world!` має мінімальний розмір, оскільки містить лише основний код без додаткових структур даних.
2. Оголошення глобального масиву `int global_array[1000];` призвело до збільшення розміру сегменту `BSS`, оскільки змінні без початкового значення зберігаються саме в цому сегменті. Загальний розмір виконуваного файлу залишився майже незмінним, оскільки `BSS` займає місце лише в оперативній пам'яті під час виконання програми.
3. Після ініціалізації масиву значенням, він перемістився з `BSS` у сегмент `.data`. Це призвело до збільшення загального розміру виконуваного файлу, оскільки ініціалізовані дані зберігаются всередині самого виконуваного файлу.
4. Оголошення великого локального масиву в функції призвело до розміщення його в стеку. Якщо масив ініціалізований, його дані розміщуються у виконуваному файлі в сегменті `.data`. Великий неініціалізований масив залишається в `BSS` або може спричинити переповнення стеку при значних розмірах.
5. Компіляція з опцією налагодження збільшує розмір виконуваного файлу за рахунок додаткової налагоджувальної інформації. А оптимізація зменшує розмір файлу та сегментів за рахунок усунення зайвих інструкцій і використання ефективніших алгоритмів обробки коду.
## Завдання №3
Скомпілюйте й запустіть тестову програму, щоб визначити приблизне розташування стека у вашій системі. Знайдіть розташування сегментів даних і тексту, а також купи всередині сегмента даних, оголосіть змінні, які будуть поміщені в ці сегменти, і виведіть їхні адреси.
Збільшіть розмір стека, викликавши функцію й оголосивши кілька великих локальних масивів. Яка зараз адреса вершини стека?
## Реалізація, компіляція та виконання завдання
Розташування стека у моїй системі:

![image](https://github.com/user-attachments/assets/91b07cf1-ccc1-4670-a44d-20c5250c55a5)

Виведення адрес змінних, які були поміщені в сегменти даних та тексту:

![image](https://github.com/user-attachments/assets/4814c3f0-45bb-45a3-9af2-3e1d54e755fb)

Результати програми після збільшення розміру стека:

![image](https://github.com/user-attachments/assets/0b6c8dfc-2014-46f8-8bc5-3a304bc9c139)

## Висновок до завдання №3
З результатів програми видно, що після виділення пам'яті для масиву адреса змінилася на менше значення, підтверджуючи, що стек зростає вниз. Отже, ці кроки дозволяють дослідити розташування основних сегментів пам'яті в системі та поведінку стека під час виклику функцій із великими локалними змінними.
## Завдання №4
Дослідити стек процесу або пригадати, як це робиться. Ви можете:
+ Автоматично за допомогою утиліти gstack.
+ Вручну за допомогою налагоджувача GDB.
## Реалізація
Це завдання було реалізовано за допомогою налагоджувача GDB (використано інструкцію з практичної роботи).
За допомогою команди `ps aux | grep stacker` було знайдено PID. У моєму випадку `PID = 1446`.
## Результати дослідження стеку
![image](https://github.com/user-attachments/assets/683a7e18-4d70-4734-94b8-f4a4bbcadede)

Команда `(gdb) bt` показує стек викликів.
## Завдання №5
Відомо, що при виклику процедур і поверненні з них процесор використовує стек. Чи можна в такій схемі обійтися без лічильника команд (IP), використовуючи замість нього вершину стека? Обґрунтуйте свою відповідь та наведіть приклади.
## Відповідь
Неможливо використовувати стек замість IP у традиційній моделі процесора, оскільки:
- Лічильник команд має чітко визначену функцію керування потоком виконання.
- Стек використовується для інших задач (збереження контексту, аргументів функцій тощо).
- Будь-яка операція над стеком змінювала б хід виконання програми.

Отже, архітектура процесорів потребує окремого лічильника команд (IP), навіть за активного використання стека для викликів процедур.
### Приклад неправильного підходу
У нас є система, де вершина стека завжди містить IP. Тоді будь-яка операція зі стеком впливатиме на хід виконання програми:
```
push next_instr; // Намагається зберегти наступну інструкцію
call function; // Виклик функції, IP зберігається у стеку
pop IP; // IP змінюється на неправильне значення
```
## Завдання №20
Реалізуйте стековий аналізатор відстеження викликів.
## Реалізація завдання
Було розроблено наступні структури даних:
* StackFrame - кадр стеку викликів
* CallStack - сам стек викликів

Розглянемо StackFrame. Реалізація:
```
typedef struct {
    const char *function;
    const char *file;
    int line;
} StackFrame;
```

Ця структура представляє один кадр у стеку викликів. Вона містить: 
+ `function` - ім'я функції, де зроблено запис у стек;
+ `file` - ім'я файлу, в якому знаходиться ця функція;
+ `line` - номер рядка у вихідному коді, де зроблено запис.

Розглянемо структуру CallStack. Реалізація:
```
typedef struct {
    StackFrame frames[STACK_SIZE];
    int top;
} CallStack;
```

Ця структура представляє весь стек викликів:
- `frames[STACK_SIZE]` - масив кадрів;
- `top` - індекс останнього записаного кадру (початкове значення `-1` означає порожній стек).

Реалізовна функції для роботи зі стеком:
* `push_stack()` - додавання кадру у стек;
* `pop_stack()` - видалення кадру зі стеку;
* `print_stack_trace()` - виведення стеку викликів.

Також були написані макроси для зручності. Розберемо кожен з них:
1. `#define TRACE_ENTER() push_stack(__func__, __FILE__, __LINE__)`. Тут `TRACE_ENTER()` викликає `push_stack()`, записуючи поточну функцію, файл та рядок;
2. `#define TRACE_EXIT() pop_stack()`. Тут `TRACE_EXIT()` викликає `pop_stack()`, видаляючи останній кадр.

Також були написані тестові функції `functionC()`, `functionB()` та `functionA()`. Ознайомитися з ними можна в файлі `stack_tracer.c`.

Функція `main()` додає себе у стек. Викликає `functionA()`, яка викликає `functionB()`, яка викликає `functionC()`. Друкує стек викликів та видаляє `main()` зі стеку перед виходом.

## Компіляція та виконання програми
![image](https://github.com/user-attachments/assets/d8bcb0ee-a966-4f3d-ac28-7af60a48e580)

`functionC()` виводить `Inside functionC`, потім виходить. Після повернення до `main()`, стек містить тільки `main()`, тому у `print_stack_trace()` виводиться лише `main()`.
