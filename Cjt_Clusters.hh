/** @file Cjt.Clusters.hh
    @brief Especificació de la classe Cjt_Clusters
 */

#ifndef Cjt_Clusters_hh
#define Cjt_Clusters_hh

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#endif

/**
    CLASSE CONJUNT DE CLÚSTERS
 */

/** @class Cjt_Clusters
    @brief Representa un conjunt de clústers al nostre arbre filogènic.
        Conté operacions per inicialitzar clústers, mirar la mida d'un clúster,  mirar si és un clúster buit,  executar l'algoritme WPGMA i "consultar
        clústers en punts intermedis de l'arbre per saber-ne la identificació de les espècies que conté "
*/

class Cjt_Clusters {
    private:
    /** @brief Tenim un map que guardarà el Conjunt de Clústers */
    map<string,Cluster> Conjunt_clust;
    /** @brief Tenim un map amb les distàncies entre los Clústers */
    map<string,map <string,double> > Taula_Distancies_C;
    
    public:
    
    //Constructora
    
    /** @brief Constructora per defecte
     
        S'executa automàticament al declarar un conjunt de Clústers
        \pre <em> cert </em>
        \post El resultat és un conjunt de clústers buit.
        \ Time Complexity: O(1)
     
     */
     Cjt_Clusters();
    
    //Destructora
    /** @brief Esborra automaticament els objectes locals en sortir d'un ambit de visibilitat */

    ~Cjt_Clusters();
    
    //Consultora
    
    /**@brief Volem comprovar si existeix un clúster del conjunt amb un cert identificador
        \pre <em> Tenim un conjunt de clústers no buit </em>
        \post Retorna true si existeix el clúster amb l'identificador, altrament retorna false si no existeix
    */
    
    bool existeix_cluster(string identificador);
    
    //Consultora
    
    /**@brief Comprovem si tenim un conjunt buit de Clústers
        \pre <em> Tenim un conjunt de clústers inicialitzat, o buit </em>
        \post Retorna el false si el conjunt és buit, cert si conté algun clúster
        
    */
    
    bool buit();
    
    //Mofidicadora
    
    /**@brief Retornem la taula de distàncies de Clústers buida

        \pre <em> cert </em>
        \post Retorna la Taula de Distàncies de clústers buida
        
    */
    
    void buidar_taula();
    
    //Mofidicadora
    
    /**@brief Retornem el Conjunt de Clústers buit
        \pre <em> cert </em>
        \post Retorna el Conjunt de Clústers buit
        
    */
    
    void buidar_conjunt();
    
    //Consultora
    
    /**@brief Volem comprovar la mida del  Conjunt de Clústers
        \pre <em> cert </em>
        \post Retorna el nombre de clústers que conté el conjunt
        
    */
    
    int mida_Ccs();
    
    //Modificadora
    
    /** @brief Volem inserir un clúster en el Conjunt de Clústers
        \pre <em> cert </em>
        \post El resultat és l'adició d'un clúster al Conjunt de Clústers
        
    */
    
    void inserir_clusters(string identificador, double Dist);
    
    //Modificadora
    
    /** @brief Executa el mètode aproximatiu WPGMA
        \pre <em> cert </em>
        \post El resultat és la fusió dels dos Clusters a menor distància en un sol Clúster y actualizem el canvi a la Taula de
            distàncies
     
    */
    
    void actualitzar_distancies_clusters_wpgma();
    
    //Modificadora
    
    /** @brief Inserta a la Taula de les distàncies dels Clústers les dades que hem obtingut des del Cjt_Espècies
        \pre <em> cert </em>
        \post La Taula de distàncies dels Clusters conté les dades que ha rebut des del Cjt_d'Espècies
     
    */
    
    void inserir_Taula_Distancies_C(const string identificador, map<string, double>& mp);
    
    //Consultora
    
    /** @brief Consultem un clúster del Conjunt de Clústers
        \pre <em> cert </em>
        \post Retornem el Clúster del conjutn que busquem amb l'identificador
     
    */
    
    Cluster consultar_Cluster(string identificador) const;
    
    //Modificadora
    
    /** @brief Ens permetrà crear un arbre filogènic a través del Conjunt de Clústers
        \pre <em> Tenim un conjunt de Clústers no buit</em>
        \post Obtenim un únic clúster a partir de l'execució del mètode aproximatiu WPGMA
        
    */
    
    void inicialitzar_arbre_filogenic();
    
    //Escriptura
       
    /** @brief Traiem pel canal de sortida el contingut de la Taula de Distàncies dels Clusters
           \pre <em> cert </em>
           \post Retornem el contingut de la Taula a través del canal estàndard de sortida.
        
    */
    
    void escriure_Taula_Distancies_C();

    //Escriptura
    
    /** @brief Traiem pel canal de sortida el contingut d'un clúster
        \pre <em> cert </em>
        \post Retornem l'hipotètic diagrama del clúster a través del canal estàndard de sortida
     
    */
    
    void escriure_clusters() const;
    
};
#endif
