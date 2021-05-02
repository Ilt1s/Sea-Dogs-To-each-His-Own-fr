#include "SD\TEXT\DIALOGS\Quest_Portman.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = DLG_TEXT_PRT[55] + pchar.questTemp.Slavetrader.ShipName + DLG_TEXT_PRT[56];
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = DLG_TEXT_PRT[57];
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = DLG_TEXT_PRT[130];
				link.l1.go = "mtraxx";
			}			
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_PRT[58], DLG_TEXT_PRT[59], DLG_TEXT_PRT[60], DLG_TEXT_PRT[61], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_PRT[62], DLG_TEXT_PRT[63], DLG_TEXT_PRT[64], DLG_TEXT_PRT[65] + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_PRT[66];
			link.l1 = DLG_TEXT_PRT[67];
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = DLG_TEXT_PRT[131];
			link.l1 = DLG_TEXT_PRT[132];
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
