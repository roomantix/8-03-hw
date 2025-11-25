# Домашнее задание к занятию 2 «Кластеризация и балансировка нагрузки»
# Романов Алексей
### Цель задания
В результате выполнения этого задания вы научитесь:
1. Настраивать балансировку с помощью HAProxy
2. Настраивать связку HAProxy + Nginx

------

### Чеклист готовности к домашнему заданию

1. Установлена операционная система Ubuntu на виртуальную машину и имеется доступ к терминалу
2. Просмотрены конфигурационные файлы, рассматриваемые на лекции, которые находятся по [ссылке](2/)

------



### Задание 1
- Запустите два simple python сервера на своей виртуальной машине на разных портах
- Установите и настройте HAProxy, воспользуйтесь материалами к лекции по [ссылке](2/)
- Настройте балансировку Round-robin на 4 уровне.
- На проверку направьте конфигурационный файл haproxy, скриншоты, где видно перенаправление запросов на разные серверы при обращении к HAProxy.



### Решение Задания 1
- Запустите два simple python сервера на своей виртуальной машине на разных портах - скриншот 1,2
- Установите и настройте HAProxy, воспользуйтесь материалами к лекции по [ссылке](2/)
- Настройте балансировку Round-robin на 4 уровне.
- На проверку направьте конфигурационный файл haproxy, скриншоты, где видно перенаправление запросов на разные серверы при обращении к HAProxy - скриншот 3 , 4 [Конфигурационный файл](https://github.com/roomantix/8-03-hw/blob/master/config/haproxy.cfg)

Скриншот 1: Решение задания 1

![Скриншот 1](https://github.com/roomantix/8-03-hw/blob/master/images/1.png)

Скриншот 2: Решение задания 1

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/2.png)

Скриншот 3: Решение задания 1

![Скриншот 3](https://github.com/roomantix/8-03-hw/blob/master/images/3.png)


Скриншот 4: Решение задания 1

![Скриншот 4](https://github.com/roomantix/8-03-hw/blob/master/images/8.png)


### Задание 2
- Запустите три simple python сервера на своей виртуальной машине на разных портах
- Настройте балансировку Weighted Round Robin на 7 уровне, чтобы первый сервер имел вес 2, второй - 3, а третий - 4
- HAproxy должен балансировать только тот http-трафик, который адресован домену example.local
- На проверку направьте конфигурационный файл haproxy, скриншоты, где видно перенаправление запросов на разные серверы при обращении к HAProxy c использованием домена example.local и без него.

### Решение

- Запустите три simple python сервера на своей виртуальной машине на разных портах - скриншот 1,2,3
- Настройте балансировку Weighted Round Robin на 7 уровне, чтобы первый сервер имел вес 2, второй - 3, а третий - 4
- HAproxy должен балансировать только тот http-трафик, который адресован домену example.local
- На проверку направьте конфигурационный файл haproxy, скриншоты, где видно перенаправление запросов на разные серверы при обращении к HAProxy c использованием домена example.local и без него. - Скриншоты 4, 5, , код ниже.


```
global
	log /dev/log	local0
	log /dev/log	local1 notice
	chroot /var/lib/haproxy
	stats socket /run/haproxy/admin.sock mode 660 level admin expose-fd listeners
	stats timeout 30s
	user haproxy
	group haproxy
	daemon

	# Default SSL material locations
	ca-base /etc/ssl/certs
	crt-base /etc/ssl/private

	# See: https://ssl-config.mozilla.org/#server=haproxy&server-version=2.0.3&config=intermediate
        ssl-default-bind-ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384
        ssl-default-bind-ciphersuites TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256
        ssl-default-bind-options ssl-min-ver TLSv1.2 no-tls-tickets

defaults
	log	global
	mode	http
	option	httplog
	option	dontlognull
        timeout connect 5000
        timeout client  50000
        timeout server  50000
	errorfile 400 /etc/haproxy/errors/400.http
	errorfile 403 /etc/haproxy/errors/403.http
	errorfile 408 /etc/haproxy/errors/408.http
	errorfile 500 /etc/haproxy/errors/500.http
	errorfile 502 /etc/haproxy/errors/502.http
	errorfile 503 /etc/haproxy/errors/503.http
	errorfile 504 /etc/haproxy/errors/504.http

frontend example  # секция фронтенд
        mode http
        bind :8088
        #default_backend web_servers
	acl ACL_example.local hdr(host) -i example.local
	use_backend web_servers if ACL_example.local	
	default_backend default_response

backend web_servers    # секция бэкенд
        mode http
        balance roundrobin
        option httpchk
        http-check send meth GET uri /index.html
        server s1 127.0.0.1:8888 check weight 2
        server s2 127.0.0.1:9999 check weight 3
		server s3 127.0.0.1:1111 check weight 4


listen web_tcp

	bind :1325

	server s1 127.0.0.1:8888 check inter 3s
	server s2 127.0.0.1:9999 check inter 3s
	server s3 127.0.0.1:1111 check inter 3s

backend default_response
	mode http
	http-request deny deny_status 403
```


Скриншот 1: Решение задания 2

![Скриншот 1](https://github.com/roomantix/8-03-hw/blob/master/images/1.png)

Скриншот 2: Решение задания 2

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/2.png)

Скриншот 3: Решение задания 2

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/4.png)

Скриншот 4: Решение задания 2

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/5.png)

Скриншот 5: Решение задания 2

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/6.png)

Скриншот 6: Решение задания 2

![Скриншот 2](https://github.com/roomantix/8-03-hw/blob/master/images/7.png)



