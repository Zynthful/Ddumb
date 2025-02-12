#include "MainComponent.h"

#include "AudioEngine/ZAudioEngine.h"
#include "Components/ZSoundTreeItem.h"

//==============================================================================
MainComponent::MainComponent()
{
    //addMouseListener(this, true);

    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(&SoundTree);
    SoundTree.OnItemSelected = [this](ZSoundTreeItem* SoundTreeItem) { OnSoundTreeItemSelected(SoundTreeItem); };

    var BoolVar(true);
    Value val(BoolVar);
    addAndMakeVisible(&PropertyPanel);
    PropertyPanel.addProperties({ new BooleanPropertyComponent(val, "prop", "Prop") });

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    openButton.setBounds(10, 10, getWidth() - 20, 20);
    PropertyPanel.setBounds(10, 70, getWidth() - 20, 20);
    SoundTree.setBoundsInset(juce::BorderSize<int>(40, 10, 10, 10));
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    AudioAppComponent::mouseDown(event);
}

void MainComponent::openButtonClicked()
{
    ImportFileChooser = std::make_unique<FileChooser>("Select a .wav to import...", File{}, "*.wav");
    auto Flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
    ImportFileChooser->launchAsync(Flags, [this](const FileChooser& Chooser)
    {
        File File = Chooser.getResult();
        if (File == juce::File{})
        {
            // Did not select a file
            return;
        }

        //AudioFormatReader* Reader = AudioFormatManager.createReaderFor(File);
        //if (Reader == nullptr)
        //{
        //    // Couldn't read the file
        //    return;
        //}

        ZAudioEngine::PlaySound(File.getFullPathName());

        //auto Source = std::make_unique<AudioFormatReaderSource>(Reader, true);
        //transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        //readerSource.reset(newSource.release());
    });
}

void MainComponent::OnSoundTreeItemSelected(ZSoundTreeItem* SoundTreeItem)
{
    ShowDetailsFor(SoundTreeItem);
}

void MainComponent::ShowDetailsFor(ZSoundTreeItem* HasDetails)
{
    PropertyPanel.clear();
    PropertyPanel.addProperties(HasDetails->CreatePropertyComponents());
}
