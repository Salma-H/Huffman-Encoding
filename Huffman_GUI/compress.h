#ifndef COMPRESS_HPP
#define COMPRESS_HPP
#include <bits/stdc++.h>

struct image
{
    int width=0, height=0;
    int intensity=0;
    std::vector<uint8_t> pixels;
    std::vector<int> ipixels;
};

void ReadPGM( std::string filePath, image &pgmfile)
{
    std::ifstream input(filePath, std::ios::binary);
    std::string line,f;
    int L;
    char c;
    uint8_t k;
    input >> f >> pgmfile.width >> pgmfile.height >> pgmfile.intensity;

    int num = pgmfile.width * pgmfile.height;
    for (int i=0; i < num; i++)
    {
        input.get(c);
        k = (uint8_t) c;
        L = (int) k;
        pgmfile.ipixels.push_back(L);
    }
    input.close();
}



// finds each pixel and replaces it with its codeword
void Mapping(const image &file,const std::map<int,std::string> &codetable, std::string &encodedimage)
{
    for( auto i : file.ipixels)
    {
        auto it = codetable.find(i);
        encodedimage += it->second;
    }
}


void compressing ( std::vector<char> &bytesvector , std::string &encoded )
{
    if (encoded.size() % 8 == 0)
    {
        std::string tempstring = "";
        for (int i = 0; i < encoded.size(); i++)
        {
            if ((i + 1) % 8 == 0)
            {
                tempstring += encoded[i];
                int S = std::stoi(tempstring, 0, 2); //converts the binary code to integer
                char c = (char) S;                    //converts the int to char
                bytesvector.push_back(c);          //sorting the characters
                tempstring = "";
            }
            else
            {
                tempstring += encoded[i];
            }
        }
    }
    else
    {
        int NumofPaddingBits = 8 - (encoded.size() % 8);
        char P = (char)NumofPaddingBits;           // convert the number of the padding bits to char
        bytesvector.push_back(P) ;              // insert the char of padding bits in the first of the bytesvector
        for (int i = 0; i < NumofPaddingBits; i++)
        {
            encoded += "0";
        }
        std::string tempString = "";
        for (int i = 0; i < encoded.size(); i++)
        {
            if ((i + 1) % 8 == 0)
            {
                tempString += encoded[i];
                int S = std::stoi(tempString, 0, 2); //converts the binary code to integer
                char c = (char)S;                    //converts the int to char
                bytesvector.push_back(c) ;
                tempString = "";
            }
            else
            {
                tempString += encoded[i];
            }
        }
    }
}

// write the vector of freq into a file
void writeFreqTable (const std::map <int,int> &frequency)
{
    std::ofstream wfile ("image.frq");
    for ( auto it=frequency.begin(); it!=frequency.end(); it++)
         wfile<< it->first << " " << it->second << std::endl;
    wfile.close() ;
}



// write compressed image into a file

void writeCompImage ( const std::vector< char > &vec , image &pgmfile )
{
    std::ofstream wfile ("image.enc",std::ios::binary);
    wfile << "P5" << std::endl << pgmfile.width <<' '<< pgmfile.height << std::endl << pgmfile.intensity << std::endl;
    for(auto i : vec)
        wfile.put(i);

    wfile.close() ;
}

// read image.enc
void readcompImage ( std::string filePath, std::vector< int > &vec2 , int &N_paddingBits , image &pgmfile)
{
    std::string format;
    char chN_paddingBits;
    char c;

    std::ifstream rfile (filePath, std::ios::binary);
    rfile >> format >> pgmfile.width >> pgmfile.height >> pgmfile.intensity;
    rfile.get(chN_paddingBits);
    uint8_t ctemp = (uint8_t) chN_paddingBits;
    N_paddingBits = (int) ctemp;

    while (rfile.get(c))
    {

        uint8_t temp = (uint8_t) c;
        int ibyte = (int) temp;

        vec2.push_back(ibyte);
    }
    rfile.close();

}

void readFreqTable (std::string filePath, std::map <int,int> &receivedfreq)
{
    std::ifstream rfile (filePath);
    if (!rfile)
    {
        std::cout<< "failed to open image.frq"<< std::endl;
        exit(1);
    }
    std::string key,value;
    while(rfile>>key>>value)
    {
        receivedfreq.insert(std::pair<int,int>(std::stoi(key),std::stoi(value)));
    }
    rfile.close();
}

void Decompressing (std::vector< int > &vec2 , int &N_paddingBits , std::string &binary )
    {
        for (int i = 0; i < vec2.size(); i++)
        {
            binary += std::bitset<8>(vec2[i]).to_string();
        }
        for (int i = 0; i < N_paddingBits; i++)
        {
            binary.pop_back();
        }
    }


void WritePGM (image &pgmfile)
{
    std::ofstream wimg ( "image.pgm" , std::ios::binary );

    if (!wimg)
    {
        std::cout<< "failed to write image.pgm" << std::endl;
        exit(1);
    }

    wimg << "P5" << std::endl << pgmfile.width <<' '<< pgmfile.height << std::endl << pgmfile.intensity << std::endl;
    for(auto i : pgmfile.ipixels)
    {
        uint8_t temp = (uint8_t) i;
        char c = (char) temp;
        wimg.put(c);
    }

    wimg.close() ;
}

#endif // COMPRESS_HPP
