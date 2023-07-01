#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <fstream>

#include "paSetup.h"

//Constructor
paSetup::paSetup(std::vector<std::tuple<std::string, int, int, int>> devices) {
    paSetup::devices = devices;
}

//Setters
void paSetup::setInDeviceNum(int num) {
    inDeviceNum = num;
}
void paSetup::setOutDeviceNum(int num) {
    outDeviceNum = num;
}
void paSetup::setInChannels(int ch) {
    inChannels = ch;
}
void paSetup::setOutChannels(int ch) {
    outChannels = ch;
}
void paSetup::setSampleRate(int sr) {
    sampleRate = sr;
}
void paSetup::setFileValGood(int ind, bool isGood) {
    fileValsGood[ind] = isGood;
}

//Getters
int paSetup::getInDeviceNum() {
    return inDeviceNum;
}
int paSetup::getOutDeviceNum() {
    return outDeviceNum;
}
int paSetup::getInChannels() {
    return inChannels;
}
int paSetup::getOutChannels() {
    return outChannels;
}
int paSetup::getSampleRate() {
    return sampleRate;
}
bool paSetup::getFileValOK(int ind) {
    return fileValsGood[ind];
}

//Validators
bool paSetup::deviceIsGood(int num) {
    if ((num < static_cast<int>(devices.size())) && (num > 0)) {
        return true;
    } else {
        return false;
    }
}
bool paSetup::inDeviceIsGood(int num) {
    if (deviceIsGood(num) && (std::get<1>(devices.at(num))) > 0) {
        return true;
    } else {
        return false;
    }
}
bool paSetup::outDeviceIsGood(int num) {
    if (deviceIsGood(num) && (std::get<2>(devices.at(num))) > 0) {
        return true;
    } else {
        return false;
    }
}
bool paSetup::inChannelsIsGood(int ch) {
    if ((ch > 0) && (ch <= std::get<1>(devices.at(inDeviceNum)))) {
        return true;
    } else {
        return false;
    }
}
bool paSetup::outChannelsIsGood(int ch) {
    if ((ch > 0) && (ch <= std::get<2>(devices.at(outDeviceNum)))) {
        return true;
    } else {
        return false;
    }
}
bool paSetup::fileValsAllGood() {
    bool allGood = true;
    for (int i = 0; i < static_cast<int>(sizeof(fileValsGood) / sizeof(fileValsGood[0])); i++) {
        if (fileValsGood[i] == false) {
            allGood = false;
        }
    }
    return allGood;
}

//Prompts

void paSetup::textPromptInDeviceNum() {
    std::string inDeviceNumResponse;
    int inDeviceNumRespToInt;
    do {
        std::cout << "Which device should be used for input? (1 - " << (devices.size() - 1) << "): ";
        std::cin >> inDeviceNumResponse;
        try {
            inDeviceNumRespToInt = std::stoi(inDeviceNumResponse);
        } catch (...) {
            inDeviceNumRespToInt = -1;
        }
        if (deviceIsGood(inDeviceNumRespToInt)) {
            if (std::get<1>(devices.at(inDeviceNumRespToInt)) <= 0) {
                std::cout << "This device has no input channels.\n";
                inDeviceNumRespToInt = -1;
            }
        }
    } while (!inDeviceIsGood(inDeviceNumRespToInt));
    inDeviceNum = inDeviceNumRespToInt;
}

void paSetup::textPromptOutDeviceNum() {
    std::string outDeviceNumResponse;
    int outDeviceNumRespToInt;
    do {
        std::cout << "Which device should be used for output? (1 - " << (devices.size() - 1) << "): ";
        std::cin >> outDeviceNumResponse;
        try {
            outDeviceNumRespToInt = std::stoi(outDeviceNumResponse);
        } catch (...) {
            outDeviceNumRespToInt = -1;
        }
        if (deviceIsGood(outDeviceNumRespToInt)) {
            if (std::get<2>(devices.at(outDeviceNumRespToInt)) <= 0) {
                std::cout << "This device has no output channels.\n";
                outDeviceNumRespToInt = -1;
            }
        }
    } while (!outDeviceIsGood(outDeviceNumRespToInt));
    outDeviceNum = outDeviceNumRespToInt;
}

//Prompts the user for a number of input channels until a valid answer is given. Assumes an apppropriate inDeviceNum is set.
void paSetup::textPromptInChannels() {
    std::string inChannelsResponse;
    int inChannelsRespToInt;
    do {
        std::cout << "How many input channels should be used? (1 - " << std::get<1>(devices.at(inDeviceNum)) << "): ";
        std::cin >> inChannelsResponse;
        try {
            inChannelsRespToInt = std::stoi(inChannelsResponse);
        } catch (...) {
            inChannelsRespToInt = -1;
        }
    } while (!inChannelsIsGood(inChannelsRespToInt));
    inChannels = inChannelsRespToInt;
}

//Prompts the user for a number of output channels until a valid answer is given. Assumes an apppropriate outDeviceNum is set.
void paSetup::textPromptOutChannels() {
    std::string outChannelsResponse;
    int outChannelsRespToInt;
    do {
        std::cout << "How many output channels should be used? (1 - " << std::get<2>(devices.at(outDeviceNum)) << "): ";
        std::cin >> outChannelsResponse;
        try {
            outChannelsRespToInt = std::stoi(outChannelsResponse);
        } catch (...) {
            outChannelsRespToInt = -1;
        }
    } while (!outChannelsIsGood(outChannelsRespToInt));
    outChannels = outChannelsRespToInt;
}

//Prompts the user for a sample rate. Only ensures that the response can be converted to a positive number.
void paSetup::textPromptSampleRate() {
    std::string sampleRateResponse; 
    int sampleRateRespToInt;
    do {
        std::cout << "What sample rate should be used? (Suggested: " << std::get<3>(devices.at(inDeviceNum)) << "): ";
        std::cin >> sampleRateResponse;
        try {
            sampleRateRespToInt = std::stoi(sampleRateResponse);
        } catch (...) {
            sampleRateRespToInt = -1;
        }
    } while (sampleRateRespToInt <= 0);
    sampleRate = sampleRateRespToInt;
}

int paSetup::textPromptGenerateFile() {
    std::string saveResponse;
    do {
        std::cout << "Save configuration? (Y / N): ";
        std::cin >> saveResponse;
    } while ((saveResponse != "Y") && (saveResponse != "N"));
    if (saveResponse == "Y") {
        if (generateFile() == 0) {
            return 0;
        } else {
            std::cout << "Unable to create file.\n";
            return -1;
        }
    }
    return 0;
}

//Gets values by file, then by prompt
void paSetup::getValuesViaConsole() {
    
    readValsFromFile();

    if ((!inDeviceIsGood(fileVals[0])) || (!outDeviceIsGood(fileVals[1]))) {
        listDevices();
    }

    if (inDeviceIsGood(fileVals[0])) {
        std::cout << "Valid input device read from file: " << std::get<0>(devices.at(fileVals[0])) << '\n';
        setInDeviceNum(fileVals[0]);
        fileValsGood[0] = true;
    } else {
        textPromptInDeviceNum();
    }

    if (outDeviceIsGood(fileVals[1])) {
        std::cout << "Valid output device read from file: " << std::get<0>(devices.at(fileVals[1])) << '\n';
        setOutDeviceNum(fileVals[1]);
        fileValsGood[1] = true;
    } else {
        textPromptOutDeviceNum();
    }

    if (inChannelsIsGood(fileVals[2])) {
        std::cout << "Valid number of input channels read from file: " << fileVals[2] << '\n';
        setInChannels(fileVals[2]);
        fileValsGood[2] = true;
    } else {
        textPromptInChannels();
    }

    if (outChannelsIsGood(fileVals[3])) {
        std::cout << "Valid number of output channels read from file: " << fileVals[3] << '\n';
        setOutChannels(fileVals[3]);
        fileValsGood[3] = true;
    } else {
        textPromptOutChannels();
    }

    if (fileVals[4] > 0) {
        std::cout << "Attempting to start with sample rate from file: " << fileVals[4] << '\n';
        setSampleRate(fileVals[4]);
    } else {
        textPromptSampleRate();
    }
}

void paSetup::listDevices() {
    std::cout << "Available devices: \n";
    for (int i = 0; i < static_cast<int>(devices.size()); i++) {
        std::cout << "\t" << i << ": " << std::get<0>(devices.at(i)) << "\n";
    }
}

void paSetup::printValues() {
    std::cout << "\tSample rate: " << getSampleRate() << '\n';
    std::cout << "\tInput device: " << getInDeviceNum() << '\n';
    std::cout << "\tOutput device: " << getOutDeviceNum() << '\n';
    std::cout << "\tInput channels: " << getInChannels() << '\n';
    std::cout << "\tOutput channels: " << getOutChannels() << '\n';
}

//File
int paSetup::generateFile() {
    std::ofstream fs;
    fs.open("config.txt");
    if (fs.is_open()) {
        fs << "Input:" << std::get<0>(devices.at(inDeviceNum)) << '\n';
        fs << "Output:" << std::get<0>(devices.at(outDeviceNum)) << '\n';
        fs << "InputChannels:" << inChannels << '\n';
        fs << "OutputChannels:" << outChannels << '\n';
        fs << "SampleRate:" << sampleRate << '\n';
        fs.close();
        std::cout << "Configuration saved to config.txt.\n";
    } else {
        return -1;
    }
    return 0;
}

int paSetup::readValsFromFile() {
    std::ifstream fs;
    fs.open("config.txt");
    if (fs.is_open()) {
        std::string line;
        while (getline(fs, line)) {
            int split = line.find(":");
            std::string setting = line.substr(0, split);
            std::string value = line.substr(split + 1, line.size() - 1);
            if (setting == "Input") {
                for (int i = 0; i < static_cast<int>(devices.size()); i++) {
                    if (value == std::get<0>(devices.at(i))) {
                        fileVals[0] = i;
                    }
                }
            } else if (setting == "Output") {
                for (int i = 0; i < static_cast<int>(devices.size()); i++) {
                    if (value == std::get<0>(devices.at(i))) {
                        fileVals[1] = i;
                    }
                }
            } else if (setting == "InputChannels") {
                try {
                    fileVals[2] = std::stoi(value);
                } catch (...) {}
            } else if (setting == "OutputChannels") {
                try {
                    fileVals[3] = std::stoi(value);
                } catch (...) {}
            } else if (setting == "SampleRate") {
                try {
                    fileVals[4] = std::stoi(value);
                } catch (...) {}
            } else {
                std::cout << "Ignoring unrecognized setting: " << setting << '\n';
            }
        }
        return 0;
    } else {
        return -1;
    }
}