upstream example_app {
	server 127.0.0.1:8888 weight=2;
	server 127.0.0.1:9999 weight=3;
	server 127.0.0.1:1111 weight=4;

}