#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

struct sensor{
	time_t curtime;
	unsigned int data;
};

struct sensor_desc{
	int fd;
	int result;
	const char *in;
	const char *name;
};

struct deviceInput{
	const char *input;
	const char *inputName;
	FILE 	*outFile;	
	const char *outFileName;

};


void init(char **args,struct deviceInput *devOut){
	devOut->input = args[1];
	devOut->inputName = args[2];
	devOut->outFileName = args[3];

	fprintf(stdout, "%s %s  saving to:  %s\n",devOut->input, devOut->inputName,devOut->outFileName );

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

void datalog(struct sensor *outFile, struct deviceInput *desc){

	   struct tm *loctime;
	   int n;
	   char name [100];
	   unsigned char *ch = (unsigned char*)&outFile->data;
	   int i;
	   if(desc->outFile = fopen (desc->outFileName,"w")){

	   		loctime = localtime(&outFile->curtime);
			fprintf(desc->outFile,"%s %s\n",asctime(loctime),desc->inputName);
			for(i = 0;i<sizeof(unsigned int);i++){
				fprintf(desc->outFile,"%#x ", (int)*ch );
				ch++;
			}
			fprintf(desc->outFile, "\n");

			fclose(desc->outFile);
 		
	   }else{
	   	perror("log");
	   }
	}

void readsensor(struct sensor_desc *input,struct sensor *data){

		if((input->fd = open(input->in,O_RDONLY))<0){
		perror(input->name);
	}

		if((input->result = read(input->fd,data, sizeof(struct sensor)))<0){
			perror(input->name);
		}else{
				//printf("bytes read: %d\n",input->result);		
		}

		close(input->fd);
}

int main(int argc, char **argv){
	struct sensor *m1;
	struct sensor_desc *input;
	struct deviceInput *devOut;

	m1 = (struct sensor *)malloc(sizeof(struct sensor));
	input = (struct sensor_desc *)malloc(sizeof(struct sensor_desc));
	devOut = (struct deviceInput *)malloc(sizeof(struct deviceInput));
	init(argv,devOut);

	input->in = devOut->input;
	input->name = devOut->inputName;
	readsensor(input,m1);
while(0==0){
	if(time(NULL) % 3 == 0 ){
		readsensor(input,m1);		
		//printstruct(m1,sizeof(struct sensor));
		datalog(m1,devOut);
	}
}
	


}