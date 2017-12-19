#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <assert.h>


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
                               public Slider::Listener,
                                public ComboBox::Listener
{
public:
    MainContentComponent()
    :   mNbPartials(1), //default nb at intialization
        mMaxNbPartials(64),
        mWaveTypeNb(1),
        currentSampleRate (0.0),
        mCurrentLevel (0.1)

    {
        addAndMakeVisible (frequencySlider);
        frequencySlider.setRange (20.0, 20000.0);
        frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
        frequencySlider.addListener (this);
        
        addAndMakeVisible (numberPartialsSlider);
        numberPartialsSlider.setRange (1, mMaxNbPartials, 1);
        numberPartialsSlider.addListener(this);
        
        addAndMakeVisible(waveformCombobox);
        waveformCombobox.addItem("Sawtooth", 1);
        waveformCombobox.addItem("Square", 2);
        waveformCombobox.addItem("Triangle", 3);
        waveformCombobox.setSelectedId(1);
        waveformCombobox.addListener(this);
        
        setSize (600, 200);
        setAudioChannels (0, 1);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        waveformCombobox.setBounds (10, 10, 120, 30);
        frequencySlider.setBounds (10, 50, getWidth() - 20, 20);
        numberPartialsSlider.setBounds (10, 100, getWidth() - 20, 20);
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if(comboBoxThatHasChanged == &waveformCombobox)
        {
            mWaveTypeNb = waveformCombobox.getSelectedId();
            fillVecWaveform(vecPartials, currentFundFrequency, mCurrentLevel, mNbPartials);
        }
    }
    
    void sliderDragEnded  (Slider* slider) override
    {
        if (slider == &frequencySlider)
        {
            currentFundFrequency = frequencySlider.getValue();
            fillVecWaveform(vecPartials, currentFundFrequency, mCurrentLevel, mNbPartials);
            
        }
        
        if (slider == &numberPartialsSlider)
        {
            mNbPartials = static_cast<int> (numberPartialsSlider.getValue());
            fillVecWaveform(vecPartials, currentFundFrequency, mCurrentLevel, mNbPartials);
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
    }
    
    
    void fillVecWaveform (std::vector<Partial>& vec, double fundFreq, double level, int nbPartials)
    {
        switch(mWaveTypeNb)
        {
            case 2:
                fillVecSquareWave (vec, fundFreq, level, nbPartials);
                break;
            case 3:
                fillVecTriWave (vec, fundFreq, level, nbPartials);
                break;
            default: //including '1'
                fillVecSawWave (vec, fundFreq, level, nbPartials);
        
        };
        
    }
    
    void fillVecSawWave (std::vector<Partial>& vec, double fundFreq, double level, int nbPartials)
    {
        vec.clear();
        
        for(int i=1; i<=nbPartials ;i++)
        {
            double partialFreq = i*fundFreq;
            double partialLevel = level/i;
            vec.push_back( Partial( partialFreq, partialLevel, getAngleDelta(partialFreq)  ) );
        }
        
    }
    
    
    void fillVecSquareWave (std::vector<Partial>& vec, double fundFreq, double level, int nbPartials)
    {
        vec.clear();
        
        for(int i=1; i<=nbPartials ;i++)
        {
            double partialFreq = i*fundFreq;
            double partialLevel = 0;
            
            if(i % 2 != 0)
                partialLevel = level/i;
        
            vec.push_back( Partial( partialFreq, partialLevel, getAngleDelta(partialFreq)  ) );
        }
        
    }
    
    void fillVecTriWave (std::vector<Partial>& vec, double fundFreq, double level, int nbPartials)
    {
        vec.clear();
        bool neg = false;
        
        for(int i=1; i<=nbPartials ;i++)
        {
            double partialFreq = i*fundFreq;
            double partialLevel = 0;
            
            if(i % 2 != 0)
            {
                partialLevel = level/(i*i);
                
                if(neg)
                    partialLevel = -partialLevel;
                
                neg = !neg;
            }
            
            vec.push_back( Partial( partialFreq, partialLevel, getAngleDelta(partialFreq)  ) );
            
        }
        
    }
    
    
    double getAngleDelta (double freq)
    {
        assert ( currentSampleRate > 0.0);
        const double cyclesPerSample = freq / currentSampleRate;
        return cyclesPerSample * 2.0 * double_Pi;    //angleDelta
    }

    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        
        fillVecWaveform(vecPartials, currentFundFrequency, mCurrentLevel, mNbPartials);
        
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            
            float currentSample = 0;
            
            if(vecPartials.size() >= 1)
            {
                for(int i=0; i<mNbPartials;i++)
                {
                    float partialSample = (float) std::sin (vecPartials[i].angle );
                    vecPartials[i].angle += vecPartials[i].angleDelta;
                    currentSample += partialSample * vecPartials[i].amplitude;

                }
            }
            

            buffer[sample] = currentSample;
            
        }
    }
    
    
    
    
private:
    Slider frequencySlider, numberPartialsSlider;
    ComboBox waveformCombobox;
    
    int mNbPartials, mMaxNbPartials, mWaveTypeNb;
    double mCurrentLevel, currentFundFrequency, currentSampleRate;
    std::vector<Partial> vecPartials;
 
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
