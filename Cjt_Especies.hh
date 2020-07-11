/** @file Cjt_Especies.hh
    @brief Especificació de la classe Conjunt d'Espècies
*/

#ifndef Cjt_Especies_hh // Així evitem errors de compilat cada vegada que l'incloem moltes vegades
#define Cjt_Especies_hh

#ifndef NO_DIAGRAM // El Doxyfile no inclou les clases en els diagrames modulars, nogensmenys el compilador c++ sí
#include <iostream>
#include <string>
#include <map>
using namespace std;
#endif

#include "Especie.hh"
#include "Cjt_Clusters.hh"
/**
   CLASSE CONJUNT ESPÈCIES
*/

/** @class Conjunt Espècies
    @brief Representa un conjunt d'espècies del nostre arbre filogènic.
        Conté operacions per llegir un conjunt d'espècies, afegir una espècie al conjunt, eliminar una espècie del conjunt, comprovar si existeix una espècie, eliminar una espècie
        del conjunt d'esppècies, i també per inicialitzar la taula de distàncies, actualizar la taula distàncies i escriure-la. També imprimim el conjunt d'espècies.
*/

class Cjt_Especies {
    
    private:
    
    /** @brief Tenim un conjunt d'espècies, ordenat segons l'identificador de cada espècie i la corresponent Espècie del conjunt en un map */
    map<string,Especie> Conjunt_esp;
    /** @brief Tindrem un map de maps, que contindrà la Taula de les distàncies i emmagatzemarem les distàncies d'una espècie a la resta del conjunt*/
    map<string,map<string,double> > Taula_Distancies;
    /** @brief Tindrem un map que ens servirà de registre per actualitzar la Taula de distàncies, segons afegim una espècies o l'eliminem*/
    map <string,bool> Canvis_Taules;
    
    public:
    
    //Constructora
    
    /** @brief Constructora per defecte
     
        S'executa automàticament al declarar un conjunt d'espècies
        \pre <em> cert </em>
        \post El resultat és un conjunt d'espècies
        \ Time Complexity: O(1)
     */
    
    Cjt_Especies();
    
    //Destructora
    
    /** @brief Esborra automaticament els objectes locals en sortir d'un ambit de visibilitat, en aquest cas, és la destrcutora per defecte del Conjunt d'Espècies */
    
    ~Cjt_Especies();
    
    //Modificadores
    
    /** @brief Afageix una espècie al conjunt d'espècies amb un cert identificador (id), si ja existeix,
               retorna un missatge d'error.
     
         \pre Cjt_Espècies está inicializada i afegeix una espècie que aparentment no està al conjunt
         \post Afegeix una espècie amb un cert identificador al conjunt d'espècies
    */
    
    void afegir_especie(Especie& especie);
    
    /** @brief Elimina una espècie del conjunt d'espècies
     
         \pre Cjt_Espècies está inicializada
         \post Elimina una espècie amb un identificador del conjunt d'espècies. Altrament si la espècie ja existeix, escriu un missatge dient que amb
               l'identificador donat no existeix tal espècie al conjunt.
     
    */
    
    void eliminar_especie(string& identificador);
    
    
    //Modificadores Taula de Distàncies
      
      /** @brief Ens permetrà tenir les dades de la Taula de Distàncies a la nova Taula de Distàncies, que en aquest cas serà la Taula de Distàncies de Clústers
           \pre <em> cert </em>
           \post El resultat serà una taula de Distàncies emmagatzemada amb les dades rebudes de la Taula de Distàncies
       
      */
      
      void inicialitzar_Taula_Distancies_C(Cjt_Clusters& ConjClust);
    
     //Modificadores Clúster
    
    /** @brief Ens permet inicialitzar el Cjt_Clusters donat el Cjt_Espècies
         \pre <em> cert </em>
         \post El resultat serà el Cjt_Clusters inicialittzat
     
    */
    
     void inicialitzar_clusters(Cjt_Clusters& ConjClust);
    
    //Consultores
    
    /** @brief Comprova si existeix una espècie al conjunt d'espècies
     
         \pre Cjt_Espècies está inicializada, <em> cert </em>
         \post Retorna cert si existeix una espècie amb l'identificador i altrament, retorna fals
     
    */
    
    bool existeix_especie(string& identificador);
    
    //Consultores
    
    /** @brief Comprova si existeix una espècie al conjunt d'espècies i ens retorna l'espècie segons l'identificador
         \pre Cjt_Espècies está inicializada, <em> cert </em>
         \post Retorna l'espècie espècie amb l'identificador
     
    */
    
    Especie consultar_Especie(string& identificador);
    
    //Modificadores Taula de Distàncies
    
   /** @brief Afegim una nova espècie a la Taula de Distàncies a través de l'identificador
         \pre Cert, sí, tenim una espècie que no existeix
         \post El resultat és la Taula de Distàncies amb l'espècie insertada
     
    */
    
    void afegir_Taula_Distancies(string identificador);
    
    //Modificadores Taula de Distàncies
     
    /** @brief Borrem una espècie de la Taula de Distàncies a través de l'identificador
          \pre Cert, sí, tenim una espècie que existeix
          \post El resultat és la Taula de Distàncies sense l'espècie eliminada
      
     */
    
    void borrar_Taula_Distancies(string identificador);
    
    //Modificadores Taula de Distàncies
    
    /** @brief Actualitzem la Taula de Distàncies
         \pre <em> cert </em>
         \post El resultat és la Taula de Distàncies amb les modificacions condicionades
     
    */

    void actualitzar_Taula_Distancies();
    
    //Lectura
    
    /** @brief Llegim des del canal d'entrada un conjunt d'espècies
        \pre Llegim al canal d'entrada un enter n >= 0 i seguidament un conjunt d'espècies, les n espècies, tenen
        dos strings associats, un identificador i un gen,  cadascún únic per a cada espècies diferent. És a dir dues espècies,
        seran diferents si, i només si, tenen un gen o un identificador diferents. Els continguts previs del conjunt d'espècies els esborrem.
        \post El resultat serà un conjunt n d'espècies que passaran a formar part del conjunt d'espècies.
     
     */
    
    void llegir_conjunt_especies(int n);
    
    //Escriptura
    
    /** @brief Imprimim el conjunt d'espècies. Si el conjunt d'espècies és buit, no imprimirà res.
        \pre El conjunt d'espècies està inicialitzat i pot ser buit
        \post Retorna el conjunt d'espècies si el conjunt és no buit, altrament no retorna res.
     
     */
    
    void escriure_cjt_especies() const;

    //Escriptura Taula De Distàncies
    
    /** @brief Imprimim la Taula de Distàncies entre cada espècie i la resta d'espècies del conjunt d'espècies.
        \pre Tenim un Conjunt d'espècies, pot ser buit
        \post Imprimeix la taula de distàncies si el conjunt és no buit, o altrament no imprimeix res
     */
    
    void escriure_Taula_Distancies();
    
};
#endif /* Cjt_Especies_hh */

