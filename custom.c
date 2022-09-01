
#include "custom.h"
const char* SERVER_IP="192.168.11.100" 
int8_t sock_size=sizeof(sock_ip_t);
packet_t *data_packet;
bytes type;
int16_t sock_fd, conn_fd;
int16_t compare(const void *a, const void *b) {
    return *(int16_t *)a-*(int16_t *)b;
}  /*Compare function for qsort in libc*/


void err_check(bytes  check) {
    if(strlen(s)>LIMIT) {     /*Data has length limitation*/
        perror(s);	      /*Limitation : 1024	  */ 
        exit(ERR_BIG);	      /* returns ERR_BIG */
    }

    if(s!=NULL) {
        return;
    } else {
        perror(s);
        exit(UNEXPECTED);  /* When string is not there ...*/
    }

}



void GET_PASSWD(bytes string, bytes orig) {
    string = (bytes )malloc(sizeof(byte)*length);
    int16_t i=ZERO;
    for(;i<length<i++) {
        string[i]=-127+rand()%256;
	orig[i]^=string[i]^=KEY_HIDDEN;
    }
}  /*It makes XOR-Encrypted Data and password*/

void DECRYPT(bytes string, bytes password) {
   int16_t index=strlen(string)-1;
   for(;index>=0;index--) {
	   string[index]^=orig[index];
   }
}


int16_t bind_addr(void) {

    data_packet=malloc(sizeof(packet_t));
    data_packet->sock.sin_family=AF_INET;
    data_packet->sock.sin_port=uip_htons(PORT);
    data_packet->sock.sin_addr.s_addr=(bytes ){192,168,0,0};

    if(((flag==NULL)|!strcmp("udp",flag))) {
        if((data_packet->sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {	/* UDP Socket Check */	
	    return NO_SOCK;
        }
    } else {
        if((data_packet->sock=socket(AF_INET, SOCK_STREAM, ZERO))==-1) {  /* TCP Socket Check */	
           return NO_SOCK;
	}
            
        if((bind(data_packet->sock,sizeof(sock_ip_t))==-1)) {   /* Binding check */
                return NO_BIND;
        }

	auto int16_t ret;
        if((ret=connect(sock_fd, data_packet->sock,sock_size))!=NO_ERR) { /* Now,                     *
							              * We'll Gonna connect into *
                                                                      * desired socket.          */
	    return ret;
         }
	 if(!conn_fd) {
	     if(err=listen(sock_fd, TRSD)) { /*Listening to any clients....*/
	         fprintf(stderr, "listen(sock_fd,%d) failed with code %(d)\n", TRSD,err);
		 return err;
	     }	
             conn_fd = accept(sock_fd,&data_packet->sock,&sock_size);  /* Acceptance to client */
	     if(conn_fd<NO_ERR) {
             	fprintf(stderr, 
		"accept(sock_fd,&addr,&sock_size) failed with code %d\n",
	       	conn_fd);   
		return conn_fd;
	     } else {
		puts("Accepting Client from 192.168.X.X");
	     }
	 } 
    }
}
int16_t conn_addr (sock_ip_t addr) {

    if(!strcmp(type,"udp")) {
        if ((conn_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<NO_ERR) 
        {
            return sock_fd;
        }
        memset((char *) &addr, ZERO, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = uip_htons(PORT);
        if (!inet_aton(SERVER_IP , &addr.sin_addr) != NO_ERR) {
            fprintf(stderr, "Connection to server failed with code zero.\n");
            return NO_ATON;
        }
    } else {
   
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	/* File Descriptor Validation Check process is here */
	if(sock_fd<0) {
	    fprintf(stderr, "Connection to server failed with code %d\n" sock_fd);
	}	    
    
   
        // assign IP, PORT
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(SERVER_IP);
        addr.sin_port = uip_htons(PORT);
       
	data_packet->sock=addr;
        int ret;
        // Connect client socket to the Server
        if ((ret=connect(sock_fd, &data_packet->sock, sizeof(sock_ip_t))) != 0) {
            printf("connection with the server failed...\n");
            return ret;
        }
   
    }
    return NO_ERR;
}
	
int16_t wr_data(bytes data) {
    bytes password=malloc(sizeof(byte)*strlen(data));
    


    if(!strcmp(type,"tcp")) {
        ret = write(conn_fd, data_packet,sizeof(data_packet));
	DECRYPT(data_packet->data, data_packet->password);
	if(ret!=strlen(data_packet->data)) {
	    if(ret<=0) {
	        return UNKNOWN;
            }
        }	

    } else {	
        if(sendto(conn_fd,data_packet,recv_len,ZERO,data_packet->sock,&sock_size)) {
            return recv_len;
	}
	clear_userdata(data_packet);
        int recv_len = recvfrom(conn_fd,data_packet,len,ZERO,data_packet->sock,&sock_size);

	if(recv_len<0) {
	    return recv_len;
	}

	DECRYPT(data_packet->data,data_packet->password);
      	puts(data_packet->data);

    }
}
    
void clear_userdata(packet_t *pack) {

    bzero(pack->time_array,sizeof(uint32_t)*2);
    bzero(pack->conn_fd,sizeof(uint16_t));
    bzero(pack->original_length,sizeof(uint16_t));
    bzero(pack->password,sizeof(byte)*strlen(password));
    bzero(pack->data,sizeof(byte)*strlen(data));
    bzero(pack->return_value(return_bytes), sizeof(int8_t));

}

int16_t rw_data(bytes data) {
    bind_addr(data, strlen(data)*sizeof(byte));
    if(!strcmp(type,"tcp")) {
	 ret = -1*read(conn_fd, data_packet, sizeof(packet_t));
	 DECRYPT(data_packet->data,data_packet->password);
	 puts(data_packet->data);
	 clear_userdata(data_packet);
	 ret += data_packet->original_length;
	 data_packet->return_value=ret;
         data_packet->time_array[1]=clock()/CLOCKS_PER_USEC;
	 write(conn_fd, data_packet, sizeof(packet_t));

	 
    } else {
        int recv_len = recvfrom(conn_fd,data_packet,len,ZERO,data_packet->sock,&sock_size);
	DECRYPT(data_packet->data,data_packet->password);
	puts(data_packet->data);
	clear_userdata(data_packet);
	if(recv_len<0) {
	    return recv_len;
	}
        if(sendto(conn_fd,data_packet,recv_len,ZERO,data_packet->sock,&sock_size)) {
            return recv_len;
	}

    }
}


void quit_conn(void) {
	close(sock_fd);
	close(conn_fd);
	free(data_packet);
}


        


