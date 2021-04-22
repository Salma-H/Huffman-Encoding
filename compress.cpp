#include <bits/stdc++.h>
#include "compress.hpp"
#include "Huffman.hpp"
//#include <cxxopts.hpp>


int main(int argc, char **argv)
{
    cxxopts::Options options("MyProgram", "One line description of MyProgram");

    options.add_options()
    ("t,file", "File name", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);
    std::string fname;
    fname = argv[1];
    
    if (!result.count("file"))
    {
        image file;
        ReadPGM(fname, file);

        std::map<int, int> frequency;
        GetFreqTable(file.ipixels, frequency);

        Heap *huff;
        huff = MakeHuffmanTree(frequency);

        std::string S = "";
        std::map<int, std::string> encodingTable;
        GetCodewords(huff, S, encodingTable);

        std::string encoded = "";
        Mapping(file, encodingTable, encoded);


        // serialization & deserialization
        std::vector<char> bytesvector;


        compressing(bytesvector, encoded);
        writeCompImage(bytesvector, file);
        writeFreqTable(frequency);
    }   
    else
    {
        std::string freqfile;
        freqfile = result["file"].as<std::string>();
        image file2;
        std::vector<int> received_bytesvector;
        int num_paddingBits = 0;
        std::map <int,int> received_FreqTable;
        std::string Binary = "";
        readcompImage(fname, received_bytesvector, num_paddingBits, file2);
    
        readFreqTable (freqfile, received_FreqTable);
        
        Decompressing (received_bytesvector , num_paddingBits , Binary );


        Heap *H;
        H = MakeHuffmanTree(received_FreqTable);   


        std::string S ="";
        std::map<int, std::string> encodingTable2;
        GetCodewords(H, S, encodingTable2);

        GetPixels( Binary, encodingTable2, file2);

        WritePGM(file2);
    }
    return 0;
}