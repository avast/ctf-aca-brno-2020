import numpy as np
import sys

import connection
import parser
import print_notation
import sudoku_fn
import exceptions

sudoku = np.zeros((9, 9)) #2d list representing sudoku: (row, column)

if __name__ == '__main__':

    while True:
        try:
            print('1')
            connection.Connection.create_reusable_socket(sudoku)
            # print('2')
            # sudoku_fn.play_game(sudoku)
        except KeyboardInterrupt:
            sys.exit()
        except Exception as e:
            print(f'Exception: {e}')
            sys.exit()

