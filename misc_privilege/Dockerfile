# Use minimal Ubuntu as a basis
FROM ubuntu

# Update and install needed programs
RUN apt-get update --fix-missing -y
RUN apt-get install -y apt-utils
RUN apt-get install -y vim
RUN apt-get install -y make
RUN apt-get update --fix-missing -y
RUN apt-get install -y gcc
RUN apt-get install -y python

# Install and configure openSSH server
RUN apt-get install -y openssh-server
RUN mkdir /var/run/sshd
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/#Port 22/Port 2222/' /etc/ssh/sshd_config

# Create a user and change passwords
RUN adduser --disabled-password --gecos "" user
RUN echo 'user:123' | chpasswd
RUN echo 'root:hardcorepass123' | chpasswd

# Copy needed files, build and remove source files
COPY privilege.c /tmp/privilege.c
COPY Makefile /tmp/Makefile
RUN cd /tmp/ && make
RUN chmod +x /tmp/privilege
RUN rm /tmp/privilege.c
RUN rm /tmp/Makefile
RUN mv /tmp/privilege /home/user/
COPY flag /home/user/
RUN chmod 600 /home/user/flag

ENV NOTVISIBLE "in users profile"

EXPOSE 2222
CMD ["/usr/sbin/sshd", "-D"]
