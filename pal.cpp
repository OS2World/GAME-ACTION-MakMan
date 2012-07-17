
#define INCL_GPILOGCOLORTABLE
#define INCL_GPIBITMAPS
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#define PAL_LENGTH 1028

int main (int argc, char** argv)
{
    FILE  *ftarget, *fsource;
    char  palTarget[PAL_LENGTH], palSource[PAL_LENGTH];
    int   ostart, olength, otarget,rc;

    printf("%s - palette manipulation utility\n",argv[0]);
    printf("Manipulating 1.%s with 2.%s\n",argv[1], argv[2]);
    ostart  = atoi(argv[3]);
    olength = atoi(argv[4]);
    otarget = atoi(argv[5]);
    printf("Copying 2.%i for %i colors to 1.%i\n",ostart, olength, otarget);


    ftarget = fopen(argv[1],"rb+");
    fsource = fopen(argv[2],"rb");

    if (ftarget!=NULL && fsource!=NULL)
     {
         fread(palTarget, PAL_LENGTH, 1, ftarget);
         fread(palSource, PAL_LENGTH, 1, fsource);
         fclose(fsource);

         for (int i = ostart*3; i < (ostart+olength)*3; i++)
            palTarget[otarget*3 + i] = palSource[i];

         fseek(ftarget,0,SEEK_SET);
         rc = fwrite(palTarget,PAL_LENGTH,1,ftarget);

         printf("Wrote modified palette %i\n",rc);
         fclose(ftarget);
      }
   else
       printf("Couldn't open one of the files\n");

}

