#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif
#include <string>
#include "../../include/Parser.h"
//#include "../../include/Layer.h"
#include "../../include/datastructures/tensor.h"
#include <vector>
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

#endif

const H5std_string FILE_NAME( FILENAME );

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata);
extern "C" void do_dset(hid_t);

int main(void)
{

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

      cerr << endl << "Iterating over elements in the file" << endl;
      herr_t idx=  H5Lvisit(group.getId(), H5_INDEX_NAME, H5_ITER_INC,  file_info, NULL);
      cerr << endl;
      /*
       * Close the file.
       */

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
file_info(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata)
{
    /*
     * Display group name.
     */
    hid_t group;
    hid_t status;
    H5O_info_t infobuf;

    // possibly create a new layer in the neural network. 
     
    group= H5Gopen2(loc_id, name, H5P_DEFAULT); // here group is actually a dset
    status = H5Oget_info_by_name(loc_id, name, &infobuf, H5P_DEFAULT);
    
    switch(infobuf.type){
        case H5O_TYPE_GROUP:{
            cout << "Group : " << name << endl;
            break;
                            }
        case H5O_TYPE_DATASET:{

            cout<< "Dataset: " << name;
            hid_t datatype, dataspace, cclass, order, size, rank; 
            hid_t dset = H5Dopen2(loc_id, name, H5P_DEFAULT);
            datatype= H5Dget_type(dset);
            cclass = H5Tget_class(datatype); 
            size= H5Tget_size(datatype);
            cout<<  " of size= "<< size <<endl;
            dataspace = H5Dget_space(dset);
            rank= H5Sget_simple_extent_ndims(dataspace); 
            cout<< rank<<endl;
            hsize_t dims[rank];
            H5Sget_simple_extent_dims(dataspace, dims, NULL);
            for (int i=0; i<rank; i++) cout<< dims[i] << "  ";
            cout<<endl;
            break;
                              }
        case H5O_TYPE_NAMED_DATATYPE:{
            cout<< "DataType" << name <<endl;
            break;
                                     }
        default:{
            cout<< "Unknown"<<endl;
            
                }       
    }
             
    H5Gclose(group);

    return 0;
 }
