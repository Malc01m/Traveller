#ifndef PASETUP_H
#define PASETUP_H

#include <vector>
#include <string>
#include <tuple>

class paSetup {

    public:

        //Constructors

        paSetup(std::vector<std::tuple<std::string, int, int, int>> devices);

        //Setters

        void setInDeviceNum(int num);
        void setOutDeviceNum(int num);
        void setInChannels(int ch);
        void setOutChannels(int ch);
        void setSampleRate(int sr);
        void setFileValGood(int ind, bool isGood);

        //Getters

        int getInDeviceNum();
        int getOutDeviceNum();
        int getInChannels();
        int getOutChannels();
        int getSampleRate();
        bool getFileValOK(int ind);

        //Validators

        bool deviceIsGood(int num);
        bool inDeviceIsGood(int num);
        bool outDeviceIsGood(int num);
        bool inChannelsIsGood(int ch);
        bool outChannelsIsGood(int ch);
        bool sampleRateIsGood(int sr);
        bool fileValsAllGood();

        //Prompts

        void textPromptInDeviceNum();
        void textPromptOutDeviceNum();
        void textPromptInChannels();
        void textPromptOutChannels();
        void textPromptSampleRate();
        int textPromptGenerateFile();
        
        void getValuesViaConsole();
        void listDevices();
        void printValues();

        //File
        
        int generateFile();
        int readValsFromFile();

    private:

        std::vector<std::tuple<std::string, int, int, int>> devices;

        //Unverified values read from file. (inDeviceNum, outDeviceNum, inChannels, outChannels, sampleRate)
        int fileVals[5] = {-1, -1, -1, -1, -1};
        //Keeps track of which values read from file were good, so user isn't asked to save again. Sample rate is assumed true until the config test fails.
        bool fileValsGood[5] = {false, false, false, false, true};

        int inDeviceNum;
        int outDeviceNum;
        int inChannels;
        int outChannels;
        int sampleRate;

};

#endif