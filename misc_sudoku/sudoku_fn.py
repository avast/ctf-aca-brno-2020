import random
import numpy
import time
import signal

import print_notation
import parser
import connection
import exceptions


import threading

threadLocal = threading.local()


def c():
    return getattr(threadLocal, 'c', None)


def get_square(sudoku, row, col):
    '''
    return square (as list) of current number in position [row,col]
    return list
    '''
    ret = []

    if row >= 0 and row <= 2:
        if col >= 0 and col <= 2:
            for i in range(0,3):
                for j in range(0,3):
                    ret.append(sudoku[i][j])
        elif col >= 3 and col <= 5:
            for i in range(0,3):
                for j in range(3,6):
                    ret.append(sudoku[i][j])
        else:
            for i in range(0,3):
                for j in range(6,9):
                    ret.append(sudoku[i][j])

    elif row >= 3 and row <= 5:
        if col >= 0 and col <= 2:
            for i in range(3,6):
                for j in range(0,3):
                    ret.append(sudoku[i][j])
        elif col >= 3 and col <= 5:
            for i in range(3,6):
                for j in range(3,6):
                    ret.append(sudoku[i][j])
        else:
            for i in range(3,6):
                for j in range(6,9):
                    ret.append(sudoku[i][j])

    else:
        if col >= 0 and col <= 2:
            for i in range(6,9):
                for j in range(0,3):
                    ret.append(sudoku[i][j])
        elif col >= 3 and col <= 5:
            for i in range(6,9):
                for j in range(3,6):
                    ret.append(sudoku[i][j])
        else:
            for i in range(6,9):
                for j in range(6,9):
                    ret.append(sudoku[i][j])

    return ret


def get_col(sudoku, col):
    '''
    get numbers from column your current number is in
    return list
    '''
    column = []

    for i in range(len(sudoku)):
        column.append(sudoku[i][col])

    return column


def fill_sudoku(sudoku):
    '''
    create new solved sudoku with all numbers
    return sudoku filled in all positions
    '''
    numbers = [1,2,3,4,5,6,7,8,9]

    # for each position [row, column]
    for row in range(len(sudoku)):
        for col in range(len(sudoku)):
            random.shuffle(numbers)
            #take number and try if it is already used in current row, column and square
            for number in numbers:
                if count_occur(sudoku[row], number) == 0  and count_occur(get_col(sudoku, col), number) == 0:
                    # if number not in get_square(sudoku, row, col):
                    if count_occur(get_square(sudoku, row, col), number) == 0:
                        #if number is not used, use it
                        sudoku[row][col] = number
                        break
            if sudoku[row][col] == 0:
                #SHITCODE, but it works for now
                #when exception is reached, this sudoku can not be generated
                #new sudoku is generated (see create_sudoku(sudoku))
                raise exceptions.SudokuCanNotBeGenerated('this sudoku has no solution')

    return sudoku


def delete_nums_from_sudoku(sudoku, numberOfBlankSpaces: int):
    '''
    delete numbers from sudoku and create task
    !!sometimes it can generate same row and column more times - rewrite it if you want
    return sudoku with gaps - these are positions that need to be filled
    '''
    for i in range(numberOfBlankSpaces):
        row = random.randint(0,8)
        col = random.randint(0,8)

        sudoku[row][col] = 0

    return sudoku


def create_sudoku(sudoku):
    '''
    create solved sudoku - if conditions are not fulfilled, generate new sudoku
    return sudoku with all positions filled
    '''
    while True:
        try:
            sudoku = fill_sudoku(sudoku)
            break
        except exceptions.SudokuCanNotBeGenerated as e:
            #sometimes conditions are not fulfilled, so we generate sudoku again
            #if you want, use backtracking algorithm instead
            for i in range(0,9):
                for j in range(0,9):
                    sudoku[i][j] = 0

    return sudoku


def generate_sudoku(sudoku):
    '''
    create sudoku and delete some numbers
    return sudoku prepared to be solved
    '''
    numberOfBlankSpaces = 30
    #30 is there just for fun, you can change it - solvable sudoku must have at least 17 number
    return delete_nums_from_sudoku(create_sudoku(sudoku), numberOfBlankSpaces)

def count_occur(list, number):
    '''
    helper function, counts occurences of number in 1d list
    return how many times number occured in list
    '''
    occurences = 0
    for i in list:
        if i == number:
            occurences+=1
    return occurences


def control_sudoku(sudoku):
    '''
    controls basic sudoku rules
    '''
    for row in range(len(sudoku)):
        for column in range(len(sudoku)):
            number = sudoku[row][column]
            if count_occur(sudoku[row], number) == 1 and count_occur(get_col(sudoku, column), number) == 1\
            and count_occur(get_square(sudoku, row, column), number) == 1:
                continue
            else:
                print_notation.end_game(c(), False, 'Sudoku is not solved correctly\n')

    print_notation.end_game(c(), True, 'CONGRATULATIONS! \nYou solved the sudoku\n')


notation = None

def notation_not_recieved(signum, frame):
    print("Notation not recieved")
    cc = c()
    cc.send_data('Too slow\n')
    cc.send_data('FAIL\n')
    cc.send_data('Next time you should solve it faster\n')
    # connection.SOCKET_CONN.shutdown(socket.SHUT_RDWR)
    cc.close_conn()
    raise exceptions.NotationNotRecieved("timeout")

signal.signal(signal.SIGALRM, notation_not_recieved)

def wait_for_notation():
    try:
        notation = c().recv_data()
        return notation
    except:
        return None

def play_game(sudoku, conn):
    threadLocal.c = conn
    generate_sudoku(sudoku)
    print_notation.show_sudoku_in_CLI(conn, sudoku)

    signal.alarm(30000)
    notation = wait_for_notation()
    signal.alarm(0)

    if notation == None:
        return

    if parser.control_notation(conn, notation):
        parser.write_to_sudoku_from_notation(conn, notation, sudoku)
        control_sudoku(sudoku)

    # print_notation.show_sudoku_in_CLI(sudoku)
