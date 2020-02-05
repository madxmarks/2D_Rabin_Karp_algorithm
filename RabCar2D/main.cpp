#include <iostream>
#include <string>

using namespace std;

unsigned const int W = 997;
unsigned const int S = 128;


void hashing2D(string *s , int *h, int hei, int len)
{
    for (int k=0; k<hei; k++)
    {
        for (int i=0; i<len; i++)
        h[k]=((h[k]*S)+s[k][i])%W;
    }

}

void rehash2D ( unsigned int Spower, string *s, int hei, int len, int *oldhash ,int pos)
{
    for(int i=0; i<hei; i++)
    {
    oldhash[i] = (((oldhash[i] -(s[i][pos] * Spower)%W+W)%W)*S%W+s[i][len+pos])%W;
    }
}

size_t Power(size_t n, size_t m)
{
    size_t res = 1;
    for (int i = 0 ; i < m; i++)
        res = (res * n )% W;
    return res;
}

int SingleHash(int* Hash ,int len, int pos){
int H = 0;
for (int i = 0; i < len; i++){
    H = ((H*S) + Hash[i+pos])%W;
}
return H;
}

int SingleReHash(unsigned int Spower, int* Hash , int oldhash, int len, int pos){
  oldhash = (((oldhash -(Hash[pos] * Spower)%W+W)%W)*S%W+Hash[len+pos])%W;
  return oldhash;
}

int Hashy (string *Fi, string *Se, int sizFir, int sizSec)
{

    int found =0, i = 0, H1 =0, H2=0, match =0;
    int *HfT = new int[sizFir]();
    int *HfP = new int[sizSec]();
    size_t Spow = Power(S,sizSec-1);
    hashing2D(Se , HfP, sizSec, sizSec);
    int PatHash = SingleHash(HfP,sizSec,0);
    int TextHash;
for (int i = 0; i <  sizFir - sizSec +1 ; i++){
    if (i == 0)
        hashing2D(Fi , HfT, sizFir, sizSec);
    else
     rehash2D ( Spow, Fi, sizFir, sizSec, HfT , i-1);
    for (int j = 0; j< sizFir-sizSec +1; j++)
    {

        if (j == 0)
        TextHash = SingleHash(HfT, sizSec,0);
        else
        TextHash = SingleReHash(Spow,HfT,TextHash,sizSec,j - 1);
        if(TextHash==PatHash)
        {
            int truu =1;
            match++;
            for (int k = 0; k < sizSec; k++){
                for (int p =0; p< sizSec; p++)
                {
                if (Fi[j+k][i+p] != Se[k][p]){
                 match--;
                 truu =0;
                 break;
                }
                }
                if (truu==0)
                    break;
                else {
                    cout << "found at " << j << " and " << i << endl;
                    break;
                }

        }
        }
        }
    }
    return match;
}

int main(){
    // to make it easier to understand and work properly it's good idea to use square matrix
int TextSiz = 4;
int PatSiz = 2;
string text[TextSiz] = {"deop","kaop","adel","akar"};
string pat[PatSiz] = {"de","ka"};
cout<<Hashy(text,pat,TextSiz,PatSiz);
}
