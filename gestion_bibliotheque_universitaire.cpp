#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// ==========================================
// ENUMERATION : ETAT D'UN LIVRE
// ==========================================

enum class EtatLivre {
    DISPONIBLE,
    EMPRUNTE
};

// ==========================================
// CLASSE LIVRE
// ==========================================

class Livre {
private:
    string identifiant;
    string titre;
    string auteur;
    int anneePublication;
    EtatLivre etat;

public:
    // Constructeur
    Livre(string id, string t, string a, int annee)
        : identifiant(id), titre(t), auteur(a),
          anneePublication(annee),
          etat(EtatLivre::DISPONIBLE) {}

    // Getters
    string getIdentifiant() const {
        return identifiant;
    }

    string getTitre() const {
        return titre;
    }

    bool estDisponible() const {
        return etat == EtatLivre::DISPONIBLE;
    }

    // Emprunter un livre
    bool emprunter() {
        if (!estDisponible()) {
            return false;
        }

        etat = EtatLivre::EMPRUNTE;
        return true;
    }

    // Retourner un livre
    bool retourner() {
        if (estDisponible()) {
            return false;
        }

        etat = EtatLivre::DISPONIBLE;
        return true;
    }

    // Afficher les informations
    void afficherInformations() const {
        cout << "\nIdentifiant : " << identifiant;
        cout << "\nTitre : " << titre;
        cout << "\nAuteur : " << auteur;
        cout << "\nAnnee : " << anneePublication;
        cout << "\nEtat : "
             << (estDisponible() ? "Disponible" : "Emprunte");
        cout << "\n-----------------------------\n";
    }
};

// ==========================================
// CLASSE ETUDIANT
// ==========================================

class Etudiant {
private:
    string matricule;
    string nom;
    string prenom;
    string email;

public:
    // Constructeur
    Etudiant(string m, string n, string p, string e)
        : matricule(m), nom(n), prenom(p), email(e) {}

    // Getters
    string getMatricule() const {
        return matricule;
    }

    string getNomComplet() const {
        return prenom + " " + nom;
    }

    // Afficher les informations
    void afficherInformations() const {
        cout << "\nMatricule : " << matricule;
        cout << "\nNom : " << nom;
        cout << "\nPrenom : " << prenom;
        cout << "\nEmail : " << email;
        cout << "\n-----------------------------\n";
    }
};

// ==========================================
// CLASSE EMPRUNT
// ==========================================

class Emprunt {
private:
    int identifiant;
    string identifiantLivre;
    string matriculeEtudiant;
    string dateEmprunt;
    string dateRetour;

public:
    // Constructeur
    Emprunt(int id, string livre, string etudiant, string date)
        : identifiant(id),
          identifiantLivre(livre),
          matriculeEtudiant(etudiant),
          dateEmprunt(date),
          dateRetour("") {}

    int getIdentifiant() const {
        return identifiant;
    }

    string getIdentifiantLivre() const {
        return identifiantLivre;
    }

    string getMatriculeEtudiant() const {
        return matriculeEtudiant;
    }

    bool estActif() const {
        return dateRetour.empty();
    }

    void enregistrerRetour(string date) {
        dateRetour = date;
    }

    void afficherEmprunt() const {
        cout << "\nNumero emprunt : " << identifiant;
        cout << "\nIdentifiant livre : " << identifiantLivre;
        cout << "\nMatricule etudiant : " << matriculeEtudiant;
        cout << "\nDate emprunt : " << dateEmprunt;
        cout << "\nDate retour : "
             << (estActif() ? "Non retourne" : dateRetour);
        cout << "\nStatut : "
             << (estActif() ? "En cours" : "Termine");
        cout << "\n-----------------------------\n";
    }
};

// ==========================================
// CLASSE BIBLIOTHEQUE
// ==========================================

class Bibliotheque {
private:
    vector<Livre> livres;
    vector<Etudiant> etudiants;
    vector<Emprunt> emprunts;

    int prochainIdentifiantEmprunt = 1;

    // Rechercher un livre
    Livre* rechercherLivre(string id) {
        for (auto& livre : livres) {
            if (livre.getIdentifiant() == id) {
                return &livre;
            }
        }

        return nullptr;
    }

    // Rechercher un etudiant
    Etudiant* rechercherEtudiant(string matricule) {
        for (auto& etudiant : etudiants) {
            if (etudiant.getMatricule() == matricule) {
                return &etudiant;
            }
        }

        return nullptr;
    }

public:

    // Ajouter un livre
    bool ajouterLivre(Livre livre) {
        if (rechercherLivre(livre.getIdentifiant()) != nullptr) {
            cout << "Erreur : cet identifiant existe deja.\n";
            return false;
        }

        livres.push_back(livre);
        cout << "Livre ajoute avec succes.\n";
        return true;
    }

    // Ajouter un etudiant
    bool ajouterEtudiant(Etudiant etudiant) {
        if (rechercherEtudiant(etudiant.getMatricule()) != nullptr) {
            cout << "Erreur : ce matricule existe deja.\n";
            return false;
        }

        etudiants.push_back(etudiant);
        cout << "Etudiant ajoute avec succes.\n";
        return true;
    }

    // Emprunter un livre
    bool emprunterLivre(string idLivre,
                        string matricule,
                        string date) {

        Livre* livre = rechercherLivre(idLivre);
        Etudiant* etudiant = rechercherEtudiant(matricule);

        if (livre == nullptr) {
            cout << "Erreur : livre introuvable.\n";
            return false;
        }

        if (etudiant == nullptr) {
            cout << "Erreur : etudiant introuvable.\n";
            return false;
        }

        if (!livre->estDisponible()) {
            cout << "Erreur : ce livre est deja emprunte.\n";
            return false;
        }

        // Modifier l'etat du livre
        livre->emprunter();

        // Enregistrer l'emprunt
        emprunts.emplace_back(
            prochainIdentifiantEmprunt++,
            idLivre,
            matricule,
            date
        );

        cout << "Emprunt effectue avec succes.\n";
        return true;
    }

    // Retourner un livre
    bool retournerLivre(string idLivre, string date) {

        Livre* livre = rechercherLivre(idLivre);

        if (livre == nullptr) {
            cout << "Erreur : livre introuvable.\n";
            return false;
        }

        if (livre->estDisponible()) {
            cout << "Erreur : ce livre n'est pas emprunte.\n";
            return false;
        }

        // Rechercher l'emprunt actif correspondant
        for (auto& emprunt : emprunts) {

            if (emprunt.getIdentifiantLivre() == idLivre
                && emprunt.estActif()) {

                // Enregistrer la date du retour
                emprunt.enregistrerRetour(date);

                // Rendre le livre disponible
                livre->retourner();

                cout << "Livre retourne avec succes.\n";
                return true;
            }
        }

        cout << "Erreur : aucun emprunt actif trouve.\n";
        return false;
    }

    // Afficher tous les livres
    void afficherLivres() const {

        if (livres.empty()) {
            cout << "Aucun livre enregistre.\n";
            return;
        }

        for (const auto& livre : livres) {
            livre.afficherInformations();
        }
    }

    // Afficher tous les etudiants
    void afficherEtudiants() const {

        if (etudiants.empty()) {
            cout << "Aucun etudiant enregistre.\n";
            return;
        }

        for (const auto& etudiant : etudiants) {
            etudiant.afficherInformations();
        }
    }

    // Afficher tous les emprunts
    void afficherEmprunts() const {

        if (emprunts.empty()) {
            cout << "Aucun emprunt enregistre.\n";
            return;
        }

        for (const auto& emprunt : emprunts) {
            emprunt.afficherEmprunt();
        }
    }
};

// ==========================================
// FONCTION PRINCIPALE
// ==========================================

int main() {

    Bibliotheque bibliotheque;

    int choix;

    do {

        cout << "\n========== BIBLIOTHEQUE UNIVERSITAIRE ==========\n";
        cout << "1. Ajouter un livre\n";
        cout << "2. Ajouter un etudiant\n";
        cout << "3. Emprunter un livre\n";
        cout << "4. Retourner un livre\n";
        cout << "5. Afficher les livres\n";
        cout << "6. Afficher les etudiants\n";
        cout << "7. Afficher les emprunts\n";
        cout << "0. Quitter\n";
        cout << "Votre choix : ";

        if (!(cin >> choix)) {
            cout << "Erreur : saisissez un nombre valide.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string id, titre, auteur, matricule;
        string nom, prenom, email, date;
        int annee;

        switch (choix) {

            case 1:
                cout << "Identifiant du livre : ";
                getline(cin, id);

                cout << "Titre : ";
                getline(cin, titre);

                cout << "Auteur : ";
                getline(cin, auteur);

                cout << "Annee de publication : ";

                if (!(cin >> annee) || annee <= 0) {
                    cout << "Annee invalide.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bibliotheque.ajouterLivre(
                    Livre(id, titre, auteur, annee)
                );
                break;

            case 2:
                cout << "Matricule : ";
                getline(cin, matricule);

                cout << "Nom : ";
                getline(cin, nom);

                cout << "Prenom : ";
                getline(cin, prenom);

                cout << "Email : ";
                getline(cin, email);

                bibliotheque.ajouterEtudiant(
                    Etudiant(matricule, nom, prenom, email)
                );
                break;

            case 3:
                cout << "Identifiant du livre : ";
                getline(cin, id);

                cout << "Matricule de l'etudiant : ";
                getline(cin, matricule);

                cout << "Date d'emprunt (JJ/MM/AAAA) : ";
                getline(cin, date);

                bibliotheque.emprunterLivre(id, matricule, date);
                break;

            case 4:
                cout << "Identifiant du livre : ";
                getline(cin, id);

                cout << "Date de retour (JJ/MM/AAAA) : ";
                getline(cin, date);

                bibliotheque.retournerLivre(id, date);
                break;

            case 5:
                bibliotheque.afficherLivres();
                break;

            case 6:
                bibliotheque.afficherEtudiants();
                break;

            case 7:
                bibliotheque.afficherEmprunts();
                break;

            case 0:
                cout << "Fermeture du programme.\n";
                break;

            default:
                cout << "Choix invalide.\n";
        }

    } while (choix != 0);

    return 0;
}
