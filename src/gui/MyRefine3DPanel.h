#ifndef __MyRefine3DPanel__
#define __MyRefine3DPanel__

/**
@file
Subclass of Refine3DPanel, which is generated by wxFormBuilder.
*/

#include "ProjectX_gui.h"

class MyRefine3DPanel;

class RefinementManager {
  public:
    bool             start_with_reconstruction;
    MyRefine3DPanel* my_parent;

    float    active_low_resolution_limit;
    float    active_high_resolution_limit;
    float    active_mask_radius;
    float    active_signed_cc_limit;
    float    active_global_mask_radius;
    int      active_number_results_to_refine;
    float    active_angular_search_step;
    float    active_search_range_x;
    float    active_search_range_y;
    float    active_classification_high_res_limit;
    bool     active_should_focus_classify;
    float    active_sphere_x_coord;
    float    active_sphere_y_coord;
    float    active_sphere_z_coord;
    bool     active_should_refine_ctf;
    float    active_defocus_search_range;
    float    active_defocus_search_step;
    float    active_percent_used;
    float    active_inner_mask_radius;
    float    active_resolution_limit_rec;
    float    active_score_weight_conversion;
    float    active_score_threshold;
    bool     active_adjust_scores;
    bool     active_crop_images;
    bool     active_should_apply_blurring;
    float    active_smoothing_factor;
    float    active_sphere_radius;
    bool     active_do_global_refinement;
    bool     active_also_refine_input;
    bool     active_should_refine_psi;
    bool     active_should_refine_theta;
    bool     active_should_refine_phi;
    bool     active_should_refine_x_shift;
    bool     active_should_refine_y_shift;
    bool     active_should_mask;
    bool     active_should_auto_mask;
    bool     active_centre_mass;
    wxString active_mask_filename;
    bool     active_should_low_pass_filter_mask;
    float    active_mask_filter_resolution;
    float    active_mask_edge;
    float    active_mask_weight;
    long     active_mask_asset_id;

    long current_job_starttime;
    long time_of_last_update;
    int  number_of_generated_3ds;

    int  running_job_type;
    int  number_of_rounds_to_run;
    int  number_of_rounds_run;
    long current_job_id;

    long current_refinement_package_asset_id;
    long current_input_refinement_id;
    long current_output_refinement_id;

    long number_of_received_particle_results;
    long number_of_expected_results;

    RefinementPackage* active_refinement_package;
    Refinement*        input_refinement;
    Refinement*        output_refinement;

    RunProfile active_refinement_run_profile;
    RunProfile active_reconstruction_run_profile;

    wxArrayString current_reference_filenames;
    wxArrayLong   current_reference_asset_ids;

    RefinementManager( );
    void SetParent(MyRefine3DPanel* wanted_parent);

    void BeginRefinementCycle( );
    void CycleRefinement( );

    void SetupRefinementJob( );
    void SetupReconstructionJob( );
    void SetupMerge3dJob( );

    void SetupInitialReconstructionJob( );
    void SetupInitialMerge3dJob( );

    void RunInitialReconstructionJob( );
    void RunInitialMerge3dJob( );

    void RunRefinementJob( );
    void RunReconstructionJob( );
    void RunMerge3dJob( );

    void ProcessJobResult(JobResult* result_to_process);
    void ProcessAllJobsFinished( );

    void OnMaskerThreadComplete( );

    void DoMasking( );

    //	void StartRefinement();
    //	void StartReconstruction();
};

class MyRefine3DPanel : public Refine3DPanel {
    friend class RefinementManager;

  protected:
    // Handlers for Refine3DPanel events.
    void OnUpdateUI(wxUpdateUIEvent& event);
    void OnExpertOptionsToggle(wxCommandEvent& event);
    void OnInfoURL(wxTextUrlEvent& event);
    void TerminateButtonClick(wxCommandEvent& event);
    void FinishButtonClick(wxCommandEvent& event);
    void StartRefinementClick(wxCommandEvent& event);
    void ResetAllDefaultsClick(wxCommandEvent& event);
    void OnHighResLimitChange(wxCommandEvent& event);

    void OnUseMaskCheckBox(wxCommandEvent& event);
    void OnAutoMaskButton(wxCommandEvent& event);

    void OnVolumeListItemActivated(wxListEvent& event);

    // overridden socket methods..

    void OnSocketJobResultMsg(JobResult& received_result);
    void OnSocketJobResultQueueMsg(ArrayofJobResults& received_queue);
    void SetNumberConnectedText(wxString wanted_text);
    void SetTimeRemainingText(wxString wanted_text);
    void OnSocketAllJobsFinished( );

    int length_of_process_number;

    RefinementManager my_refinement_manager;

    int active_orth_thread_id;
    int active_mask_thread_id;
    int next_thread_id;

  public:
    wxStopWatch stopwatch;

    long time_of_last_result_update;

    bool refinement_package_combo_is_dirty;
    bool run_profiles_are_dirty;
    bool input_params_combo_is_dirty;
    bool volumes_are_dirty;

    JobResult* buffered_results;
    long       selected_refinement_package;

    //int length_of_process_number;

    JobTracker my_job_tracker;

    bool auto_mask_value; // this is needed to keep track of the automask, as the radiobutton will be overidden to no when masking is selected

    bool running_job;

    void SetDefaults( );
    void Reset( );

    MyRefine3DPanel(wxWindow* parent);
    void SetInfo( );

    void WriteInfoText(wxString text_to_write);
    void WriteErrorText(wxString text_to_write);
    void WriteBlueText(wxString text_to_write);

    void FillRefinementPackagesComboBox( );
    void FillRunProfileComboBoxes( );
    void FillInputParamsComboBox( );
    void ReDrawActiveReferences( );

    void NewRefinementPackageSelected( );

    void OnRefinementPackageComboBox(wxCommandEvent& event);
    void OnInputParametersComboBox(wxCommandEvent& event);

    void OnOrthThreadComplete(ReturnProcessedImageEvent& my_event);
    void OnMaskerThreadComplete(wxThreadEvent& my_event);
};

#endif // __MyRefine3DPanel__