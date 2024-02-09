#include "BisConsole.h"
#include <Windows.h>
#include <time.h>
#include "DocumentHtml.h"

#define CODE_NORMAL false

/// <summary>
/// Constructeur par défaut
/// </summary>
CDocumentHtml::CDocumentHtml()
	:m_NomFichier(), m_Fichier(NULL), m_AjoutCssPossible(false), m_EcritureBalisePossible(false), m_CreationReussie(false), m_BalisesOuvertes(CChaine())
{
}

/// <summary>
/// Destructeur
/// </summary>
/*virtual*/ CDocumentHtml::~CDocumentHtml()
{
	if (m_Fichier != NULL)
	{
		fclose((FILE*)m_Fichier);
		m_Fichier = NULL;
	}
}

/// <summary>
/// Permet de lancer le processus de création d'un document HTML dont le nom de fichier est spécifié par son chemin d'accès relatif à l'exécutable
/// </summary>
/// <param name="nomFichier">Nom du fichier</param>
/// <param name="titre">Titre du document</param>
/// <returns>Vrai si la création a été réalisée jusqu'à la fin, sinon faux</returns>
bool CDocumentHtml::Creer(const char* nomFichier, const char* titre)
{
	if (m_Fichier != NULL) return false;
	m_CreationReussie = false;
	m_AjoutCssPossible = false;
	m_EcritureBalisePossible = false;
	if (!m_NomFichier.Modifier(nomFichier, true) || (m_NomFichier.Longueur() == 0)) return false;
	if ((m_NomFichier.Longueur() < 6) || (stricmp(m_NomFichier.Contenu() + (m_NomFichier.Longueur() - 5), ".html") != 0))
	{
		if (!m_NomFichier.Concatener(".html")) return false;
	}
	if (titre == NULL) titre = "Document sans titre";
	m_Fichier = (FILE*)fopen_x(m_NomFichier.Contenu(), "w+t");
	if (m_Fichier == NULL) return false;
	fprintf((FILE*)m_Fichier, "<!doctype HTML>\n\n");
	m_BalisesOuvertes.Vider();
	m_EcritureBalisePossible = true;
	bool resultat = OuvrirBalise("html");
	if (resultat) fprintf((FILE*)m_Fichier, "\n");
	resultat = resultat && OuvrirBalise("head");
	resultat = resultat && BaliseAutonome("meta", "charset=\"windows-1252\"");
	resultat = resultat && BaliseAutonome("meta", "http-equiv=\"content-type\" content=\"text/html;charset=windows-1252\"");
	resultat = resultat && OuvrirEtFermerBalise("title", titre);
	resultat = resultat && OuvrirBalise("style");
	if (resultat)
	{
		fprintf((FILE*)m_Fichier, "%s", "\t\thtml,body\n\t\t{\n\t\t\twidth:100%;\n\t\t\theight:100%;\n\t\t\tmargin:0px;\n\t\t}\n\t\tbody\n\t\t{\n\t\t\tdisplay:table;\n\t\t}\n\t\tbody>*\n\t\t{\n\t\t\tdisplay:table-row;\n\t\t\tbackground-color:rgba(0,0,0,0.35);\n\t\t}\n\t\tmain\n\t\t{\n\t\t\theight:100%;\n\t\t\tbackground-color:rgba(255,255,255,0.5);\n\t\t}\n\t\theader\n\t\t{\n\t\t\ttext-align:center;\n\t\t}\n\t\tfooter\n\t\t{\n\t\t\ttext-align:center;\n\t\t}\n\t\tfooter>*\n\t\t{\n\t\t\tfont-style:italic;\n\t\t}\n\t\tmain>*\n\t\t{\n\t\t\tmargin:0.5em;\n\t\t}\n\t\ttable,th,td\n\t\t{\n\t\t\tborder-style:solid;\n\t\t\tborder-width:1px;\n\t\t\tborder-color:black;\n\t\t\tborder-collapse:collapse;\n\t\t}\n");
		m_EcritureBalisePossible = false;
		m_AjoutCssPossible = true;
		resultat = CompleterCss();
		m_AjoutCssPossible = false;
		m_EcritureBalisePossible = true;
	}
	resultat = resultat && FermerBalise("style");
	resultat = resultat && FermerBalise("head");
	if (resultat) fprintf((FILE*)m_Fichier, "\n");
	resultat = resultat && OuvrirBalise("body");
	resultat = resultat && OuvrirBalise("header");
	resultat = resultat && OuvrirEtFermerBalise("h1", titre);
	resultat = resultat && FermerBalise("header");
	resultat = resultat && OuvrirBalise("main");
	resultat = resultat && GenererCorps();
	resultat = resultat && FermerBalise("main");
	resultat = resultat && OuvrirBalise("footer");
	if (resultat)
	{
		time_t rawTime;
		time(&rawTime);
		struct tm timeInfo;
		localtime_s(&timeInfo, &rawTime);
		char textePied[200 + 1];
		sprintf(textePied, "Document généré le %d/%02d/%4d à %d:%02d:%02d", (short)timeInfo.tm_mday, (short)(1 + timeInfo.tm_mon), (short)(1900 + timeInfo.tm_year), (short)timeInfo.tm_hour, (short)timeInfo.tm_min, (short)timeInfo.tm_sec);
		resultat = resultat && OuvrirEtFermerBalise("p", textePied);
	}
	resultat = resultat && FermerBalise("footer");
	resultat = resultat && FermerBalise("body");
	if (resultat) fprintf((FILE*)m_Fichier, "\n");
	resultat = resultat && FermerBalise("html");
	m_EcritureBalisePossible = false;
	fclose((FILE*)m_Fichier);
	m_Fichier = NULL;
	m_CreationReussie = resultat;
	return resultat;
}

/// <summary>
/// Méthode pouvant être réécrite afin de compléter la partie de code CSS du document HTML
/// </summary>
/// <returns>Vrai pour indiquer que l'on veut finaliser "normalement" la création du document HTML, sinon faux pour arrêter immédiatement cette création avec un retour d'erreur</returns>
/*virtual*/ bool CDocumentHtml::CompleterCss()
{
	return true;
}

/// <summary>
/// Permet d'ajouter une définition CSS comme code CSS additionnel
/// </summary>
/// <param name="selecteur">Code CSS décrivant un ou plusieurs sélecteurs (séparés les uns des autres par une virgule)</param>
/// <param name="proprietes">Code CSS réalisant les modifications de propriétés (séparées les unes des autres par un point-virgule)</param>
/// <returns>Vrai si cet ajout a réussi, sinon faux</returns>
bool CDocumentHtml::AjouterCss(const char* selecteur, const char* proprietes)
{
	if (!m_AjoutCssPossible) return false;
	if (CChaine::LongueurChaine(selecteur, true) == 0) return false;
	if (CChaine::LongueurChaine(proprietes, true) == 0) return true;
	fprintf((FILE*)m_Fichier, "\t\t%s { %s }\n", selecteur, proprietes); // TODO : améliorable en terme de lisibilité de code css produit
	return true;
}

/// <summary>
/// Permet de créer un élément du DOM avec une balise ouvrante
/// </summary>
/// <param name="nomBalise">Nom de la balise</param>
/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
/// <returns>Vrai si l'ouverture a fonctionné, sinon faux</returns>
bool CDocumentHtml::OuvrirBalise(const char* nomBalise, const char* attributs)
{
	if (!m_EcritureBalisePossible) return false;
	if ((CChaine::LongueurChaine(nomBalise, true) < 1) || !CChaine::ChaineRespecte(nomBalise, CChaine::AccepterLettresNA | CChaine::AccepterChiffres)) return false;
	CChaine balise;
	if (balise.Modifier(nomBalise, (char)(CChaine::SuppressionEspacesSuperflus | CChaine::EnMinuscule)))
	{
		if (m_BalisesOuvertes.Ajouter(balise))
		{
			for (long i = 0, n = m_BalisesOuvertes.Nombre() - 1; i < n; i++) fprintf((FILE*)m_Fichier, "\t");
			fprintf((FILE*)m_Fichier, "<%s", balise.Contenu());
			if (attributs != NULL) fprintf((FILE*)m_Fichier, " %s", attributs);
			fprintf((FILE*)m_Fichier, ">\n");
		}
	}
	return true;
}

/// <summary>
/// Permet de fermer l'élément du DOM actuellement "ouvert", et ce, avec sa balise fermante
/// </summary>
/// <param name="nomBalise">Nom de la balise, sinon NULL</param>
/// <param name="toutFermerJusqueBaliseSpecifiee">Indique que l'on veut fermer toutes les balises actuellement ouvertes jusqu'à atteindre et fermer celle spécifiée</param>
/// <returns>Vrai si la fermeture a pu se faire, sinon faux</returns>
bool CDocumentHtml::FermerBalise(const char* nomBalise, bool toutFermerJusqueBaliseSpecifiee)
{
	if (!m_EcritureBalisePossible) return false;
	if (m_BalisesOuvertes.Nombre() == 0) return false;
	if (nomBalise == NULL)
	{
		if (toutFermerJusqueBaliseSpecifiee) return false;
		long indiceBalise = m_BalisesOuvertes.Nombre() - 1;
		if (indiceBalise < 0) return false;
		for (long i = 0, n = m_BalisesOuvertes.Nombre() - 1; i < n; i++) fprintf((FILE*)m_Fichier, "\t");
		fprintf((FILE*)m_Fichier, "</%s>\n", m_BalisesOuvertes.Element<const CChaine>(indiceBalise).Contenu());
		return m_BalisesOuvertes.Supprimer(indiceBalise);
	}
	else
	{
		bool reussi = false;
		CChaine balise;
		if (balise.Modifier(nomBalise, (char)(CChaine::SuppressionEspacesSuperflus | CChaine::EnMinuscule)))
		{
			if (toutFermerJusqueBaliseSpecifiee)
			{
				if (m_BalisesOuvertes.Rechercher(balise, CChaine::ComparaisonStricte) >= 0)
				{
					reussi = true;
					for (long iBO = m_BalisesOuvertes.Nombre() - 1; iBO >= 0; iBO--)
					{
						const CChaine& baliseOuverte = m_BalisesOuvertes.Element<const CChaine>(iBO);
						reussi = reussi && FermerBalise();
						if (baliseOuverte.Comparer(balise, CChaine::ComparaisonStricte) == 0) break;
					}
				}
			}
			else
			{
				long iBO = m_BalisesOuvertes.Nombre() - 1;
				const CChaine& baliseOuverte = m_BalisesOuvertes.Element<const CChaine>(iBO);
				reussi = (baliseOuverte.Comparer(balise, CChaine::ComparaisonStricte) == 0) && FermerBalise();
			}
		}
		return reussi;
	}
}

/// <summary>
/// Permet de créer un élément du DOM avec une balise autonome
/// </summary>
/// <param name="nomBalise">Nom de la balise</param>
/// <param name="attributs">Chaîne d'attributs de cette balise autonome</param>
/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
bool CDocumentHtml::BaliseAutonome(const char* nomBalise, const char* attributs)
{
	if (!m_EcritureBalisePossible) return false;
	if ((CChaine::LongueurChaine(nomBalise, true) < 1) || !CChaine::ChaineRespecte(nomBalise, CChaine::AccepterLettresNA | CChaine::AccepterChiffres)) return false;
	CChaine balise;
	if (balise.Modifier(nomBalise, (char)(CChaine::SuppressionEspacesSuperflus | CChaine::EnMinuscule)))
	{
		for (long i = 0, n = m_BalisesOuvertes.Nombre(); i < n; i++) fprintf((FILE*)m_Fichier, "\t");
		fprintf((FILE*)m_Fichier, "<%s", balise.Contenu());
		if (attributs != NULL) fprintf((FILE*)m_Fichier, " %s", attributs);
		fprintf((FILE*)m_Fichier, "/>\n");
	}
	return true;
}

/// <summary>
/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
/// </summary>
/// <param name="nomBalise">Nom de la balise</param>
/// <param name="contenu">Contenu à placer entre la balise ouvrante et la balise fermante</param>
/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
bool CDocumentHtml::OuvrirEtFermerBalise(const char* nomBalise, const char* contenu)
{
	return OuvrirEtFermerBalise(nomBalise, NULL, contenu);
}

/// <summary>
/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
/// </summary>
/// <param name="nomBalise">Nom de la balise</param>
/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
/// <param name="contenu">Contenu à placer entre la balise ouvrante et la balise fermante</param>
/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
bool CDocumentHtml::OuvrirEtFermerBalise(const char* nomBalise, const char* attributs, const char* contenu)
{
	if (!m_EcritureBalisePossible) return false;
	if ((CChaine::LongueurChaine(nomBalise, true) < 1) || !CChaine::ChaineRespecte(nomBalise, CChaine::AccepterLettresNA | CChaine::AccepterChiffres)) return false;
	CChaine balise;
	if (balise.Modifier(nomBalise, (char)(CChaine::SuppressionEspacesSuperflus | CChaine::EnMinuscule)))
	{
		for (long i = 0, n = m_BalisesOuvertes.Nombre(); i < n; i++) fprintf((FILE*)m_Fichier, "\t");
		fprintf((FILE*)m_Fichier, "<%s", balise.Contenu());
		if (attributs != NULL) fprintf((FILE*)m_Fichier, " %s", attributs);
		fprintf((FILE*)m_Fichier, ">%s</%s>\n", contenu, balise.Contenu());
	}
	return true;
}

__pragma(warning(push))
__pragma(warning(disable:4996))
__pragma(warning(disable:4793))
/// <summary>
/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu paramétré, et enfin, sa balise fermante
/// </summary>
/// <param name="nomBalise">Nom de la balise</param>
/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
/// <param name="format">Format du contenu à placer entre la balise ouvrante et la balise fermante</param>
/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
bool CDocumentHtml::OuvrirEtFermerBaliseF(const char* nomBalise, const char* attributs, const char* format, ...)
{
	if (!m_EcritureBalisePossible) return false;
	if ((CChaine::LongueurChaine(nomBalise, true) < 1) || !CChaine::ChaineRespecte(nomBalise, CChaine::AccepterLettresNA | CChaine::AccepterChiffres)) return false;
	CChaine balise;
	if (balise.Modifier(nomBalise, (char)(CChaine::SuppressionEspacesSuperflus | CChaine::EnMinuscule)))
	{
		for (long i = 0, n = m_BalisesOuvertes.Nombre(); i < n; i++) fprintf((FILE*)m_Fichier, "\t");
		fprintf((FILE*)m_Fichier, "<%s", balise.Contenu());
		if (attributs != NULL) fprintf((FILE*)m_Fichier, " %s", attributs);
		fprintf((FILE*)m_Fichier, ">");
		va_list arguments;
		va_start(arguments, format);
		vfprintf((FILE*)m_Fichier, format, arguments);
		va_end(arguments);
		fprintf((FILE*)m_Fichier, "</%s>\n", balise.Contenu());
	}
	return true;
}
__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable:28159))
/// <summary>
/// Permet d'ouvrir ce document HTML
/// </summary>
/// <returns>Vrai si l'ouverture a pu se faire, sinon faux</returns>
bool CDocumentHtml::Ouvrir()
{
	if ((m_NomFichier.Longueur() < 1) || !m_CreationReussie) return false;
	const char* nomFichier = m_NomFichier.Contenu();
	const long incrementTaille = 20;
	long tailleCheminFichier = incrementTaille;
	char* cheminFichier = (char*)malloc(tailleCheminFichier * sizeof(char));
	if (cheminFichier == NULL) return false;
	while (true)
	{
		GetModuleFileNameA(NULL, cheminFichier, tailleCheminFichier);
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) break;
		void* nouvelleAdresse = realloc(cheminFichier, (tailleCheminFichier + incrementTaille) * sizeof(char));
		if (nouvelleAdresse == NULL) { free(cheminFichier); return false; }
		cheminFichier = (char*)nouvelleAdresse;
		tailleCheminFichier += incrementTaille;
	}
	if (GetLastError() != ERROR_SUCCESS) { free(cheminFichier); return false; }
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
		if (*car == '/') *car = '\\';
	}
	CChaine commande;
	if (commande.Modifier("explorer.exe ") && commande.Concatener(cheminFichier))
	{
		WinExec(commande.Contenu(), SW_NORMAL);
	}
	free(cheminFichier);
	return true;
}
__pragma(warning(pop))

/// <summary>
/// Permet d'ouvrir un fichier à partir d'un emplacement relatif à celui de l'exécutable
/// </summary>
/// <param name="nomFichier">Nom du fichier avec un chemin relatif à calculer à partir de l'emplacement de l'exécutable</param>
/// <param name="modalite">Modalité d'ouverture</param>
/// <returns>"Pointeur" de type FILE si le fichier a pu être ouvert, sinon NULL</returns>
/*static*/ void* CDocumentHtml::fopen_x(const char* nomFichier, const char* modalite)
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
