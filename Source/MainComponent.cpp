#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

struct Partial
{
    Partial(double freq, double ampl, double angDelta, double ang = 0)
    : frequency(freq), amplitude(ampl), angleDelta(angDelta), angle(ang)
    { }
    
    double frequency;
    double amplitude;
    double angleDelta;
    double angle;
    
};


class MainContentComponent   : public AudioAppComponent,
                               public Slider::Listener
{
public:
    MainContentComponent()
    :   mNbPartials(1),
        currentSampleRate (0.0),
        mCurrentLevel (0.1)

    {
        addAndMakeVisible (frequencySlider);
        frequencySlider.setRange (20.0, 20000.0);
        frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
        frequencySlider.addListener (this);
        
        addAndMakeVisible (numberPartialsSlider);
        numberPartialsSlider.setRange (1, 10);
        numberPartialsSlider.addListener(this);
        
        setSize (600, 200);
        setAudioChannels (0, 1);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        frequencySlider.setBounds (10, 10, getWidth() - 20, 20);
        numberPartialsSlider.setBounds (10, 50, getWidth() - 20, 20);
    }
    
    void sliderDragEnded  (Slider* slider) override
    {
        if (slider == &frequencySlider)
        {
            currentFundFrequency = frequencySlider.getValue();
            updateVecAllPartials(currentFundFrequency, mCurrentLevel, mNbPartials);
            
        }
        
        if (slider == &numberPartialsSlider)
        {
            mNbPartials = static_cast<int> (numberPartialsSlider.getValue());
            updateVecAllPartials(currentFundFrequency, mCurrentLevel, mNbPartials);
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &frequencySlider)
        {
//            if (currentSampleRate > 0.0)
//                updateAngleDelta();
        }
    }
    
    void updateVecAllPartials(double fundFreq, double level, int nbPartials)
    {
        vecAllPartials.clear();
        
        for(int i=1; i<=nbPartials ;i++)
        {
            double partialFreq = i*fundFreq;
            vecAllPartials.push_back( Partial( partialFreq, level/i, getAngleDelta(partialFreq)  ) );

        }
        
        
    }
    
    double getAngleDelta (double freq)
    {
        const double cyclesPerSample = freq / currentSampleRate;
        return cyclesPerSample * 2.0 * double_Pi;    //angleDelta
    }

    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        
        updateVecAllPartials(currentFundFrequency, mCurrentLevel, mNbPartials);
        
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
//            const float currentSample = (float) std::sin (currentAngle);
//            currentAngle += angleDelta;
//            buffer[sample] = currentSample * level;
            
            float currentSample = 0;
            
            if(vecAllPartials.size() >= 1)
            {
                for(int i=0; i<mNbPartials;i++)
                {
                    float partialSample = (float) std::sin (vecAllPartials[i].angle );
                    vecAllPartials[i].angle = vecAllPartials[i].angle + vecAllPartials[i].angleDelta;
                    currentSample += partialSample * vecAllPartials[i].amplitude;

                }
            }
            

            buffer[sample] = currentSample;
            
        }
    }
    
    
    
    
private:
    Slider frequencySlider;
    Slider numberPartialsSlider;
    int mNbPartials;
    double mCurrentLevel, currentFundFrequency, currentSampleRate;
    
    std::vector<Partial> vecAllPartials;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
