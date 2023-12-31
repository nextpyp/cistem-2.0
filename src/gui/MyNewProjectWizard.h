#ifndef __MyNewProjectWizard__
#define __MyNewProjectWizard__

/**
@file
Subclass of NewProjectWizard, which is generated by wxFormBuilder.
*/

#include "ProjectX_gui.h"

//// end generated include

/** Implementing NewProjectWizard */
class MyNewProjectWizard : public NewProjectWizard {
  protected:
    // Handlers for NewProjectWizard events.
    void OnBrowseButtonClick(wxCommandEvent& event);

  public:
    /** Constructor */
    MyNewProjectWizard(wxWindow* parent);
    //// end generated class members

    void OnProjectTextChange(wxCommandEvent& event);
    void OnProjectPathChange(wxCommandEvent& event);
    void OnParentDirChange(wxCommandEvent& event);
    void OnFinished(wxWizardEvent& event);
    void GenerateProjectPath( );
    void CheckProjectPath( );
};

#endif // __MyNewProjectWizard__
