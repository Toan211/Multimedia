#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>


#include <chrono> 

using namespace std;
using namespace std::chrono;

string stream_as_string(istream& stm)
{
    return { istreambuf_iterator<char>(stm), std::istreambuf_iterator<char>{} };
}

vector<int> encoding(string s1)
{
    std::cout << "Encoding\n";
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    std::cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            std::cout << p << "\t" << table[p] << "\t\t"
                << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    std::cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

void decoding(vector<int> op)
{
    std::cout << "\nDecoding\n";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    std::cout << s;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        std::cout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
}

int main()
{
#if 1
    ofstream OutFile;
    OutFile.open("OutPut2-10k.txt");
    string encodedString, decodedString;
    ifstream inFile(/*copy file text path: Example*/"C:/Users/Admin/source/repos/LZW_Text/LZW/test/Hunger2-10k.txt");
    string str;
    str = stream_as_string(inFile);

    // Get starting timepoint 
    auto start = high_resolution_clock::now();

    vector<int> output_code = encoding(str);

    auto stop = high_resolution_clock::now();

    
    for (int i = 0; i < output_code.size(); i++) {
        OutFile << output_code[i] << " ";
     
    }

   // std::cout << "Compressed Number of Bytes: " << (encodedString.length()) << " bytes" << endl;

    OutFile << endl;

    // Get duration. Substart timepoints to  
   // get durarion. To cast it to proper unit 
   // use duration cast method 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

#else
    ifstream inFile("C:/Users/Admin/source/repos/LZW/LZW/OutPutMP3.txt");
    string str;
    int word;
    vector<int> Decode;
    while (inFile >> word)
    {
        Decode.push_back(word);
    }

    for (int i = 0; i < Decode.size(); i++)
    {
        cout << Decode[i] << endl;
    }

    decoding(Decode);
#endif
    return 0;
}
