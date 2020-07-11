#include "Cluster.hh"
#include <iostream>
using namespace std;


Cluster::Cluster(const BinTree<pair<string, double> >& Cluster) {Ccluster = Cluster;}

Cluster::Cluster(string identificador, double distClust) {
    Ccluster = BinTree<pair<string, double> >(make_pair(identificador, distClust));
}

Cluster::Cluster(string identificador, double distClust, const BinTree<pair<string, double> >& esquer, const BinTree<pair<string, double> >& dret) {
    Ccluster = BinTree<pair<string, double> > (make_pair(identificador, distClust),esquer,dret);
}

Cluster::Cluster(pair<string, double>& tmp, const Cluster& Clust1, const Cluster& Clust2) {
    BinTree< pair<string, double> > esquer(make_pair(Clust1.Ccluster.value().first, Clust1.Ccluster.value().second),Clust1.Ccluster.left(),Clust1.Ccluster.right());
    BinTree< pair<string, double> > dret(make_pair(Clust2.Ccluster.value().first,
        Clust2.Ccluster.value().second), Clust2.Ccluster.left(), Clust2.Ccluster.right());
    Ccluster = BinTree< pair<string, double> >(tmp, esquer, dret);
}

Cluster::~Cluster() {}

void Cluster::escriure_cluster() const {
    if (not Ccluster.empty()) {
        cout << '[';
        double distClust = Ccluster.value().second;
        if (distClust >= 0) cout << '(';
        cout << Ccluster.value().first;
        if (distClust >= 0) cout << ", " << distClust << ") ";
        Cluster ClusterEsquer(Ccluster.left());
        Cluster ClusterDret(Ccluster.right());
        ClusterEsquer.escriure_cluster();
        ClusterDret.escriure_cluster();
        cout << ']';
    }
}


