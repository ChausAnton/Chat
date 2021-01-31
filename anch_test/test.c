#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc , char * argv [] ){

        // argv[1] = 1.jpg

        FILE *file;
        char *buffer;
        unsigned long fileLen;

        //Open file
        file = fopen(argv[1], "rb");
        if (!file)
        {
                fprintf(stderr, "Unable to open file %s", argv[1]);
                return 0;
        }

        //Get file length
        fseek(file, 0, SEEK_END);
        fileLen=ftell(file);
        fseek(file, 0, SEEK_SET);

        //Allocate memory
        buffer=(char *)malloc(fileLen);
        if (!buffer)
        {
                fprintf(stderr, "Memory error!");
                                fclose(file);
                return 1;
        }

       fread(buffer,fileLen,sizeof(char),file);
       fclose(file);

       int i=0;

        FILE *write_ptr;
        write_ptr = fopen("test.jpg","wb");  // w for write, b for binary
       while (i < fileLen){
           fwrite(&buffer[i] ,sizeof(buffer[i]),1,write_ptr);
           printf("%c ",buffer[i]);
           i++;
           if( ! (i % 16) ) printf( "\n" );
       }

        
    
    fclose(write_ptr);

        return 0;

}
