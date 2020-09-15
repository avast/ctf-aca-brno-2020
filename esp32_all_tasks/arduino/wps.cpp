#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wps.h"

const unsigned long powers[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

unsigned char checksum(unsigned long input)
{
  unsigned char result = 0;
  for (char i = 1; i < 8; i++)
  {
      result += (input / powers[i - 1]) % 10;
  }
  return result % 10;
}

unsigned char check(const char* pin, const unsigned long real_pin)
{
    size_t pin_len = strlen(pin);
    if (pin_len != 8)
        return 0;

    unsigned long pin_value = strtol(pin, NULL, 10);
    unsigned char result = 0;
    if (pin_value / 10000 == real_pin / 10000)
        result += 1;
    if (pin_value % 10000 == real_pin % 10000)
        result += 2;

    if (checksum(pin_value) == pin_value % 10)
        result += 4;
    return result;
}

bool generate_response(char* buffer, size_t buffer_size, unsigned char input, const char* flag)
{
    const char* ok = "OK";
    const char* fail = "fail";
    char succ [100];
    snprintf(succ, 100, "Authentication success!\nFlag: '%s'.\n", flag);
    const char* no_succ = "Authentication failed!\n";

    snprintf(buffer, buffer_size, "%s|%s|%s|%s\n",
            (input & 0x1 ? ok : fail),
            (input & 0x2 ? ok : fail),
            (input & 0x4 ? ok : fail),
            (input == 0x7 ? succ : no_succ));
    return input == 0x7;
}

