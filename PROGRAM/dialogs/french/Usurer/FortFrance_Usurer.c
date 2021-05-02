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
			//--> Ѕрем€ гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = DLG_TEXT_USR[13];
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = DLG_TEXT_USR[14];
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = DLG_TEXT_USR[15];
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = DLG_TEXT_USR[16];
                link.l1.go = "Sharlie_14";
			}
			//<-- Ѕрем€ гасконца
		break;
		
		case "Sharlie":
			dialog.text = DLG_TEXT_USR[17];
			link.l1 = DLG_TEXT_USR[18];
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = DLG_TEXT_USR[19];
			link.l1 = DLG_TEXT_USR[20];
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = DLG_TEXT_USR[21];
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = DLG_TEXT_USR[22];
				link.l1.go = "Sharlie_3";
			}
			link.l2 = DLG_TEXT_USR[23];
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = DLG_TEXT_USR[24];
			link.l1 = DLG_TEXT_USR[25]+npchar.name+" !";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("Lettre de reconnaissance de dette obtenue");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = DLG_TEXT_USR[133];
			link.l1 = DLG_TEXT_USR[134];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = DLG_TEXT_USR[27];
			link.l1 = DLG_TEXT_USR[28];
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = DLG_TEXT_USR[29];
			link.l1 = DLG_TEXT_USR[30];
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = DLG_TEXT_USR[31]+DLG_TEXT_USR[32]+DLG_TEXT_USR[33];
			link.l1 = DLG_TEXT_USR[34];
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = DLG_TEXT_USR[35];
			link.l1 = DLG_TEXT_USR[36];
			link.l1.go = "Sharlie_10";
			link.l2 = DLG_TEXT_USR[37];
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = DLG_TEXT_USR[38];
			link.l1 = DLG_TEXT_USR[39];
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = DLG_TEXT_USR[40]+DLG_TEXT_USR[41];
			link.l1 = DLG_TEXT_USR[42];
			if (CheckCharacterItem(pchar, "pistol1")) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = DLG_TEXT_USR[43];
			link.l1 = DLG_TEXT_USR[44];
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info(DLG_TEXT_USR[45]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = DLG_TEXT_USR[46];
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 21.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать врем€
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = DLG_TEXT_USR[47];
			link.l1 = DLG_TEXT_USR[48];
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = DLG_TEXT_USR[49];
			link.l1 = DLG_TEXT_USR[50];
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = DLG_TEXT_USR[51];
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = DLG_TEXT_USR[52];
				link.l1.go = "Sharlie_3";
			}
			link.l2 = DLG_TEXT_USR[53];
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = DLG_TEXT_USR[54];
			link.l1 = DLG_TEXT_USR[55];
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = DLG_TEXT_USR[56];
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info(DLG_TEXT_USR[57]);
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

