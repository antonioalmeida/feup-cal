#include <string>
#include <vector>
#include <sstream>

#define MIN(x,y) ((x) < (y) ? (x) : (y))

using namespace std;

vector<int> computePrefix(string pattern){
	int m=pattern.length();
	vector<int> prefix(m);
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
	return prefix;
}

int KMP(string pattern, string text){
	int num=0;
	int m=pattern.length();
	vector<int> prefix = computePrefix(pattern);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}

int KMP(string pattern, string text, const vector<int> &prefix){
	int num=0;
	int m=pattern.length();

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}

int editDistance(string pattern, string text){
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

vector<string> splitting(string original){
	vector<string> result;
	stringstream temp(original);
	string token;
	while(temp >> token)
		result.push_back(token);
	return result;
}
