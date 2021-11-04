/*
INTEGRANTES: 

* Edson Bryan Bejar Roman
* Katherine Nikole Bejar Roman

*/

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

void showlist(list <string> g)
{
    list <string> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}
unsigned int edit_distance(const string& s1, const string& s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    vector <vector <unsigned int>> d(len1 + 1, vector <unsigned int >(len2 + 1));
    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), (d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)));
    return d[len1][len2];
}


void correccion(std::unordered_map <int, std::string> &input, std::unordered_map <int, std::string> &dictionary){
    ofstream archivo;
    archivo.open("output.txt");
    string result="";
    for( auto it = begin(input); it != end(input); ++it ){
        bool c = false;
        for( auto it2 = begin(dictionary); it2 != end(dictionary); ++it2 ){
            if(*it==*it2){
                c=true;
                break;
            }
        }
        if(!c){
            queue<string> posibles;
            cout<<"Palabra " << *it << " no encontrada en el diccionario"<<endl;
            for(auto it2 = begin(dictionary); it2 != end(dictionary); ++it2 ){
                if(edit_distance(*it, *it2)<3){
                    posibles.push(*it2);
                    //posibles.insert(std::make_pair(i, it2));
                }            
            }
            if(!posibles.empty()){
                cout<<"Posibles correcciones: "<<endl;
                int z=0;
                int e=0;
                for(;z<posibles.size(); z++){
                    cout<<posibles.front()<<" - "<<z<<endl;
                    posibles.push(posibles.front());
                    posibles.pop();
                }
                cout<<"Escriba por cual desea reemplazar: ";cin>>e;
                while(e>=z||0>e){
                    cout<<"Escriba por favor uno de los numeros antes mencionados: ";cin>>e;
                }
                if(e!=0){
                    for(;e>0;e--){
                        posibles.push(posibles.front());
                        posibles.pop();
                    }
                }
                cout<<"Hecho, reemplazando por: "<<posibles.front()<<endl;
                result+=posibles.front()+" ";
            }
            else{
                cout<<"Posibles correcciones: No hay en el diccionario"<<endl;
            }
        }
        else{
            result+=*it+" ";
        }
    }
    archivo<<result;
    cout<<"\nArchivo 'output.txt' creado con exito"<<endl;
}

int main() {
 
    std::unordered_map <int, std::string> dictionary;
    ifstream file;
    file.open("engmix.txt");
    string word;
    int i = 1;
    while(file>>word)
    {
        dictionary.insert(std::make_pair(i, word));
        cout << i << "palabra." << endl;
        i++;
        
    }

    std::unordered_map <int, std::string> input;
    ifstream input1;
    input1.open("input.txt");
    std::string word2;
    //int i = 1;
    while(input1>>word2)
    {
        input.insert(std::make_pair(i, word2));
    }
    correccion(input, dictionary);

    return 0;
}