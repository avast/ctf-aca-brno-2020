import connection
import sys

#sudoku notation --> [row, column]-number; [row, column]-number; [row, column]-number

def print_in_notation(c, row, column, number):
    '''
    send sudoku in notation to socket
    sudoku is 2d list, so it is indexed from 0. Therefore we must increase each
        index of row and column to write correct notation
    '''
    c.send_data('[' + str(int(row) + 1) + ',' + str(int(column) + 1) + ']-' + str(int(number)))


def show_sudoku_in_CLI(c, sudoku):
    '''
    write whole sudoku in correct notation
    '''
    first_print = True
    for row in range(len(sudoku)):
        for column in range(len(sudoku[row])):
            if sudoku[row][column] != 0:
                #sudoku parts to be filled are 0 now - so we do not need to print them
                if first_print:
                    print_in_notation(c, row, column, sudoku[row][column])
                    first_print = False
                else:
                    c.send_data('; ')
                    print_in_notation(c, row, column, sudoku[row][column])

    c.send_data('\n') #notation does not print new line, so we must do it


def end_game(c, success, message = ''):
    '''
    end game with either success or fail
    '''
    if success == True:
        c.send_data('flag = avastCTF{sUD0Ku_is_3asy}\n')
    else:
        c.send_data('FAIL\n')

    c.send_data(message)
    c.close_conn()
    print("connection closed")
