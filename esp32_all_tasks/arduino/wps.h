typedef __SIZE_TYPE__ size_t;

unsigned char check(const char* pin, const unsigned long real_pin);
bool generate_response(char* buffer, size_t buffer_size, unsigned char input, const char* flag);
unsigned char checksum(unsigned long input);
