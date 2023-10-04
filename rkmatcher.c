#include <stdio.h>
#include <string.h>
#include <math.h>

// Функция для вычисления хеш-кода в n-ичной системе счисления
int makeHash(char *str, int length, int n) {
    int hash = 0;

    for (int i = 0; i < length; i++) {
        hash = (hash * n + str[i]) % n; // Вычисляем хеш-код строки в n-ичной системе счисления
    }
    return hash;
}

// Функция для поиска и выделения совпадений подстроки pattern в строке text
void RabinaKarpa(char *text, char *pattern, int n) {
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);
    int pattern_hash = makeHash(pattern, pattern_length, n); // Вычисляем хеш-код шаблона
    int text_hash = makeHash(text, pattern_length, n); // Вычисляем хеш-код начального участка текста
    int found_positions[text_length]; // Массив для отслеживания позиций совпадений
    int found_count = 0; // Количество найденных совпадений

    // Проходим по тексту с помощью окна шаблона длины pattern_length
    for (int i = 0; i <= text_length - pattern_length; i++) {
        if (text_hash == pattern_hash) { // Если хеш-коды совпадают
            int j;
            for (j = 0; j < pattern_length; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == pattern_length) { // Если все символы совпали
                found_positions[found_count] = i; // Записываем позицию совпадения
                found_count++;
            }
        }
        // Обновляем хеш-код для следующего участка текста
        text_hash = (text_hash * n + text[i + pattern_length] - text[i] * (int)pow(n, pattern_length)) % n;
        if (text_hash < 0) {
            text_hash += n;
        }
    }
    
    // Выводим исходный текст с выделенными совпадениями
    int text_index = 0;
    for (int i = 0; i < found_count; i++) {
        int start = found_positions[i];
        int end = start + pattern_length - 1;
        // Выводим символы до начала совпадения
        while (text_index < start) {
            printf("%c", text[text_index]);
            text_index++;
        }
        // Выделяем совпадение (зеленый текст)
        printf("\033[1;32m");
        for (int j = start; j <= end; j++) {
            printf("%c", text[j]); //%c потому что вывод посимвольно
        }
        printf("\033[0m"); // Завершаем выделение (возвращаем обычный цвет)
        text_index = end + 1; // Устанавливаем индекс после совпадения
    }

    // Выводим оставшуюся часть исходного текста
    while (text_index < text_length) {
        printf("%c", text[text_index]);
        text_index++;
    }
    printf("\n");
}

int main() {
    char *text = "asd qwertyu qwqeryt"; // Исходный текст
    char *pattern = "asd"; // Искомый шаблон
    int n = 256; // Основание системы счисления (например, 256 для ASCII)

    RabinaKarpa(text, pattern, n); // Вызываем функцию поиска и выделения совпадений

    return 0;
}
