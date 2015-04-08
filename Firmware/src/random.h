#ifndef RANDOM_H
#define RANDOM_H

//http://microsin.net/programming/AVR/lfsr-pseudo-random-number-generator.html
// * Подпрограмма генерации случайного байта с использованием 32-bit LFSR
uint8_t random_byte_lfsr32(void);
// * Генерация случайного байта x так, что min < = x < = max.
int8_t random_byte_in(int8_t min, int8_t max);
// * Генерация случайного байта x так, что min < = x < = max
uint8_t random_ubyte_in(uint8_t min, uint8_t max);

#endif //RANDOM_H