import tornado.template
import tornado.ioloop
import tornado.web
TEMPLATE = '''
<html>
 <head><title> Weather Spotting Society </title></head>
 <body><center>
 <div>Hello, what is your favourite weather phenomenon?</div>
 <div><form method="get" action="/">
  <input type="text" name="answer">
  <input type="submit" value="Submit">
 </form>
 </div>
 <div>ANSWER</div>
 </center>
 </body>
</html>
'''


class MainHandler(tornado.web.RequestHandler):

    def get(self):
        try:
            answer = self.get_argument('answer', '')
            if not answer:
                template_data = TEMPLATE.replace("ANSWER", "")
            elif answer.lower() == "tornado":
                template_data = TEMPLATE.replace("ANSWER", '<div>Good choice!</div><img src="https://upload.wikimedia.org/wikipedia/commons/9/98/F5_tornado_Elie_Manitoba_2007.jpg" width=500 />')
            else:
                template_data = TEMPLATE.replace("ANSWER", answer + "? Really? Why?")
            t = tornado.template.Template(template_data)
            self.write(t.generate(name=answer))
        except:
            pass


application = tornado.web.Application([
    (r"/", MainHandler),
], debug=True, static_path=None, template_path=None)

if __name__ == '__main__':
    application.listen(8002)
    tornado.ioloop.IOLoop.instance().start()
