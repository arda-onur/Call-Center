#ARDA ONUR S018752
TARGET= client callcenter
normal: $(TARGET)
client: echo_client.c
	gcc -pthread echo_client.c -o echo_client
server: callcenter.c
	gcc -pthread callcenter.c -o callcenter
clean:
	$(RM) $(TARGET)
