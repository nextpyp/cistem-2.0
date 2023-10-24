#ifndef __RefineCTFPanel__
#define __RefineCTFPanel__

/**
@file
Subclass of Refine3DPanel, which is generated by wxFormBuilder.
*/

#include "ProjectX_gui.h"

class RefineCTFPanel;

class CTFRefinementManager {
  public:
    bool            start_with_reconstruction;
    RefineCTFPanel* my_parent;

    float    active_low_resolution_limit;
    float    active_high_resolution_limit;
    float    active_mask_radius;
    float    active_signed_cc_limit;
    float    active_defocus_search_range;
    float    active_defocus_search_step;
    float    active_inner_mask_radius;
    float    active_resolution_limit_rec;
    float    active_score_weight_conversion;
    float    active_score_threshold;
    bool     active_adjust_scores;
    bool     active_crop_images;
    bool     active_should_apply_blurring;
    float    active_smoothing_factor;
    float    active_sphere_radius;
    bool     active_should_mask;
    bool     active_should_auto_mask;
    wxString active_mask_filename;
    bool     active_should_low_pass_filter_mask;
    float    active_mask_filter_resolution;
    float    active_mask_edge;
    float    active_mask_weight;
    long     active_mask_asset_id;

    bool active_ctf_refinement;
    bool active_beamtilt_refinement;

    long current_job_starttime;
    long time_of_last_update;
    long time_of_last_histogram_update;
    int  number_of_generated_3ds;

    int  running_job_type;
    long current_job_id;

    long current_refinement_package_asset_id;
    long current_input_refinement_id;
    long current_output_refinement_id;

    long number_of_received_results;
    long number_of_expected_results;

    float best_beamtilt_x;
    float best_beamtilt_y;
    float best_particle_shift_x;
    float best_particle_shift_y;
    float best_score;

    Curve defocus_change_histogram;

    RefinementPackage* active_refinement_package;
    Refinement*        input_refinement;
    Refinement*        output_refinement;

    RunProfile active_refinement_run_profile;
    RunProfile active_reconstruction_run_profile;

    wxArrayString current_reference_filenames;
    wxArrayLong   current_reference_asset_ids;

    CTFRefinementManager( );
    void SetParent(RefineCTFPanel* wanted_parent);

    void BeginRefinementCycle( );

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

    void RunBeamTiltEstimationJob( );

    void ProcessJobResult(JobResult* result_to_process);
    void ProcessAllJobsFinished( );

    void OnMaskerThreadComplete( );

    void DoMasking( );

    //	void StartRefinement();
    //	void StartReconstruction();
};

class RefineCTFPanel : public RefineCTFPanelParent {
    friend class CTFRefinementManager;

  protected:
    // Handlers for Refine3DPanel events.
    void OnUpdateUI(wxUpdateUIEvent& event);
    void OnExpertOptionsToggle(wxCommandEvent& event);
    void OnInfoURL(wxTextUrlEvent& event);
    void TerminateButtonClick(wxCommandEvent& event);
    void FinishButtonClick(wxCommandEvent& event);
    void StartRefinementClick(wxCommandEvent& event);
    void ResetAllDefaultsClick(wxCommandEvent& event);

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

    CTFRefinementManager my_refinement_manager;

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

    RefineCTFPanel(wxWindow* parent);
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

#endif // __RefineCTFPanel__
