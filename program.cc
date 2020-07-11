/** @mainpage CONSTRUCCIÓ D'UN ARBRE FILOGÈNIC
 
 El nostre objectiu de la pràctica, consistirà en: Construir un programa modular, el qual ens permeti construir un arbre filogènic per un conjunt N d'espècies
 uttilitzant un mètode aproximatiu anomenat WPGMA.

I per introduir-nos en el tema, els arbres filogènics,  són diagrames i ens mostraran les hipotètiques relacions evolutives d'un conjunt d'espècies.
 \n També cal recalcar que en cap cas seran fets definitius, provats, sinó hipòtesis de com possiblement van evolucionar a partir d'un avantapassat en comú. \n
 Per poder generar un arbre, sempre necessitarem la informació obtinguda a partir de comparar i analitzar moltes característiques de les espècies, com també les proteïnes i les seqüències d'ADN. \n
 Ja que si podem seqüenciar l'ADN, ens permetrà, augmentar l'habilitat de comparar gens entre espècies.
 
 \n Trobarem les espècies a les fulles de l'arbre, i formaran juntes les arrels de l'arbre i per identificar un avantpassat en comú, en aquesta pràctica, per nosaltres serà un punt de ramificació, un node,
 una intersecció on divergiran dos grups de descendència. \n
 
 Introduirem les classes:  <em>Especie </em>, <em> Cjt_Especies </em>,  <em> Cluster </em> i  <em> Cjt_Clusters </em>
 */
 /** @file program.cc
     @brief Programa principal per la pràctica  <em> Construcció d'un arbre filogènic </em>.
 */

#include "Cluster.hh"
#include "Cjt_Especies.hh"
#include "Cjt_Clusters.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif
using namespace std;


/** @brief Programa principal  <em> Construcció d'un arbre filogènic </em>.
*/
int main() {
    
    string tasca;
    Cjt_Especies ConjuntEspecies;
    Cjt_Clusters ConjuntClusters;
    int k; //fixem la longitud k de totes les subcadenes possibles en una cadena d'ADN
    cin >> k;
    Especie::longitud_k(k);
    
    while (cin >> tasca and tasca != "fin") {
        
        if (tasca == "lee_cjt_especies") {
            cout << "# lee_cjt_especies" << endl;
            int n;
            cin >> n; // n >= 0; n = nombre d'espècies que llegirem
            string identificador, gen; //cada espècie amb identificador, i gen
            ConjuntEspecies.llegir_conjunt_especies(n);
        }
        
        else if (tasca == "crea_especie") {
            string identificador, gen;
            cin >> identificador >> gen;
            cout << "# crea_especie " << identificador << ' ' << gen << endl;
            //verifiquem si no tenim l'espècie al conjunt, si és així, la incloem
            if (not ConjuntEspecies.existeix_especie(identificador)) {
                Especie especie(identificador,gen);
                ConjuntEspecies.afegir_especie(especie);
            }
            //l'espècie ja la tenim al conjunt i no cal afegir-la
            else cout << "ERROR: La especie " << identificador << " ya existe." << endl;
        }
        
        else if (tasca == "obtener_gen") {
            string identificador;
            cin >> identificador;
            cout << "# obtener_gen " << identificador << endl;
            //abans de mirar si podrem trobar el gen d'una espècie, comprovem si existeix
            if (ConjuntEspecies.existeix_especie(identificador)) {
                cout << ConjuntEspecies.consultar_Especie(identificador).obtenir_gen() << endl;
            }
            //no podem obtenir el gen, ja que no existeix l'espècie
            else cout << "ERROR: La especie " << identificador << " no existe." << endl;
        }
        
        else if (tasca == "distancia") {
            string identificador, identificador1;
            cin >> identificador >> identificador1;
            cout << "# distancia " << identificador << ' ' << identificador1 << endl;
            //cap espècie amb identificador1 i identificador existirà, per tant no sabrem les distàncies entre elles
            if (not ConjuntEspecies.existeix_especie(identificador) and not ConjuntEspecies.existeix_especie(identificador1)) {
                cout << "ERROR: La especie " << identificador << " y la especie " << identificador1 << " no existen." << endl;
            }
            //Altrament, o una o l'altre no existeixen
            else if (not ConjuntEspecies.existeix_especie(identificador)) {
                cout << "ERROR: La especie " << identificador << " no existe." << endl;
            }
            else if (not ConjuntEspecies.existeix_especie(identificador1)) {
                cout << "ERROR: La especie " << identificador1 << " no existe." << endl;
            }
            //com que ja hem descartat la possibilitat de que no existeixin les espècies, per tant, són al conjunt,
            //podrem calcular les distàncies entre elles sense verificar que existeixen
            else {
                cout << Especie::calcular_distancies(ConjuntEspecies.consultar_Especie(identificador),
                                                     ConjuntEspecies.consultar_Especie(identificador1)) << endl;
            }
        }
        
        else if (tasca == "elimina_especie") {
            string identificador;
            cin >> identificador;
            cout << "# elimina_especie " << identificador << endl;
            //eliminem una espècie si hi és al conjunt
            if (ConjuntEspecies.existeix_especie(identificador)) {
                ConjuntEspecies.eliminar_especie(identificador);
            }
            else cout << "ERROR: La especie " << identificador << " no existe." << endl;
        }
               
        else if (tasca == "existe_especie") {
            string identificador;
            cin >> identificador;
            cout << "# existe_especie " << identificador << endl;
            //comprovem l'existència de l'espècie
            if (ConjuntEspecies.existeix_especie(identificador)) cout << "SI" << endl;
            else cout << "NO" << endl;
        }
        
        else if (tasca == "imprime_cjt_especies") {
            cout << "# imprime_cjt_especies" << endl;
            ConjuntEspecies.escriure_cjt_especies();
        }
        
        else if (tasca == "tabla_distancias") {
            cout << "# tabla_distancias" << endl;
            ConjuntEspecies.actualitzar_Taula_Distancies();
            ConjuntEspecies.escriure_Taula_Distancies(); //escriurem les distàncies entre les espècies
        }
        
        else if (tasca == "inicializa_clusters") {
            cout << "# inicializa_clusters" << endl;
            ConjuntEspecies.inicialitzar_clusters(ConjuntClusters);
            ConjuntEspecies.inicialitzar_Taula_Distancies_C(ConjuntClusters);
            ConjuntClusters.escriure_Taula_Distancies_C();
        }
        
        else if (tasca == "ejecuta_paso_wpgma") {
            cout << "# ejecuta_paso_wpgma" << endl;
            if (ConjuntClusters.mida_Ccs() < 2) { cout << "ERROR: num_clusters <= 1" << endl;
            }
            //tenim un conjunt de clusters de com a mínim format per dos clústers i podrem aplicar el mètode
            //aproximatiu WPGMA
            else {
                ConjuntClusters.actualitzar_distancies_clusters_wpgma();
                ConjuntClusters.escriure_Taula_Distancies_C();
            }
        }
        
        else if (tasca == "imprime_cluster") {
            string identificador;
            cin >> identificador;
            cout << "# imprime_cluster " << identificador << endl;
            //primer verifiquem l'existència del cluster per després consultar-lo i escriure'l
            if (ConjuntClusters.existeix_cluster(identificador)) {
               ConjuntClusters.consultar_Cluster(identificador).escriure_cluster();
                cout << endl;
            }
            else cout << "ERROR: El cluster " << identificador << " no existe." << endl;
        }
        
        else if (tasca == "imprime_arbol_filogenetico") {
            cout << "# imprime_arbol_filogenetico" << endl;
            ConjuntEspecies.inicialitzar_clusters(ConjuntClusters);
            //el nostre conjunt de clústers no estarà buit i per tant podrem imprimir l'arbre
            //filogènic
            if (not ConjuntClusters.buit()) {
                ConjuntEspecies.inicialitzar_Taula_Distancies_C(ConjuntClusters);
                ConjuntClusters.inicialitzar_arbre_filogenic();
                ConjuntClusters.escriure_clusters();
                cout << endl;
                }
            else cout << "ERROR: El conjunto de clusters es vacio." << endl;
        }
        cout << endl;
    }
}


        
        
    
    
    
