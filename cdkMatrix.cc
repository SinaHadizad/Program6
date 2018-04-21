//Sina Hadizad
//srh160630@utdallas.edu
//CS3377.002

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "stdint.h"
#include "cdk.h"


#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{

  public:

   uint32_t magicNumber;
   uint32_t versionNumber;
   uint64_t numRecords;  

};

int main()
{
  BinaryFileHeader *myHeader = new BinaryFileHeader();

  ifstream binInfile ("binary.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  ostringstream convert;
  convert << hex << uppercase << myHeader->magicNumber;
  string magicString = "0x" + convert.str();
  const char* magic = magicString.c_str();

  ostringstream convert2;
  convert2 << myHeader->versionNumber;
  string versionString = "Version: " + convert2.str();
  const char* version = versionString.c_str();

  ostringstream convert3;
  convert3 << myHeader->numRecords;
  string numString = "Records: " + convert3.str();
  const char* num = numString.c_str(); 

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;           // CDK Screen Matrix

  const char *rowTitles[] = {"R0", "a", "b", "c"};
  const char *columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, magic);
  setCDKMatrixCell(myMatrix, 1, 2, version);
  setCDKMatrixCell(myMatrix, 1, 3, num);
  drawCDKMatrix(myMatrix, true);    /* required  */

  binInfile.close();

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
