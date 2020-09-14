import re
import print_notation
import connection

def control_notation(c, notation):
    '''
    controls input notation
    sudoku notation --> [row, column]-number; [row, column]-number; [row, column]-number
    return true if notation is OK, else return false and end game
    '''
    matching_regex = '\A(\[[1-9],[1-9]\]-[1-9])+(;\s\[[1-9],[1-9]\]-[1-9])*\s*\Z'

    if re.match(matching_regex, notation):
        c.send_data('Notation is OK\n')
    else:
        print_notation.end_game(c, False, 'Your notation syntax is not correct\n')
        return False

    return True


def write_to_sudoku_from_notation(c, notation, sudoku):
    '''
    this function writes new numbers from notation
    '''
    notation_list = notation.split(';')

    for element in notation_list:
        # conn.send(str.encode(element))
        number_list = re.findall(r'[0-9]+', element)
        add_one_number(c, int(number_list[0]) - 1, int(number_list[1]) -1, number_list[2], sudoku)


def add_one_number(c, row, column, number, sudoku):
    '''
    number 0 represents sudoku part to be solved
    if number is different than 0, it means that sudoku part is either default or solved
    '''
    if sudoku[row][column] == 0: #to prevent changing default numbers
        sudoku[row][column] = int(number)
    else:
        print_notation.end_game(c, False, 'Stop trying to rewrite default sudoku parts\n')
