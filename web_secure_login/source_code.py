import json
from base64 import b64decode
from base64 import b64encode
from Crypto import Random
from Crypto.Cipher import AES
import tornado.ioloop
import tornado.web

secret_key = redacted
flag_value = redacted 


class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("index.html")


class LoginHandler(tornado.web.RequestHandler):
    def post(self):
        username = self.get_argument("username")
        if username == "admin":
            self.render("index.html", msg="Admin access is temporarily disabled.")

        cookie = {}
        cookie['username'] = self.get_argument("username")
        cookie['admin'] = 0
        cookie_data = json.dumps(cookie, sort_keys=True)
        encrypted = AESCipher(secret_key).encrypt(cookie_data)
        print(encrypted)
        self.set_cookie("auth", encrypted)

        self.redirect("/flag")


class FlagHandler(tornado.web.RequestHandler):
    def get(self):
        auth = self.get_cookie("auth", "")
        decrypted = AESCipher(secret_key).decrypt(auth)
        auth_data = json.loads(decrypted)
        is_admin = auth_data['admin'] == 1
        if is_admin:
            self.render("flag.html", flag=flag_value)
        else:
            self.render("flag.html", flag="Come back when you are admin.")


class LogoutHandler(tornado.web.RequestHandler):
    def post(self):
        self.clear_cookie("auth")
        self.redirect("/")


def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/login", LoginHandler),
        (r"/flag", FlagHandler),
        (r"/logout", LogoutHandler),
    ])


block_size = 16
pad = lambda s: bytes(s + (block_size - len(s) % block_size) * chr(block_size - len(s) % block_size), 'utf-8')
unpad = lambda s: s[0:-ord(s[-1:])]


class AESCipher:

    def __init__(self, key):
        self.key = key

    def encrypt(self, raw):
        raw = pad(raw)
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return b64encode(iv + cipher.encrypt(raw))

    def decrypt(self, enc):
        enc = b64decode(enc)
        iv = enc[:16]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return unpad(cipher.decrypt(enc[16:])).decode('utf8')


if __name__ == "__main__":
    app = make_app()
    app.listen(8000)
    tornado.ioloop.IOLoop.current().start()
