import sys
import socket
# from _thread import *

global SOCKET_CONN

class Connection(object):
    '''
    design pattern: SINGLETON
    '''
    __instance = None
    conn = None

    host = ''
    port = 20000


    def __init__(self, conn):
        self._conn = conn


    def send_data(self, data):
        self._conn.send(str.encode(data))


    def recv_data(self):
        data = self._conn.recv(2048)
        return data.decode('utf-8')


    def close_conn(self):
            self._conn.close()

    def send(self, b):
        return self._conn.send(b)


    def conn_client(self):
        '''
        print task after client is connected
        '''
        if Connection.__instance is not None:
            self.conn.send(str.encode('-------------------------------------------------\n'))
            self.conn.send(str.encode('Solve SUDOKU below in 30 seconds to find the key.\n'))
            self.conn.send(str.encode('-------------------------------------------------\n'))
            self.conn.send(str.encode('NOTATION SYNTAX: [r1,c1]-n1; [r2,c2]-n2\n'))
            self.conn.send(str.encode('r - row, c - column, n - number\n\n'))
            self.conn.send(str.encode('Example: [1,9]-4; [2,7]-5; [2,8]-9\n'))
            self.conn.send(str.encode('-------------------------------------------------\n'))
            self.conn.send(str.encode('Be sure you use notation in correct way.\n'))
            self.conn.send(str.encode('-------------------------------------------------\n'))
            self.conn.send(str.encode('Your task:\n'))

    @classmethod
    def create_reusable_socket(cls, sudoku):
        '''
        establish connection and reuse socket
        inspired by: https://subscription.packtpub.com/book/networking_and_servers/9781786463999/1/ch01lvl1sec20/reusing-socket-addresses
        '''
        if True:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            # Get the old state of the SO_REUSEADDR option
            old_state = s.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)

            # Enable the SO_REUSEADDR option
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            new_state = s.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)

            srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

            try:
                srv.bind((Connection.host, Connection.port))
            except socket.error as e:
                print(str(e))

            srv.listen()
            # print ("Listening on port: %s " %port)
            while True:
                try:
                    conn, addr = srv.accept()
                    print('Connected to: ' + addr[0] + ':' + str(addr[1]))

                    c = Connection(conn)

                    def t(conn):
                         conn.send(str.encode('-------------------------------------------------\n'))
                         conn.send(str.encode('Solve SUDOKU below in 30 seconds to find the key.\n'))
                         conn.send(str.encode('-------------------------------------------------\n'))
                         conn.send(str.encode('NOTATION SYNTAX: [r1,c1]-n1; [r2,c2]-n2\n'))
                         conn.send(str.encode('r - row, c - column, n - number\n\n'))
                         conn.send(str.encode('Example: [1,9]-4; [2,7]-5; [2,8]-9\n'))
                         conn.send(str.encode('-------------------------------------------------\n'))
                         conn.send(str.encode('Be sure you use notation in correct way.\n'))
                         conn.send(str.encode('-------------------------------------------------\n'))
                         conn.send(str.encode('Your task:\n'))

                         import sudoku_fn
                         sudoku_fn.play_game(sudoku, c)
                    
                    import threading


                    def m(conn):
                        import multiprocessing
                        tt = multiprocessing.Process(target=t, args=(conn, ))

                        tt.start()

                        tt.join(timeout=30)
                        tt.terminate()

                    threading.Thread(target=m, args=(c,)).start()
                    # start_new_thread(t,(conn,))

                    # Connection.conn_client(self)
                    # break
                except KeyboardInterrupt:
                    break
                except socket.error as e:
                    print(str(e))
                    break
