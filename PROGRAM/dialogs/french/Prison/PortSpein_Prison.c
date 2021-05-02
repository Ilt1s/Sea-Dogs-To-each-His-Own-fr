#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = DLG_TEXT_PRS[7];
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = DLG_TEXT_PRS[8];
			link.l1 = DLG_TEXT_PRS[9];
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = DLG_TEXT_PRS[10];
			link.l1 = DLG_TEXT_PRS[11];
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = DLG_TEXT_PRS[12]+DLG_TEXT_PRS[13];
			link.l1 = DLG_TEXT_PRS[14];
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = DLG_TEXT_PRS[15];
			link.l1 = DLG_TEXT_PRS[16];
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = DLG_TEXT_PRS[17];
			link.l1 = DLG_TEXT_PRS[18];
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
