/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * This example creates a group in the file and dataset in the group.
 * Hard link to the group object is created and the dataset is accessed
 * under different names.
 * Iterator function is used to find the object names in the root group.
 * Note that the C++ API iterateElems is still taking the operator function
 * in C.  Additional work on iterateElems is in progress.
 */
#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif
#include <string>

#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
    using std::cout;
    using std::cerr;
    using std::endl;
#endif  // H5_NO_STD
#endif

#include "H5Cpp.h"

#ifndef H5_NO_NAMESPACE
using namespace H5;
using namespace std;

#endif

const H5std_string FILE_NAME( "../../data/weights.best.hdf5" );
const int	RANK = 2;

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, void *opdata);

int main(void)
{
    hsize_t  dims[2];
    hsize_t  cdims[2];

   // Try block to detect exceptions raised by any of the calls inside it
   try
   {
      /*
       * Turn off the auto-printing when failure occurs so that we can
       * handle the errors appropriately
       */
      Exception::dontPrint();

      H5File file = H5File( FILE_NAME, H5F_ACC_RDWR );
      Group group = Group( file.openGroup( "model_weights" ));

      /*
       * Access "Compressed_Data" dataset in the group.
       */
      try {  // to determine if the dataset exists in the group
         DataSet * dataset = new DataSet( group.openDataSet( "Compressed_Data" ));
      }
      catch( GroupIException not_found_error )
      {
	 cout << " Dataset is not found." << endl;
      }
      cout << "dataset \"/Data/Compressed_Data\" is open" << endl;


      /*
       * Create hard link to the Data group.
       */
      file.link( H5G_LINK_HARD, "Data", "Data_new" );

      /*
       * We can access "Compressed_Data" dataset using created
       * hard link "Data_new".
       */
      try {  // to determine if the dataset exists in the file
        DataSet *  dataset = new DataSet( file->openDataSet( "/Data_new/Compressed_Data" ));
      }
      catch( FileIException not_found_error )
      {
         cout << " Dataset is not found." << endl;
      }
      cout << "dataset \"/Data_new/Compressed_Data\" is open" << endl;

      /*
       * Close the dataset.
       */
      delete dataset;

      /*
       * Use iterator to see the names of the objects in the file
       * root directory.
       */
      int ret = file->iterateElems("/", NULL, file_info, NULL);
      cout << endl;

      /*
       * Unlink  name "Data" and use iterator to see the names
       * of the objects in the file root direvtory.
       */
      cout << "Unlinking..." << endl;
      try {  // attempt to unlink the dataset
         file->unlink( "Data" );
      }
      catch( FileIException unlink_error )
      {
         cout << " unlink failed." << endl;
      }
      cout << "\"Data\" is unlinked" << endl;

      cerr << endl << "Iterating over elements in the file again" << endl;
      ret = file->iterateElems("/", NULL, file_info, NULL);
      cerr << endl;

      /*
       * Close the file.
       */
      delete file;

   }  // end of try block

   // catch failure caused by the H5File operations
   catch( FileIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the DataSet operations
   catch( DataSetIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the DataSpace operations
   catch( DataSpaceIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the Attribute operations
   catch( AttributeIException error )
   {
      //error.printError();
      return -1;
   }
   return 0;
}

/*
 * Operator function.
 */
herr_t
file_info(hid_t loc_id, const char *name, void *opdata)
{
    /*
     * Display group name.
     */
    cout << "Name : " << name << endl;

    return 0;
 }
