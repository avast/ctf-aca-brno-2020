FROM python:3.7

ADD server.py index.html flag.html /
RUN pip install tornado pycrypto
CMD python ./server.py
