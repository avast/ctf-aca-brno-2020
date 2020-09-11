FROM python:3

ENV ENCRYPTEDFLAG 9FTZkljZ3Q3XuBTM0N2Mq5WMfRGbw8FZwAzZ7ZEVDR3chZXY
ADD server.py start.sh /
RUN chmod 755 start.sh
RUN pip install tornado
CMD ./start.sh && rm start.sh && python ./server.py
