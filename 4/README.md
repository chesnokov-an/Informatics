# Lab 4
> Данный проект является решением лабораторной работы №4 по информатике.

## Описание
	Из входного потока вводится произвольное количество строк произвольной длины. Каждая строка в общем случае содержит одно или более слов, разделенных пробелами и/или знаками табуляции.
Завершение ввода определяется концом файла. Для каждой входной строки формируется новая выходная строка, в которую помещается результат. В полученной строке слова разделяются только одним пробелом, пробелов в её начале и в конце быть не должно. Введённая и сформированная строки выводятся на экран в двойных кавычках.
    
	Лабораторная работа № 4 состоит из двух лабораторных работ: № 4а и № 4б. В ходе выполнения лабораторной работы № 4а должна быть разработана программа, использующая функцию readline() из состава библиотеки GNU readline для ввода строк и функции стан-
дартной библиотеки для их обработки (<string.h>).
	В ходе выполнения лабораторной работы № 4б должна быть разработана программа, идентичная
п. 1, за исключением того, что все библиотечные функции заменены на собственную реализацию
данных функций, представленную в отдельных файлах (например: mystring.h, mystring.c).

## Индивидуальное задание:
Удалить из строки все слова нечётной длины.

## Как установить и запустить проект:
1. Склонировать репозиторий проекта:
```bash
ssh://gitea@git.dozen.mephi.ru:1222/inf2024/s24501_chesnokov.an.git
```
2. Скомпилировать код:
```bash
make
```
3. Запуск:
```bash
./prog
```
