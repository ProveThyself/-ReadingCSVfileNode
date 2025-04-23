#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <locale.h>
#include "student.h"

// Максимальная длина строки в файле
#define MAX_LINE_LENGTH 512 
// Максимальное количество полей в строке CSV
#define MAX_TOKENS 5  
// Максимальная длина каждого поля (берется из student.h)
#define MAX_TOKEN_LENGTH MAX_FIELD  

// Функция для разделения строки на токены по разделителю
int split(const char* str, char delimiter, char tokens[][MAX_TOKEN_LENGTH]) {
    int token_count = 0; // Счетчик найденных токенов
    int pos = 0; // Позиция в текущем токене

    // Проходим по строке до конца строки или символа новой строки
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[i] == delimiter) {
            // Завершаем текущий токен и переходим к следующему
            tokens[token_count][pos] = '\0';
            token_count++;
            pos = 0;
            if (token_count >= MAX_TOKENS) break; // Превышено максимальное количество токенов
        }
        else if (pos < MAX_TOKEN_LENGTH - 1) {
            // Добавляем символ в текущий токен
            tokens[token_count][pos++] = str[i];
        }
    }

    // Добавляем последний токен, если он есть
    if (pos > 0 && token_count < MAX_TOKENS) {
        tokens[token_count][pos] = '\0';
        token_count++;
    }

    return token_count; // Возвращаем количество найденных токенов
}

// Функция для парсинга строки CSV в структуру student
bool parse_csv_line(const char* line, student& s) {
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH] = { {0} }; // Массив для хранения токенов
    int token_count = split(line, ';', tokens); // Разбиваем строку на токены

    // Проверяем, что получили все 5 полей
    if (token_count != 5) {
        return false;
    }

    // Копируем данные из токенов в структуру student
    strncpy(s.last_name, tokens[0], MAX_FIELD - 1);
    s.last_name[MAX_FIELD - 1] = '\0'; // Завершение строки
    strncpy(s.first_name, tokens[1], MAX_FIELD - 1);
    s.first_name[MAX_FIELD - 1] = '\0';
    strncpy(s.middle_name, tokens[2], MAX_FIELD - 1);
    s.middle_name[MAX_FIELD - 1] = '\0';
    s.age = atoi(tokens[3]);  // Преобразуем строку в число
    strncpy(s.gender, tokens[4], MAX_FIELD - 1);
    s.gender[MAX_FIELD - 1] = '\0';

    return true;
}

// Структура узла связного списка
struct Node {
    student data; // Данные студента
    Node* next; // Указатель на следующий узел

    Node(const student& s) : data(s), next(nullptr) {} // Конструктор
};

// Функция для печати всего списка
void print_list(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        current->data.print(); // Печатаем данные текущего узла
        current = current->next;  // Переходим к следующему узлу
    }
}

// Функция для удаления всего списка и освобождения памяти
void delete_list(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next; // Сохраняем указатель на следующий узел
        delete current; // Удаляем текущий узел
        current = next; // Переходим к следующему узлу
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Получаем имя файла из аргументов командной строки или используем значение по умолчанию
    const char* filename = (argc > 1) ? argv[1] : "Group.csv";

    // Открываем файл для чтения
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Не удалось открыть файл: %s\n", filename);
        return 1;
    }

    Node* head = nullptr; // Указатель на начало списка
    Node* tail = nullptr; // Указатель на конец списка
    char line[MAX_LINE_LENGTH]; // Буфер для чтения строки из файла

    // Читаем файл построчно
    while (fgets(line, sizeof(line), f)) {
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = '\0';

        // Пропускаем пустые строки
        if (line[0] == '\0') continue;

        student s;
        if (parse_csv_line(line, s)) {
            // Создаем новый узел списка
            Node* new_node = new Node(s);

            // Добавляем узел в конец списка
            if (head == nullptr) {
                head = tail = new_node; // Список был пуст
            }
            else {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }
    fclose(f); // Закрываем файл

    // Печатаем и удаляем список
    print_list(head);
    delete_list(head);

    return 0;
}


