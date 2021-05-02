#include "SD\TEXT\DIALOGS\Quest_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_GUB[0], DLG_TEXT_GUB[1]);
				link.l1 = DLG_TEXT_GUB[357];
				link.l1.go = "Portugal";
				break;
			}
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
		
		//Португалец
		case "Portugal":
			dialog.text = DLG_TEXT_GUB[358];
			link.l1 = DLG_TEXT_GUB[359];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_GUB[360];
			link.l1 = DLG_TEXT_GUB[361];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = DLG_TEXT_GUB[362];
			link.l1 = DLG_TEXT_GUB[363];
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info(DLG_TEXT_GUB[364]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_GUB[365];
			link.l1 = DLG_TEXT_GUB[366];
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
