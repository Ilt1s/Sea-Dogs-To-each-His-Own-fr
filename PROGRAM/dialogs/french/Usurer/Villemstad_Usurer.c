#include "SD\TEXT\DIALOGS\Quest_usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = DLG_TEXT_USR[77];
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = DLG_TEXT_USR[78];
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_USR[79];
			link.l1 = DLG_TEXT_USR[80];
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_USR[81];
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 =DLG_TEXT_USR[82];
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = DLG_TEXT_USR[83];
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = DLG_TEXT_USR[84];
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = DLG_TEXT_USR[85]+GetFullName(pchar)+DLG_TEXT_USR[86];
			link.l1 = DLG_TEXT_USR[87];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = DLG_TEXT_USR[88]+GetFullName(pchar)+DLG_TEXT_USR[89];
			link.l1 = DLG_TEXT_USR[90];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = DLG_TEXT_USR[91];
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = DLG_TEXT_USR[92];
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = DLG_TEXT_USR[93];
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info(DLG_TEXT_USR[94]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_USR[95];
			link.l1 = DLG_TEXT_USR[96];
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = DLG_TEXT_USR[97];
			link.l1 = DLG_TEXT_USR[98];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_USR[99];
			link.l1 = DLG_TEXT_USR[100];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = DLG_TEXT_USR[101];
			link.l1 = DLG_TEXT_USR[102];
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = DLG_TEXT_USR[103];
			link.l1 = DLG_TEXT_USR[104];
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = DLG_TEXT_USR[105];
			link.l1 = DLG_TEXT_USR[106]+npchar.name+DLG_TEXT_USR[107];
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = DLG_TEXT_USR[108];
			link.l1 = DLG_TEXT_USR[109];
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
