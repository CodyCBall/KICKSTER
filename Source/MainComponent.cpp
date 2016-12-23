// KICKSTER APPLICATION
// DEVELOPED BY CODY BALL 2016

#include <math.h>
#include "ADSR.h"
#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"

ADSR* env = new ADSR();

class MainContentComponent   : public AudioAppComponent,
public Slider::Listener ,HighResolutionTimer, public Button::Listener
{
public:
    MainContentComponent()
    :   startTime (Time::getMillisecondCounterHiRes() * 0.001),
    currentSampleRate (0.0),
    currentAngle (0.0),
    angleDelta (0.0),
    interval(5.0)

    {
        addAndMakeVisible (startSlider);                            //display startSlider "frequency start"
        startSlider.setRange (1000.0, 20000.0);
        startSlider.setSkewFactorFromMidPoint (8000.0); // [4]
        startSlider.addListener (this);
        startSlider.setColour(0x1001310, Colours::black);
        startSlider.setColour(0x1001300, Colours::black);
        startSlider.setColour(0x1001500, Colours::black);   // slider textbox
        startSlider.setColour(0x1001400, Colours::white);
        startSlider.setColour(0x1001700 , Colours::white);
        startSlider.setTextValueSuffix(" Hz");
        
        addAndMakeVisible(pitchDecaySlider);                        //display pitch decay slider
        pitchDecaySlider.setRange(10.0, 250.0);
        pitchDecaySlider.setSkewFactor(1.0);
        pitchDecaySlider.addListener(this);
        pitchDecaySlider.setColour(0x1001310, Colours::black);      // slider track
        pitchDecaySlider.setColour(0x1001300, Colours::black);      // slider ball
        pitchDecaySlider.setColour(0x1001500, Colours::black);      // slider textbox
        pitchDecaySlider.setColour(0x1001400, Colours::white);      // text color
        pitchDecaySlider.setColour(0x1001700 , Colours::white);
        pitchDecaySlider.setTextValueSuffix(" ms");
        
        addAndMakeVisible (gainSlider);                         //display gain slider
        gainSlider.setSliderStyle(juce::Slider::LinearVertical);
        gainSlider.setRange (0.0, 1.0);
        gainSlider.setTextBoxStyle(gainSlider.TextBoxBelow, true, 50, 25);
        gainSlider.setSkewFactorFromMidPoint (0.5); // [4]
        gainSlider.setColour(0x1001310, Colours::black);            // slider track
        gainSlider.setColour(0x1001300, Colours::black);            // slider ball
        gainSlider.setColour(0x1001500, Colours::black);            // slider textbox
        gainSlider.setColour(0x1001400, Colours::white);            // text color
        gainSlider.addListener (this);
        
        addAndMakeVisible (clickOneSlider);                         //Display click one gain slider
        clickOneSlider.setSliderStyle(juce::Slider::LinearVertical);
        clickOneSlider.setRange (0.0, 1.0);
        clickOneSlider.setTextBoxStyle(clickOneSlider.TextBoxBelow, true, 50, 25);
        clickOneSlider.setSkewFactorFromMidPoint (0.5); // [4]
        clickOneSlider.setColour(0x1001310, Colours::black);         // slider track
        clickOneSlider.setColour(0x1001300, Colours::black);         // slider ball
        clickOneSlider.setColour(0x1001500, Colours::black);         // slider textbox
        clickOneSlider.setColour(0x1001400, Colours::white);         // text color
        clickOneSlider.addListener (this);
        
        addAndMakeVisible (clickTwoSlider);                     //Display click two gain slider
        clickTwoSlider.setSliderStyle(juce::Slider::LinearVertical);
        clickTwoSlider.setRange (0.0, 1.0);
        clickTwoSlider.setTextBoxStyle(clickTwoSlider.TextBoxBelow, true, 50, 25);
        clickTwoSlider.setSkewFactorFromMidPoint (0.5); // [4]
        clickTwoSlider.setColour(0x1001310, Colours::black);          // slider track
        clickTwoSlider.setColour(0x1001300, Colours::black);          // slider ball
        clickTwoSlider.setColour(0x1001500, Colours::black);          // slider textbox
        clickTwoSlider.setColour(0x1001400, Colours::white);          // text color
        clickTwoSlider.addListener (this);
        
        addAndMakeVisible(attackSlider);
        attackSlider.setSliderStyle(Slider::LinearVertical);
        attackSlider.setRange(0.0, 10);
        attackSlider.setTextBoxStyle(attackSlider.TextBoxBelow, true, 50, 25);
        attackSlider.setSkewFactor(5);
        attackSlider.setColour(0x1001310, Colours::black);         // slider track
        attackSlider.setColour(0x1001300, Colours::black);          // slider ball
        attackSlider.setColour(0x1001500, Colours::black);   // slider textbox
        attackSlider.setColour(0x1001400, Colours::white);     //text color
        attackSlider.addListener(this);
        
        addAndMakeVisible(decaySlider);
        decaySlider.setSliderStyle(Slider::LinearVertical);
        decaySlider.setRange(0.0, 10);
        decaySlider.setTextBoxStyle(decaySlider.TextBoxBelow, true, 50, 25);
        decaySlider.setSkewFactor(5);
        decaySlider.setColour(0x1001310, Colours::black);    // slider track
        decaySlider.setColour(0x1001300, Colours::black);     // slider ball
        decaySlider.setColour(0x1001500, Colours::black);   // slider textbox
        decaySlider.setColour(0x1001400, Colours::white);     //text color
        decaySlider.addListener(this);
        
        addAndMakeVisible(sustainSlider);
        sustainSlider.setSliderStyle(Slider::LinearVertical);
        sustainSlider.setRange(0.0, 10);
        sustainSlider.setTextBoxStyle(sustainSlider.TextBoxBelow, true, 50, 25);
        sustainSlider.setSkewFactor(5);
        sustainSlider.setColour(0x1001310, Colours::black);     // slider track
        sustainSlider.setColour(0x1001300, Colours::black);     // slider ball
        sustainSlider.setColour(0x1001500, Colours::black);   // slider textbox
        sustainSlider.setColour(0x1001400, Colours::white);     // text color
        sustainSlider.addListener(this);
        
        addAndMakeVisible(releaseSlider);
        releaseSlider.setSliderStyle(Slider::LinearVertical);
        releaseSlider.setRange(0.0, 10);
        releaseSlider.setTextBoxStyle(releaseSlider.TextBoxBelow, true, 50, 25);
        releaseSlider.setSkewFactor(5);
        releaseSlider.setColour(0x1001310, Colours::black);
        releaseSlider.setColour(0x1001300, Colours::black);
        releaseSlider.setColour(0x1001500, Colours::black);   // slider textbox
        releaseSlider.setColour(0x1001400, Colours::white);     //text color
        releaseSlider.addListener(this);
    
        addAndMakeVisible(pitchDecayLabel);                         // display pitch decay label "pitch decay"
        pitchDecayLabel.attachToComponent(&pitchDecaySlider, true);
        pitchDecayLabel.setText("Pitch Decay", dontSendNotification);
        pitchDecayLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(gainLabel);                       //display sub gain label "Sub"
        gainLabel.attachToComponent(&gainSlider, true);
        gainLabel.setText("Sub", dontSendNotification);
        gainLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(clickOneLabel);                           // display click 1 label "C1"
        clickOneLabel.attachToComponent(&clickOneSlider, true);
        clickOneLabel.setText("C1", dontSendNotification);
        clickOneLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(clickTwoLabel);                       // display click 2 label "C2"
        clickTwoLabel.attachToComponent(&clickTwoSlider, true);
        clickTwoLabel.setText("C2", dontSendNotification);
        clickTwoLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(mixerLabel);                             // display mixer label "Mixer"
        mixerLabel.attachToComponent(&clickOneSlider, true);
        mixerLabel.setText("Mixer", dontSendNotification);
        mixerLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(startLabel);                  // display startLabel "Start Frequency"
        startLabel.attachToComponent (&startSlider, true);
        startLabel.setColour(0x1000281, Colours::white);
        startLabel.setText ("Start Frequency", dontSendNotification);
        
        addAndMakeVisible(attackLabel);                 // display attack label "A"
        attackLabel.attachToComponent(&attackSlider, false);
        attackLabel.setText("A", dontSendNotification);
        attackLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(decayLabel);                      //display decay label "D"
        decayLabel.attachToComponent(&decaySlider, false);
        decayLabel.setText("D", dontSendNotification);
        decayLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(sustainLabel);                        //display sustain label "S"
        sustainLabel.attachToComponent(&sustainSlider, false);
        sustainLabel.setText("S", dontSendNotification);
        sustainLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(releaseLabel);                    //display release label "R"
        releaseLabel.attachToComponent(&attackSlider, false);
        releaseLabel.setText("R", dontSendNotification);
        releaseLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(fundamental);                     // fundamental combo box
        fundamental.setSelectedId(1);
        fundamental.setColour(0x1000b00, Colours::black);
        fundamental.setColour(0x1000a00, Colours::white);
        fundamental.setColour(0x1000c00, Colours::white);
        fundamental.addItem("A", 1);
        fundamental.addItem("A#", 2);
        fundamental.addItem("B", 3);
        fundamental.addItem("C", 4);
        fundamental.addItem("C#", 5);
        fundamental.addItem("D", 6);
        fundamental.addItem("D#", 7);
        fundamental.addItem("E", 8);
        fundamental.addItem("F", 9);
        fundamental.addItem("F#", 10);
        fundamental.addItem("G", 11);
        fundamental.addItem("G#", 12);
        
        addAndMakeVisible(clickOneBox);                             //click one combo box
        clickOneBox.setColour(0x1000b00, Colours::black);
        clickOneBox.setColour(0x1000a00, Colours::white);
        clickOneBox.setColour(0x1000c00, Colours::white);
        clickOneBox.addItem("House 1", 1);
        clickOneBox.addItem("House 2", 2);
        clickOneBox.addItem("House 3", 3);
        clickOneBox.addItem("House 4", 4);
        clickOneBox.addItem("House 5", 5);
        clickOneBox.addItem("Hardstyle 1", 6);
        clickOneBox.addItem("Hardstyle 2", 7);
        clickOneBox.addItem("Hardstyle 3", 8);
        clickOneBox.addItem("Hardstyle 4", 9);
        clickOneBox.addItem("Hardstyle 5", 10);
        clickOneBox.addItem("Trap 1", 11);
        clickOneBox.addItem("Trap 2", 12);
        clickOneBox.addItem("Trap 3", 13);
        clickOneBox.addItem("Trap 4", 14);
        clickOneBox.addItem("Trap 5", 15);
        
        addAndMakeVisible(clickTwoBox);                             // click two combo box
        clickTwoBox.setColour(0x1000b00, Colours::black);
        clickTwoBox.setColour(0x1000a00, Colours::white);
        clickTwoBox.setColour(0x1000c00, Colours::white);
        clickTwoBox.addItem("House 1", 1);
        clickTwoBox.addItem("House 2", 2);
        clickTwoBox.addItem("House 3", 3);
        clickTwoBox.addItem("House 4", 4);
        clickTwoBox.addItem("House 5", 5);
        clickTwoBox.addItem("Hardstyle 1", 6);
        clickTwoBox.addItem("Hardstyle 2", 7);
        clickTwoBox.addItem("Hardstyle 3", 8);
        clickTwoBox.addItem("Hardstyle 4", 9);
        clickTwoBox.addItem("Hardstyle 5", 10);
        clickTwoBox.addItem("Trap 1", 11);
        clickTwoBox.addItem("Trap 2", 12);
        clickTwoBox.addItem("Trap 3", 13);
        clickTwoBox.addItem("Trap 4", 14);
        clickTwoBox.addItem("Trap 5", 15);
       
        fundamentalLabel.attachToComponent(&fundamental, true);             // fundamental label
        fundamentalLabel.setColour(0x1000281, Colours::white);

        addAndMakeVisible(clickSectionOneLabel);                        //click one label
        clickSectionOneLabel.attachToComponent(&clickOneBox, true);
        clickSectionOneLabel.setText("Click 1", dontSendNotification);
        clickSectionOneLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(clickSectionTwoLabel);                        //click two label
        clickSectionTwoLabel.attachToComponent(&clickTwoBox, true);
        clickSectionTwoLabel.setText("Click 2", dontSendNotification);
        clickSectionTwoLabel.setColour(0x1000281, Colours::white);
        
        addAndMakeVisible(menuBox);                         // menu combo box
        menuBox.setColour(0x1000b00, Colours::lightgrey);
        menuBox.setColour(0x1000a00, Colours::black);
        menuBox.setColour(0x1000c00, Colours::white);
        menuBox.addItem("Load Preset", 1);
        menuBox.addItem("Save Preset", 2);
        menuBox.addItem("About", 3);
        
        addAndMakeVisible(menuLabel);                       // display "Menu" label
        menuLabel.attachToComponent(&menuBox, false);
        menuLabel.setColour(0x1000281, Colours::white);
        menuLabel.setText("Menu", dontSendNotification);
        
        clickSectionOneLabel.attachToComponent(&clickOneBox, true);         // attach clicklabel one to click box one
        clickSectionOneLabel.setColour(0x1000281, Colours::white);
        
        clickSectionTwoLabel.attachToComponent(&clickTwoBox, true);             // attach clicklabel two to click box two
        clickSectionTwoLabel.setColour(0x1000281, Colours::white);

        pitchDecaySlider.setColour(0x1001310, Colours::black);
        pitchDecaySlider.setColour(0x1001300, Colours::black);
        pitchDecaySlider.setColour(0x1001500, Colours::black);   // slider textbox
        pitchDecaySlider.setColour(0x1001400, Colours::white);
        
        fundamentalLabel.setText("Fundamental", dontSendNotification);
        
        addAndMakeVisible(playButton);                          // display play button
        playButton.setColour(0x1000100, Colours::lightgrey);
        playButton.setColour(0x1000101, Colours::black);
        playButton.addListener(this);
        
        addAndMakeVisible(playLabel);                       // play button label "play"
        playLabel.attachToComponent(&playButton, true);
        playLabel.setText("Play", dontSendNotification);
        playLabel.setFont (18.0f);
        playLabel.setColour(0x1000281,Colours::white);
        
        setSize (700, 500);                                 // set size of initial window
        setAudioChannels (0, 2);                            // no inputs, two output
    }
    
    ~MainContentComponent()
    {
        gainSlider.removeListener(this);                    // remove slider listeners
        startSlider.removeListener(this);
        shutdownAudio();                                    // shut down audio
    }
    
    void resized() override                                 // resizing of window
    {
        
        Rectangle<int> area (getLocalBounds());
    
      
    }
    

  
    void paint (Graphics& g) override
    {
                                                                    // size and plot of graphic components
        const int sliderLeft = 100;
        startSlider.setBounds (sliderLeft+15, 75, 300, 20);
        fundamental.setBounds(sliderLeft, 125, 50, 20);
        clickOneBox.setBounds(495, 84, 90, 20);
        clickTwoBox.setBounds(495, 134, 90, 20);
        pitchDecaySlider.setBounds(90, 175, 300, 20);
        playButton.setBounds(225, 433, 250, 20);
        gainLabel.setTopLeftPosition(gainSlider.getX(), gainSlider.getY()+90);
        clickOneLabel.setTopLeftPosition(clickOneSlider.getX(), clickOneSlider.getY()+90);
        clickTwoLabel.setTopLeftPosition(clickTwoSlider.getX(), clickTwoSlider.getY()+90);
        playLabel.setTopLeftPosition(playButton.getX()+105, playButton.getY()+25);
        envelopeLabel.setTopLeftPosition(attackSlider.getX()+50, attackSlider.getY()-100);
        mixerLabel.setTopLeftPosition(gainSlider.getX()+35, gainSlider.getY()-100);
        mixerLabel.setFont(20.0f);
        menuBox.setBounds(12, 25, 80, 20);
        
        g.fillAll (Colours::black);                     // first layer backdrop

        g.setColour(Colours::white);                    // second layer for outter border
        Path firstRec;
        firstRec.addRectangle(3, 3, 694, 494);
        g.fillPath(firstRec);
        
        g.setColour(Colours::black);                    // third layer of outter border
        Path secondRec;
        secondRec.addRectangle(6, 6, 688, 488);
        g.fillPath(secondRec);
        
        Path thirdRec;
        g.setColour(Colours::blue);                     // main GUI "blue"
        thirdRec.addRectangle(9, 9, 682, 482);
        g.fillPath(thirdRec);
        
        g.setColour(Colours::black);
        Path envBorder;
        envBorder.addRectangle(47, 297, 156, 156);      //border of envelope section rectangle
        g.fillPath(envBorder);
        
        g.setColour(Colours::lightgrey);
        Path envRec;
        envRec.addRectangle(50, 300, 150, 150);         //envelope section rectangle
        g.fillPath(envRec);
        
        
        g.setColour(Colours::black);
        Path mixerBorder;
        mixerBorder.addRectangle(497, 297, 156, 156);       //border of mixer section rectangle
        g.fillPath(mixerBorder);
        
        g.setColour(Colours::lightgrey);
        Path mixerRec;
        mixerRec.addRectangle(500, 300, 150, 150);      //mixer section rectangle
        g.fillPath(mixerRec);
        
        
        g.setColour(Colours::black);            // Bordermain section rectangle
        g.setOpacity(0.3);
        Path borderMainRec;
        borderMainRec.addRectangle(10, 60, 680, 200);
        g.fillPath(borderMainRec);
        
        g.setColour(Colours::white);            // main section rectangle
        g.setOpacity(0.09);
        Path mainRec;
        mainRec.addRectangle(14, 64, 672, 192);
        g.fillPath(mainRec);
        
        g.setColour(Colours::black);                // top rectangle (logo)
        g.setOpacity(0.5);
        Path topRec;
        topRec.addRectangle(10, 10, 680, 50);
        g.fillPath(topRec);
        
        g.setColour(Colours::black);            // main section rectangle
        g.setOpacity(.3);
        Path bottomBorderRec;
        bottomBorderRec.addRectangle(10, 260, 680, 230);
        g.fillPath(bottomBorderRec);
        
        
//        g.setColour(Colours::black);            // first row
//        g.setOpacity(.1);
//        Path startFrequencyRec;
//        startFrequencyRec.addRectangle(10, 60, 680, 50);
//        g.fillPath(startFrequencyRec);
//        
//        g.setColour(Colours::black);            // second row
//        g.setOpacity(.15);
//        Path fundamentalRec;
//        fundamentalRec.addRectangle(10, 110, 680, 50);
//        g.fillPath(fundamentalRec);
//        
//        g.setColour(Colours::black);            // third row
//        g.setOpacity(.1);
//        Path pitchDecayRec;
//        pitchDecayRec.addRectangle(10, 160, 680, 50);
//        g.fillPath(pitchDecayRec);
//        
//        g.setColour(Colours::black);            // fourth row
//        g.setOpacity(.15);
//        Path slopeRec;
//        slopeRec.addRectangle(10, 210, 680, 50);
//        g.fillPath(slopeRec);
        
      
       
//        g.setFont (55.0f);
//        g.setColour (Colours::black);
//        g.drawText("KICKSTER", 100, 6, 500, 200, Justification::centredTop);   //Kickster Logo Shadow

        g.setFont (50.0f);
        g.setColour (Colours::white);
        g.drawText("KICKSTER", 100, 10, 500, 200, Justification::centredTop);   //Kickster Logo
        
        attackSlider.setBounds(50, 300, 30, 150);
        
        decaySlider.setBounds(90, 300, 30, 150);
        sustainSlider.setBounds(130, 300, 30, 150);
        releaseSlider.setBounds(170, 300, 30, 150);
        attackLabel.setTopLeftPosition(attackSlider.getX()+5, attackSlider.getY()+150);
        decayLabel.setTopLeftPosition(decaySlider.getX()+5, decaySlider.getY()+150);
        sustainLabel.setTopLeftPosition(sustainSlider.getX()+5, sustainSlider.getY()+150);
        releaseLabel.setTopLeftPosition(releaseSlider.getX()+5, releaseSlider.getY()+150);
        
        menuLabel.setTopLeftPosition(menuBox.getX()+16, menuBox.getY()-20);
        clickSectionOneLabel.setTopLeftPosition(clickOneBox.getX(), clickOneBox.getY()-20);
        clickSectionTwoLabel.setTopLeftPosition(clickTwoBox.getX(), clickTwoBox.getY()-20);
        
        gainSlider.setBounds (510, 300, 30, 150);
        clickOneSlider.setBounds (560, 300, 30, 150);
        clickTwoSlider.setBounds (610, 300, 30, 150);
       
    }
//    
//    void mouseDown (const MouseEvent& e) override
//    {
//        
//        attack.startDraggingComponent (this, e);
//    }
//    
//    void mouseDrag (const MouseEvent& e) override
//    {
//        attack.dragComponent (this, e, nullptr);
//     
//    }
    
    
//    void addMouseListener(	MouseListener * newListener,
//                                         bool 	wantsEventsForAllNestedChildComponents
//                                         )
//    {
//        
//        
//    }

    
    void sliderValueChanged (Slider* slider) override           // slider value changed
    {
        if (slider == &startSlider)                         // start slider listener
        {
            if (currentSampleRate > 0.0)
                updateAngleDelta();
        }
    }
    
    void comboBoxChanged(ComboBox *b)               // combo box action
    {
      
        
        
    }
    
    void updateAngleDelta()
    {
        const double cyclesPerSample = startSlider.getValue() / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }
    
  
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        
    }
    
    void releaseResources() override
    {
        
        
    }
    
    IIRCoefficients makeHighPass (const double sampleRate,
                                                   const double frequency) noexcept
    {
        const double n = std::tan (double_Pi * frequency / sampleRate);
        const double nSquared = n * n;
        const double c1 = 1.0 / (1.0 + std::sqrt (2.0) * n + nSquared);
        
        return IIRCoefficients (c1,
                                c1 * -2.0,
                                c1,
                                1.0,
                                c1 * 2.0 * (nSquared - 1.0),
                                c1 * (1.0 - std::sqrt (2.0) * n + nSquared));
    }
    
    void hiResTimerCallback	() override                 // high resolution timer
    {
        angleDelta = 1.8;
        startTimer(5);                                 //start timer with interval between callbacks.
//        double target = currentSampleRate * 1;
        std::cout << "timer started\n";
        
//        for (double i = 10; i >=0 ; i-=0.001)
//        {
//            
//             angleDelta -= exp(100)*currentSampleRate;
//            std::cout << angleDelta << std::endl;
//        }
        while(angleDelta>0.015)                         // frequency decrementing
        {
            angleDelta -= log(100);
        
        std::cout << angleDelta << std::endl;
        }
        
        stopTimer();                                // stop timer after decrementing is complete
        
    }
    

    
    void buttonClicked(Button* button) override         // button clicked
    {
        if (button == &playButton)              // check for play button clicked
        {
            angleDelta=1.8;
            std::cout << "Button clicked\n";
                hiResTimerCallback();               // call to timer to decrement frequency
        }
    }
    
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override            // process samples
    {
        const float level = (float) gainSlider.getValue();
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);

        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            const float currentSample = (float) std::sin (currentAngle);
            currentAngle += angleDelta;
            buffer[sample] = currentSample * level;
            
        }
    }
    
private:
  
    double startTime;
    Slider gainSlider;
    Slider startSlider;
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    Slider clickOneSlider;
    Slider clickTwoSlider;
    Slider pitchDecaySlider;
    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;
    Label startLabel;
    Label gainLabel;
    Label playLabel;
    Label clickOneLabel;
    Label clickTwoLabel;
    Label clickSectionOneLabel;
    Label clickSectionTwoLabel;
    Label pitchDecayLabel;
    Label envelopeLabel;
    Label mixerLabel;
    ComboBox fundamental;
    ComboBox clickOneBox;
    ComboBox clickTwoBox;
    ComboBox menuBox;
    Label fundamentalLabel;
    Label menuLabel;
    TextButton playButton;
    double currentSampleRate, currentAngle, angleDelta, interval; // [1]
    ComponentDragger attack;
    IIRCoefficients coeffs;
    IIRFilter filtering;
    float cutoff;
    float cutoffKnob;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
