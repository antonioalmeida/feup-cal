#include <string>
#include <vector>
#include <sstream>

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

vector<string> splitting(string original){
	vector<string> result;
	stringstream temp(original);
	string token;
	while(temp >> token)
		result.push_back(token);
	return result;
}
