#ifndef CHAINE_H
#define CHAINE_H

#include "Tableau.h"

/// <summary>
/// Définit une chaîne dynamique de caractères
/// </summary>
class CChaine : public CEntite
{
public:
	/// <summary>
	/// Modalité de comparaison d'une chaîne avec une autre, basé sur un ordonnancement croissant stricte (cf. strcmp)
	/// </summary>
	static const char ComparaisonStricte = 0;

	/// <summary>
	/// Modalité de comparaison d'une chaîne avec une autre, basé sur un ordonnancement croissant sans distinction de casse (cf. stricmp/strcasecmp)
	/// </summary>
	static const char ComparaisonIC = 1;

	/// <summary>
	/// Modalité de comparaison d'une chaîne avec une autre, basé sur un ordonnancement croissant sans distinction d'accentuation
	/// </summary>
	static const char ComparaisonIA = 2;

	/// <summary>
	/// Modalité de comparaison d'une chaîne avec une autre, basé sur un ordonnancement croissant sans distinction de casse et d'accentuation
	/// </summary>
	static const char ComparaisonICA = 3;

public:
	/// <summary>
	/// Transformation de chaîne : aucune transformation
	/// </summary>
	static const char AucuneTransformation = 0;

	/// <summary>
	/// Transformation de chaîne : suppression des espaces superflus de début et de fin
	/// </summary>
	static const char SuppressionEspacesSuperflus = 1;

	/// <summary>
	/// Transformation de chaîne : remplacement des majuscules par des minuscules
	/// </summary>
	static const char EnMinuscule = 2;

	/// <summary>
	/// Transformation de chaîne : remplacement des minuscules par des majuscules
	/// </summary>
	static const char EnMajuscule = 4;

public:
	/// <summary>
	/// Constante indiquant que l'on accepte (à priori) aucun caractère
	/// </summary>
	static const char RienAccepter = 0;

	/// <summary>
	/// Constante indiquant que l'on accepte les chiffres décimaux
	/// </summary>
	static const char AccepterChiffres = 1;

	/// <summary>
	/// Constante indiquant que l'on accepte les lettres non accentuées
	/// </summary>
	static const char AccepterLettresNA = 2;

	/// <summary>
	/// Constante indiquant que l'on accepte les lettres accentuées
	/// </summary>
	static const char AccepterLettresAC = 4;

	/// <summary>
	/// Constante indiquant que l'on accepte toutes les lettres (accentuées et non accentuées)
	/// </summary>
	static const char AccepterLettres = AccepterLettresNA | AccepterLettresAC;

	/// <summary>
	/// Constante indiquant que l'on accepte les séparateurs usuels entre les mots (espace, apostrophe et tiret)
	/// </summary>
	static const char AccepterSeparateursMot = 8;

	/// <summary>
	/// Constante indiquant que l'on accepte tous les caractères usuels d'un mot (mot simple ou composé)
	/// </summary>
	static const char AccepterMot = AccepterLettres | AccepterSeparateursMot;

	/// <summary>
	/// Constante indiquant que l'on accepte les caractères de ponctuation d'une phrase (virgule, point-virgule, deux points, point, point d'exclamation et point d'interrogation)
	/// </summary>
	static const char AccepterPonctuations = 16;

	/// <summary>
	/// Constante indiquant que l'on accepte tous les caractères usuels d'une phrase
	/// </summary>
	static const char AccepterPhrase = AccepterMot | AccepterPonctuations;

public:
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entité de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalité de comparaison spécifiée sert comme critère d'unicité de telles entités au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à tester</param>
	/// <returns>Vrai si cette modalité de comparaison sert comme critère d'unicité, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les données de cette entité sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entité à utiliser optionnellement pour tester la validité de l'entité pour laquelle cette méthode est appelée</param>
	/// <returns>Vrai si cette entité est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Compare cette entité à celle passée en paramètre, selon la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="autreEntite">Autre entité à laquelle on compare celle pour laquelle cette méthode est appelée, et ce, selon la modalité de comparaison spécifiée</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
	/// <returns>-1 si cette entité est "inférieure" à l'autre entité, 1 si cette entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
	int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;

public:
	/// <summary>
	/// Constructeur par défaut
	/// </summary>
	CChaine();

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Chaîne source de cette copie</param>
	CChaine(const CChaine& source);

	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être copiée dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de début et de fin de chaîne doivent être supprimés ou non</param>
	CChaine(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être copiée dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) à appliquer lors de cette initialisation de chaîne</param>
	CChaine(const char* chaine, char transformation);

	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="caractere">Caractère devant être utilisés pour remplir cette chaîne à son initialisation</param>
	/// <param name="repetition">Nombre de fois que ce caractère doit être répété lors du remplissage de cette chaîne</param>
	CChaine(char caractere, long repetition);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CChaine();

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par remplacement de son contenu
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être copiée dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de début et de fin de chaîne doivent être supprimés ou non</param>
	/// <returns>Vrai si la modification a pu être réalisée, sinon faux</returns>
	bool Modifier(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par remplacement de son contenu
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être copiée dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) à appliquer</param>
	/// <returns>Vrai si la modification a pu être réalisée, sinon faux</returns>
	bool Modifier(const char* chaine, char transformation);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par remplacement de son contenu
	/// </summary>
	/// <param name="caractere">Caractère devant être utilisés pour remplir cette chaîne</param>
	/// <param name="repetition">Nombre de fois que ce caractère doit être répété lors du remplissage de cette chaîne</param>
	/// <returns>Vrai si la modification a pu être réalisée, sinon faux</returns>
	bool Remplir(char caractere, long repetition);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par remplacement de son contenu selon un format
	/// </summary>
	/// <param name="format">Chaîne de format à utiliser pour redéfinir le contenu de cette chaîne</param>
	/// <returns>Vrai si la modification a pu être réalisée, sinon faux</returns>
	bool ModifierF(const char* format, ...);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par concaténation à son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être concaténée dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de début et de fin de chaîne doivent être supprimés ou non</param>
	/// <returns>Vrai si la concaténation a pu être réalisée, sinon faux</returns>
	bool Concatener(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par concaténation à son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="chaine">Chaîne de caractères devant être concaténée dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) à appliquer</param>
	/// <returns>Vrai si la concaténation a pu être réalisée, sinon faux</returns>
	bool Concatener(const char* chaine, char transformation);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par concaténation à son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="caractere">Caractère devant être utilisés pour compléter cette chaîne</param>
	/// <param name="repetition">Nombre de fois que ce caractère doit être répété lors du remplissage de cette chaîne</param>
	/// <returns>Vrai si la concaténation a pu être réalisée, sinon faux</returns>
	bool Concatener(char caractere, long repetition);

	/// <summary>
	/// Permet de modifier cette chaîne de caractères par concaténation à son contenu actuel, d'un contenu additionnel selon un format
	/// </summary>
	/// <param name="format">Chaîne de format à utiliser pour compléter le contenu de cette chaîne</param>
	/// <returns>Vrai si la concaténation a pu être réalisée, sinon faux</returns>
	bool ConcatenerF(const char* format, ...);

	/// <summary>
	/// Compare cette entité à celle passée en paramètre, selon la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="autreChaine">Autre chaîne à laquelle on compare celle pour laquelle cette méthode est appelée, et ce, selon la modalité de comparaison spécifiée</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
	/// <returns>-1 si cette entité est "inférieure" à l'autre entité, 1 si cette entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
	int Comparer(const char* autreChaine, char modaliteComparaison) const;

	/// <summary>
	/// Retourne la longueur actuelle de cette chaîne
	/// </summary>
	/// <returns>Longueur actuelle de cette chaîne si elle est définie, sinon 0</returns>
	long Longueur() const;

	/// <summary>
	/// Retourne le contenu de cette chaîne pour consultation
	/// </summary>
	/// <returns>Adresse de début du contenu de cette chaîne si elle est définie, sinon l'adresse d'une chaîne constante vide</returns>
	const char* Contenu() const;

	/// <summary>
	/// Indique si cette chaîne est définie ou non
	/// </summary>
	/// <returns>Vrai si cette chaîne est définie (allocation réalisée), sinon faux</returns>
	bool EstDefinie() const;

private:
	/// <summary>
	/// Membre contenant le nombre actuel de caractères de cette chaîne
	/// </summary>
	long m_Longueur;

	/// <summary>
	/// Membre contenant l'adresse de début de ce tableau de caractères
	/// </summary>
	char* m_Adresse;

private:
	/// <summary>
	/// Ensemble des lettres accentuées en majuscule
	/// </summary>
	static const char LettresAccentueesEnMajuscule[];

	/// <summary>
	/// Ensemble des lettres accentuées en majuscule transformées par suppression de leur accent
	/// </summary>
	static const char LettresAccentueesEnMajuscule_SansAccent[];

	/// <summary>
	/// Ensemble des lettres accentuées en majuscule transformées en minuscule
	/// </summary>
	static const char LettresAccentueesEnMajuscule_EnMinuscule[];

	/// <summary>
	/// Ensemble des lettres accentuées en minuscule
	/// </summary>
	static const char LettresAccentueesEnMinuscule[];

	/// <summary>
	/// Ensemble des lettres accentuées en minuscule transformées par suppression de leur accent
	/// </summary>
	static const char LettresAccentueesEnMinuscule_SansAccent[];

	/// <summary>
	/// Ensemble des lettres accentuées en minuscule transformées en majuscule
	/// </summary>
	static const char LettresAccentueesEnMinuscule_EnMajuscule[];

public:
	/// <summary>
	/// Vérifie si le caractère spécifié est un chiffre décimal
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est un chiffre décimal, sinon faux</returns>
	static bool EstChiffre(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre, sinon faux</returns>
	static bool EstLettre(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre en majuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre en majuscule, sinon faux</returns>
	static bool EstLettreMajuscule(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre en minuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre en minuscule, sinon faux</returns>
	static bool EstLettreMinuscule(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre non accentuée
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre, sinon faux</returns>
	static bool EstLettreNonAccentuee(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre accentuée
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre accentuée, sinon faux</returns>
	static bool EstLettreAccentuee(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre non accentuée en majuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre non accentuée en majuscule, sinon faux</returns>
	static bool EstLettreMajusculeNonAccentuee(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre non accentuée en minuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre non accentuée en minuscule, sinon faux</returns>
	static bool EstLettreMinusculeNonAccentuee(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre accentuée en majuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre non accentuée en majuscule, sinon faux</returns>
	static bool EstLettreMajusculeAccentuee(char caractere);

	/// <summary>
	/// Vérifie si le caractère spécifié est une lettre accentuée en minuscule
	/// </summary>
	/// <param name="caractere">Caractère à tester</param>
	/// <returns>Vrai si le caractère testé est une lettre accentuée en minuscule, sinon faux</returns>
	static bool EstLettreMinusculeAccentuee(char caractere);

	/// <summary>
	/// Retourne le caractère spécifiée, en respectant la casse, mais débarassé de tout accent
	/// </summary>
	/// <param name="caractere">Caractère à "transformer" si nécessaire</param>
	/// <returns>Caractère sans accent</returns>
	static char CaractereNonAccentue(char caractere);

	/// <summary>
	/// Retourne le caractère spécifiée, en respectant son accentuation si nécessaire, mais écrit en majuscule
	/// </summary>
	/// <param name="caractere">Caractère à "transformer" si nécessaire</param>
	/// <returns>Caractère écrit en majuscule</returns>
	static char CaractereEnMajuscule(char caractere);

	/// <summary>
	/// Retourne le caractère spécifiée, en respectant son accentuation si nécessaire, mais écrit en minuscule
	/// </summary>
	/// <param name="caractere">Caractère à "transformer" si nécessaire</param>
	/// <returns>Caractère écrit en minuscule</returns>
	static char CaractereEnMinuscule(char caractere);

	/// <summary>
	/// Teste l'égalité stricte des deux caractères spécifiés
	/// </summary>
	/// <param name="caractere1">Caractère à tester</param>
	/// <param name="caractere2">Autre caractère à tester</param>
	/// <returns>Vrai si les deux caractères sont égaux de manière stricte, sinon faux</returns>
	static bool CaracteresSontEgaux(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'égalité sans distinction de casse des deux caractères spécifiés
	/// </summary>
	/// <param name="caractere1">Caractère à tester</param>
	/// <param name="caractere2">Autre caractère à tester</param>
	/// <returns>Vrai si les deux caractères sont égaux sans distinction de casse, sinon faux</returns>
	static bool CaracteresSontEgaux_IC(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'égalité sans distinction d'accentuation des deux caractères spécifiés
	/// </summary>
	/// <param name="caractere1">Caractère à tester</param>
	/// <param name="caractere2">Autre caractère à tester</param>
	/// <returns>Vrai si les deux caractères sont égaux sans distinction d'accentuation, sinon faux</returns>
	static bool CaracteresSontEgaux_IA(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'égalité sans distinction de casse et d'accentuation des deux caractères spécifiés
	/// </summary>
	/// <param name="caractere1">Caractère à tester</param>
	/// <param name="caractere2">Autre caractère à tester</param>
	/// <returns>Vrai si les deux caractères sont égaux sans distinction de casse et d'accentuation, sinon faux</returns>
	static bool CaracteresSontEgaux_ICA(char caractere1, char caractere2);

	/// <summary>
	/// Compare de manière stricte les deux caractères spécifiés
	/// </summary>
	/// <param name="caractere1">Caractère à comparer</param>
	/// <param name="caractere2">Autre caractère à comparer</param>
	/// <returns>-1 si le premier caractère spécifié est plus petit que l'autre caractère, 1 si le premier caractère spécifié est plus grand que l'autre caractère, sinon 0</returns>
	static int ComparerCaractere(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caractères spécifiés sans distinction de casse
	/// </summary>
	/// <param name="caractere1">Caractère à comparer</param>
	/// <param name="caractere2">Autre caractère à comparer</param>
	/// <returns>-1 si le premier caractère spécifié est plus petit que l'autre caractère, 1 si le premier caractère spécifié est plus grand que l'autre caractère, sinon 0</returns>
	static int ComparerCaractere_IC(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caractères spécifiés sans distinction d'accentuation
	/// </summary>
	/// <param name="caractere1">Caractère à comparer</param>
	/// <param name="caractere2">Autre caractère à comparer</param>
	/// <returns>-1 si le premier caractère spécifié est plus petit que l'autre caractère, 1 si le premier caractère spécifié est plus grand que l'autre caractère, sinon 0</returns>
	static int ComparerCaractere_IA(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caractères spécifiés sans distinction de casse et d'accentuation
	/// </summary>
	/// <param name="caractere1">Caractère à comparer</param>
	/// <param name="caractere2">Autre caractère à comparer</param>
	/// <returns>-1 si le premier caractère spécifié est plus petit que l'autre caractère, 1 si le premier caractère spécifié est plus grand que l'autre caractère, sinon 0</returns>
	static int ComparerCaractere_ICA(char caractere1, char caractere2);

	/// <summary>
	/// Retourne la longueur de la chaîne spécifiée
	/// <para>Version "sécurisée" de strlen vis à vis du pointeur NULL</para>
	/// </summary>
	/// <param name="chaine">Chaîne dont on veut déterminer la longueur</param>
	/// <param name="sansTenirCompteEspacesSuperflus">Indique si on doit ignorer ou pas les espaces superflus de début et de fin de chaîne</param>
	/// <returns>Longueur de la chaîne si elle existe, sinon 0</returns>
	static long LongueurChaine(const char* chaine, bool sansTenirCompteEspacesSuperflus = false);

	/// <summary>
	/// Compare les deux chaînes spécifiées
	/// <para>Version "sécurisée" de strcmp vis à vis des pointeurs NULL, avec possibilité d'ignorer les différences de casse et/ou d'ignorer les différences d'accentuation</para>
	/// </summary>
	/// <param name="chaine1">Chaîne "1" à comparer</param>
	/// <param name="chaine2">Chaîne "2" à comparer</param>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les différences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les différences d'accentuation</param>
	/// <returns>-1 si la chaîne "1" est plus petite que la chaîne "2", 1 si la chaîne "1" est plus grande que la chaîne "2", sinon 0</returns>
	static int ComparerChaine(const char* chaine1, const char* chaine2, bool ignorerCasse, bool ignorerAccentuation);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée n'est constituée que de caractères parmi ceux autorisés
	/// </summary>
	/// <param name="chaine">Chaîne à tester</param>
	/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
	/// <param name="caracteresAcceptables">Chaîne contenant les caractères acceptables</param>
	/// <param name="caracteresInterdits">Chaîne contenant les caractères spécifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
	/// <returns>Vrai si tous les caractères de la chaîne respecte les prescriptions spécifiées, sinon faux</returns>
	static bool ChaineRespecte(const char* chaine, char acceptation, const char* caracteresAcceptables = NULL, const char* caracteresInterdits = NULL);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée représente une valeur réelle (ou entière)
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à tester</param>
	/// <returns>Vrai si la chaîne spécifiée représente une valeur réelle, sinon faux</returns>
	static bool EstReel(const char* chaine);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée représente une valeur réelle (ou entière)
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à tester</param>
	/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement où se trouver le séparateur décimal dans la chaîne testée, sinon NULL</param>
	/// <returns>Vrai si la chaîne spécifiée représente une valeur réelle, sinon faux</returns>
	static bool EstReel(const char* chaine, const char*& separateurDecimal);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée représente une valeur réelle (ou entière)
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à tester</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement où se trouver le séparateur décimal dans la chaîne testée, sinon NULL</param>
	/// <returns>Vrai si la chaîne spécifiée représente une valeur réelle, sinon faux</returns>
	static bool EstReel(const char* chaine, const char*& messageErreur, const char*& separateurDecimal);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur réelle
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnReel(const char* chaine, double& valeur);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur réelle
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnReel(const char* chaine, const char*& messageErreur, double& valeur);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée représente une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à tester</param>
	/// <returns>Vrai si la chaîne spécifiée représente une valeur entière, sinon faux</returns>
	static bool EstEntier(const char* chaine);

	/// <summary>
	/// Permet de vérifier si la chaîne spécifiée représente une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à tester</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <returns>Vrai si la chaîne spécifiée représente une valeur entière, sinon faux</returns>
	static bool EstEntier(const char* chaine, const char*& messageErreur);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, long& valeur);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, const char*& messageErreur, long& valeur);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, __int64& valeur);

	/// <summary>
	/// Tente de convertir la chaîne spécifiée en une valeur entière
	/// </summary>
	/// <param name="chaine">Chaîne de caractères à convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la chaîne spécifiée a pu être convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, const char*& messageErreur, __int64& valeur);

private:
	/// <summary>
	/// Définit un type de données pour les fonctions capables de tester l'égalité entre deux caractères
	/// </summary>
	typedef bool(*TesteurEgaliteCaracteres)(char, char);

	/// <summary>
	/// Définit un type de données pour les fonctions capables de comparer deux caractères
	/// </summary>
	typedef int(*ComparateurCaracteres)(char, char);

	/// <summary>
	/// Retourne la fonction de test d'égalité entre deux caractères en fonction des options spécifiées
	/// </summary>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les différences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les différences d'accentuation</param>
	/// <returns>Fonction de test d'égalité entre deux caractères en fonction des options spécifiées</returns>
	static TesteurEgaliteCaracteres ObtenirTesteurEgaliteCaracteres(bool ignorerCasse, bool ignorerAccentuation);

	/// <summary>
	/// Retourne la fonction de comparaison entre deux caractères en fonction des options spécifiées
	/// </summary>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les différences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les différences d'accentuation</param>
	/// <returns>Fonction de comparaison entre deux caractères en fonction des options spécifiées</returns>
	static ComparateurCaracteres ObtenirComparateurCaracteres(bool ignorerCasse, bool ignorerAccentuation);
};

/// <summary>
/// Définit le modèle de CChaine lors de l'instanciation d'un objet CTableau pour y stocker des entités de type CChaine
/// </summary>
class CRegleSurChaine : public CChaine
{
public:
	/// <summary>
	/// Indique si la modalité de comparaison spécifiée sert comme critère d'unicité de telles entités au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à tester</param>
	/// <returns>Vrai si cette modalité de comparaison sert comme critère d'unicité, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les données de cette entité sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entité à utiliser optionnellement pour tester la validité de l'entité pour laquelle cette méthode est appelée</param>
	/// <returns>Vrai si cette entité est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Permet de tester la validité de l'entité spécifiée en paramètre
	/// <para>La réécriture de cette méthode n'a d'intérêt que si cette classe sert entre autre d'entité validatrice, et donc à priori, à définir l'entité par défaut d'un tableau</para>
	/// </summary>
	/// <param name="entiteATester">Entité à tester</param>
	/// <returns>Vrai si l'entité à tester est valide selon les règles imposées par l'entité pour laquelle cette méthode est appelée, sinon faux</returns>
	bool TesterValidite(const CEntite& entiteATester) const;

public:
	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="unicite">Indique si toutes les modalités de comparaison impliquent l'unicité ou pas</param>
	/// <param name="longueurMinimale">Longueur minimale que doit avoir toute chaîne de caractères</param>
	CRegleSurChaine(bool unicite, long longueurMinimale = 0);

	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="uniciteStricte">Indique si la modalité de comparaison stricte implique l'unicité ou pas</param>
	/// <param name="uniciteIC">Indique si la modalité de comparaison sans distinction de casse implique l'unicité ou pas</param>
	/// <param name="uniciteIA">Indique si la modalité de comparaison sans distinction d'accentuation implique l'unicité ou pas</param>
	/// <param name="uniciteICA">Indique si la modalité de comparaison sans distinction de casse et d'accentuation implique l'unicité ou pas</param>
	/// <param name="longueurMinimale">Longueur minimale que doit avoir toute chaîne de caractères</param>
	CRegleSurChaine(bool uniciteStricte, bool uniciteIC, bool uniciteIA, bool uniciteICA, long longueurMinimale = 0);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Chaîne source de cette copie</param>
	CRegleSurChaine(const CRegleSurChaine& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CRegleSurChaine();

private:
	/// <summary>
	/// Membre retenant pour chaque modalité de comparaison, si on doit appliquer un test d'unicité des chaînes de caractères
	/// </summary>
	bool m_PourUnicite[CChaine::ComparaisonICA + 1];

	/// <summary>
	/// Membre indiquant la longueur minimale que doit avoir une chaîne de caractères
	/// </summary>
	long m_LongueurMinimale;
};

/// <summary>
/// Définit un ensemble de "champs" résultant du découpage d'une chaîne de caractères en fonction d'un caractère séparateur
/// </summary>
class CChaineDecoupee : public CEntite
{
public:
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entité de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalité de comparaison spécifiée sert comme critère d'unicité de telles entités au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à tester</param>
	/// <returns>Vrai si cette modalité de comparaison sert comme critère d'unicité, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les données de cette entité sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entité à utiliser optionnellement pour tester la validité de l'entité pour laquelle cette méthode est appelée</param>
	/// <returns>Vrai si cette entité est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Compare cette entité à celle passée en paramètre, selon la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="autreEntite">Autre entité à laquelle on compare celle pour laquelle cette méthode est appelée, et ce, selon la modalité de comparaison spécifiée</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
	/// <returns>-1 si cette entité est "inférieure" à l'autre entité, 1 si cette entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
	int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;

public:
	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="chaine">Chaîne que l'on va "découper" en fonction du caractère séparateur spécifié</param>
	/// <param name="separateur">Caractère séparateur utilisé pour le découpage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ résultant du découpage doit faire l'objet d'une suppression de ces espaces superflus de début et de fin de chaîne</param>
	CChaineDecoupee(const char* chaine, char separateur = '\t', bool suppressionEspacesSuperflus = true);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Chaîne découpée qui sert de source de cette copie</param>
	CChaineDecoupee(const CChaineDecoupee& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CChaineDecoupee();

	/// <summary>
	/// Retourne le nombre de champs
	/// </summary>
	/// <returns>Nombre de champs de cette chaîne découpée</returns>
	long Nombre() const;

	/// <summary>
	/// Retourne le champ spécifié par son indice
	/// </summary>
	/// <param name="indice">Indice du champ à récupérer</param>
	/// <returns>Adresse de début de la chaîne de caractères correspondant au champ spécifié par son indice si possible, sinon l'adresse d'une chaîne vide constante</returns>
	const char* Element(long indice) const;

	/// <summary>
	/// Indique si le champ spécifié par son indice est égal à la chaîne spécifiée
	/// </summary>
	/// <param name="indice">Indice du champ à tester</param>
	/// <param name="indice">Correspondance recherchée lors du test du champ concerné</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
	/// <returns>Vrai si le champ spécifié est égal à la chaîne de caractères spécifiées, sinon faux</returns>
	bool EstEgal(long indice, const char* chaine, char modaliteComparaison = CChaine::ComparaisonStricte) const;

	/// <summary>
	/// Permet de vérifier si le champ spécifié par son indice n'est constituée que de caractères parmi ceux autorisés
	/// </summary>
	/// <param name="indice">Indice du champ à tester</param>
	/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
	/// <param name="caracteresAcceptables">Chaîne contenant les caractères acceptables</param>
	/// <param name="caracteresInterdits">Chaîne contenant les caractères spécifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
	/// <returns>Vrai si tous les caractères du champ spécifié respecte les prescriptions spécifiées, sinon faux</returns>
	bool Respecte(long indice, char acceptation, const char* caracteresAcceptables, const char* caracteresInterdits) const;

	/// <summary>
	/// Indique si le champ spécifié représente un nombre entier
	/// </summary>
	/// <param name="indice">Indice du champ à tester</param>
	/// <returns>Vrai si le champ spécifié représente une valeur entière, sinon faux</returns>
	bool EstEntier(long indice) const;

	/// <summary>
	/// Indique si le champ spécifié représente un nombre réel
	/// </summary>
	/// <param name="indice">Indice du champ à tester</param>
	/// <returns>Vrai si le champ spécifié représente une valeur réelle, sinon faux</returns>
	bool EstReel(long indice) const;

	/// <summary>
	/// Tente de convertir le champ spécifié en un nombre entier [type char]
	/// </summary>
	/// <param name="indice">Indice du champ à convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur résultant de cette conversion réussie, sinon 0</param>
	/// <returns>Vrai si le champ spécifié a pu être converti en une valeur entière, sinon faux</returns>
	bool EnEntier(long indice, char& valeur) const;

	/// <summary>
	/// Tente de convertir le champ spécifié en un nombre entier [type short]
	/// </summary>
	/// <param name="indice">Indice du champ à convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur résultant de cette conversion réussie, sinon 0</param>
	/// <returns>Vrai si le champ spécifié a pu être converti en une valeur entière, sinon faux</returns>
	bool EnEntier(long indice, short& valeur) const;

	/// <summary>
	/// Tente de convertir le champ spécifié en un nombre entier [type long]
	/// </summary>
	/// <param name="indice">Indice du champ à convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur résultant de cette conversion réussie, sinon 0</param>
	/// <returns>Vrai si le champ spécifié a pu être converti en une valeur entière, sinon faux</returns>
	bool EnEntier(long indice, long& valeur) const;

	/// <summary>
	/// Tente de convertir le champ spécifié en un nombre entier [type __int64]
	/// </summary>
	/// <param name="indice">Indice du champ à convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur résultant de cette conversion réussie, sinon 0</param>
	/// <returns>Vrai si le champ spécifié a pu être converti en une valeur entière, sinon faux</returns>
	bool EnEntier(long indice, __int64& valeur) const;

	/// <summary>
	/// Tente de convertir le champ spécifié en un nombre réel [type double]
	/// </summary>
	/// <param name="indice">Indice du champ à convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur résultant de cette conversion réussie, sinon 0.0</param>
	/// <returns>Vrai si le champ spécifié a pu être converti en une valeur réelle, sinon faux</returns>
	bool EnReel(long indice, double& valeur) const;

protected:
	/// <summary>
	/// Méthode définissant la chaîne à découper
	/// </summary>
	/// <param name="chaine">Chaîne à découper</param>
	/// <param name="separateur">Caractère séparateur utilisé pour le découpage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ résultant du découpage doit faire l'objet d'une suppression de ces espaces superflus de début et de fin de chaîne</param>
	/// <returns>Vrai si le découpage a pu se faire, sinon faux</returns>
	bool CopierChaine(const char* chaine);

	/// <summary>
	/// Méthode réalisant le découpage de la chaîne actuelle en fonction du caractère séparateur spécifié
	/// </summary>
	/// <param name="chaine">Chaîne à découper</param>
	/// <param name="separateur">Caractère séparateur utilisé pour le découpage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ résultant du découpage doit faire l'objet d'une suppression de ces espaces superflus de début et de fin de chaîne</param>
	/// <returns>Vrai si le découpage a pu se faire, sinon faux</returns>
	bool Decouper(char separateur = '\t', bool suppressionEspacesSuperflus = true);

protected:
	/// <summary>
	/// Membre retenant le nombre de caractères constitutifs du "buffer" de cette chaîne découpée
	/// </summary>
	long m_LongueurChaine;

	/// <summary>
	/// Membre retenant le nombre de caractères maximum (marqueur de fin de chaîne non compris) que l'on peut stocker dans le "buffer" de cette chaîne découpée
	/// </summary>
	long m_TailleChaine;

	/// <summary>
	/// Membre contenant l'adresse de début du "buffer" de cette chaîne découpée
	/// </summary>
	char* m_Chaine;

private:
	/// <summary>
	/// Membre retenant le nombre de champs obtenus suite au découpage
	/// </summary>
	long m_NombreChamps;

	/// <summary>
	/// Membre retenant le nombre de cases qui sont actuellement disponibles dans le tableau des adresses des champs
	/// </summary>
	long m_TailleChamps;

	/// <summary>
	/// Membre stockant l'adresse de début de chaque champ résultant du découpage
	/// </summary>
	char** m_Champs;
};

#endif//CHAINE_H
