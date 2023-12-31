#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "rfs.h"

#define error_printf printf
#define debug_printf if( debugLevel>0 ) printf

#define MAX_FILES 256
#define MAX_ARGS  256

void closeFiles();

void dummy_printf(char *ptr,...);

FILE *fpout;
FILE *fpin;

int inputFileCount;
char *inputFileName;
int fileLength;

uint8_t *buf;
long buflen;

const char *argerror     = "error: Two file arguments required";
const char commentLine[] = "/************************************************************************/\n";

char stringbuf[256];

int fileargs = 0;
int optArgs = 0;
int filearg[ MAX_FILES ];
int optArg[  MAX_ARGS  ];
char *fromfile;
char *tofile;
struct tm *tptr;
time_t lt;

char *outputFileName;
float compressRatio  = 0.0f;

int compression  = 0;
int debugLevel   = 0;

typedef struct __fileInfo {

  char *fileName;
  int fileLength;

} FileInfo;

FileInfo files[MAX_FILES];

int main(int argc, char *argv[]){

  int i,j;
  int ret;
  unsigned char ch='\0';
  int count;
  char tempc;
  int len;
  char * tmpStr;
  
  int temp;
  int temp2;
  int temp3;
    
  if ( argc <= 2 ){
    error_printf( "Syntax: rfscreate [option] ... [option] <outputfile> <inputfiles>\n\n\r" );
    error_printf( "        <outputfile> : Name of output file\n\r");
    error_printf( "        <inputfiles> : List of input files to convert\n\r" );
    error_printf( "        -c           : Compress files\n\r");
    error_printf( "        -d:<0-9>     : Debug level\n\r" );
    error_printf( "\n" );
    exit(1);
  }

  /*************************************************************************/
  /*                     Command line parsing                              */
  /*************************************************************************/
  i=1; 
  optArgs = 0; 
  fileargs = 0;

  debug_printf( "-------------------- Argument processing -------------------\n" );
  while( i < argc ){
    
    ch = argv[i][0];

    if( ch == '-' ){

      debug_printf("option : %s\n", argv[i]);

      switch(argv[i][1]){

      case 'n':
        if (argv[i][2] == 'c'){
          compression = 0;
        }
        break;

      case 'd':
        ret = sscanf( argv[i], "-d:%d", &temp );
        if(ret == 1){
          debugLevel = temp;
        }
        debug_printf( "Debug level       : %d\n", temp );
        
        break;

      default:
        error_printf("Unknown option: %s\n",argv[i]);
        break;
      }

      optArg[optArgs] = i;
      optArgs++;

    }
    else{

      filearg[fileargs] = i;
      debug_printf( "filearg[%d] = argv[%d]: %s\n", fileargs, filearg[fileargs], argv[i] );

      fileargs++;

    }

    i++;

  }

  if( fileargs<2 ){
    error_printf(argerror);
    exit(1);
  }

  debug_printf( "------------------- /Argument processing -------------------\n" );


  debug_printf( "---------------- File information gathering ----------------\n" );

  /* Get local time */
  lt = time(NULL);
  if(lt!=-1){
    tptr = localtime(&lt);
    printf( "Local time            : %s",asctime(tptr) );
  }
  else{
    error_printf("Error: Failed to get local time.\n");
    exit(1);
  }

  /* Open output file */
  outputFileName = argv[filearg[0]];
  if( (fpout=fopen(outputFileName ,"wb")) == NULL ){
    error_printf("Error: File %s could not be opened for write.\n", outputFileName );
    closeFiles();
    exit(1);
  }
  else{
    printf( "Output file           : %s\n", outputFileName );
  }

  /* Loop through input files */
  inputFileCount = fileargs-1;
  for( j=0; j<inputFileCount; j++ ){

    inputFileName = argv[filearg[j+1]];

    /* Open the file */
    if( (fpin=fopen( inputFileName ,"rb")) == NULL ){
      error_printf("Error: File %s could not be opened for reading.\n", inputFileName );
      closeFiles();
      exit(1);
    }

    /* Find file length */
    fseek(fpin,0,SEEK_END);
    fileLength = ftell(fpin);
    fseek(fpin,0,SEEK_SET);

    /* Store the information */
    files[j].fileName   = inputFileName;
    files[j].fileLength = fileLength;

    /* Close the file */
    fclose(fpin);

  }

  debug_printf( "--------------- /File information gathering ----------------\n" );

  /* Write initial header to it */
  fprintf( fpout, "/************************************************************************/\n");
  fprintf( fpout, "/* Autogenerated file - DO NOT EDIT                                     */\n");
  fprintf( fpout, "/*                                                                      */\n");
  fprintf( fpout, "/* Date: %02d.%02d.%04d %02d:%02d:%02d                                            */\n",
           tptr->tm_mday,
           tptr->tm_mon+1,
           tptr->tm_year+1900,
           tptr->tm_hour,
           tptr->tm_min,
           tptr->tm_sec
           );
  /* fprintf( fpout, "/\* Date: %s                      *\/\n", asctime(tptr) ); */
  fprintf( fpout, "/*                                                                      */\n");
  fprintf( fpout, "/* Files embedded in this file;                                         */\n");
  fprintf( fpout, "/*                                                                      */\n");
  fprintf( fpout, "/*    Length    Index    Name                                           */\n");
  fprintf( fpout, "/*----------------------------------------------------------------------*/\n");
  printf( "    Length    Index    Name\n");
  printf( "----------------------------------------------------------------------\n");
  for( j=0; j<inputFileCount; j++ ){
    printf( "  %8d       %2d    %s\n", files[j].fileLength, j, files[j].fileName );
    sprintf( stringbuf, "/*  %8d       %2d    %s", files[j].fileLength, j, files[j].fileName );
    len = strlen( stringbuf );
    for( i=len; i<(sizeof(commentLine)-4); i++ ) stringbuf[i] = ' ';
    stringbuf[i++] = '*';
    stringbuf[i++] = '/';
    stringbuf[i++] = '\n';
    stringbuf[i  ] = 0x00;
    /*printf(stringbuf);*/
    fprintf( fpout, stringbuf );
  }
  fprintf( fpout, "/************************************************************************/\n");
  fprintf( fpout, "#ifndef __RFS_FILES_H_\n\n");
  fprintf( fpout, "#define __RFS_FILES_H_\n\n");

  fprintf( fpout, "#include <stdint.h>\n");
  fprintf( fpout, "\n");


  fprintf( fpout, "#define RFS_FILE_COUNT %d\n", inputFileCount );
  fprintf( fpout, "const uint32_t RFS_fileCount = RFS_FILE_COUNT;\n" );
  fprintf( fpout, "\n");

  /* Write file name constants */
  for( j=0; j<inputFileCount; j++ ){
    fprintf( fpout, "const uint8_t RFS_fileName%d[] = \"%s\";\n", j, files[j].fileName );
  }
 
  /* Write file name pointer array */
  fprintf( fpout, "\n");
  fprintf( fpout, "const uint8_t *RFS_fileNames[ RFS_FILE_COUNT ] = {\n" );
  for( j=0; j<inputFileCount; j++ ){
    fprintf( fpout, "   RFS_fileName%d", j );
    if( j != (inputFileCount-1) ) fprintf( fpout, ",\n" );
  }
  fprintf( fpout, "\n");
  fprintf( fpout, "};\n");

  /* Write file length array */
  fprintf( fpout, "\n");
  fprintf( fpout, "const uint32_t RFS_fileLength[ RFS_FILE_COUNT ] = {\n" );
  for( j=0; j<inputFileCount; j++ ){
    fprintf( fpout, "   %d", files[j].fileLength );
    if( j != (inputFileCount-1) ) fprintf( fpout, ",\n" );
  }
  fprintf( fpout, "\n");
  fprintf( fpout, "};\n");

  /* Predeclare pointers to file data*/
  fprintf( fpout, "\n");
  for( j=0; j<inputFileCount; j++ ){
    fprintf( fpout, "const uint8_t RFS_fileData%d[];\n",j );
  }

  /* Write file data pointer array */
  fprintf( fpout, "\n");
  fprintf( fpout, "const uint8_t *RFS_fileData[ RFS_FILE_COUNT ] = {\n" );
  for( j=0; j<inputFileCount; j++ ){
    fprintf( fpout, "   RFS_fileData%d", j );
    if( j != (inputFileCount-1) ) fprintf( fpout, ",\n" );
  }
  fprintf( fpout, "\n");
  fprintf( fpout, "};\n");

  /* Write actual image data */  
  for( j=0; j<inputFileCount; j++ ){

    /* Open the file */
    if( (fpin=fopen( files[j].fileName ,"rb")) == NULL ){
      error_printf("Error: File %s could not be opened for reading.\n", files[j].fileName );
      closeFiles();
      exit(1);
    }

    /* Write file data into header file */
    fprintf( fpout, "\n");
    fprintf( fpout, "const uint8_t RFS_fileData%d[] = {\n",j );

    count = 0;
    fprintf( fpout, "\n   ");
    for( i=0; i<files[j].fileLength; i++ ){
      ch = fgetc( fpin );
      fprintf( fpout, "0x%02x", (unsigned int)ch );
      if ( j != (files[j].fileLength-1) ) fprintf( fpout, ", " );
      if ( (++count % 16) == 0 )  fprintf( fpout, "\n   ");
    }

    if( debugLevel>0) printf("last byte = %02Xh\n", (unsigned int)ch );
    temp = fgetc( fpin );
    ch = (unsigned char)temp;
    if( temp != EOF ){
      printf("File %s contains more data than file length indicates! Bytes read = %d [%d]\n",
             files[j].fileName,
             count,
             files[j].fileLength
             );
    }

    fclose( fpin );

    fprintf( fpout, "\n");
    fprintf( fpout, "};\n");

  }
  
  fprintf( fpout, "#endif\n");

  return 0;

}

void closeFiles(){

  int ret;

  debug_printf("Closing all open files\n");
  fclose(fpin);
  fclose(fpout);

}


void dummy_printf(char *ptr,...){
}
