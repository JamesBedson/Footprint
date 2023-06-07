
# Footprint: Digital Effects Pedalboard

## Table of Contents

1.  Purpose
2.  Overall Description
    -   2.1 Product Perspective
    -   2.2 General Control & Visualization
    -   2.3 Pedalboard
3.  Features
4. Usage
5.  Supported Platforms
6.  Installation
7.  Development
8.  Contributors

## Purpose<a name="purpose"></a>

The purpose of this software is to provide an application for guitarists, bassists, and all other types of musicians that emulates instrument effect pedals commonly used in concerts and live-music setups. The software will be available as a VST or AU (Audio Units) plugin, allowing musicians to choose four different effects and connect them in series, either for live performances or recording purposes.

## Overall description<a name="Overall description"></a>

#### Product perspective:
The plugin consist on different effects that can be combined to simulate a pedalboard for processing audio.  Also, through different knobs, sliders and buttons; different parameters of each pedal and also a general control section can be modified in real-time to adapt to the artist requierements to find different sounds.
#### General control:
Footprint is based in two main sections:
1.  Control section with:
	    - Input gain knob
	    - Output gain knob
	    - Mono - Stereo switch
	    - RMS and Peak display
	    - Input and output waveform display

2.  Pedalboard section with:
    -   4 different pedal slots to be combined in multiple ways
#### Pedalboard
Footprint offers 4 different pedals to combine: Compressor, Envelope Filter, Reverb and Distortion. Each one simulating the most common parameters to modify by the user.

## Supported platforms<a name="Supported platforms"></a>
An audio plugin, does not depend only on the platform but also on the host that will be running through.
As a pedalboard plugin, it will be released in the VST3 or AU format, which is compatible with almost every DAW available.
As a *free and open-source platfrom*, [Reaper](https://www.reaper.fm/) is one of the most recomended DAW's to work with.

## Development<a name="Development"></a>
Footprint have been developed with the [JUCE](https://www.juce.com)  framework. It is an open source C++ codebase that can be used to create plug-ins.

## Contributors<a name="contributors"></a>
The following contributors have participated in the development of this software:

Josep Sala, James Bedson, Pau Segalés, Bru Güell, Iker Landarech, Aina Masenello and Marina Hernandez
