
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

using std::cout;    using std::endl;
using std::vector;  using std::string;
using std::ifstream; using std::ofstream;
const vector<string> FEATURE_VEC{"a", "about", "above", "after", "again", "against", "all", "am", "an", "and",
                                 "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being",
                                 "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't",
                                 "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during",
                                 "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have",
                                 "haven't", "having", "he", "he'd", "he'll", "he's", "her","here", "here's", "hers",
                                 "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm",
                                 "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's",
                                 "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off",
                                 "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out",
                                 "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should",
                                 "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their",
                                 "theirs", "them", "themselves", "then", "there", "there's", "these", "they",
                                 "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too",
                                 "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're",
                                 "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
                                 "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would",
                                 "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
                                 "yourself", "yourselves", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+",
                                 ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_",
                                 "`", "{", "|", "}", "~"};


struct Similarity {
    string authorA, authorB;
    double angle;
};

std::ostream& operator<<(std::ostream& os, const Similarity& s) {
    os << std::setw(15) << std::setfill(' ') << "Similarity - " << s.authorA << " <-> " << s.authorB <<": " << s.angle;  
    //of << "Similarity - hamilton <-> unknown:   " << angle(hamilton_vec, unknown_vec) << endl;
    return os;
}


// Function prototypes
string fileToString(ifstream& file);
vector<int> createCountVec(const string& text);
int dotProduct(const vector<int>& v1, const vector<int>& v2);
double mag(const vector<int>& v);
double angle(const vector<int>& v1, const vector<int>& v2);

template<typename T>
int countOccurrences(const T& text, const T& val);

int main() {

    ifstream hamilton_fs("../res/hamilton.txt");
    ifstream jj_fs("../res/jj.txt");
    ifstream madison_fs("../res/madison.txt");
    ifstream unknown_fs("../res/unknown.txt");
    
    string hamilton_str = fileToString(hamilton_fs);
    string jj_str = fileToString(jj_fs);
    string madison_str = fileToString(madison_fs);
    string unknown_str = fileToString(unknown_fs);

    vector<int> hamilton_vec = createCountVec(hamilton_str);
    vector<int> jj_vec = createCountVec(jj_str);
    vector<int> madison_vec = createCountVec(madison_str);
    vector<int> unknown_vec = createCountVec(unknown_str);
    
    ofstream of;
    of.open("./output.txt");
    if (of.is_open()) {
        // of << "Similarity - hamilton <-> unknown:   " << angle(hamilton_vec, unknown_vec) << endl;
        // of << "Similarity - jj <-> unknown:         " << angle(jj_vec, unknown_vec) << endl;
        // of << "Similarity - madison <-> unknown:    " << angle(madison_vec, unknown_vec) << endl;
        vector<Similarity> rank {{"hamilton", "unknown", angle(hamilton_vec, unknown_vec)}, {"jj", "unknown", angle(jj_vec, unknown_vec)}, {"madison", "unknown", angle(madison_vec, unknown_vec)}};
        std::copy(rank.begin(), rank.end(), std::ostream_iterator<Similarity>(of, "\n"));
        auto closerSimila = [] (Similarity& a, Similarity& b) {
            return a.angle < b.angle;
        };
        std::sort(rank.begin(), rank.end(), closerSimila);
        of << "The Closet Author is " << rank[0].authorA << endl;
        of.close();
    } else {
        cout << "Failed to open the file" << endl;
    }
    return 0;

}


string fileToString(ifstream& file) {
    string ret = "";
    string line;
    while (std::getline(file, line)) {
        std::transform(line.begin(), line.end(),line.begin(), ::tolower);
        ret += line + " ";
    }
    return ret;
}

vector<int> createCountVec(const string& text) {
    vector<int> ret;
    for (auto k_word : FEATURE_VEC) {
        ret.push_back(countOccurrences<string>(text, k_word));
    }
    return ret;
}

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
}

double mag(const vector<int>& v) {
    return std::sqrt(dotProduct(v, v));
}

template<typename T>
int countOccurrences(const T& text, const T& val) {
    int count = 0;
    auto curr = text.begin();
    auto end = text.end();
    while (curr != end) {
        auto temp = std::search(curr, end, val.begin(), val.end());
        if (temp != end) {
            count ++;
        } else {
            break;
        }
        curr = ++temp;
    }
    return count;
}

double angle(const vector<int>& v1, const vector<int>& v2) {
    return dotProduct(v1, v2) / (mag(v1) * mag(v2));
}
