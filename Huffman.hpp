#include <iostream>
#include <vector>
#include <queue>
#include <map>



struct Heap
{
    int data;
    int freq;
    Heap *left;
    Heap *right;

    Heap(int data, int freq) 
	{ 
		left = right = nullptr; 
		this->data = data; 
		this->freq = freq; 
	}
};

bool isLeaf (const Heap *H)
{
    return H !=nullptr && H->left == nullptr && H->right == nullptr;
}


struct compare { 

	bool operator()(Heap *l, Heap *r) 
	{ 
		return (l->freq > r->freq); 
	} 
}; 

void  GetFreqTable( const std::vector<int> &vect, std::map <int,int> &frequency)
{
    for(auto i : vect)
        frequency[i]++;
}

void GetCodewords(const Heap* root, std::string str,std::map<int, std::string> &codewords) 
{
    
    if (!isLeaf(root)) 
    {
        if(root->left)
            GetCodewords(root->left, str + "0",codewords);
        if(root->right)
            GetCodewords(root->right, str + "1",codewords);
    }
    else
    {
        codewords.insert( std::pair<int, std::string>(root->data,str) );
    }

}

Heap *MakeHuffmanTree(std::map <int,int> &frequency) 
{ 
	Heap *left, *right, *top; 
	std::priority_queue<Heap*, std::vector<Heap*>, compare> minHeap; 

    for (auto it = frequency.begin(); it != frequency.end(); it++) 
		minHeap.push(new Heap(it->first, it->second)); 

	while (minHeap.size() != 1) 
    { 
		left = minHeap.top(); 
		minHeap.pop(); 
		right = minHeap.top(); 
		minHeap.pop(); 
		top = new Heap(0, left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		minHeap.push(top); 
	} 
    return minHeap.top();
} 



void MapbyValue(std::map<int, std::string> &M1,std::map<std::string,int> &M2)
{
    for(auto it = M1.begin(); it != M1.end(); ++it)
    {
        M2.insert(std::pair< std::string, int >(it->second,it->first));
    }
}

//for decompression
void GetPixels( std::string &str, std::map<int ,std::string> &M, image &encimage)
{
    std::map< std::string, int> codewords;
    MapbyValue(M, codewords);
    std::string pixel ="";
    for ( int i=0; i < str.size(); i++) //|| pixel.size() != 1; i++)
    {

        std::map< std::string, int>::iterator it = codewords.begin();
        it = codewords.find(pixel);
        
        if ( it != codewords.end() )
        {
            encimage.ipixels.push_back(it->second);
            pixel = str[i];
        }
        else
        {
            pixel += str[i];            
        }

    }

    //std::cout << encimage.ipixels.size()<< std::endl;
}