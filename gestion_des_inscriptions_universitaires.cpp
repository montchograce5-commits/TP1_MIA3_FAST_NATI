#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

// ==================================================
// CLASSE ETUDIANT
// ==================================================

class Etudiant {
private:
    string matricule;
    string nom;
    string prenom;
    string email;

public:
    Etudiant() {}

    Etudiant(string m, string n, string p, string e) {
        matricule = m;
        nom = n;
        prenom = p;
        email = e;
    }

    string getMatricule() const {
        return matricule;
    }

    string getNom() const {
        return nom;
    }

    string getPrenom() const {
        return prenom;
    }

    string getEmail() const {
        return email;
    }

    void afficherInformations() const {
        cout << "Matricule : " << matricule << endl;
        cout << "Nom       : " << nom << endl;
        cout << "Prenom    : " << prenom << endl;
        cout << "Email     : " << email << endl;
    }
};


// ==================================================
// CLASSE FILIERE
// ==================================================

class Filiere {
private:
    int idFiliere;
    string nomFiliere;

public:
    Filiere(int id, string nom) {
        idFiliere = id;
        nomFiliere = nom;
    }

    string getNomFiliere() const {
        return nomFiliere;
    }
};


// ==================================================
// CLASSE NIVEAU
// ==================================================

class Niveau {
private:
    int idNiveau;
    string libelle;

public:
    Niveau(int id, string l) {
        idNiveau = id;
        libelle = l;
    }

    string getLibelle() const {
        return libelle;
    }
};


// ==================================================
// CLASSE ANNEE ACADEMIQUE
// ==================================================

class AnneeAcademique {
private:
    int idAnnee;
    string libelle;

public:
    AnneeAcademique(int id, string l) {
        idAnnee = id;
        libelle = l;
    }

    string getLibelle() const {
        return libelle;
    }
};


// ==================================================
// CLASSE INSCRIPTION
// ==================================================

class Inscription {
private:
    int idInscription;
    string dateInscription;
    string statut;

    Etudiant etudiant;
    Filiere filiere;
    Niveau niveau;
    AnneeAcademique annee;

public:

    Inscription(int id, string date, string s,
                Etudiant e, Filiere f,
                Niveau n, AnneeAcademique a)
        : etudiant(e), filiere(f), niveau(n), annee(a) {

        idInscription = id;
        dateInscription = date;
        statut = s;
    }

    int getId() const {
        return idInscription;
    }

    string getMatricule() const {
        return etudiant.getMatricule();
    }

    string getAnnee() const {
        return annee.getLibelle();
    }

    const Etudiant& getEtudiant() const {
        return etudiant;
    }

    string getFiliere() const {
        return filiere.getNomFiliere();
    }

    string getNiveau() const {
        return niveau.getLibelle();
    }

    string getDate() const {
        return dateInscription;
    }

    string getStatut() const {
        return statut;
    }

    void afficherInscription() const {

        cout << "\n====================================\n";

        cout << "IDENTIFIANT INSCRIPTION : "
             << idInscription << endl;

        etudiant.afficherInformations();

        cout << "Filiere : " << filiere.getNomFiliere() << endl;
        cout << "Niveau : " << niveau.getLibelle() << endl;
        cout << "Annee academique : " << annee.getLibelle() << endl;
        cout << "Date d'inscription : " << dateInscription << endl;
        cout << "Statut : " << statut << endl;

        cout << "====================================\n";
    }
};


// ==================================================
// FONCTIONS DE SAISIE
// ==================================================

string lireChamp(string message) {

    string valeur;

    while (true) {

        cout << message;
        getline(cin, valeur);

        if (valeur.find_first_not_of(" \t") == string::npos) {
            cout << "Erreur : ce champ est obligatoire.\n";
            continue;
        }

        if (valeur.find('|') != string::npos) {
            cout << "Erreur : le caractere | est interdit.\n";
            continue;
        }

        return valeur;
    }
}


int lireChoix() {

    string ligne;
    int choix;

    while (true) {

        cout << "\nVotre choix : ";
        getline(cin, ligne);

        stringstream ss(ligne);

        if (ss >> choix) {

            ss >> ws;

            if (ss.eof()) {
                return choix;
            }
        }

        cout << "Erreur : veuillez saisir un nombre valide.\n";
    }
}


// ==================================================
// CLASSE SCOLARITE
// ==================================================

class Scolarite {

private:

    vector<Inscription> inscriptions;

    int prochainId;

    string nomFichier;


    // ----------------------------------------------
    // DECOUPER UNE LIGNE DU FICHIER
    // ----------------------------------------------

    vector<string> decouper(string ligne) {

        vector<string> champs;
        string champ;
        stringstream ss(ligne);

        while (getline(ss, champ, '|')) {
            champs.push_back(champ);
        }

        return champs;
    }


    // ----------------------------------------------
    // SAUVEGARDER LES DONNEES
    // ----------------------------------------------

    bool sauvegarder() const {

        ofstream fichier(nomFichier.c_str());

        if (!fichier) {
            cout << "Erreur : impossible d'ouvrir le fichier.\n";
            return false;
        }

        int j;

        for (j = 0; j < (int)inscriptions.size(); j++) {

            const Inscription& i = inscriptions[j];

            fichier
                << i.getId() << "|"
                << i.getMatricule() << "|"
                << i.getEtudiant().getNom() << "|"
                << i.getEtudiant().getPrenom() << "|"
                << i.getEtudiant().getEmail() << "|"
                << i.getFiliere() << "|"
                << i.getNiveau() << "|"
                << i.getAnnee() << "|"
                << i.getDate() << "|"
                << i.getStatut()
                << endl;
        }

        if (!fichier) {
            cout << "Erreur pendant la sauvegarde.\n";
            return false;
        }

        fichier.close();

        return true;
    }


    // ----------------------------------------------
    // RECHERCHER UN ETUDIANT DEJA ENREGISTRE
    // ----------------------------------------------

    bool trouverEtudiant(string matricule,
                         Etudiant& resultat) const {

        int j;

        for (j = 0; j < (int)inscriptions.size(); j++) {

            if (inscriptions[j].getMatricule() == matricule) {

                resultat = inscriptions[j].getEtudiant();

                return true;
            }
        }

        return false;
    }


public:

    // ----------------------------------------------
    // CONSTRUCTEUR
    // ----------------------------------------------

    Scolarite() {

        prochainId = 1;

        nomFichier = "inscriptions.txt";

        chargerDonnees();
    }


    // ----------------------------------------------
    // CHARGER LES DONNEES AU DEMARRAGE
    // ----------------------------------------------

    void chargerDonnees() {

        ifstream fichier(nomFichier.c_str());

        if (!fichier) {
            cout << "Aucune sauvegarde precedente.\n";
            return;
        }

        string ligne;

        int lignesIgnorees = 0;

        while (getline(fichier, ligne)) {

            vector<string> c = decouper(ligne);

            if (c.size() != 10) {
                lignesIgnorees++;
                continue;
            }

            int id = atoi(c[0].c_str());

            if (id <= 0 ||
                c[1].empty() ||
                c[2].empty() ||
                c[3].empty() ||
                c[4].empty() ||
                c[5].empty() ||
                c[6].empty() ||
                c[7].empty() ||
                c[8].empty() ||
                c[9].empty()) {

                lignesIgnorees++;
                continue;
            }

            Etudiant e(c[1], c[2], c[3], c[4]);

            Filiere f(1, c[5]);

            Niveau n(1, c[6]);

            AnneeAcademique a(1, c[7]);

            Inscription i(id, c[8], c[9], e, f, n, a);

            inscriptions.push_back(i);

            if (id >= prochainId) {
                prochainId = id + 1;
            }
        }

        fichier.close();

        cout << inscriptions.size()
             << " inscription(s) chargee(s).\n";

        if (lignesIgnorees > 0) {
            cout << lignesIgnorees
                 << " ligne(s) incorrecte(s) ignoree(s).\n";
        }
    }


    // ----------------------------------------------
    // VERIFIER UNE INSCRIPTION
    // ----------------------------------------------

    bool verifierInscription(string matricule,
                             string annee) const {

        int j;

        for (j = 0; j < (int)inscriptions.size(); j++) {

            if (inscriptions[j].getMatricule() == matricule &&
                inscriptions[j].getAnnee() == annee) {

                return true;
            }
        }

        return false;
    }


    // ----------------------------------------------
    // ENREGISTRER UNE INSCRIPTION
    // ----------------------------------------------

    void ajouterInscription() {

        cout << "\n===== NOUVELLE INSCRIPTION =====\n";

        string matricule;
        string nom;
        string prenom;
        string email;
        string filiere;
        string niveau;
        string annee;
        string date;

        matricule = lireChamp("Matricule : ");

        annee = lireChamp("Annee academique : ");

        if (verifierInscription(matricule, annee)) {

            cout << "\nCet etudiant est deja inscrit pour cette annee.\n";

            return;
        }

        Etudiant e;

        if (trouverEtudiant(matricule, e)) {

            cout << "\nEtudiant deja connu du systeme.\n";

            cout << "Informations existantes :\n";

            e.afficherInformations();
        }

        else {

            nom = lireChamp("Nom : ");

            prenom = lireChamp("Prenom : ");

            email = lireChamp("Email : ");

            e = Etudiant(matricule, nom, prenom, email);
        }

        filiere = lireChamp("Filiere : ");

        niveau = lireChamp("Niveau : ");

        date = lireChamp("Date d'inscription : ");

        Filiere f(1, filiere);

        Niveau n(1, niveau);

        AnneeAcademique a(1, annee);

        Inscription i(prochainId, date, "Validee",
                      e, f, n, a);

        inscriptions.push_back(i);

        if (sauvegarder()) {

            prochainId++;

            cout << "\nInscription enregistree avec succes !\n";
        }

        else {

            inscriptions.pop_back();

            cout << "L'inscription n'a pas ete conservee.\n";
        }
    }


    // ----------------------------------------------
    // RECHERCHER UN ETUDIANT
    // ----------------------------------------------

    void rechercherEtudiant() {

        string matricule;

        matricule = lireChamp("Entrez le matricule : ");

        bool trouve = false;

        int j;

        for (j = 0; j < (int)inscriptions.size(); j++) {

            if (inscriptions[j].getMatricule() == matricule) {

                inscriptions[j].afficherInscription();

                trouve = true;
            }
        }

        if (!trouve) {
            cout << "\nEtudiant introuvable.\n";
        }
    }


    // ----------------------------------------------
    // AFFICHER TOUTES LES INSCRIPTIONS
    // ----------------------------------------------

    void afficherListeEtudiants() {

        if (inscriptions.empty()) {

            cout << "\nAucune inscription enregistree.\n";

            return;
        }

        cout << "\n===== LISTE DES INSCRIPTIONS =====\n";

        int j;

        for (j = 0; j < (int)inscriptions.size(); j++) {

            inscriptions[j].afficherInscription();
        }

        cout << "\nNombre total d'inscriptions : "
             << inscriptions.size() << endl;
    }


    // ----------------------------------------------
    // AFFICHER PAR ANNEE ACADEMIQUE
    // ----------------------------------------------

    void afficherParAnnee() {

        string annee;

        annee = lireChamp("Entrez l'annee academique : ");

        bool trouve = false;

        int j;

        cout << "\n===== INSCRIPTIONS : "
             << annee << " =====\n";

        for (j = 0; j < (int)inscriptions.size(); j++) {

            if (inscriptions[j].getAnnee() == annee) {

                inscriptions[j].afficherInscription();

                trouve = true;
            }
        }

        if (!trouve) {

            cout << "\nAucune inscription pour cette annee.\n";
        }
    }


    // ----------------------------------------------
    // NOMBRE TOTAL D'INSCRIPTIONS
    // ----------------------------------------------

    int nombreInscriptions() const {

        return (int)inscriptions.size();
    }
};


// ==================================================
// PROGRAMME PRINCIPAL
// ==================================================

int main() {

    Scolarite scolarite;

    int choix;

    do {

        cout << "\n";
        cout << "========================================\n";
        cout << "  GESTION DES INSCRIPTIONS UNIVERSITAIRES\n";
        cout << "========================================\n";

        cout << "1. Enregistrer une inscription\n";
        cout << "2. Rechercher un etudiant\n";
        cout << "3. Afficher toutes les inscriptions\n";
        cout << "4. Afficher par annee academique\n";
        cout << "5. Nombre total d'inscriptions\n";
        cout << "0. Quitter\n";

        choix = lireChoix();

        switch (choix) {

            case 1:
                scolarite.ajouterInscription();
                break;

            case 2:
                scolarite.rechercherEtudiant();
                break;

            case 3:
                scolarite.afficherListeEtudiants();
                break;

            case 4:
                scolarite.afficherParAnnee();
                break;

            case 5:
                cout << "\nNombre total : "
                     << scolarite.nombreInscriptions()
                     << " inscription(s).\n";
                break;

            case 0:
                cout << "\nFermeture de l'application.\n";
                break;

            default:
                cout << "\nChoix invalide.\n";
        }

    } while (choix != 0);

    return 0;
}
