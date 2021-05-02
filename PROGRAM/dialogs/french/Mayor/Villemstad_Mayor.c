#include "SD\TEXT\DIALOGS\Quest_Mayor.h"// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = DLG_TEXT_MR[46];
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[47], DLG_TEXT_MR[48]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[49], DLG_TEXT_MR[50]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = DLG_TEXT_MR[51];
			link.l1 = DLG_TEXT_MR[52];
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = DLG_TEXT_MR[53];
			link.l1 = DLG_TEXT_MR[54];
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = DLG_TEXT_MR[55];
			link.l1 = DLG_TEXT_MR[56];
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info(DLG_TEXT_MR[57]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_MR[58];
			link.l1 = DLG_TEXT_MR[59];
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}