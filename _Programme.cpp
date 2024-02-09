#include "BisConsole.h"
#include "Interface.h"
#include "DocumentHtml.h"
#include "GeoCommune.h"


/// <summary>
/// Permet d'afficher toutes les donn�es charg�es
/// </summary>
/// <param name="geo">Objet contenant toutes les donn�es de GeoCommune</param>
void AfficherDonnees(const CGeoCommune& geo);

/// <summary>
/// Permet de contr�ler la validit� des donn�es calcul�es pendant le chargement
/// </summary>
/// <param name="geo">Objet contenant toutes les donn�es de GeoCommune</param>
void ControlerCalculs(const CGeoCommune& geo);

/// <summary>
/// Point d'entr�e de l'application
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
/// Permet d'afficher toutes les donn�es charg�es
/// </summary>
/// <param name="geo">Objet contenant toutes les donn�es de GeoCommune</param>
void AfficherDonnees(const CGeoCommune& geo)
{
	console_clear();
	printf("            Liste des entit�s communales\n");
	printf("            ============================\n");
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		printf("\nEntit� communale %ld/%ld :\n* nom : %s\n", iEC + 1, nEC, ec.Nom());
	}
	AttendreTouche(TOUCHE_ESC, "passer � la liste des communes par entit� communale");
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
			AttendreTouche(TOUCHE_RETURN, "passer � la liste des communes de l'entit� communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer au d�tail des relev�s de zones par commune");
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
					printf("* relev� en %d : %lg km�\n", r.Annee(), r.Superficie());
				}
			}
			if ((iC < (nC - 1)) || (iEC < (nEC - 1)))
				AttendreTouche(TOUCHE_RETURN, "passer au d�tail des relev�s de la commune suivante");
			else
				AttendreTouche(TOUCHE_ESC, "passer � l'analyse crois�e par entit� communale");
		}
	}
	// Simulation par affichage des tableaux d'analyse crois�e
	for (long iEC = 0, nEC = geo.NombreEntitesCommunales(); iEC < nEC; iEC++)
	{
		const CEntiteCommunale& ec = geo.EntiteCommunale(iEC);
		CChaine titre(ec.Nom(), CChaine::EnMajuscule);
		CChaine soulignement('=', titre.Longueur());
		console_clear();
		printf("            %s\n", titre.Contenu());
		printf("            %s\n", soulignement.Contenu());
		printf("\nVoici les ann�es de relev�s pris en compte :\n");
		for (long iRA = 0, nRA = ec.NombreRelevesAnnuels(); iRA < nRA; iRA++)
		{
			const CReleve& ra = ec.ReleveAnnuel(iRA);
			printf("Relev� annuel en %d : %lg km�\n", ra.Annee(), ra.Superficie());
		}
		printf("\nVoici par zone, les pourcentages de superficie par ann�e :\n");
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
					printf("* relev� en %d : %.2lf %% (%lg km� / %lg km�)\n", ra.Annee(), pourcentage, r.Superficie(), ra.Superficie());
				}
				else
				{
					printf("* relev� en %d : 0 %% (0 km� / %lg km�)\n", ra.Annee(), ra.Superficie());
				}
			}
		}
		if (iEC < (nEC - 1))
			AttendreTouche(TOUCHE_RETURN, "passer � l'analyse crois�e de l'entit� communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer � l'exportation des r�sultats");
	}
}

/// <summary>
/// Permet de contr�ler la validit� des donn�es calcul�es pendant le chargement
/// </summary>
/// <param name="geo">Objet contenant toutes les donn�es de GeoCommune</param>
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
			printf("\nPour l'ann�e %d, on trouve :\n* une somme des relev�s des zones de %lg km�\n* un relev� annuel de %lg km�", ra.Annee(), sommeReleves, ra.Superficie());
		}
		if (iEC < (nEC - 1))
			AttendreTouche(TOUCHE_RETURN, "passer � l'analyse crois�e de l'entit� communale suivante");
		else
			AttendreTouche(TOUCHE_ESC, "passer � la suite du traitement");
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
