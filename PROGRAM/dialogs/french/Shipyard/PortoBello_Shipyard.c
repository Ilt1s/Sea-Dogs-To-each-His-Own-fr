// диалог по городам
#include "SD\TEXT\DIALOGS\Quest_Shipyard.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[0], DLG_TEXT_SHY[1]), DLG_TEXT_SHY[2], DLG_TEXT_SHY[3],
                          DLG_TEXT_SHY[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[5], DLG_TEXT_SHY[6]), DLG_TEXT_SHY[7],
                      DLG_TEXT_SHY[8], DLG_TEXT_SHY[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = DLG_TEXT_SHY[16];
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = DLG_TEXT_SHY[17];
			link.l1 = DLG_TEXT_SHY[18];
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = DLG_TEXT_SHY[20];
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
