// KICKSTER APPLICATION
// DEVELOPED BY CODY BALL 2016


#include"../JuceLibraryCode/JuceHeader.h"


Component* createMainContentComponent();

//==============================================================================
class KICKSTERApplication  : public JUCEApplication
{
public:
    //==============================================================================
    KICKSTERApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {

        mainWindow = new MainWindow (getApplicationName());     // Create main window
    }

    void shutdown() override
    {
                                    // Shut down application

        mainWindow = nullptr;       // Deletes window
    }

   
    void systemRequestedQuit() override
    {
                                    // Called when the app is being asked to quit
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // For running multiple instances of app.
    }

    
    /*
        Implements the desktop window that contains of an instance of
        the MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (createMainContentComponent(), true);
            setResizable (true, true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (KICKSTERApplication)
