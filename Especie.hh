/** @file Especie.hh
    @brief Especificació de la classe Especie
*/

#ifndef Especie_hh // Així evitem errors de compilat cada vegada que l'incloem moltes vegades
#define Especie_hh

#ifndef NO_DIAGRAM // El Doxyfile no inclou les clases en els diagrames modulares, nogensmenys el compilador c++ sí
#include <iostream>
#include <string>
#include <map>
using namespace std;
#endif

/**
   CLASSE ESPÈCIE
*/

/** @class Especie
    @brief Representa una espècie al nostre arbre filogènic.
        Conté operacions per crear una espècie per defecte o amb un gen i un  identificador, o identificador. També per  comporvar si existeix una espècie, calular els k-mers,
        i també calcula les distàncies entre dues espècies diferents.  També podem obtenir el gen, i l'identificador d'una espècie, com així  també consultar els k-mer's. I ens llegeix i
        i escriu (resp) l'identificador i el gen i ens retorna el gen de l'espècie.
*/

class Especie {
    private:
    
    /** @brief És el gen que estarà associat a l'espècie */
    string gen;
    
    /** @brief És la longitud, que li direm k on k > 0, de les subseqüencies de la seqüència que representa el gen */
    static int k;
    
    /** @brief Aquí tenim la seqüencia dels k-mers on un k-mer és kmer(g,k) on g és una seqüència d'ADN i k és la long. de les sub seqüències del gen */
    map<string,int> kmer;
    
    /** @brief És l'dentificador  que estarà associat a l'espècie */
    string identificador;

    public:
    
    //Constructora
    
    /** @brief Constructora per defecte
     
        S'executa automàticament al declarar una espècie
        \pre <em> cert </em>
        \post El resultat és una espècie
        Time Complexity: O(1)
     
     */
    
    Especie();
    
    //Constructora
    
    /** @brief Constructora que retornarà una espècie amb un identificador i un gen
     
        \pre <em> cert </em>
        \post El resultat és una espècie amb un identificador i un gen associat
     
     */
    
    Especie(string& identifcador,string& gen);
    
    //Constructora
    
    /** @brief Constructora que retornarà una espècie amb un identificador
     
        \pre <em> cert, és una espècie que no té un identificador associat</em>
        \post El resultat és una espècie amb un identificador
     
     */
    
    Especie(string& identificador);
    
    //Destructora
    
    /** @brief Esborra automaticament els objectes locals en sortir d'un ambit de visibilitat, és la destructora per defecte d'espècie  */

    ~Especie();
    
    //Modificadores
    
    /**
       @brief Calcularem els kmer's, és a dir el conjunt de kmer(gen,k) que correspondrà a un instància de la classe.
        Els k-mers seran el conjunt de las subseqüències contigues del gen de longitud k (los k-mers del gen)
     
       \pre <em> Cada espècie li assiganrem un gen, del qual farem els kmer(gen,k) de longitd k </em>
       \post El resultat serà el conjunt de kmer's d'una seqüència d'ADN.
     
    */

    void conjsub_kmers();
    
    /**
       @brief Calcularem la distància entre un parell d'espècies al nostre arbre filogènic
        Posarem la distància com a static, perquè l'usarem al llarg de tot el programa en les diverses classes
       \pre <em> Ambdues espècies tindran tant  un identificador vàlid, com un gen associat vàlid </em>
       \post El resultat serà la distància entre dues espècies de l'arbre.
     
    */
    
    static double calcular_distancies(Especie especie, Especie especie1);
    
    /**
        @brief Podem assiganar el valor de la constant k, que és la longitud d'una subseqüencia del kmer a totes les instàncies d'espècie
        \pre <em> cert </em>
        \post Assignem a totes les instàncies d'espècie una longitud de cada subseqüència i li diem long_k
     
     */
    
    static void longitud_k(int long_k);

    //Consultores
    
    /** @brief Obtenim el gen associat a una espècie
    
       \pre <em> cert </em>
       \post El resultat és el gen del p.i, que és l'espècie
     
    */
    
    string obtenir_gen();
    
    /** @brief Obtenim l'identificador associat a una espècie
    
       \pre <em> cert </em>
       \post El resultat és l'dentificador del p.i de l'espècie
     
    */
    
    string consultar_identificador();
    
    //Lectura i escriptura
    
    /** @brief Operació de lectura d'una espècie
        \pre <em>  Hi ha preparat al canal estàndard d'entrada un identificador i un gen que són dos strings </em>
        \post El paràmetre implícit contindrà l'identifcador i el gen
     
     */
    
    void llegir();
    
    //Lectura i escriptura
    
    /** @brief Operació d'escriptura d'una espècie
        \pre <em>  cert </em>
        \post Escriurem pel canal de sortida estàndard, el gen associat a l'espècie
     */
    
    void escriure() const;
    
};
#endif /* Especie_hh */
