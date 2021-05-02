#include "SD\TEXT\DIALOGS\Quest_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_GUB[0], DLG_TEXT_GUB[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_GUB[2], DLG_TEXT_GUB[3]);
		    link.l1.go = "exit";
		break;

		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = DLG_TEXT_GUB[352];
                link.l1 = DLG_TEXT_GUB[353];
                link.l1.go = "exit";
				break;
			}                   
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
