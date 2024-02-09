#include "BisConsole.h"
#include <Windows.h>
#include "FichierCSV.h"

#define CODE_NORMAL false

/// <summary>
/// Constructeur par défaut
/// </summary>
CFichierCSV::CFichierCSV()
	:CChaineDecoupee(NULL)
{
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Chargeur de fichier CSV qui sert de source de cette copie</param>
CFichierCSV::CFichierCSV(const CFichierCSV& source)
	:CChaineDecoupee(source)
{
}

/// <summary>
/// Destructeur
/// </summary>
/*virtual*/ CFichierCSV::~CFichierCSV()
{
}

/// <summary>
/// Permet de lancer le processus de chargement des données à partir du fichier spécifié par son chemin d'accès relatif à l'exécutable
/// </summary>
/// <param name="nomFichier">Nom du fichier</param>
/// <param name="separateur">Caractère séparateur utilisé pour le découpage de chaque ligne lue</param>
/// <param name="suppressionEspacesSuperflus">Indique si chaque champ résultant du découpage de chaque ligne lue doit faire l'objet d'une suppression de ces espaces superflus de début et de fin de chaîne</param>
/// <returns>Vrai si le chargement a été réalisé jusqu'à la fin du fichier, sinon faux</returns>
/*virtual*/ bool CFichierCSV::Charger(const char* nomFichier, char separateur, bool suppressionEspacesSuperflus)
{
	FILE* fichier = (FILE*)fopen_x(nomFichier, "rt");
	if (fichier == NULL) return false;
	const long incrementBuffer = 10;
	bool resultat = true;
	while (!feof(fichier))
	{
		// Boucle de lecture d'une ligne dans le buffer de la classe de base CChaineDecoupee
		long nombreCaracteres = 0;
		while (!feof(fichier))
		{
			if (m_TailleChaine < 0) m_TailleChaine = 0;
			if (nombreCaracteres == m_TailleChaine)
			{
				void* nouvelleAdresse = (m_Chaine == NULL) ? malloc((incrementBuffer + 1) * sizeof(char)) : realloc(m_Chaine, (m_TailleChaine + incrementBuffer + 1) * sizeof(char));
				if (nouvelleAdresse == NULL)
				{
					resultat = false;
					break;
				}
				m_Chaine = (char*)nouvelleAdresse;
				m_TailleChaine += incrementBuffer;
			}
			int caractere = fgetc(fichier);
			if ((caractere < 0) || (caractere == '\n'))
			{
				if ((caractere == '\n') || feof(fichier)) break;
				resultat = false;
				break;
			}
			m_Chaine[nombreCaracteres++] = caractere;
		}
		if (!resultat) break;
		// Ajout du marqueur de fin de chaîne en fin de partie utile du buffer de la classe de base CChaineDecoupee
		{
			m_LongueurChaine = nombreCaracteres;
			__pragma(warning(push))
				__pragma(warning(disable:6011))
				m_Chaine[m_LongueurChaine] = 0;
			__pragma(warning(pop))
		}
		// Traitement de la ligne lue
		if (Decouper())
		{
			resultat = Traiter(*this);
			if (!resultat) break;
		}
	}
	fclose(fichier);
	return resultat;
}

/// <summary>
/// Permet d'ouvrir un fichier à partir d'un emplacement relatif à celui de l'exécutable
/// </summary>
/// <param name="nomFichier">Nom du fichier avec un chemin relatif à calculer à partir de l'emplacement de l'exécutable</param>
/// <param name="modalite">Modalité d'ouverture</param>
/// <returns>"Pointeur" de type FILE si le fichier a pu être ouvert, sinon NULL</returns>
/*static*/ void* CFichierCSV::fopen_x(const char* nomFichier, const char* modalite)
{
	if ((nomFichier == NULL) || (*nomFichier == 0)) return NULL;
	if ((modalite == NULL) || (*modalite == 0)) return NULL;
#if CODE_NORMAL
	return fopen(nomFichier, modalite);
#else
	FILE* fichier;
	const long incrementTaille = 20;
	long tailleCheminFichier = incrementTaille;
	char* cheminFichier = (char*)malloc(tailleCheminFichier * sizeof(char));
	if (cheminFichier == NULL) return NULL;
	while (true)
	{
		GetModuleFileNameA(NULL, cheminFichier, tailleCheminFichier);
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) break;
		void* nouvelleAdresse = realloc(cheminFichier, (tailleCheminFichier + incrementTaille) * sizeof(char));
		if (nouvelleAdresse == NULL) { free(cheminFichier); return NULL; }
		cheminFichier = (char*)nouvelleAdresse;
		tailleCheminFichier += incrementTaille;
	}
	if (GetLastError() != ERROR_SUCCESS) { free(cheminFichier); return NULL; }
	char* dernierSeparateur = strrchr(cheminFichier, '\\');
	if (dernierSeparateur == NULL) return false;
	while (strncmp(nomFichier, "../", 3) == 0)
	{
		dernierSeparateur--;
		while ((dernierSeparateur >= cheminFichier) && (*dernierSeparateur != '\\')) dernierSeparateur--;
		if (dernierSeparateur < cheminFichier) return false;
		nomFichier += 3;
	}
	long tailleFinale = (long)((dernierSeparateur + 1) - cheminFichier) + (long)strlen(nomFichier) + 1;
	if (tailleCheminFichier < tailleFinale)
	{
		long indiceDernierSeparateur = dernierSeparateur - cheminFichier;
		void* nouvelleAdresse = realloc(cheminFichier, tailleFinale * sizeof(char));
		if (nouvelleAdresse == NULL) { free(cheminFichier); return false; }
		cheminFichier = (char*)nouvelleAdresse;
		dernierSeparateur = cheminFichier + indiceDernierSeparateur;
	}
	strcpy(dernierSeparateur + 1, nomFichier);
	for (char* car = cheminFichier; *car != 0; car++)
	{
		if (*car == '\\') *car = '/';
	}
	fichier = fopen(cheminFichier, modalite);
	free(cheminFichier);
	return fichier;
#endif
}
