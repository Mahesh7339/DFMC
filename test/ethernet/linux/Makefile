CLIENTSRC = tcp_test_echo_client.c 
SERVERSRC = tcp_test_echo_server.c
ERRORSRC = errorMsg.c
ADDSRC = tcp_handle_socket.c 
client: $(CLIENTSRC) $(ERRORSRC)
	@(gcc -o testClient $(CLIENTSRC) $(ERRORSRC))

server:$(SERVERSRC) $(ERRORSRC) $(ADDSRC)
	gcc -o testServer $(SERVERSRC) $(ERRORSRC) $(ADDSRC)

runc:
	./testClient 127.0.0.1 "Hello"

clean:
	rm -f testServer
	rm -f testClient

