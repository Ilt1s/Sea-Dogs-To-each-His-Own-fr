#include "SD\TEXT\DIALOGS\Quest_church.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[0], DLG_TEXT_CHR[1]), DLG_TEXT_CHR[2], DLG_TEXT_CHR[3],
                          DLG_TEXT_CHR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[5], DLG_TEXT_CHR[6]), DLG_TEXT_CHR[7],
                      DLG_TEXT_CHR[8], DLG_TEXT_CHR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = DLG_TEXT_CHR[24];
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_CHR[25];
			link.l1 = DLG_TEXT_CHR[26];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_CHR[27];
			link.l1 = DLG_TEXT_CHR[28];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_CHR[29];
			link.l1 = DLG_TEXT_CHR[30];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = DLG_TEXT_CHR[31];
			link.l1 = DLG_TEXT_CHR[32];
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = DLG_TEXT_CHR[33]+DLG_TEXT_CHR[34]+DLG_TEXT_CHR[35]+DLG_TEXT_CHR[36];
			link.l1 = DLG_TEXT_CHR[37];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_CHR[38];
			link.l1 = DLG_TEXT_CHR[39];
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = DLG_TEXT_CHR[40];
			link.l1 = DLG_TEXT_CHR[41];
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info(DLG_TEXT_CHR[42]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = DLG_TEXT_CHR[43]+sld.name+DLG_TEXT_CHR[44];
			link.l1 = DLG_TEXT_CHR[45];
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = DLG_TEXT_CHR[46]+DLG_TEXT_CHR[47]+sld.name+DLG_TEXT_CHR[48];
			link.l1 = DLG_TEXT_CHR[49];
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = DLG_TEXT_CHR[50]+DLG_TEXT_CHR[51]+sld.name+DLG_TEXT_CHR[52];
			link.l1 = DLG_TEXT_CHR[53];
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = DLG_TEXT_CHR[54];
			link.l1 = DLG_TEXT_CHR[55];
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}