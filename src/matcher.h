#include <string>
#include <vector>
#include <sstream>

#define MIN(x,y) ((x) < (y) ? (x) : (y))

using namespace std;

//TODO: Substitude by TP's solution
vector<int> computePrefix(string pat){
    // length of the previous longest prefix suffix
    int len = 0;
    int M = pat.size();
    vector<int> lps(M);
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < M){
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if (len != 0)
                len = lps[len-1];
            else{
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

//TODO: Substitude by TP's solution
int KMP(string pat, string txt){
    int M = pat.size();
    int N = txt.size();
    int counter = 0;
    vector<int> lps = computePrefix(pat);
    int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]){
            j++;
            i++;
        }
        if (j == M){
            counter++;
            j = lps[j-1];
        }
        else if (i < N && pat[j] != txt[i]){
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }

    return counter;
}

int KMP(string pat, string txt, vector<int> lps){
    int M = pat.size();
    int N = txt.size();
    int counter = 0;
    int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]){
            j++;
            i++;
        }
        if (j == M){
            counter++;
            j = lps[j-1];
        }
        else if (i < N && pat[j] != txt[i]){
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }

    return counter;
}

//TODO: Substitude by TP's solution
int editDistance(string pattern, string text){
	const std::size_t len1 = pattern.size(), len2 = text.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
			d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (pattern[i - 1] == text[j - 1] ? 0 : 1) });
	return d[len1][len2];
}

vector<string> splitting(string original){
	vector<string> result;
	stringstream temp(original);
	string token;
	while(temp >> token)
		result.push_back(token);
	return result;
}
