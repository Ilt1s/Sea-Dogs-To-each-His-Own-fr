#include "SD\TEXT\DIALOGS\Plantation.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
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
			dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]), RandPhraseSimple(DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));				
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[8],DLG_TEXT_BASE[9]), RandPhraseSimple(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]));				
			link.l1 = RandPhraseSimple("Hm...", "Bien...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[12], DLG_TEXT_BASE[13]), RandPhraseSimple(DLG_TEXT_BASE[14], DLG_TEXT_BASE[15]));
			link.l1 = RandPhraseSimple("Je vois...", "D'accord...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("VOICE\Russian\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[18], DLG_TEXT_BASE[19]);
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[20]+NationNameGenitive(sti(pchar.nation))+DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]+NationNameAblative(sti(pchar.nation))+DLG_TEXT_BASE[23]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[24], DLG_TEXT_BASE[25]);
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("VOICE\Russian\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[26], DLG_TEXT_BASE[27]);
						link.l1 = RandPhraseSimple(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29]);
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31]);
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = DLG_TEXT_BASE[32];
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = DLG_TEXT_BASE[33];
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
				}
				else
				{
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[34], DLG_TEXT_BASE[35]);
					link.l1 = DLG_TEXT_BASE[36];
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = DLG_TEXT_BASE[37];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("VOICE\Russian\soldier_arest_1.wav");
				dialog.text = DLG_TEXT_BASE[40];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[41], DLG_TEXT_BASE[42]);
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = DLG_TEXT_BASE[43];
			link.l1 = DLG_TEXT_BASE[44];
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = DLG_TEXT_BASE[45]+NationNameAblative(sti(GetBaseHeroNation()))+DLG_TEXT_BASE[46];
			link.l1 = DLG_TEXT_BASE[47];
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = DLG_TEXT_BASE[50];
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2" && GetSquadronGoods(pchar, GOOD_SLAVES) >= 50)
			{
				dialog.text = DLG_TEXT_BASE[51];
				link.l1 = TimeGreeting()+DLG_TEXT_BASE[52]+FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES)))+DLG_TEXT_BASE[53];
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = DLG_TEXT_BASE[54];
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = DLG_TEXT_BASE[56];
				link.l1 = DLG_TEXT_BASE[57];
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
            dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = DLG_TEXT_BASE[68];
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = DLG_TEXT_BASE[69];
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = DLG_TEXT_BASE[70];
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = DLG_TEXT_BASE[71];
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = DLG_TEXT_BASE[72]+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+DLG_TEXT_BASE[73]+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_cinnamon":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = DLG_TEXT_BASE[76]+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+DLG_TEXT_BASE[77]+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_copra":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = DLG_TEXT_BASE[80]+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+DLG_TEXT_BASE[81]+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "mtraxx_10";
		break;
		
		
		case "mtraxx_10":
            dialog.text = DLG_TEXT_BASE[90];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
	}
} 
