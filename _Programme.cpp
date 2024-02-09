#include "BisConsole.h"
#include "Interface.h"
#include "DocumentHtml.h"
#include "GeoCommune.h"


/// <summary>
/// Permet d'afficher toutes les données chargées
/// </summary>
/// <param name="geo">Objet contenant toutes les données de GeoCommune</param>
void AfficherDonnees(const CGeoCommune& geo);

/// <summary>
/// Permet de contrôler la validité des données calculées pendant le chargement
/// </summary>
/// <param name="geo">Objet contenant toutes les données de GeoCommune</param>
void ControlerCalculs(const CGeoCommune& geo);

/// <summary>
/// Point d'entrée de l'application
/// </summary>
void main()
{
	CGeoCommune geo;
	if (geo.Charger("../../Donnees/geo.txt"))
	{
		ControlerCalculs(geo);
		AfficherDonnees(geo);
	}
}

/// <summary>
/// Permet d'afficher toutes les données chargées
/// </summary>
/// <param name="geo">Objet contenant toutes les données de GeoCommune</param>
void AfficherDonnees(const CGeoCommune& geo)
{
	console_clear();
	printf("            Liste des entités communales\n");
	printf("            ============================\n");
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		printf("\nEntité communale %ld/%ld :\n* nom : %s\n", iEC + 1, nEC, ec.Nom());
	}
	AttendreTouche(TOUCHE_ESC, "passer à la liste des communes par entité communale");
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		CChaine titre(ec.Nom(), CChaine::EnMajuscule);
		CChaine soulignement('=', titre.Longueur());
		console_clear();
		printf("            %s\n", titre.Contenu());
		printf("            %s\n", soulignement.Contenu());
		for (long iC = 0, nC = ec.NombreCommunes(); iC < nC; iC++)
		{
			const CCommune& c = ec.Commune(iC);
			printf("\nCommune %ld/%ld :\n* nom : %s\n", iC + 1, nC, c.Nom());
		}
		if (iEC < (nEC - 1))
			AttendreTouche(TOUCHE_RETURN, "passer à la liste des communes de l'entité communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer au détail des relevés de zones par commune");
	}
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		for (long iC = 0, nC = ec.NombreCommunes(); iC < nC; iC++)
		{
			const CCommune& c = ec.Commune(iC);
			CChaine titre;
			titre.Modifier(ec.Nom(), CChaine::EnMajuscule);
			titre.Concatener(" - ");
			titre.Concatener(c.Nom(), CChaine::EnMajuscule);
			CChaine soulignement('=', titre.Longueur());
			console_clear();
			printf("            %s\n", titre.Contenu());
			printf("            %s\n", soulignement.Contenu());
			for (long iZ = 0, nZ = c.NombreZones(); iZ < nZ; iZ++)
			{
				const CZone& z = c.Zone(iZ);
				printf("\nZone %ld/%ld :\n* nom : %s\n", iZ + 1, nZ, z.Nom());
				for (long iR = 0, nR = z.NombreReleves(); iR < nR; iR++)
				{
					const CReleve& r = z.Releve(iR);
					printf("* relevé en %d : %lg km²\n", r.Annee(), r.Superficie());
				}
			}
			if ((iC < (nC - 1)) || (iEC < (nEC - 1)))
				AttendreTouche(TOUCHE_RETURN, "passer au détail des relevés de la commune suivante");
			else
				AttendreTouche(TOUCHE_ESC, "passer à l'analyse croisée par entité communale");
		}
	}
	// Simulation par affichage des tableaux d'analyse croisée
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		CChaine titre(ec.Nom(), CChaine::EnMajuscule);
		CChaine soulignement('=', titre.Longueur());
		console_clear();
		printf("            %s\n", titre.Contenu());
		printf("            %s\n", soulignement.Contenu());
		printf("\nVoici les années de relevés pris en compte :\n");
		for (long iRA = 0, nRA = ec.NombreRelevesAnnuels(); iRA < nRA; iRA++)
		{
			const CReleve& ra = ec.ReleveAnnuel(iRA);
			printf("Relevé annuel en %d : %lg km²\n", ra.Annee(), ra.Superficie());
		}
		printf("\nVoici par zone, les pourcentages de superficie par année :\n");
		for (long iZEC = 0, nZEC = ec.NombreZones(); iZEC < nZEC; iZEC++)
		{
			const CZone& zec = ec.Zone(iZEC);
			printf("\nZone %ld/%ld :\n* nom : %s\n", iZEC + 1, nZEC, zec.Nom());
			for (long iRA = 0, nRA = ec.NombreRelevesAnnuels(); iRA < nRA; iRA++)
			{
				const CReleve& ra = ec.ReleveAnnuel(iRA);
				long iR = zec.RechercherReleve(ra);
				if (iR >= 0)
				{
					const CReleve& r = zec.Releve(iR);
					double pourcentage = r.Superficie() / ra.Superficie() * 100.0;
					printf("* relevé en %d : %.2lf %% (%lg km² / %lg km²)\n", ra.Annee(), pourcentage, r.Superficie(), ra.Superficie());
				}
				else
				{
					printf("* relevé en %d : 0 %% (0 km² / %lg km²)\n", ra.Annee(), ra.Superficie());
				}
			}
		}
		if (iEC < (nEC - 1))
			AttendreTouche(TOUCHE_RETURN, "passer à l'analyse croisée de l'entité communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer à l'exportation des résultats");
	}
}

/// <summary>
/// Permet de contrôler la validité des données calculées pendant le chargement
/// </summary>
/// <param name="geo">Objet contenant toutes les données de GeoCommune</param>
void ControlerCalculs(const CGeoCommune& geo)
{
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		CChaine titre(ec.Nom(), CChaine::EnMajuscule);
		CChaine soulignement('=', titre.Longueur());
		console_clear();
		printf("            %s\n", titre.Contenu());
		printf("            %s\n", soulignement.Contenu());
		for (long iRA = 0, nRA = ec.NombreRelevesAnnuels(); iRA < nRA; iRA++)
		{
			const CReleve& ra = ec.ReleveAnnuel(iRA);
			double sommeReleves = 0.0;
			for (long iZEC = 0, nZEC = ec.NombreZones(); iZEC < nZEC; iZEC++)
			{
				const CZone& zec = ec.Zone(iZEC);
				long iR = zec.RechercherReleve(ra);
				if (iR >= 0)
				{
					const CReleve& r = zec.Releve(iR);
					sommeReleves += r.Superficie();
				}
			}
			printf("\nPour l'année %d, on trouve :\n* une somme des relevés des zones de %lg km²\n* un relevé annuel de %lg km²", ra.Annee(), sommeReleves, ra.Superficie());
		}
		if (iEC < (nEC - 1))
			AttendreTouche(TOUCHE_RETURN, "passer à l'analyse croisée de l'entité communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer à la suite du traitement");
	}
}

/*
//#include "GeoCommune.h"
class CGeoCommune
{
public:
	bool Charger(const char* nomFichier) { return false; }
};
*/
