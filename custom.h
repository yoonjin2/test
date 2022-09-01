#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<time.h>
#define PORT 20111
#define LIMIT 1024


#define TRSD 10
#define KEY_HIDDEN 329142328412
#define CLOCKS_PER_USEC CLOCKS_PER_SEC/1000000.0F   /*CPU Frequency    *
						     *in 1 microsecond */



#define NO_ATON    3    /* Use this when inet_aton() has failed */
#define NO_BIND    2    /* Use this when bind() has failed */


#define NO_SOCK    1    /* Use this when socket()
			 *  has failed                     */

/* Duplicated Alias */
#define NO_ERR     0   /* When No error        */
#define ZERO 	   0   

                       /* * * * * * * * * * * * *
                        * When you want         * 
			* to make some          *  
			* better visibility     *
		        * to your return value  *
                        * (Section for          *
                        * Better Looking        *
                        * Code generation)      *
			* * * * * * * * * * * * */


#define ERR_DEAD  -1   /* Use this when connection is dead*/


#define ERR_LOSS  -2   /* Use this when there's data loss *
			* in your return value            */

#define UNKNOWN -3


typedef char   byte;    /* char is byte in here   */
typedef byte*  bytes;   /* byte* is same as bytes */

typedef struct packet {
    in_addr_t  sock;  
    uint32_t   time_array[2];  
    uint16_t   conn_fd;
    uint16_t   original_length;
    /* Timestamp Array for Integrity check */

    bytes     password;  
    /* Password will be generated randomly */

    bytes    data;      
    /* Encrypted data for original data */

    int8_t    return_value;  
    /* length of lost bytes */

} packet_t;  /* You don't need to use struct packet keyword.       *
	      *  You can use packet_t alias instead;               */

void GET_PASSWD(bytes string, bytes orig);       /* * * * * * * * * * * 
					* random function   *
					* as                * 
                                        * default random    *
					* password types    * 
					* * * * * * * * * * */
void DECRYPT(bytes string, bytes password);

void err_check(bytes check);  /* * * * * * * * * * * * 
			       * easy error check    *
                               * function for code   *
                               * * * * * * * * * * * */

int16_t wr_data(bytes data); /* function for sending      *
                             * some (bytes ) casted data */
int16_t bind_addr(); /* function for   * 
							  * binding socket */
int16_t conn_addr(in_addr_t addr);

int16_t rw_data(bytes data);
                               /* * * * * * * * * * * * * * * * * 
				* function for receiving some   *
                                * data from external IPs;       *
				* it will return a length of    *
				* lost data.                    *
				* * * * * * * * * * * * * * * * */
void quit_conn(void) ;

