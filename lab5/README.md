# Лабораторная работа N5
## LZW

Реализовать LZW упаковщик-распаковщик.
- Алфавит - 8 бит (1 байт)
- Размер LZW таблицы - 2^9 .. 2^16. Задается при запуске упаковщика. Хранится в упакованном файле.
- Оптимизации по памяти - не храним строчки как есть. 4Gb - слишком много.
- Оптимизации по скорости - некий хэш на операции 'C in T' в упаковщике.
- Оптимизации по хранению - кол-во бит для хранения 8.9.9.9....10.10.10....16.16.16 - динамически. Откусываем уголок.

Формат упакованного файла:

- 0x0000 .. 0x0003 LZWЫ [ 0x4C , 0x5A , 0x57 , 0xF9 ]
- 0x0004 .. 0x0004 размер LZW таблицы - число от 9 до 16. 1 байт.
- 0x0005 .. EOF - упаковынные данные.

Без контроля целостности.

Пример запуска упаковщика:

$ ./pack 13 in.txt out.lzw

Пример запуска распаковщика:

$ ./unpack out.lzw out.txt

Руализуем как .so для lzwy.h
