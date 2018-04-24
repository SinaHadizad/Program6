//Sina Hadizad
//srh160630@utdallas.edu
//CS3377.002

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "cdk.h"


#define MATRIX_WIDTH 5 // matrix set to 5 rows and 3 columns
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{ //header record described by initial class

  public:

   uint32_t magicNumber;
   uint32_t versionNumber;
   uint64_t numRecords;  

};

const int maxRecordStringLength = 25;

class BinaryFileRecord{ //data record described by secondary class

  public:

   uint8_t strLength;
   char stringBuffer[maxRecordStringLength];

};

int main()
{
  BinaryFileHeader *myHeader = new BinaryFileHeader(); //creating new objects for classes
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binInfile ("binary.bin", ios::in | ios::binary); //utilizing binary I/O to read file

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));

  if(!binInfile.is_open()){ //error statement
    
    cout << "Error opening file" << endl;

  }
  else{ 
   
    ostringstream convert; //using stringstream method to convert information from binary file into readable hex in const char* form
    convert << hex << uppercase << myHeader->magicNumber;
    string magicString = "0x" + convert.str();
    const char* magic = magicString.c_str();

    ostringstream convert2; //using stringstream method to convert information from binary file into readable int in const char* form
    convert2 << myHeader->versionNumber;
    string versionString = "Version: " + convert2.str();
    const char* version = versionString.c_str();

    ostringstream convert3; //using stringstream method to convert information from binary file into readable int in const char* form
    convert3 << myHeader->numRecords;
    string numString = "Records: " + convert3.str();
    const char* num = numString.c_str(); 
    
    WINDOW *window; //CDK screen matrix
    CDKSCREEN *cdkscreen;
    CDKMATRIX *myMatrix;        
  
    const char *rowTitles[] = {"R0", "a", "b", "c"};
    const char *columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
    int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
    int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

    window = initscr(); //initialize CDK screen and make sure putty terminal is large enough
    cdkscreen = initCDKScreen(window);
  
    initCDKColor(); //start CDK colors

    //create the matrix, manually cast
   
    myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
		            MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			    boxTypes, 1, 1, ' ', ROW, true, true, false);

    if (myMatrix ==NULL)
      {
        printf("Error creating Matrix\n");
        _exit(1);
      }

    drawCDKMatrix(myMatrix, true); //display the matrix

    setCDKMatrixCell(myMatrix, 1, 1, magic); //display values from header class into matrix
    setCDKMatrixCell(myMatrix, 1, 2, version);
    setCDKMatrixCell(myMatrix, 1, 3, num);

    string temp = convert3.str(); //required conversion to read up to certain # of records
    int records = atoi(temp.c_str());
    int i = 0;

    while(i < records){ //while loop to read strings and count their corresponding lengths 

      string phrase = myRecord->stringBuffer;
      const char* phrasePrint = phrase.c_str();

      ostringstream convert4;
      convert4 << static_cast<int>(myRecord->strLength);
      string length = "strlen: " + convert4.str();
      const char* lengthPrint = length.c_str();
    
      i++;

      setCDKMatrixCell(myMatrix, i+1, 1, lengthPrint); //display values from data class into matrix
      setCDKMatrixCell(myMatrix, i+1, 2, phrasePrint);
     
      binInfile.read((char*) myRecord, sizeof(BinaryFileRecord)); //required to move buffer
    }
  
    drawCDKMatrix(myMatrix, true); //required

    sleep (15); //evaluate results
  
    endCDK(); //cleanup screen
  
    binInfile.close(); //close file for error purposes

  } //end of else statement
   
}


