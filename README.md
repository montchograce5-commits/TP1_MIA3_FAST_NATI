Gestion d'une bibliothèque universitaire 📚

Application console développée en C++ dans le cadre d'un projet de programmation orientée objet (POO).

Ce projet permet de gérer les livres, les étudiants et les opérations d'emprunt et de retour au sein d'une bibliothèque universitaire.

Fonctionnalités

- Ajouter et consulter des livres.
- Enregistrer et consulter des étudiants.
- Emprunter un livre.
- Retourner un livre.
- Vérifier la disponibilité des livres.
- Consulter l'historique des emprunts.
- Empêcher les emprunts multiples d'un même livre simultanément.

Concepts techniques

- Programmation orientée objet (POO).
- Classes et objets.
- Attributs et méthodes.
- Constructeurs.
- Encapsulation.
- Associations entre classes.
- Cardinalités UML.
- Vecteurs et pointeurs en C++.

Technologies utilisées

- Langage : C++
- Standard : C++17
- Compilation : G++ (MinGW)
- Modélisation : UML / PlantUML

Structure du projet

Le projet repose sur quatre classes principales :

- "Livre"
- "Etudiant"
- "Emprunt"
- "Bibliotheque"

Objectif du projet

Mettre en pratique les principes fondamentaux de la programmation orientée objet à travers la conception et le développement d'une application de gestion de bibliothèque universitaire.



🎓 Gestion des Inscriptions Universitaires

📌 Présentation du projet

Gestion des Inscriptions Universitaires est une application console développée en C++ dans le cadre d'un travail pratique (TP) sur la programmation orientée objet (POO).

L'objectif est de faciliter la gestion et le suivi des inscriptions académiques au sein d'une université.

L'application permet au service de scolarité d'enregistrer les étudiants, de gérer leurs inscriptions et de consulter les informations académiques.

🚀 Fonctionnalités

- Enregistrement d'une inscription académique.
- Association d'un étudiant à une filière et à un niveau.
- Vérification des inscriptions en double.
- Recherche d'un étudiant par matricule.
- Affichage de la liste des étudiants inscrits.
- Consultation des inscriptions par année académique.
- Sauvegarde automatique des données dans un fichier texte.
- Chargement des données au démarrage de l'application.
- Attribution automatique des identifiants d'inscription.
- Gestion des erreurs de saisie.

🛠️ Technologies utilisées

- Langage : C++
- Paradigme : Programmation orientée objet (POO).
- Standard : C++98.
- Structures de données : Vector.
- Persistance des données : Fichiers texte.
- IDE : Dev-C++ / Visual Studio Code.

🏗️ Architecture du projet

Le système repose sur six classes principales :

Classe| Responsabilité
Etudiant| Gestion des informations personnelles.
Inscription| Gestion des inscriptions académiques.
Filiere| Gestion des filières universitaires.
Niveau| Gestion des niveaux d'études.
AnneeAcademique| Gestion des années académiques.
Scolarite| Gestion des opérations d'inscription.

⚙️ Installation et exécution

1. Cloner le dépôt :

git clone URL_DU_DEPOT

2. Accéder au dossier :

cd Gestion-des-Inscriptions-Universitaires

3. Compiler le programme :

g++ -std=c++98 main.cpp -o gestion

4. Exécuter :

./gestion

Sous Windows :

gestion.exe

💾 Sauvegarde des données

Les inscriptions sont conservées dans un fichier "inscriptions.txt".

Les données sont automatiquement chargées au démarrage et sauvegardées après chaque nouvelle inscription.

🎯 Objectifs pédagogiques

Ce projet permet de mettre en pratique :

- La création et l'utilisation des classes et des objets.
- L'encapsulation.
- Les constructeurs.
- Les associations entre classes.
- Les tableaux dynamiques avec "vector".
- Les boucles et les structures conditionnelles.
- La manipulation des fichiers en C++.
- La modélisation UML.

🔮 Améliorations futures

- Gestion des paiements des frais universitaires.
- Authentification des agents de scolarité.
- Génération automatique des attestations d'inscription.
- Interface graphique.
- Utilisation d'une véritable base de données.

👩‍💻 Auteur

Projet académique réalisé dans le cadre d'un travail pratique en programmation orientée objet avec C++.

---

Statut : Version initiale fonctionnelle et évolutive.
