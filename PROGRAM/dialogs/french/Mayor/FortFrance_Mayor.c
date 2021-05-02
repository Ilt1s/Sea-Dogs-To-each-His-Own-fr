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
			//--> Ѕрем€ гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = DLG_TEXT_MR[23];
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Ѕрем€ гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = DLG_TEXT_MR[307];
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = DLG_TEXT_MR[308];
                link.l1.go = "patria_2";
			}			
			// Jason ƒороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = DLG_TEXT_MR[1207];
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = DLG_TEXT_MR[1208];
                link.l1.go = "goldengirl_10";
			}			
		break;
		
		case "Sharlie_junglejew":
			dialog.text = DLG_TEXT_MR[24]+DLG_TEXT_MR[25]+DLG_TEXT_MR[26];
			link.l1 = DLG_TEXT_MR[27];
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_bad"); 
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = DLG_TEXT_MR[309];
				link.l1 = DLG_TEXT_MR[310];
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[311];
				link.l1 = DLG_TEXT_MR[312];
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = DLG_TEXT_MR[313];
			link.l1 = DLG_TEXT_MR[314];
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		// Jason ƒороже золота
		case "goldengirl":
			dialog.text = DLG_TEXT_MR[1209];
			link.l1 = DLG_TEXT_MR[1210];
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = DLG_TEXT_MR[1211];
			link.l1 = DLG_TEXT_MR[1212];
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = DLG_TEXT_MR[1213];
			link.l1 = DLG_TEXT_MR[1214];
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = DLG_TEXT_MR[1215];
			link.l1 = DLG_TEXT_MR[1216];
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = DLG_TEXT_MR[1217];
			link.l1 = DLG_TEXT_MR[1218];
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = DLG_TEXT_MR[1219];
			link.l1 = DLG_TEXT_MR[1220];
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = DLG_TEXT_MR[1221];
			link.l1 = DLG_TEXT_MR[1222];
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = DLG_TEXT_MR[1223];
			link.l1 = DLG_TEXT_MR[1224];
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = DLG_TEXT_MR[1225];
			link.l1 = DLG_TEXT_MR[1226];
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей бордел€
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = DLG_TEXT_MR[1227];
			link.l1 = DLG_TEXT_MR[1228];
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = DLG_TEXT_MR[1229];
			link.l1 = DLG_TEXT_MR[1230];
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = DLG_TEXT_MR[1231];
			link.l1 = DLG_TEXT_MR[1232];
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = DLG_TEXT_MR[1233];
			link.l1 = DLG_TEXT_MR[1234];
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = DLG_TEXT_MR[1235];
			link.l1 = DLG_TEXT_MR[1236];
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
