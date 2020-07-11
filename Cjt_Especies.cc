#include "Cjt_Especies.hh"


Cjt_Especies::Cjt_Especies() {}

Cjt_Especies::~Cjt_Especies() {}



void Cjt_Especies::llegir_conjunt_especies(int n) {
    Conjunt_esp.clear(); //ens assegurem de buidar els conjunts previs cada vegada que llegim un nou conjunt
    Taula_Distancies.clear(); //també les distàncies per calcular les noves
    Canvis_Taules.clear(); //reestablim qualsevol possible canvi fet durant l'actualització de les taules de la distància
    Especie especie;
    for (int i = 0; i < n; ++i) {
        especie.llegir();
        afegir_especie(especie);
    }
}

void Cjt_Especies::afegir_especie(Especie& especie) {
    pair<map<string,Especie>::iterator, bool > tmp_pair;
    tmp_pair = Conjunt_esp.insert(make_pair(especie.consultar_identificador(), especie));
    if (tmp_pair.second) Canvis_Taules.insert(make_pair(especie.consultar_identificador(), true)); //bool = true --> afegim espècie i
    //queda constància al map que enregistra els canvis de la Taula
}

void Cjt_Especies::eliminar_especie(string& identificador) {
    if (Conjunt_esp.find(identificador) != Conjunt_esp.end()) {
        Conjunt_esp.erase(identificador);
        Canvis_Taules.insert(make_pair(identificador, false)); //eliminem de la taula de canvis l'espècie amb l'identficador desitjat
        //per posteriorment, actualitzar la taula de les distàncies; bool = false --> eliminar espècie
    }
}

Especie Cjt_Especies::consultar_Especie(string& identificador) {
    return Conjunt_esp.find(identificador)->second;
}


bool Cjt_Especies::existeix_especie(string& identificador) {
    if (Conjunt_esp.find(identificador) != Conjunt_esp.end()) return true;
    else return false;
}

void Cjt_Especies::afegir_Taula_Distancies(string identificador) {
    Taula_Distancies[identificador];
    for (map<string, map<string,double > >::iterator it = Taula_Distancies.begin(); it != Taula_Distancies.end();++it) {
        pair<string,string> tmp;
        tmp.first = min(identificador,it->first), tmp.second = max(identificador,it->first);
        if (it->first < identificador) tmp.first = it->first, tmp.second = identificador;
        else tmp.first = identificador, tmp.second = it->first;
        if (it->first != identificador) {
            Taula_Distancies[tmp.first][tmp.second] = Especie::calcular_distancies(Conjunt_esp.find(it->first)->second, Conjunt_esp.find(identificador)->second); //guardem la distància de les espècies del map amb l'espècie afegida
        }
    }
}

void Cjt_Especies::borrar_Taula_Distancies(string identificador) {
    Taula_Distancies.erase(identificador);
    for (map<string,map<string, double> >::iterator it = Taula_Distancies.begin(); it != Taula_Distancies.end(); ++it) {
        it->second.erase(identificador);
    }
}

void Cjt_Especies::actualitzar_Taula_Distancies() {
    map<string,bool>::iterator it = Canvis_Taules.begin(); //els canvis que hem enregistrat a afegir espècie i borrar espècie
    //ens serviran per canviar la Taula de Distàncies, actualitzar-la a cada canvi sofert per una inserció o per haver esborrat una espècie
    while (it != Canvis_Taules.end()) {
        if (it->second) afegir_Taula_Distancies(it->first);
        else borrar_Taula_Distancies(it->first);
        it = Canvis_Taules.erase(it);
    }
}

void Cjt_Especies::inicialitzar_Taula_Distancies_C(Cjt_Clusters& ConjClust) {
    actualitzar_Taula_Distancies();
    for (map<string, map<string,double> >::iterator it = Taula_Distancies.begin(); it != Taula_Distancies.end(); ++it) {
        ConjClust.inserir_Taula_Distancies_C(it->first,it->second);
    }
}

void Cjt_Especies::inicialitzar_clusters(Cjt_Clusters& ConjClust) {
    ConjClust.buidar_conjunt(); //abans d'inicialitzar qualsevol conjunt de clusters, buidem el conjunt anterior
    ConjClust.buidar_taula(); //buidem la taula de distàncies dels clusters per assegurar-nos que podrem operar correctament amb les noves
    //distàncies dels nous clústers
    for(map<string,Especie>::const_iterator it= Conjunt_esp.begin(); it!= Conjunt_esp.end(); it++) {
        ConjClust.inserir_clusters(it->first, -1);
    }
}

void Cjt_Especies::escriure_cjt_especies() const {
    for (map<string, Especie>::const_iterator it = Conjunt_esp.begin(); it  != Conjunt_esp.end(); ++it) {
        cout << it->first << ' ';
        it->second.escriure();
    }
}
    
void Cjt_Especies::escriure_Taula_Distancies(){
    if (Conjunt_esp.empty()) Taula_Distancies.clear(); //si el nostre conjunt és buit, podem buidar la taula de distàncies
    for (map<string,map<string,double> >::iterator it = Taula_Distancies.begin(); it != Taula_Distancies.end(); ++it) {
        cout << it->first << ':';
        for (map<string,double>::iterator it1 = Taula_Distancies[it->first].begin(); it1 != Taula_Distancies[it->first].end(); ++it1) {
            cout << ' ' << it1->first <<  " (" << it1->second << ')';
        }
        cout << endl;
    }
}
