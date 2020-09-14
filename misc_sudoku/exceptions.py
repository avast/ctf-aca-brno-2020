class SudokuCanNotBeGenerated(Exception):
    '''
    this exception is used to generate sudoku
    see function create_sudoku() in sudoku_fn.py
    '''
    pass

class NotationNotRecieved(Exception):
    '''
    this exception is used to controll timeout for sending notation from client
    see function notation_not_recieved() in sudoku_fn.py
    '''
    pass
