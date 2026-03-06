#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <cstdlib>

using namespace std;

uint32_t floatBits(float f);
void printIEEE(const string& label, float f);
int getExponent(float f);
float buildThresholdFloat(int biasedExp);

int main(int argc, char* argv[]){

    if(argc != 3){
        cerr << "usage:\n"
             << "\t" << argv[0] << " loop_bound loop_counter\n\n"
                  << "\t" << "loop_bound is a positive floating-point value\n"
                  << "\t" << "loop_counter is a positive floating-point value\n";
        return 1;
    }


    float bound = atof(argv[1]);
    float counter = atof(argv[2]);

    printIEEE("Loop bound: ", bound);
    printIEEE("Loop counter:", counter);
    std::cout << "\n";



    int expBound = getExponent(bound);
    int expCounter = getExponent(counter);


    int expDiff = expBound - expCounter;

    if(expDiff >= 24){
        int thresholdBiasedExp = expCounter + 24;
        float threshold = buildThresholdFloat(thresholdBiasedExp);
        cout << "Warning: Possible overflow!\n";
        cout << "Overflow threshold:\n";
        cout << "\t" << threshold << "\n";


        uint32_t tbits = floatBits(threshold);
        bitset<1> tsign(tbits >> 31);
        bitset<8> texp((tbits >> 23) & 0xFF);
        bitset<23> tmant(tbits & 0x7FFFFF);
        cout << "\t" << tsign << " " << texp
            << " " << tmant << "\n";
    } else {
        cout << "There is no overflow!\n";
    }
    return 0;
    
}

uint32_t floatBits(float f){
    uint32_t bits;
    memcpy(&bits, &f, sizeof(bits));
    return bits;
}

void printIEEE(const string& label, float f) {
    uint32_t bits = floatBits(f);

    bitset<1> sign (bits >> 31);
    bitset<8> exponent((bits >> 23) & 0xFF);
    bitset<23> matissa(bits & 0x7FFFFF);


    cout << label << " "
    << sign << " "
    << exponent << " "
    << matissa << "\n";

}

int getExponent(float f){
    uint32_t bits = floatBits(f);

    return static_cast<int>((bits >> 23) & 0xFF);
}

float buildThresholdFloat(int biasedExp){
    uint32_t bits = static_cast<uint32_t>(biasedExp) << 23;
    float result;

    memcpy(&result, &bits, sizeof(result));
    return result;
}