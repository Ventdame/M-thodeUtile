#include "BisConsole.h"
#include "Chaine.h"

/// <summary>
/// Retourne le nombre de comparaisons pris en charge par toute entit� de ce type
/// </summary>
/// <returns>Nombre de comparaisons</returns>
char CChaine::NombreComparaisons() const
{
	return 4;
}

/// <summary>
/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
/// </summary>
/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
bool CChaine::EstComparaisonPourUnicite(char modaliteComparaison) const
{
	return false;
}

/// <summary>
/// Permet de cr�er un duplicata de cette entit�
/// </summary>
/// <returns>Objet cr�� dynamiquement par clonage</returns>
CEntite* CChaine::Cloner() const
{
	return new CChaine(*this);
}

/// <summary>
/// Indique si les donn�es de cette entit� sont valides
/// </summary>
/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
bool CChaine::EstValide(const CEntite* entiteValidatrice) const
{
	if (entiteValidatrice != NULL) return entiteValidatrice->TesterValidite(*this);
	return true;
}

/// <summary>
/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
/// </summary>
/// <param name="autreEntite">Autre entit� � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
int CChaine::Comparer(const CEntite& autreEntite, char modaliteComparaison) const
{
	return Comparer(((const CChaine&)autreEntite).m_Adresse, modaliteComparaison);
}

/// <summary>
/// Constructeur par d�faut
/// </summary>
CChaine::CChaine()
	:CEntite(), m_Longueur(0), m_Adresse(NULL)
{
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Cha�ne source de cette copie</param>
CChaine::CChaine(const CChaine& source)
	:CEntite(source), m_Longueur(0), m_Adresse(NULL)
{
	Modifier(source.m_Adresse);
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
CChaine::CChaine(const char* chaine, bool suppressionEspacesSuperflus)
	:CEntite(), m_Longueur(0), m_Adresse(NULL)
{
	Modifier(chaine, suppressionEspacesSuperflus);
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
/// <param name="transformation">Transformation(s) � appliquer lors de cette initialisation de cha�ne</param>
CChaine::CChaine(const char* chaine, char transformation)
	:CEntite(), m_Longueur(0), m_Adresse(NULL)
{
	Modifier(chaine, transformation);
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="caractere">Caract�re devant �tre utilis�s pour remplir cette cha�ne � son initialisation</param>
/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
CChaine::CChaine(char caractere, long repetition)
	:CEntite(), m_Longueur(0), m_Adresse(NULL)
{
	Remplir(caractere, repetition);
}

/// <summary>
/// Destructeur
/// </summary>
CChaine::~CChaine()
{
	if (m_Adresse != NULL) free(m_Adresse);
}

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Modifier(const char* chaine, bool suppressionEspacesSuperflus)
{
	return Modifier(chaine, suppressionEspacesSuperflus ? CChaine::SuppressionEspacesSuperflus : CChaine::AucuneTransformation);
}

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
/// <param name="transformation">Transformation(s) � appliquer</param>
/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Modifier(const char* chaine, char transformation)
{
	if ((transformation < CChaine::AucuneTransformation) || (transformation > (CChaine::EnMajuscule * 2 - 1))) return false;
	bool suppressionEspacesDebutFin = ((transformation & CChaine::SuppressionEspacesSuperflus) != 0);
	bool mettreEnMinuscule = ((transformation & CChaine::EnMinuscule) != 0);
	bool mettreEnMajuscule = ((transformation & CChaine::EnMajuscule) != 0);
	if (mettreEnMinuscule && mettreEnMajuscule) return false;
	// V�rification de la validit� du param�tre "entrant" (autre que l'entit�)
	if (chaine == NULL) return false;
	// Gestion de la "suppression" des espaces de d�but et de fin de cha�ne
	const char* finSource;
	if (suppressionEspacesDebutFin)
	{
		while (*chaine == ' ') chaine++;
		finSource = chaine;
		for (const char* car = chaine; *car != 0; car++)
		{
			if (*car != ' ') finSource = car;
		}
		if (*finSource) finSource++;
	}
	else
	{
		finSource = chaine + strlen(chaine);
	}
	// R�allocation de l'espace m�moire n�cessaire � la nouvelle information
	long longueurSource = (long)(finSource - chaine);
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((longueurSource + 1) * sizeof(char)) : realloc(m_Adresse, (longueurSource + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	// Copie de la nouvelle information dans l'entit�
	if (longueurSource > 0) strncpy(m_Adresse, chaine, longueurSource);
	m_Adresse[longueurSource] = 0;
	m_Longueur = longueurSource;
	// Gestion des transformations de casse
	if (mettreEnMinuscule)
	{
		for (char* car = m_Adresse; *car != 0; car++)
		{
			*car = CaractereEnMinuscule(*car);
		}
	}
	else if (mettreEnMajuscule)
	{
		for (char* car = m_Adresse; *car != 0; car++)
		{
			*car = CaractereEnMajuscule(*car);
		}
	}
	// Indication de la r�ussite de la modification de l'entit�
	return true;
}

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
/// </summary>
/// <param name="caractere">Caract�re devant �tre utilis�s pour remplir cette cha�ne</param>
/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Remplir(char caractere, long repetition)
{
	if (repetition < 0) return false;
	if (repetition == 0) return Modifier("");
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((repetition + 1) * sizeof(char)) : realloc(m_Adresse, (repetition + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	memset(m_Adresse, caractere, repetition * sizeof(char));
	m_Adresse[repetition] = 0;
	m_Longueur = repetition;
	return true;
}

__pragma(warning(push))
__pragma(warning(disable:4996))
__pragma(warning(disable:4793))
/// <summary>
/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu selon un format
/// </summary>
/// <param name="format">Cha�ne de format � utiliser pour red�finir le contenu de cette cha�ne</param>
/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::ModifierF(const char* format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	long longueurTexte = vsnprintf(NULL, 0, format, arguments);
	va_end(arguments);
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((longueurTexte + 1) * sizeof(char)) : realloc(m_Adresse, (longueurTexte + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	va_start(arguments, format);
	vsnprintf(m_Adresse, longueurTexte + 1, format, arguments);
	va_end(arguments);
	m_Longueur = longueurTexte;
	return true;
}
__pragma(warning(pop))

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre concat�n�e dynamiquement dans cet objet</param>
/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Concatener(const char* chaine, bool suppressionEspacesSuperflus)
{
	return Concatener(chaine, suppressionEspacesSuperflus ? CChaine::SuppressionEspacesSuperflus : CChaine::AucuneTransformation);
}

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
/// </summary>
/// <param name="chaine">Cha�ne de caract�res devant �tre concat�n�e dynamiquement dans cet objet</param>
/// <param name="transformation">Transformation(s) � appliquer</param>
/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Concatener(const char* chaine, char transformation)
{
	if ((m_Adresse == NULL) || (m_Longueur == 0)) return Modifier(chaine, transformation);
	// V�rification de la validit� du param�tre "entrant" (autre que l'entit�)
	if (chaine == NULL) return false;
	if (chaine[0] == 0) return true;
	// R�allocation de l'espace m�moire n�cessaire � la nouvelle information
	long longueurSource = (long)strlen(chaine);
	long longueurTexte = m_Longueur + longueurSource;
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((longueurTexte + 1) * sizeof(char)) : realloc(m_Adresse, (longueurTexte + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	// Copie de la nouvelle information dans l'entit� (ici par concat�nation)
	strcpy(m_Adresse + m_Longueur, chaine);
	m_Longueur = longueurTexte;
	// Indication de la r�ussite de la modification de l'entit�
	return true;
}

/// <summary>
/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
/// </summary>
/// <param name="caractere">Caract�re devant �tre utilis�s pour compl�ter cette cha�ne</param>
/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::Concatener(char caractere, long repetition)
{
	if ((m_Adresse == NULL) || (m_Longueur == 0)) return Remplir(caractere, repetition);
	if (repetition < 0) return false;
	if (repetition == 0) return true;
	long longueurTexte = m_Longueur + repetition;
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((longueurTexte + 1) * sizeof(char)) : realloc(m_Adresse, (longueurTexte + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	memset(m_Adresse + m_Longueur, caractere, repetition * sizeof(char));
	m_Adresse[longueurTexte] = 0;
	m_Longueur = longueurTexte;
	return true;
}

__pragma(warning(push))
__pragma(warning(disable:4996))
__pragma(warning(disable:4793))
/// <summary>
/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel selon un format
/// </summary>
/// <param name="format">Cha�ne de format � utiliser pour compl�ter le contenu de cette cha�ne</param>
/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
bool CChaine::ConcatenerF(const char* format, ...)
{
	if ((m_Adresse == NULL) && !Modifier("")) return false;
	va_list arguments;
	va_start(arguments, format);
	long longueurTexte = m_Longueur + vsnprintf(NULL, 0, format, arguments);
	va_end(arguments);
	void* nouvelleAdresse = (m_Adresse == NULL) ? malloc((longueurTexte + 1) * sizeof(char)) : realloc(m_Adresse, (longueurTexte + 1) * sizeof(char));
	if (nouvelleAdresse == NULL) return false;
	m_Adresse = (char*)nouvelleAdresse;
	va_start(arguments, format);
	vsnprintf(m_Adresse + m_Longueur, longueurTexte + 1, format, arguments);
	va_end(arguments);
	m_Longueur = longueurTexte;
	return true;
}
__pragma(warning(pop))

/// <summary>
/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
/// </summary>
/// <param name="autreChaine">Autre cha�ne � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
int CChaine::Comparer(const char* autreChaine, char modaliteComparaison) const
{
	if ((modaliteComparaison < CChaine::ComparaisonStricte) || (modaliteComparaison > CChaine::ComparaisonICA)) return 0;
	return ComparerChaine
	(
		m_Adresse,
		autreChaine,
		(modaliteComparaison == CChaine::ComparaisonIC) || (modaliteComparaison == CChaine::ComparaisonICA),
		(modaliteComparaison == CChaine::ComparaisonIA) || (modaliteComparaison == CChaine::ComparaisonICA)
	);
}

/// <summary>
/// Retourne la longueur actuelle de cette cha�ne
/// </summary>
/// <returns>Longueur actuelle de cette cha�ne si elle est d�finie, sinon 0</returns>
long CChaine::Longueur() const
{
	return m_Longueur;
}

/// <summary>
/// Retourne le contenu de cette cha�ne pour consultation
/// </summary>
/// <returns>Adresse de d�but du contenu de cette cha�ne si elle est d�finie, sinon l'adresse d'une cha�ne constante vide</returns>
const char* CChaine::Contenu() const
{
	return (m_Adresse != NULL) ? m_Adresse : "";
}

/// <summary>
/// Indique si cette cha�ne est d�finie ou non
/// </summary>
/// <returns>Vrai si cette cha�ne est d�finie (allocation r�alis�e), sinon faux</returns>
bool CChaine::EstDefinie() const
{
	return (m_Adresse != NULL);
}

/// <summary>
/// Ensemble des lettres accentu�es en majuscule
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMajuscule[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',0 };

/// <summary>
/// Ensemble des lettres accentu�es en majuscule transform�es par suppression de leur accent
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMajuscule_SansAccent[] = "AAAAAEEEEIIIIOOOOOUUUUY";

/// <summary>
/// Ensemble des lettres accentu�es en majuscule transform�es en minuscule
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMajuscule_EnMinuscule[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',0 };

/// <summary>
/// Ensemble des lettres accentu�es en minuscule
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMinuscule[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',0 };

/// <summary>
/// Ensemble des lettres accentu�es en minuscule transform�es par suppression de leur accent
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMinuscule_SansAccent[] = "aaaaaeeeeiiiiooooouuuuyyc";

/// <summary>
/// Ensemble des lettres accentu�es en minuscule transform�es en majuscule
/// </summary>
/*static*/ const char CChaine::LettresAccentueesEnMinuscule_EnMajuscule[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',0 };

/// <summary>
/// V�rifie si le caract�re sp�cifi� est un chiffre d�cimal
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est un chiffre d�cimal, sinon faux</returns>
/*static*/ bool CChaine::EstChiffre(char caractere)
{
	return (caractere >= '0') && (caractere <= '9');
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre, sinon faux</returns>
/*static*/ bool CChaine::EstLettre(char caractere)
{
	return EstLettreMajuscule(caractere) || EstLettreMinuscule(caractere);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre en majuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre en majuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMajuscule(char caractere)
{
	return EstLettreMajusculeNonAccentuee(caractere) || EstLettreMajusculeAccentuee(caractere);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre en minuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre en minuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMinuscule(char caractere)
{
	return EstLettreMinusculeNonAccentuee(caractere) || EstLettreMinusculeAccentuee(caractere);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre, sinon faux</returns>
/*static*/ bool CChaine::EstLettreNonAccentuee(char caractere)
{
	return EstLettreMajusculeNonAccentuee(caractere) || EstLettreMinusculeNonAccentuee(caractere);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre accentu�e, sinon faux</returns>
/*static*/ bool CChaine::EstLettreAccentuee(char caractere)
{
	return EstLettreMajusculeAccentuee(caractere) || EstLettreMinusculeAccentuee(caractere);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e en majuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en majuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMajusculeNonAccentuee(char caractere)
{
	return (caractere >= 'A') && (caractere <= 'Z');
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e en minuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en minuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMinusculeNonAccentuee(char caractere)
{
	return (caractere >= 'a') && (caractere <= 'z');
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e en majuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en majuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMajusculeAccentuee(char caractere)
{
	return (strchr(LettresAccentueesEnMajuscule, caractere) != NULL);
}

/// <summary>
/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e en minuscule
/// </summary>
/// <param name="caractere">Caract�re � tester</param>
/// <returns>Vrai si le caract�re test� est une lettre accentu�e en minuscule, sinon faux</returns>
/*static*/ bool CChaine::EstLettreMinusculeAccentuee(char caractere)
{
	return (strchr(LettresAccentueesEnMinuscule, caractere) != NULL);
}

/// <summary>
/// Retourne le caract�re sp�cifi�e, en respectant la casse, mais d�barass� de tout accent
/// </summary>
/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
/// <returns>Caract�re sans accent</returns>
/*static*/ char CChaine::CaractereNonAccentue(char caractere)
{
	const char* resultat = strchr(LettresAccentueesEnMajuscule, caractere);
	if (resultat != NULL)
	{
		return LettresAccentueesEnMajuscule_SansAccent[resultat - LettresAccentueesEnMajuscule];
	}
	else
	{
		resultat = strchr(LettresAccentueesEnMinuscule, caractere);
		if (resultat != NULL)
		{
			return LettresAccentueesEnMinuscule_SansAccent[resultat - LettresAccentueesEnMinuscule];
		}
		else
		{
			return caractere;
		}
	}
}

/// <summary>
/// Retourne le caract�re sp�cifi�e, en respectant son accentuation si n�cessaire, mais �crit en majuscule
/// </summary>
/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
/// <returns>Caract�re �crit en majuscule</returns>
/*static*/ char CChaine::CaractereEnMajuscule(char caractere)
{
	const char* resultat = strchr(LettresAccentueesEnMinuscule, caractere);
	if (resultat != NULL)
	{
		return LettresAccentueesEnMinuscule_EnMajuscule[resultat - LettresAccentueesEnMinuscule];
	}
	else if ((caractere >= 'a') && (caractere <= 'z'))
	{
		return caractere + ('A' - 'a');
	}
	else
	{
		return caractere;
	}
}

/// <summary>
/// Retourne le caract�re sp�cifi�e, en respectant son accentuation si n�cessaire, mais �crit en minuscule
/// </summary>
/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
/// <returns>Caract�re �crit en minuscule</returns>
/*static*/ char CChaine::CaractereEnMinuscule(char caractere)
{
	const char* resultat = strchr(LettresAccentueesEnMajuscule, caractere);
	if (resultat != NULL)
	{
		return LettresAccentueesEnMajuscule_EnMinuscule[resultat - LettresAccentueesEnMajuscule];
	}
	else if ((caractere >= 'A') && (caractere <= 'Z'))
	{
		return caractere + ('a' - 'A');
	}
	else
	{
		return caractere;
	}
}

/// <summary>
/// Teste l'�galit� stricte des deux caract�res sp�cifi�s
/// </summary>
/// <param name="caractere1">Caract�re � tester</param>
/// <param name="caractere2">Autre caract�re � tester</param>
/// <returns>Vrai si les deux caract�res sont �gaux de mani�re stricte, sinon faux</returns>
/*static*/ bool CChaine::CaracteresSontEgaux(char caractere1, char caractere2)
{
	return (caractere1 == caractere2);
}

/// <summary>
/// Teste l'�galit� sans distinction de casse des deux caract�res sp�cifi�s
/// </summary>
/// <param name="caractere1">Caract�re � tester</param>
/// <param name="caractere2">Autre caract�re � tester</param>
/// <returns>Vrai si les deux caract�res sont �gaux sans distinction de casse, sinon faux</returns>
/*static*/ bool CChaine::CaracteresSontEgaux_IC(char caractere1, char caractere2)
{
	return (CaractereEnMinuscule(caractere1) == CaractereEnMinuscule(caractere2));
}

/// <summary>
/// Teste l'�galit� sans distinction d'accentuation des deux caract�res sp�cifi�s
/// </summary>
/// <param name="caractere1">Caract�re � tester</param>
/// <param name="caractere2">Autre caract�re � tester</param>
/// <returns>Vrai si les deux caract�res sont �gaux sans distinction d'accentuation, sinon faux</returns>
/*static*/ bool CChaine::CaracteresSontEgaux_IA(char caractere1, char caractere2)
{
	return (CaractereNonAccentue(caractere1) == CaractereNonAccentue(caractere2));
}

/// <summary>
/// Teste l'�galit� sans distinction de casse et d'accentuation des deux caract�res sp�cifi�s
/// </summary>
/// <param name="caractere1">Caract�re � tester</param>
/// <param name="caractere2">Autre caract�re � tester</param>
/// <returns>Vrai si les deux caract�res sont �gaux sans distinction de casse et d'accentuation, sinon faux</returns>
/*static*/ bool CChaine::CaracteresSontEgaux_ICA(char caractere1, char caractere2)
{
	return (CaractereEnMinuscule(CaractereNonAccentue(caractere1)) == CaractereEnMinuscule(CaractereNonAccentue(caractere2)));
}

/// <summary>
/// Compare de mani�re stricte les deux caract�res sp�cifi�s
/// </summary>
/// <param name="caractere1">Caract�re � comparer</param>
/// <param name="caractere2">Autre caract�re � comparer</param>
/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
/*static*/ int CChaine::ComparerCaractere(char caractere1, char caractere2)
{
	if (((unsigned char)caractere1) < ((unsigned char)caractere2)) return -1;
	if (((unsigned char)caractere1) > ((unsigned char)caractere2)) return 1;
	return 0;
}

/// <summary>
/// Compare les deux caract�res sp�cifi�s sans distinction de casse
/// </summary>
/// <param name="caractere1">Caract�re � comparer</param>
/// <param name="caractere2">Autre caract�re � comparer</param>
/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
/*static*/ int CChaine::ComparerCaractere_IC(char caractere1, char caractere2)
{
	return ComparerCaractere(CaractereEnMinuscule(caractere1), CaractereEnMinuscule(caractere2));
}

/// <summary>
/// Compare les deux caract�res sp�cifi�s sans distinction d'accentuation
/// </summary>
/// <param name="caractere1">Caract�re � comparer</param>
/// <param name="caractere2">Autre caract�re � comparer</param>
/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
/*static*/ int CChaine::ComparerCaractere_IA(char caractere1, char caractere2)
{
	return ComparerCaractere(CaractereNonAccentue(caractere1), CaractereNonAccentue(caractere2));
}

/// <summary>
/// Compare les deux caract�res sp�cifi�s sans distinction de casse et d'accentuation
/// </summary>
/// <param name="caractere1">Caract�re � comparer</param>
/// <param name="caractere2">Autre caract�re � comparer</param>
/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
/*static*/ int CChaine::ComparerCaractere_ICA(char caractere1, char caractere2)
{
	return ComparerCaractere(tolower(CaractereNonAccentue(caractere1)), tolower(CaractereNonAccentue(caractere2)));
}

/// <summary>
/// Retourne la longueur de la cha�ne sp�cifi�e
/// <para>Version "s�curis�e" de strlen vis � vis du pointeur NULL</para>
/// </summary>
/// <param name="chaine">Cha�ne dont on veut d�terminer la longueur</param>
/// <param name="sansTenirCompteEspacesSuperflus">Indique si on doit ignorer ou pas les espaces superflus de d�but et de fin de cha�ne</param>
/// <returns>Longueur de la cha�ne si elle existe, sinon 0</returns>
/*static*/ long CChaine::LongueurChaine(const char* chaine, bool sansTenirCompteEspacesSuperflus)
{
	if (chaine == NULL) return 0;
	const char* car;
	if (sansTenirCompteEspacesSuperflus)
	{
		for (chaine; *chaine == ' '; chaine++) {}
		const char* dernierCaractereSignificatif = chaine - 1;
		for (car = chaine; *car != 0; car++)
		{
			if (*car != ' ') dernierCaractereSignificatif = car;
		}
		car = dernierCaractereSignificatif + 1;
	}
	else
	{
		for (car = chaine; *car != 0; car++) {}
	}
	return (long)(car - chaine);
}

/// <summary>
/// Compare les deux cha�nes sp�cifi�es
/// <para>Version "s�curis�e" de strcmp vis � vis des pointeurs NULL, avec possibilit� d'ignorer les diff�rences de casse et/ou d'ignorer les diff�rences d'accentuation</para>
/// </summary>
/// <param name="chaine1">Cha�ne "1" � comparer</param>
/// <param name="chaine2">Cha�ne "2" � comparer</param>
/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
/// <returns>-1 si la cha�ne "1" est plus petite que la cha�ne "2", 1 si la cha�ne "1" est plus grande que la cha�ne "2", sinon 0</returns>
/*static*/ int CChaine::ComparerChaine(const char* chaine1, const char* chaine2, bool ignorerCasse, bool ignorerAccentuation)
{
	if ((chaine1 == NULL) || (*chaine1 == 0))
	{
		return ((chaine2 == NULL) || (*chaine2 == 0)) ? 0 : 1;
	}
	else if ((chaine2 == NULL) || (*chaine2 == 0)) return -1;
	ComparateurCaracteres comparerCaracteres = ObtenirComparateurCaracteres(ignorerCasse, ignorerAccentuation);
	while (true)
	{
		if (*chaine1 == 0) return (*chaine2 == 0) ? 0 : -1;
		if (*chaine2 == 0) return 1;
		int resultat = comparerCaracteres(*chaine1, *chaine2);
		if (resultat != 0) return resultat;
		chaine1++;
		chaine2++;
	}
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e n'est constitu�e que de caract�res parmi ceux autoris�s
/// </summary>
/// <param name="chaine">Cha�ne � tester</param>
/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
/// <param name="caracteresAcceptables">Cha�ne contenant les caract�res acceptables</param>
/// <param name="caracteresInterdits">Cha�ne contenant les caract�res sp�cifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
/// <returns>Vrai si tous les caract�res de la cha�ne respecte les prescriptions sp�cifi�es, sinon faux</returns>
/*static*/ bool CChaine::ChaineRespecte(const char* chaine, char acceptation, const char* caracteresAcceptables, const char* caracteresInterdits)
{
	if (chaine == NULL) return false;
	if (*chaine == 0) return true;
	if ((acceptation < RienAccepter) || (acceptation > (AccepterPonctuations * 2 - 1))) return false;
	if ((acceptation == RienAccepter) && ((caracteresAcceptables == NULL) || (*caracteresAcceptables == 0))) return false;
	while (*chaine)
	{
		if ((caracteresInterdits != NULL) && (strchr(caracteresInterdits, *chaine) != NULL)) return false;
		bool caractereAccepte = false;
		if ((acceptation & AccepterChiffres) != 0)
		{
			caractereAccepte = (*chaine >= '0') && (*chaine <= '9');
		}
		if (!caractereAccepte && ((acceptation & AccepterLettresNA) != 0))
		{
			caractereAccepte = ((*chaine >= 'A') && (*chaine <= 'Z'))
				|| ((*chaine >= 'a') && (*chaine <= 'z'));
		}
		if (!caractereAccepte && ((acceptation & AccepterLettresAC) != 0))
		{
			caractereAccepte = EstLettreAccentuee(*chaine);
		}
		if (!caractereAccepte && ((acceptation & AccepterSeparateursMot) != 0))
		{
			caractereAccepte = (strchr(" '-", *chaine) != NULL);
		}
		if (!caractereAccepte && ((acceptation & AccepterPonctuations) != 0))
		{
			caractereAccepte = (strchr(",;:.!?", *chaine) != NULL);
		}
		if (!caractereAccepte && (caracteresAcceptables != NULL))
		{
			caractereAccepte = (strchr(caracteresAcceptables, *chaine) != NULL);
		}
		if (!caractereAccepte) return false;
		chaine++;
	}
	return true;
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � tester</param>
/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
/*static*/ bool CChaine::EstReel(const char* chaine)
{
	const char* messageErreur;
	const char* separateurDecimal;
	return EstReel(chaine, separateurDecimal, messageErreur);
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � tester</param>
/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement o� se trouver le s�parateur d�cimal dans la cha�ne test�e, sinon NULL</param>
/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
/*static*/ bool CChaine::EstReel(const char* chaine, const char*& separateurDecimal)
{
	const char* messageErreur;
	return EstReel(chaine, separateurDecimal, messageErreur);
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � tester</param>
/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement o� se trouver le s�parateur d�cimal dans la cha�ne test�e, sinon NULL</param>
/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
/*static*/ bool CChaine::EstReel(const char* chaine, const char*& messageErreur, const char*& separateurDecimal)
{
	messageErreur = NULL;
	separateurDecimal = NULL;
	if (chaine == NULL)
	{
		messageErreur = "La cha�ne repr�sentant un nombre r�el doit exister !";
		return false;
	}
	bool chiffreRencontre = false;
	for (const char* adresseCaractere = chaine; *adresseCaractere != 0; adresseCaractere++)
	{
		if ((*adresseCaractere >= '0') && (*adresseCaractere <= '9'))
		{
			chiffreRencontre = true;
		}
		else if ((*adresseCaractere == ',') || (*adresseCaractere == '.'))
		{
			if (separateurDecimal != NULL)
			{
				messageErreur = "Un nombre r�el ne peut contenir qu'un seul s�parateur d�cimal !";
				return false;
			}
			separateurDecimal = adresseCaractere;
		}
		else if ((*adresseCaractere == '+') || (*adresseCaractere == '-'))
		{
			if (adresseCaractere != chaine)
			{
				messageErreur = "Le signe d'un nombre r�el ne peut se trouver qu'au d�but de celui-ci !";
				return false;
			}
		}
		else
		{
			messageErreur = "Un nombre r�el ne peut contenir que des chiffres, un signe et un s�parateur d�cimal !";
			return false;
		}
	}
	if (!chiffreRencontre)
	{
		messageErreur = "Un nombre r�el doit contenir au moins un chiffre !";
		return false;
	}
	return true;
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur r�elle
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnReel(const char* chaine, double& valeur)
{
	const char* messageErreur;
	return EnReel(chaine, messageErreur, valeur);
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur r�elle
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnReel(const char* chaine, const char*& messageErreur, double& valeur)
{
	const char* separateurDecimal;
	valeur = 0.0;
	if (!EstReel(chaine, messageErreur, separateurDecimal)) return false;
	if ((separateurDecimal != NULL) && (*separateurDecimal == ','))
	{
		*((char*)separateurDecimal) = '.';
		valeur = atof(chaine);
		*((char*)separateurDecimal) = ',';
	}
	else
	{
		valeur = atof(chaine);
	}
	return true;
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � tester</param>
/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur enti�re, sinon faux</returns>
/*static*/ bool CChaine::EstEntier(const char* chaine)
{
	const char* messageErreur;
	return EstEntier(chaine, messageErreur);
}

/// <summary>
/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � tester</param>
/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur enti�re, sinon faux</returns>
/*static*/ bool CChaine::EstEntier(const char* chaine, const char*& messageErreur)
{
	messageErreur = NULL;
	if (chaine == NULL)
	{
		messageErreur = "La cha�ne repr�sentant un nombre entier doit exister !";
		return false;
	}
	bool chiffreRencontre = false;
	for (const char* adresseCaractere = chaine; *adresseCaractere != 0; adresseCaractere++)
	{
		if ((*adresseCaractere >= '0') && (*adresseCaractere <= '9'))
		{
			chiffreRencontre = true;
		}
		else if ((*adresseCaractere == '+') || (*adresseCaractere == '-'))
		{
			if (adresseCaractere != chaine)
			{
				messageErreur = "Le signe d'un nombre entier ne peut se trouver qu'au d�but de celui-ci !";
				return false;
			}
		}
		else
		{
			messageErreur = "Un nombre entier ne peut contenir que des chiffres et un signe !";
			return false;
		}
	}
	if (!chiffreRencontre)
	{
		messageErreur = "Un nombre entier doit contenir au moins un chiffre !";
		return false;
	}
	return true;
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnEntier(const char* chaine, long& valeur)
{
	const char* messageErreur;
	return EnEntier(chaine, messageErreur, valeur);
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnEntier(const char* chaine, const char*& messageErreur, long& valeur)
{
	valeur = 0;
	if (!EstEntier(chaine, messageErreur)) return false;
	valeur = atol(chaine);
	return true;
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnEntier(const char* chaine, __int64& valeur)
{
	const char* messageErreur;
	return EnEntier(chaine, messageErreur, valeur);
}

/// <summary>
/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
/// </summary>
/// <param name="chaine">Cha�ne de caract�res � convertir</param>
/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
/*static*/ bool CChaine::EnEntier(const char* chaine, const char*& messageErreur, __int64& valeur)
{
	valeur = 0;
	if (!EstEntier(chaine, messageErreur)) return false;
	valeur = _atoi64(chaine);
	return true;
}

/// <summary>
/// Retourne la fonction de test d'�galit� entre deux caract�res en fonction des options sp�cifi�es
/// </summary>
/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
/// <returns>Fonction de test d'�galit� entre deux caract�res en fonction des options sp�cifi�es</returns>
/*static*/ CChaine::TesteurEgaliteCaracteres CChaine::ObtenirTesteurEgaliteCaracteres(bool ignorerCasse, bool ignorerAccentuation)
{
	if (ignorerCasse)
	{
		return ignorerAccentuation ? CaracteresSontEgaux_ICA : CaracteresSontEgaux_IC;
	}
	else
	{
		return ignorerAccentuation ? CaracteresSontEgaux_IA : CaracteresSontEgaux;
	}
}

/// <summary>
/// Retourne la fonction de comparaison entre deux caract�res en fonction des options sp�cifi�es
/// </summary>
/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
/// <returns>Fonction de comparaison entre deux caract�res en fonction des options sp�cifi�es</returns>
/*static*/ CChaine::ComparateurCaracteres CChaine::ObtenirComparateurCaracteres(bool ignorerCasse, bool ignorerAccentuation)
{
	if (ignorerCasse)
	{
		return ignorerAccentuation ? ComparerCaractere_ICA : ComparerCaractere_IC;
	}
	else
	{
		return ignorerAccentuation ? ComparerCaractere_IA : ComparerCaractere;
	}
}

/// <summary>
/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
/// </summary>
/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
bool CRegleSurChaine::EstComparaisonPourUnicite(char modaliteComparaison) const
{
	if ((modaliteComparaison < CChaine::ComparaisonStricte) || (modaliteComparaison > CChaine::ComparaisonICA)) return false;
	return m_PourUnicite[modaliteComparaison];
}

/// <summary>
/// Permet de cr�er un duplicata de cette entit�
/// </summary>
/// <returns>Objet cr�� dynamiquement par clonage</returns>
CEntite* CRegleSurChaine::Cloner() const
{
	return new CRegleSurChaine(*this);
}

/// <summary>
/// Indique si les donn�es de cette entit� sont valides
/// </summary>
/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
bool CRegleSurChaine::EstValide(const CEntite* entiteValidatrice) const
{
	return true;
}

/// <summary>
/// Permet de tester la validit� de l'entit� sp�cifi�e en param�tre
/// <para>La r��criture de cette m�thode n'a d'int�r�t que si cette classe sert entre autre d'entit� validatrice, et donc � priori, � d�finir l'entit� par d�faut d'un tableau</para>
/// </summary>
/// <param name="entiteATester">Entit� � tester</param>
/// <returns>Vrai si l'entit� � tester est valide selon les r�gles impos�es par l'entit� pour laquelle cette m�thode est appel�e, sinon faux</returns>
bool CRegleSurChaine::TesterValidite(const CEntite& entiteATester) const
{
	return (((const CChaine&)entiteATester).Longueur() >= m_LongueurMinimale);
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="unicite">Indique si toutes les modalit�s de comparaison impliquent l'unicit� ou pas</param>
/// <param name="longueurMinimale">Longueur minimale que doit avoir toute cha�ne de caract�res</param>
CRegleSurChaine::CRegleSurChaine(bool unicite, long longueurMinimale)
	:CChaine()
{
	for (char modaliteComparaison = 0, nombreComparaisons = NombreComparaisons(); modaliteComparaison < nombreComparaisons; modaliteComparaison++)
	{
		m_PourUnicite[modaliteComparaison] = unicite;
	}
	m_LongueurMinimale = (longueurMinimale >= 0) ? longueurMinimale : 0;
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="uniciteStricte">Indique si la modalit� de comparaison stricte implique l'unicit� ou pas</param>
/// <param name="uniciteIC">Indique si la modalit� de comparaison sans distinction de casse implique l'unicit� ou pas</param>
/// <param name="uniciteIA">Indique si la modalit� de comparaison sans distinction d'accentuation implique l'unicit� ou pas</param>
/// <param name="uniciteICA">Indique si la modalit� de comparaison sans distinction de casse et d'accentuation implique l'unicit� ou pas</param>
/// <param name="longueurMinimale">Longueur minimale que doit avoir toute cha�ne de caract�res</param>
CRegleSurChaine::CRegleSurChaine(bool uniciteStricte, bool uniciteIC, bool uniciteIA, bool uniciteICA, long longueurMinimale)
	:CChaine()
{
	m_PourUnicite[CChaine::ComparaisonStricte] = uniciteStricte;
	m_PourUnicite[CChaine::ComparaisonIC] = uniciteIC;
	m_PourUnicite[CChaine::ComparaisonIA] = uniciteIA;
	m_PourUnicite[CChaine::ComparaisonICA] = uniciteICA;
	m_LongueurMinimale = (longueurMinimale >= 0) ? longueurMinimale : 0;
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Cha�ne source de cette copie</param>
CRegleSurChaine::CRegleSurChaine(const CRegleSurChaine& source)
	:CChaine(source)
{
	memcpy(m_PourUnicite, source.m_PourUnicite, sizeof(m_PourUnicite));
	m_LongueurMinimale = source.m_LongueurMinimale;
}

/// <summary>
/// Destructeur
/// </summary>
CRegleSurChaine::~CRegleSurChaine()
{
}

/// <summary>
/// Retourne le nombre de comparaisons pris en charge par toute entit� de ce type
/// </summary>
/// <returns>Nombre de comparaisons</returns>
char CChaineDecoupee::NombreComparaisons() const
{
	return 0;
}

/// <summary>
/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
/// </summary>
/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
bool CChaineDecoupee::EstComparaisonPourUnicite(char modaliteComparaison) const
{
	return false;
}

/// <summary>
/// Permet de cr�er un duplicata de cette entit�
/// </summary>
/// <returns>Objet cr�� dynamiquement par clonage</returns>
CEntite* CChaineDecoupee::Cloner() const
{
	return new CChaineDecoupee(*this);
}

/// <summary>
/// Indique si les donn�es de cette entit� sont valides
/// </summary>
/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
bool CChaineDecoupee::EstValide(const CEntite* entiteValidatrice) const
{
	return (m_Chaine != NULL) && (m_NombreChamps >= 1);
}

/// <summary>
/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
/// </summary>
/// <param name="autreEntite">Autre entit� � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
int CChaineDecoupee::Comparer(const CEntite& autreEntite, char modaliteComparaison) const
{
	return 0;
}

/// <summary>
/// Constructeur sp�cifique
/// </summary>
/// <param name="chaine">Cha�ne que l'on va "d�couper" en fonction du caract�re s�parateur sp�cifi�</param>
/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
CChaineDecoupee::CChaineDecoupee(const char* chaine, char separateur, bool suppressionEspacesSuperflus)
	:CEntite(), m_LongueurChaine(0), m_TailleChaine(-1), m_Chaine(NULL), m_NombreChamps(0), m_TailleChamps(0), m_Champs(NULL)
{
	if (CopierChaine(chaine)) Decouper(separateur, suppressionEspacesSuperflus);
}

/// <summary>
/// M�thode d�finissant la cha�ne � d�couper
/// </summary>
/// <param name="chaine">Cha�ne � d�couper</param>
/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
/// <returns>Vrai si le d�coupage a pu se faire, sinon faux</returns>
bool CChaineDecoupee::CopierChaine(const char* chaine)
{
	if (chaine == NULL) return false;
	long longueurChaine = (long)strlen(chaine);
	if (longueurChaine > m_TailleChaine)
	{
		void* nouvelleAdresse = (m_Chaine == NULL) ? malloc((longueurChaine + 1) * sizeof(char)) : realloc(m_Chaine, (longueurChaine + 1) * sizeof(char));
		if (nouvelleAdresse == NULL) return false;
		m_Chaine = (char*)nouvelleAdresse;
		m_TailleChaine = longueurChaine;
	}
	m_LongueurChaine = longueurChaine;
	strcpy(m_Chaine, chaine);
	return true;
}

/// <summary>
/// M�thode r�alisant le d�coupage de la cha�ne actuelle en fonction du caract�re s�parateur sp�cifi�
/// </summary>
/// <param name="chaine">Cha�ne � d�couper</param>
/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
/// <returns>Vrai si le d�coupage a pu se faire, sinon faux</returns>
bool CChaineDecoupee::Decouper(char separateur, bool suppressionEspacesSuperflus)
{
	long nChamps = 1;
	for (const char* car = m_Chaine; *car != 0; car++)
	{
		if (*car == separateur) nChamps++;
	}
	if (nChamps > m_TailleChamps)
	{
		void* nouvelleAdresse = (m_Champs == NULL) ? malloc(nChamps * sizeof(char*)) : realloc(m_Champs, nChamps * sizeof(char*));
		if (nouvelleAdresse == NULL) return false;
		m_Champs = (char**)nouvelleAdresse;
		m_TailleChamps = nChamps;
	}
	m_NombreChamps = nChamps;
	m_Champs[0] = m_Chaine;
	long iChamp = 1;
	for (char* car = m_Chaine; *car != 0; car++)
	{
		if (*car == separateur)
		{
			*car = 0;
			__pragma(warning(push))
				__pragma(warning(disable:6386))
				m_Champs[iChamp++] = (car + 1);
			__pragma(warning(pop))
		}
	}
	if (suppressionEspacesSuperflus)
	{
		for (long iChamp = 0; iChamp < m_NombreChamps; iChamp++)
		{
			char* car = m_Champs[iChamp];
			while (*car == ' ') car++;
			m_Champs[iChamp] = car;
			char* dernierCaractereSignificatif = car - 1;
			for (; *car != 0; car++)
			{
				if (*car != ' ') dernierCaractereSignificatif = car;
			}
			car = dernierCaractereSignificatif + 1;
			*car = 0;
		}
	}
	return true;
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Cha�ne d�coup�e qui sert de source de cette copie</param>
CChaineDecoupee::CChaineDecoupee(const CChaineDecoupee& source)
	:CEntite(), m_LongueurChaine(0), m_Chaine(NULL), m_NombreChamps(0), m_Champs(NULL)
{
	if ((source.m_Chaine != NULL) && (source.m_NombreChamps >= 1))
	{
		m_Chaine = (char*)malloc((source.m_LongueurChaine + 1) * sizeof(char));
		if (m_Chaine != NULL)
		{
			m_TailleChaine = source.m_LongueurChaine;
			m_LongueurChaine = source.m_LongueurChaine;
			memcpy(m_Chaine, source.m_Chaine, (m_LongueurChaine + 1) * sizeof(char));
			m_Champs = (char**)malloc(source.m_NombreChamps * sizeof(char*));
			if (m_Champs != NULL)
			{
				m_TailleChamps = source.m_NombreChamps;
				m_NombreChamps = source.m_NombreChamps;
				for (long iChamp = 0; iChamp < source.m_NombreChamps; iChamp++)
				{
					m_Champs[iChamp] = m_Chaine + (source.m_Champs[iChamp] - source.m_Chaine);
				}
			}
		}
	}
}

/// <summary>
/// Destructeur
/// </summary>
CChaineDecoupee::~CChaineDecoupee()
{
	if (m_Champs != NULL) free(m_Champs);
	if (m_Chaine != NULL) free(m_Chaine);
}

/// <summary>
/// Retourne le nombre de champs
/// </summary>
/// <returns>Nombre de champs de cette cha�ne d�coup�e</returns>
long CChaineDecoupee::Nombre() const
{
	return m_NombreChamps;
}

/// <summary>
/// Retourne le champ sp�cifi� par son indice
/// </summary>
/// <param name="indice">Indice du champ � r�cup�rer</param>
/// <returns>Adresse de d�but de la cha�ne de caract�res correspondant au champ sp�cifi� par son indice si possible, sinon l'adresse d'une cha�ne vide constante</returns>
const char* CChaineDecoupee::Element(long indice) const
{
	return ((indice >= 0) && (indice < m_NombreChamps)) ? m_Champs[indice] : "";
}

/// <summary>
/// Indique si le champ sp�cifi� par son indice est �gal � la cha�ne sp�cifi�e
/// </summary>
/// <param name="indice">Indice du champ � tester</param>
/// <param name="indice">Correspondance recherch�e lors du test du champ concern�</param>
/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
/// <returns>Vrai si le champ sp�cifi� est �gal � la cha�ne de caract�res sp�cifi�es, sinon faux</returns>
bool CChaineDecoupee::EstEgal(long indice, const char* chaine, char modaliteComparaison) const
{
	return CChaine::ComparerChaine
	(
		Element(indice),
		chaine,
		(modaliteComparaison == CChaine::ComparaisonIC) || (modaliteComparaison == CChaine::ComparaisonICA),
		(modaliteComparaison == CChaine::ComparaisonIA) || (modaliteComparaison == CChaine::ComparaisonICA)
	) == 0;
}

/// <summary>
/// Permet de v�rifier si le champ sp�cifi� par son indice n'est constitu�e que de caract�res parmi ceux autoris�s
/// </summary>
/// <param name="indice">Indice du champ � tester</param>
/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
/// <param name="caracteresAcceptables">Cha�ne contenant les caract�res acceptables</param>
/// <param name="caracteresInterdits">Cha�ne contenant les caract�res sp�cifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
/// <returns>Vrai si tous les caract�res du champ sp�cifi� respecte les prescriptions sp�cifi�es, sinon faux</returns>
bool CChaineDecoupee::Respecte(long indice, char acceptation, const char* caracteresAcceptables, const char* caracteresInterdits) const
{
	return CChaine::ChaineRespecte(Element(indice), acceptation, caracteresAcceptables, caracteresInterdits);
}

/// <summary>
/// Indique si le champ sp�cifi� repr�sente un nombre entier
/// </summary>
/// <param name="indice">Indice du champ � tester</param>
/// <returns>Vrai si le champ sp�cifi� repr�sente une valeur enti�re, sinon faux</returns>
bool CChaineDecoupee::EstEntier(long indice) const
{
	return CChaine::EstEntier(Element(indice));
}

/// <summary>
/// Indique si le champ sp�cifi� repr�sente un nombre r�el
/// </summary>
/// <param name="indice">Indice du champ � tester</param>
/// <returns>Vrai si le champ sp�cifi� repr�sente une valeur r�elle, sinon faux</returns>
bool CChaineDecoupee::EstReel(long indice) const
{
	return CChaine::EstReel(Element(indice));
}

/// <summary>
/// Tente de convertir le champ sp�cifi� en un nombre entier [type char]
/// </summary>
/// <param name="indice">Indice du champ � convertir si possible</param>
/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
bool CChaineDecoupee::EnEntier(long indice, char& valeur) const
{
	valeur = 0;
	__int64 valeurConvertie;
	if (!CChaine::EnEntier(Element(indice), valeurConvertie)) return false;
	if ((valeurConvertie < -128LL) || (valeurConvertie > 127LL)) return false;
	valeur = (char)valeurConvertie;
	return true;
}

/// <summary>
/// Tente de convertir le champ sp�cifi� en un nombre entier [type short]
/// </summary>
/// <param name="indice">Indice du champ � convertir si possible</param>
/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
bool CChaineDecoupee::EnEntier(long indice, short& valeur) const
{
	valeur = 0;
	__int64 valeurConvertie;
	if (!CChaine::EnEntier(Element(indice), valeurConvertie)) return false;
	if ((valeurConvertie < -32768LL) || (valeurConvertie > 32767LL)) return false;
	valeur = (short)valeurConvertie;
	return true;
}

/// <summary>
/// Tente de convertir le champ sp�cifi� en un nombre entier [type long]
/// </summary>
/// <param name="indice">Indice du champ � convertir si possible</param>
/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
bool CChaineDecoupee::EnEntier(long indice, long& valeur) const
{
	valeur = 0;
	__int64 valeurConvertie;
	if (!CChaine::EnEntier(Element(indice), valeurConvertie)) return false;
	if ((valeurConvertie < -2147483648LL) || (valeurConvertie > 2147483647LL)) return false;
	valeur = (long)valeurConvertie;
	return true;
}

/// <summary>
/// Tente de convertir le champ sp�cifi� en un nombre entier [type __int64]
/// </summary>
/// <param name="indice">Indice du champ � convertir si possible</param>
/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
bool CChaineDecoupee::EnEntier(long indice, __int64& valeur) const
{
	return CChaine::EnEntier(Element(indice), valeur);
}

/// <summary>
/// Tente de convertir le champ sp�cifi� en un nombre r�el [type double]
/// </summary>
/// <param name="indice">Indice du champ � convertir si possible</param>
/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0.0</param>
/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur r�elle, sinon faux</returns>
bool CChaineDecoupee::EnReel(long indice, double& valeur) const
{
	return CChaine::EnReel(Element(indice), valeur);
}
