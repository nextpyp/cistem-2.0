#include "../../core/core_headers.h"

class
        Merge3DApp : public MyApp {
  public:
    bool DoCalculation( );
    void DoInteractiveUserInput( );

  private:
};

IMPLEMENT_APP(Merge3DApp)

// override the DoInteractiveUserInput

void Merge3DApp::DoInteractiveUserInput( ) {
    wxString output_reconstruction_1;
    wxString output_reconstruction_2;
    wxString dump_file_seed_1;
    wxString dump_file_seed_2;
    int      number_of_dump_files;

    UserInput* my_input = new UserInput("Local-Merge3D", 1.01);

    output_reconstruction_1        = my_input->GetFilenameFromUser("Output intermediate reconstruction 1", "The first output intermediate reconstruction", "my_reconstruction_1.mrc", false);
    output_reconstruction_2        = my_input->GetFilenameFromUser("Output intermediate reconstruction 2", "The second output intermediate reconstruction", "my_reconstruction_2.mrc", false);
    dump_file_seed_1               = my_input->GetFilenameFromUser("Seed for input dump filenames for odd particles", "The seed name of the first dump files with the intermediate reconstruction arrays", "dump_file_seed_1_.dat", false);
    dump_file_seed_2               = my_input->GetFilenameFromUser("Seed for input dump filenames for even particles", "The seed name of the second dump files with the intermediate reconstruction arrays", "dump_file_seed_2_.dat", false);
    number_of_dump_files           = my_input->GetIntFromUser("Number of dump files", "The number of dump files that should be read from disk and merged", "1", 1);

    delete my_input;


    //	my_current_job.Reset(14);

    my_current_job.ManualSetArguments("tttti", output_reconstruction_1.ToUTF8( ).data( ),
                                      output_reconstruction_2.ToUTF8( ).data( ),
                                      dump_file_seed_1.ToUTF8( ).data( ),
                                      dump_file_seed_2.ToUTF8( ).data( ),
                                      number_of_dump_files);
}

// override the do calculation method which will be what is actually run..

bool Merge3DApp::DoCalculation( ) {
    wxString output_dumpfile_1              = my_current_job.arguments[0].ReturnStringArgument( );
    wxString output_dumpfile_2              = my_current_job.arguments[1].ReturnStringArgument( );
    wxString dump_file_seed_1               = my_current_job.arguments[2].ReturnStringArgument( );
    wxString dump_file_seed_2               = my_current_job.arguments[3].ReturnStringArgument( );
    int      number_of_dump_files           = my_current_job.arguments[4].ReturnIntegerArgument( );
  

    int        i;
    int        logical_x_dimension;
    int        logical_y_dimension;
    int        logical_z_dimension;
    int        original_x_dimension;
    int        original_y_dimension;
    int        original_z_dimension;
    int        count;
    int        intermediate_box_size;
    int        images_processed;
    float      mask_volume_fraction;
    float      mask_falloff = 10.0;
    float      pixel_size;
    float      original_pixel_size;
    float      average_occupancy;
    float      average_sigma;
    float      sigma_bfactor_conversion;
    float      particle_area_in_pixels;
    float      scale;
    float      binning_factor;
    wxString   my_symmetry;
    wxDateTime my_time_in;
    wxFileName dump_file_name = wxFileName::FileName(dump_file_seed_1);
    wxString   extension      = dump_file_name.GetExt( );
    wxString   dump_file;
    bool       insert_even;
    bool       center_mass;
    bool       crop_images;

    
    my_time_in = wxDateTime::Now( );

    dump_file = wxFileName::StripExtension(dump_file_seed_1) + wxString::Format("%i", 1) + "." + extension;

    if ( (is_running_locally && DoesFileExist(dump_file)) || (! is_running_locally && DoesFileExistWithWait(dump_file, 90)) ) // C++ standard says if LHS of OR is true, RHS never gets evaluated
    {
        //
    }
    else {
        SendError(wxString::Format("Error: Dump file %s not found\n", dump_file));
        exit(-1);
    }

    Reconstruct3D temp_reconstruction;
    temp_reconstruction.ReadArrayHeader(dump_file, logical_x_dimension, logical_y_dimension, logical_z_dimension,
                                        original_x_dimension, original_y_dimension, original_z_dimension, images_processed, pixel_size, original_pixel_size,
                                        average_occupancy, average_sigma, sigma_bfactor_conversion, my_symmetry, insert_even, center_mass);
    wxPrintf("\nReconstruction dimensions = %i, %i, %i, pixel size = %f, symmetry = %s\n", logical_x_dimension, logical_y_dimension, logical_z_dimension, pixel_size, my_symmetry);
    temp_reconstruction.Init(logical_x_dimension, logical_y_dimension, logical_z_dimension, pixel_size, average_occupancy, average_sigma, sigma_bfactor_conversion);
    Reconstruct3D my_reconstruction_1(logical_x_dimension, logical_y_dimension, logical_z_dimension, pixel_size, average_occupancy, average_sigma, sigma_bfactor_conversion, my_symmetry);
    Reconstruct3D my_reconstruction_2(logical_x_dimension, logical_y_dimension, logical_z_dimension, pixel_size, average_occupancy, average_sigma, sigma_bfactor_conversion, my_symmetry);

    wxPrintf("\nReading reconstruction arrays...\n\n");
    float min = 0.0, max = 0.0; 

    for ( count = 1; count <= number_of_dump_files; count++ ) {
        dump_file = wxFileName::StripExtension(dump_file_seed_1) + wxString::Format("%i", count) + "." + extension;
        wxPrintf("%s\n", dump_file);
        if ( (is_running_locally && DoesFileExist(dump_file)) || (! is_running_locally && DoesFileExistWithWait(dump_file, 90)) ) // C++ standard says if LHS of OR is true, RHS never gets evaluated
        {
            temp_reconstruction.ReadArrays(dump_file);
            temp_reconstruction.image_reconstruction.GetMinMax(min, max);
            if (min == 0.0 && max == 0.0) {
                wxPrintf("%s is empty. Skipping...\n", dump_file);
                continue;
            }
            my_reconstruction_1 += temp_reconstruction;
        }
        else {
            SendError(wxString::Format("Error: Dump file %s not found\n", dump_file));
            exit(-1);
        }
    }

    for ( count = 1; count <= number_of_dump_files; count++ ) {
        dump_file = wxFileName::StripExtension(dump_file_seed_2) + wxString::Format("%i", count) + "." + extension;
        wxPrintf("%s\n", dump_file);
        if ( (is_running_locally && DoesFileExist(dump_file)) || (! is_running_locally && DoesFileExistWithWait(dump_file, 90)) ) // C++ standard says if LHS of OR is true, RHS never gets evaluated
        {
            temp_reconstruction.ReadArrays(dump_file);
            temp_reconstruction.image_reconstruction.GetMinMax(min, max);
            if (min == 0.0 && max == 0.0) {
                wxPrintf("%s is empty. Skipping...\n", dump_file);
                continue;
            }
            my_reconstruction_2 += temp_reconstruction;
        }
        else {
            SendError(wxString::Format("Error: Dump file %s not found\n", dump_file));
            exit(-1);
        }
    }

    wxPrintf("\nFinished reading arrays\n");

    my_reconstruction_1.DumpArrays(output_dumpfile_1, false);
    my_reconstruction_1.image_reconstruction.GetMinMax(min, max);
    if (min == 0.0 && max == 0.0) wxPrintf("Output %s is empty.\n", output_dumpfile_1);
    my_reconstruction_2.DumpArrays(output_dumpfile_2, true);
    my_reconstruction_2.image_reconstruction.GetMinMax(min, max);
    if (min == 0.0 && max == 0.0) wxPrintf("Output %s is empty.\n", output_dumpfile_2);

    wxPrintf("\nFinished merging intermediate reconstruction\n");

    return true;
    
}
