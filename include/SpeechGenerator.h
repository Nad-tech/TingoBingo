#pragma once

#include <string>
#include <atomic>

class SpeechGenerator
{
public:
    static bool GenerateSpeech
    (
        const std::string& text,  
        const std::atomic<bool>& stopRequested
    );
};