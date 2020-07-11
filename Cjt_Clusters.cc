#include "Cjt_Clusters.hh"
#include <iostream>
using namespace std;

Cjt_Clusters::Cjt_Clusters() {}

Cjt_Clusters::~Cjt_Clusters(){}

bool Cjt_Clusters::buit() { return Conjunt_clust.empty(); }

int Cjt_Clusters::mida_Ccs() { return Conjunt_clust.size(); }

void Cjt_Clusters::inserir_clusters(string identificador, double Dist) {
    Conjunt_clust.insert(make_pair(identificador, Cluster(identificador, Dist)));
}

bool Cjt_Clusters::existeix_cluster(string identificador) {
    if (Conjunt_clust.find(identificador) != Conjunt_clust.end()) return true;
    else return false;
}

void Cjt_Clusters::buidar_taula() {Taula_Distancies_C.clear();}
   
void Cjt_Clusters::buidar_conjunt() {Conjunt_clust.clear();}

Cluster Cjt_Clusters::consultar_Cluster(string identificador) const {
    return Conjunt_clust.find(identificador)->second;
}

void Cjt_Clusters::inserir_Taula_Distancies_C(const string identificador, map<string,double>& mp) {
    Taula_Distancies_C.insert(make_pair(identificador,mp));
}

void Cjt_Clusters::escriure_clusters() const {
    for (map<string, Cluster>::const_iterator it = Conjunt_clust.begin(); it != Conjunt_clust.end(); ++it)
        it->second.escriure_cluster();
}

void Cjt_Clusters::actualitzar_distancies_clusters_wpgma() {
    //executem els tres passos de l'algoritme WPGMA, primer hem d'obtenir els dos clústers que estan a la mínima
    //en el conjunt N de clúster i obtenir-ne un de resultat que en siguí la fusió;
    //primerarment calculem la distància
    string Clust1 = Taula_Distancies_C.begin()->first;
    string Clust2 = Taula_Distancies_C[Clust1].begin()->first;
    for (map<string, map<string, double>>::iterator it = Taula_Distancies_C.begin();it != Taula_Distancies_C.end(); ++it) {
        for (map<string, double>::iterator it1 = it->second.begin();it1 != it->second.end(); ++it1) {
            if (Taula_Distancies_C[Clust1][Clust2] > it1->second) {
                Clust1 = it->first;
                Clust2 = it1->first;
            }
        }
    }
    string ClusterNou;
    ClusterNou = Clust1 + Clust2;
    pair< string, double> p;
    p = make_pair(ClusterNou, Taula_Distancies_C[Clust1][Clust2] / 2);
    
    Cluster cluster (p, Conjunt_clust.find(Clust1)->second, Conjunt_clust.find(Clust2)->second);
    Conjunt_clust.insert(make_pair(Clust2, cluster));


    Conjunt_clust.erase(Clust1); //eliminem els clústers A i B del conjunt del conjunt que conté N clústers
    Conjunt_clust.erase(Clust2);
    Conjunt_clust.insert(make_pair(ClusterNou, cluster)); //i creem el clúster resultat

    
    //darrerament podrem actualizar el contingut de la nostre Taula de Distàncies dels Clústers, i fem efectiu el canvi
    for (map<string, map<string, double>>::iterator it = Taula_Distancies_C.begin(); it->first != Clust1; ++it) {
        pair <string, double> tmp;
        tmp.second = (Taula_Distancies_C[it->first][Clust1] + Taula_Distancies_C[it->first][Clust2]) / 2;
        tmp.first = ClusterNou;
        it->second.erase(Clust1);
        it->second.insert(tmp);
        it->second.erase(Clust2);
    }
    
    for (map<string, double>::iterator it1 = Taula_Distancies_C.find(Clust1)->second.begin(); it1 != Taula_Distancies_C[Clust1].end(); ++it1) { //actualitzem la taula de distàncies
        if (it1->first != Clust2) {
            if (it1->first < Clust2) {
                it1->second = (Taula_Distancies_C[Clust1][it1->first] +
                    Taula_Distancies_C[it1->first][Clust2]) / 2;
            }
            else {
                it1->second = (Taula_Distancies_C[Clust1][it1->first] + Taula_Distancies_C[Clust2][it1->first]) / 2;
            }
        }
    }
    for (map<string, map<string, double>>::iterator it = Taula_Distancies_C.find(Clust1);it->first != Clust2; ++it) it->second.erase(Clust2); //podem actualitzar la taula de distàncies
    pair<string, map<string, double> > pair3;
    pair3.first = ClusterNou;
    pair3.second = Taula_Distancies_C[Clust1];
    Taula_Distancies_C.erase(Clust1);
    Taula_Distancies_C.erase(Clust2);
    Taula_Distancies_C.insert(pair3);
}
    

void Cjt_Clusters::inicialitzar_arbre_filogenic() {
    while (Conjunt_clust.size() != 1) actualitzar_distancies_clusters_wpgma();
}

void Cjt_Clusters::escriure_Taula_Distancies_C(){
    if (Conjunt_clust.empty()) Taula_Distancies_C.clear();
    for (map<string,map<string,double> >::iterator it = Taula_Distancies_C.begin(); it != Taula_Distancies_C.end(); ++it) {
        cout << it->first << ':';
        for (map<string,double>::iterator it1 = Taula_Distancies_C[it->first].begin(); it1 != Taula_Distancies_C[it->first].end(); ++it1) {
            cout << ' ' << it1->first <<  " (" << it1->second << ')';
        }
        cout << endl;
    }
}
