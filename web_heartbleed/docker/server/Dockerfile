FROM debian:jessie

RUN \
  apt-get update -y &&  apt-get install -y apache2 php5 libapache2-mod-php5 wget

RUN a2enmod ssl
RUN a2ensite default-ssl

RUN echo Europe/Brussels > /etc/timezone && dpkg-reconfigure --frontend noninteractive tzdata

ENV DEBIAN_FRONTEND noninteractive
RUN wget http://snapshot.debian.org/archive/debian/20130319T033933Z/pool/main/o/openssl/openssl_1.0.1e-2_amd64.deb -O /tmp/openssl_1.0.1e-2_amd64.deb && \
 dpkg -i /tmp/openssl_1.0.1e-2_amd64.deb
RUN wget http://snapshot.debian.org/archive/debian/20130319T033933Z/pool/main/o/openssl/libssl1.0.0_1.0.1e-2_amd64.deb -O /tmp/libssl1.0.0_1.0.1e-2_amd64.deb && \
 dpkg -i /tmp/libssl1.0.0_1.0.1e-2_amd64.deb


RUN rm -r /var/www/html
ADD www /var/www

RUN echo "ServerName localhost" >> /etc/apache2/apache2.conf

EXPOSE 443

CMD ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
