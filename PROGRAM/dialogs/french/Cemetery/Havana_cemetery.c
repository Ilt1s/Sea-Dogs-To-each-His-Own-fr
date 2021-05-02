#include "SD\TEXT\DIALOGS\Quest_cemeteryman.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CE[0], DLG_TEXT_CE[1]), DLG_TEXT_CE[2] + GetAddress_Form(NPChar) + " ?", DLG_TEXT_CE[3], DLG_TEXT_CE[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CE[5], DLG_TEXT_CE[6]), DLG_TEXT_CE[7],
                      DLG_TEXT_CE[8], DLG_TEXT_CE[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = DLG_TEXT_CE[10];
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_CE[11];
			link.l1 = DLG_TEXT_CE[12];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_CE[13];
			link.l1 = DLG_TEXT_CE[14];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_CE[15];
			link.l1 = DLG_TEXT_CE[16];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "";
			link.l1 = DLG_TEXT_CE[17];
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "";
			link.l1 = DLG_TEXT_CE[18];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_CE[19];
			link.l1 = DLG_TEXT_CE[20];
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = DLG_TEXT_CE[21];
			link.l1 = DLG_TEXT_CE[22];
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = DLG_TEXT_CE[23];
			link.l1 = DLG_TEXT_CE[24];
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = DLG_TEXT_CE[25];
			link.l1 = DLG_TEXT_CE[26];
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = DLG_TEXT_CE[27];
			link.l1 = DLG_TEXT_CE[28];
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = DLG_TEXT_CE[29];
			link.l1 = DLG_TEXT_CE[30];
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = DLG_TEXT_CE[31];
			link.l1 = DLG_TEXT_CE[32];
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = DLG_TEXT_CE[33];
			link.l1 = DLG_TEXT_CE[34];
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

