#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#define INPUT_1 "/dev/urandom"
#define OUTPUT_1 "/home/gngrbrd/dev/scratch/sensor.dat"

struct deviceInput{
	const char *input;
	const char *inputName;
	const char *output;
	const char *outputName;
};

struct sensor_desc{
	int s1fd;
	int fd;
	int result;
	struct tm *loctime;
	const char *out;
	const char *in;
	const char *name_out;
	const char *name_in;
};

struct sensor
{
	time_t curtime;
	unsigned int data;
};


void init(char **args,struct deviceInput *devOut){
	devOut->input = args[1];
	devOut->inputName = args[2];
	devOut->output = args[3];
	devOut->outputName = args[4];

	fprintf(stdout, "%s %s %s %s  \n",devOut->input, devOut->inputName, devOut->output , devOut->outputName);

}
void printstruct(void *var, int size){
	unsigned char *ch;
	ch = (unsigned char *)malloc(size);
	memcpy(ch,var,size);
	printf("size:  %d\n",size);
	int i; for(i = 0;i<size;i++){
		printf("%#x ", (int)*ch );
		ch++;
	}
	printf("\n");
}

void readsensor(struct sensor_desc *input,struct sensor *data){
	//open sensor input for reading
	if((input->fd = open(input->in,O_RDONLY))<0){
		perror(input->name_in);
	}
	//open ouput file for writing
	if((input->s1fd = open(input->out,O_WRONLY| O_CREAT | O_TRUNC, 0666))<0){
		perror(input->name_out);
	}
	//read data into struct sensor
	if((input->result = read(input->fd,&data->data, sizeof(struct sensor)))<0){
				perror(input->in);
			}else{
					printf("bytes read: %d\n",input->result);		
			}
			data->curtime = time(NULL); 
			input->loctime = localtime(&data->curtime);
			printf("%s\n",asctime(input->loctime));

			if((input->result = write(input->s1fd,data, sizeof(struct sensor)))<0){
				perror(input->out);
			}else{
					printf("bytes written: %d\n",input->result);
			}

			close(input->s1fd);
			close(input->fd);

}

int main(int argc, char **argv){

struct sensor_desc *input;
struct sensor *s1;
struct deviceInput *dev;

input = (struct sensor_desc *)malloc(sizeof(struct sensor_desc));
s1 = (struct sensor*)malloc(sizeof(struct sensor));
dev = (struct deviceInput*)malloc(sizeof(struct deviceInput));

init(argv,dev);
input->out = dev->output;
input->in = dev->input;
input->name_in = dev->inputName;
input->name_out = dev->outputName;

readsensor(input,s1);
printstruct(s1,sizeof(struct sensor));		


while(0 == 0){
	//printf("%d\n",(int)time(NULL) - (int)s1->curtime );
	if((time(NULL) - s1->curtime) == 5){
		readsensor(input,s1);
		printstruct(s1,sizeof(struct sensor));
	}		
}


}	


