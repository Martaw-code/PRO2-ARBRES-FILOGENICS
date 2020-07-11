/** @file Cluster.hh
    @brief Especificació de la classe Cluster
*/
#ifndef Cluster_hh
#define Cluster_hh


#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include "BinTree.hh"
#endif

/**
   CLASSE CLÚSTER
*/

/** @class Cluster
    @brief Representa un cluster al nostre arbre filogènic.
        Conté operacions per
*/

class Cluster {
    private:
    
    BinTree <pair <string, double > > Ccluster;
    
    public:
    
    //Constructora
    
    /** @brief Constructora per defecte
     
        S'executa automàticament al declarar un conjunt de Clústers
        \pre <em> cert </em>
        \post El resultat és un clúster buit.
        \ Time Complexity: O(1)
     
     */
    Cluster();
    
    //Destructora
      /** @brief Esborra automaticament els objectes locals en sortir d'un ambit de visibilitat, és a dir és  la destructora per defecte de la classe Cluster */

    ~Cluster();
    
    //Constructora
    
    /** @brief És la constructora d'un clúster amb la distància i els identificadors dels seus fills
     
        \pre <em> cert </em>
        \post El resultat és un clúster amb la seva identtificador i la seva distància amb els fills.
        
     */
    
    Cluster(string identificador, double distClust);
    
    //Constructora
    
    /** @brief És la constructora d'un clúster a partir del BinTree
     
        \pre <em> cert </em>
        \post El resultat és un clúster creat a partir del binTree.
        
     */
    
    Cluster(const BinTree< pair<string, double> > & Ccluster);
    
    //Constructora
    
    /** @brief És la constructora d'un clúster a partir del BinTree
    
        \pre <em> cert </em>
        \post El resultat és un clúster amb dos fills, cada intersecció de la descendència, el node, conté l'identificador i distància amb els dos fills
        
     */
    
    Cluster(string identificador, double distClust, const BinTree< pair<string, double> > & esquerra, const BinTree< pair<string, double> >& dreta);
    
    //Constructora
    
    /** @brief És la constructora d'un clúster
     
        \pre <em> cert </em>
        \post El resultat és un clúster amb dos fills Clústers
     */
    
    Cluster(pair<string, double>& tmp, const Cluster& Clust1, const Cluster& Clust2);

    
    //Escriptura
    
    /** @brief Imprimeix el contingut d'un Clúster
    
       \pre <em> cert </em>
       \post Podem treure per pantalla el clúster resultant
    */
    
    void escriure_cluster() const;
    
};
#endif
