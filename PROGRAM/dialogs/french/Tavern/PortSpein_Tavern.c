#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[83], DLG_TEXT_STR[84] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_STR[85] + GetAddress_Form(NPChar) + "...", DLG_TEXT_STR[86],
                          DLG_TEXT_STR[87], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[88], DLG_TEXT_STR[89]), DLG_TEXT_STR[90],
                      DLG_TEXT_STR[91], DLG_TEXT_STR[92], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = DLG_TEXT_STR[179];
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = DLG_TEXT_STR[180];
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = DLG_TEXT_STR[181];
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = DLG_TEXT_STR[182];
				link.l1.go = "guardoftruth";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = DLG_TEXT_STR[183];
			link.l1 = DLG_TEXT_STR[184];
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = DLG_TEXT_STR[185];
			link.l1 = DLG_TEXT_STR[186];
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = DLG_TEXT_STR[187];
			link.l1 = DLG_TEXT_STR[188];
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = DLG_TEXT_STR[189]+DLG_TEXT_STR[190];
			link.l1 = DLG_TEXT_STR[191];
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = DLG_TEXT_STR[192];
			link.l1 = DLG_TEXT_STR[193];
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = DLG_TEXT_STR[194]+DLG_TEXT_STR[195];
			link.l1 = DLG_TEXT_STR[196];
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = DLG_TEXT_STR[197];
				link.l1 = DLG_TEXT_STR[198];
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = DLG_TEXT_STR[199];
				link.l1 = DLG_TEXT_STR[200];
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = DLG_TEXT_STR[201];
			link.l1 = DLG_TEXT_STR[202];
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = DLG_TEXT_STR[203]+DLG_TEXT_STR[204];
			link.l1 = DLG_TEXT_STR[205];
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = DLG_TEXT_STR[206];
			link.l1 = DLG_TEXT_STR[207]+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = DLG_TEXT_STR[208];
			link.l1 = DLG_TEXT_STR[209];
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = DLG_TEXT_STR[210];
			link.l1 = DLG_TEXT_STR[211];
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_STR[212]+DLG_TEXT_STR[213];
			link.l1 = DLG_TEXT_STR[214];
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}