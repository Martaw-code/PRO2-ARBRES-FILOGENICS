//
//  Especie.cc
//  PRÀCTICA PRO2 ENTREGA INTERMITJA
//

#include <iostream>
#include <string>
#include <map>
#include "Especie.hh"

using namespace std;

Especie::Especie(){}

Especie::~Especie(){}

//Assignem un identificador, i un gen (resp) al identificador i gen d'una espècie
Especie::Especie(string& identificador, string& gen) {
    this->identificador = identificador;
    this->gen = gen;
}
//Assigna a la variable local identificador un paràmetre que és un identificador
Especie::Especie(string& identificador) {
    this->identificador = identificador;
}

//Donada una cadena d'ADN de longitud n (longitud que formen els nucleòtids),
//la quantitat de k-mers subsequències possibles (de longitud k) serà com a molt de
//gen.size() - k + 1, on n = gen.size() 3-kmer: AAA ATC AGT; 5-kmer: AAAGT AATGT
void Especie::conjsub_kmers() {
    if (kmer.empty()) {
        if (k <= gen.size()) {
            //representen els kmer's
            string gen_s;
            //posem el k-kmer al subconjunt
            for (int i = 0; i < k; ++i) gen_s.push_back(gen[i]);
            //verifiquem si el map ja conté la subcadena, i simplement augmentem les vegades que apareix
            //si retorna false
            pair <map <string, int>::iterator, bool > pair1;
            
            for (int i = 0; i < gen.size() - k + 1; ++i) {
                //el map no conté la seq. concreta del kmer, doncs l'insertem perquè tenen una clau diferent
                pair1 = kmer.insert(make_pair(gen_s, 1));
                //el map ja conté el kmer doncs augmentem el nombre de vegades que apareix
                if (not pair1.second) ++pair1.first->second;
                
                gen_s.erase(gen_s.begin()); //Traïem el primer nuclòtid llegit, per llegir un nucleòtid
                gen_s.push_back(gen[i+k]); //Afegim el següent nuclòtid en el substring del gen
            }
        }
    }
}

//Calcular distàncies ∀i,j on i,j ∈ {conjunt N d'espècies}
//sabem, que kmer(g,k) de cada espècie és el conjunt de les subseqüències contigues del gen de longitud k (els k-mers del gen)
//per tant per a cada espècie volem tenir un kmer diferent
double Especie::calcular_distancies(Especie especie, Especie especie1) {
    map <string, int> mp, mp1;
    //cada espècie té un kmer diferent, tq assignarem a cadascuna un map de la forma kmer(g,k)
    especie.conjsub_kmers(), especie1.conjsub_kmers();
    mp = especie.kmer, mp1 = especie1.kmer;
    //volem calcular el minim nombre d'ocurrències(els k-mer que comparteixen les dos espècies)
    double interseccio = 0;
    //volem calcular el màxim nombre de vegades, els k-mer que tenen en total les dos espècies
    //per tant agafarem el màxim nombre possible de combinacions de kmer's de les dos espècies
    int unio = especie.gen.size() - k + 1 + especie1.gen.size() - k + 1;
    //agafarem dos iteradors per recorrer els kmer's de cada espècie
    map <string, int>::iterator it1 = mp.begin(), it2 = mp1.begin();
    while (it1 != mp.end() and it2 != mp1.end()) {
        //comparteixen una subsequencia de k-mer's
        if (it1->first == it2->first) {
            if (it1->second > it2->second) interseccio += it2->second;
            else interseccio += it1->second;
            ++it1,++it2;
        }
        else if (it1->first > it2->first) ++it2;
        else ++it1;
    }
    //del total, hi restarem els que formen part de la intersecció, perque ja estaven
    //contemplats a la unió inicialment
    unio -=interseccio;
    double distancia = (1 - (1.0*interseccio/unio))*100;
    return distancia;
}

//Usarem el valor de k(static) per calcular distàncies ∀ i,j on i,j ∈ {Conjunt N d'espècies}
int Especie::k = 0;


//k-mer es refereix a totes les subcadenes possibles de longitud k que hi ha en una cadena d'ADN.
//Fixem una longitud k que tindran les subcadenes d'ADN
void Especie::longitud_k(int long_k) {
    k = long_k;
}
//Obtenim una seqüència de nuclòtids d'ADN (el gen).Cada espècie té un gen únic.
string Especie::obtenir_gen(){
    return gen;
}
//Obtenim l'identificador de cada espècie. Cada espècie té un identificador únic
string Especie::consultar_identificador(){
    return identificador;
}
//Llegim els trets (identificador i gen de cada espècie)
void Especie::llegir() {
    cin >> identificador >> gen;
}
//Escrivim el gen de cada espècie
void Especie::escriure() const {
    cout << gen << endl;
}
