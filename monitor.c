#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#define INPUT_1 "/home/gngrbrd/dev/scratch/sensor.dat"

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

};


void init(char **args,struct deviceInput *devOut){
	devOut->input = args[1];
	devOut->inputName = args[2];

	fprintf(stdout, "%s %s  \n",devOut->input, devOut->inputName);

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
void lotto(struct sensor *outFile, FILE *pFile){
	srand((unsigned) &outFile->data);
	int i;
	   for( i = 0 ; i < 6 ; i++ ) 
   {

      fprintf(pFile,"%d ",rand() % 55);
      fprintf(stdout,"%d ",rand() % 55);

   }      fprintf(pFile,"\n ");
   		fprintf(stdout,"\n ");
}
void datalog(struct sensor *outFile, struct deviceInput *desc){

	   FILE * pFile;
	   FILE *pLog;
	   struct tm *loctime;
	   int n;
	   char name [100];
	   unsigned char *ch = (unsigned char*)&outFile->data;
	   int i;
	   if(pFile = fopen ("/home/gngrbrd/dev/scratch/myfile.txt","w")){

	   		loctime = localtime(&outFile->curtime);
			fprintf(pFile,"%s %s\n",asctime(loctime),desc->inputName);
			for(i = 0;i<sizeof(unsigned int);i++){
				fprintf(pFile,"%#x ", (int)*ch );
				ch++;
			}
			fprintf(pFile, "\n");
			lotto(outFile,pFile);

			fclose(pFile);
 		
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