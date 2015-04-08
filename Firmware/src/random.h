#ifndef RANDOM_H
#define RANDOM_H

//http://microsin.net/programming/AVR/lfsr-pseudo-random-number-generator.html
// * ������������ ��������� ���������� ����� � �������������� 32-bit LFSR
uint8_t random_byte_lfsr32(void);
// * ��������� ���������� ����� x ���, ��� min < = x < = max.
int8_t random_byte_in(int8_t min, int8_t max);
// * ��������� ���������� ����� x ���, ��� min < = x < = max
uint8_t random_ubyte_in(uint8_t min, uint8_t max);

#endif //RANDOM_H