#include "SD\TEXT\DIALOGS\Quest\Plantation_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_Q[2], DLG_TEXT_Q[3]), RandPhraseSimple(DLG_TEXT_Q[4], DLG_TEXT_Q[5]));				
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[6], DLG_TEXT_Q[7]);
				link.l1.go = "exit";				
    		} 
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_Q[8], DLG_TEXT_Q[9]), RandPhraseSimple(DLG_TEXT_Q[10], DLG_TEXT_Q[11]));
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[12], DLG_TEXT_Q[13]);
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("VOICE\Russian\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple(DLG_TEXT_Q[14], DLG_TEXT_Q[15]);
					link.l1 = RandPhraseSimple(DLG_TEXT_Q[16], DLG_TEXT_Q[17]);
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple(DLG_TEXT_Q[18]+NationNameGenitive(sti(pchar.nation))+DLG_TEXT_Q[19], DLG_TEXT_Q[20]+NationNameAblative(sti(pchar.nation))+DLG_TEXT_Q[21]);
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[22], DLG_TEXT_Q[23]);
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("VOICE\Russian\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple(DLG_TEXT_Q[24], DLG_TEXT_Q[25]);
						link.l1 = RandPhraseSimple(DLG_TEXT_Q[26], DLG_TEXT_Q[27]);
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple(DLG_TEXT_Q[28], DLG_TEXT_Q[29]);
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = DLG_TEXT_Q[30];
						link.l1.go = "Licence";
						link.l2 = DLG_TEXT_Q[31];
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l2.go = "NotPegYou";
					}
					else
					{
						link.l1 = DLG_TEXT_Q[32];
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
				}
				else
				{
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple(DLG_TEXT_Q[33], DLG_TEXT_Q[34]);
					link.l1 = DLG_TEXT_Q[35];
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = DLG_TEXT_Q[36];
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[37], DLG_TEXT_Q[38]);
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("VOICE\Russian\soldier_arest_1.wav");
				dialog.text = DLG_TEXT_Q[39];
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[40], DLG_TEXT_Q[41]);
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = DLG_TEXT_Q[44]+NationNameAblative(sti(GetBaseHeroNation()))+DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = DLG_TEXT_Q[49];
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2" && GetSquadronGoods(pchar, GOOD_SLAVES) >=50)
			{
				dialog.text = DLG_TEXT_Q[50];
				link.l1 = TimeGreeting()+DLG_TEXT_Q[51]+FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES)))+DLG_TEXT_Q[52];
				link.l1.go = "mtraxx";
			}
            dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "exit";
		break;
		
		case "plantator_1":
            dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "exit";
		break;
		
		case "mtraxx":
            dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		break;
		
		case "":
            dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
            dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
            dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		
		case "":
            dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
            dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
	}
} 
