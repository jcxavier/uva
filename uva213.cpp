// Author: João Xavier
// Date: 26-04-2012

/* @JUDGE_ID: '00000' 213 C++ "Message Decoding" */

/* @BEGIN_OF_SOURCE_CODE */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <sstream>

#define MAX_LENGTH 115
#define ADVANCE 3

// states
enum state {
    STATE_RD_HEADER,
    STATE_RD_MSG_SIZE,
    STATE_RD_CODE,
    STATE_PRINT
};

using namespace std;

unsigned int bin2dec[MAX_LENGTH];
unsigned int binMaxs[] = { 0, 1, 3, 7, 15, 31, 63, 127 };

inline int stoi(const string str) {
    stringstream ss(str);
    int i;
    ss >> i;
    return i;
}

inline bool isMsg(const string str) {
    return str.find('1') != string::npos;
}

inline bool isEndCode(const string str) {
    return str.find('0') == string::npos;
}

string dec2bin(unsigned n, unsigned int length) {
    const int size = sizeof(n)*8;
    string res;
    bool s = false;
    for (int a = 0; a < size; a++) {
        bool bit = n >> (size-1);
        if (bit)
            s = true;
        if (s)
            res.push_back(bit + '0');
        n<<=1;
    }
    if (!res.size())
        res.push_back('0');
    
    while (res.size() < length) {
        res = "0" + res;
    }
        
    return res;
}

int main (int argc, char* argv[]) {
    // init array
    memset(bin2dec, 0, sizeof(bin2dec));
    bin2dec[1] =   1;
    bin2dec[10] =  2;
    bin2dec[11] =  3;
    bin2dec[100] = 4;
    bin2dec[101] = 5;
    bin2dec[110] = 6;
    bin2dec[111] = 7;
    
    map<string, char> decode;
    string lineBuffer = "", header, pool, decodedMsg;
    state currentState = STATE_RD_HEADER;
    
    unsigned int msgSize = 0;
    bool shouldRepeat = false;
    
    while (!cin.eof()) {
        getline(cin, lineBuffer);
        
        // clean input
        size_t found;
        do {
            found = lineBuffer.find('\r');
            
            if (found != string::npos) {
                lineBuffer.erase(found, 1);
            } else {
                break;
            }
        }
        while (found != string::npos);
        
        if (lineBuffer.length() == 0) {
            continue; // ignore all empty lines
        }
        else {
            do {  
                switch (currentState) {
                    case STATE_RD_HEADER: {
                        // reinit vars
                        pool = "";
                        decodedMsg = "";
                        msgSize = 0;
                        decode.clear();
                        
                        header = lineBuffer;
                        const unsigned int headerLength = header.length();                    
                        
                        // fill map
                        for (unsigned int counter = 0, binLength = 1; counter < headerLength; binLength++) {
                            unsigned int max = binMaxs[binLength];
                            
                            for (unsigned int i = 0; i < max && counter < headerLength; i++, counter++) {
                                decode[dec2bin(i, binLength)] = header[counter];
                            }
                        }

                        // state advance
                        shouldRepeat = false;
                        currentState = STATE_RD_MSG_SIZE;
                        break;
                    }
                    
                    case STATE_RD_MSG_SIZE: {
                        unsigned int fixedAdvance = ADVANCE - pool.length();
                        pool += lineBuffer.substr(0, fixedAdvance);
                        
                        if (pool.length() == ADVANCE) {
                            msgSize = bin2dec[stoi(pool)];
                            
                            pool = "";
                            lineBuffer = lineBuffer.substr(fixedAdvance);
                            
                            // state advance
                            currentState = (msgSize ? STATE_RD_CODE : STATE_PRINT);
                            shouldRepeat = true;
                        } else {
                            shouldRepeat = false;
                        }
                        
                        break;
                    }
                    
                    case STATE_RD_CODE: {
                        pool += lineBuffer;
                        string code;
                        
                        for (unsigned int idx = 0; currentState == STATE_RD_CODE; idx += msgSize) {
                            code = pool.substr(idx, msgSize);
                            
                            if (code.length() != msgSize) {
                                pool = code;
                                shouldRepeat = false;
                                break;
                            }
                        
                            if (isEndCode(code)) {
                                if (idx + msgSize >= pool.length()) {
                                    lineBuffer = "";
                                    shouldRepeat = false;
                                }
                                else {
                                    lineBuffer = pool.substr(idx + msgSize);
                                    shouldRepeat = true;
                                }
                                
                                // state advance
                                pool = "";
                                currentState = STATE_RD_MSG_SIZE;
                            } else {
                                decodedMsg += decode[code];
                            }
                        }
                        
                        break;
                    }
                    
                    case STATE_PRINT: {
                        cout << decodedMsg << endl;
                        
                        // state advance
                        shouldRepeat = false;
                        currentState = STATE_RD_HEADER;
                        break;
                    }
                }
            } while (shouldRepeat);
        }    
    }
    
    return 0;
}

/* @END_OF_SOURCE_CODE */
