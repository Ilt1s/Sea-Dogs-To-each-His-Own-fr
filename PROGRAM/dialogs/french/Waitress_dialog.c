#include "SD\TEXT\DIALOGS\Waitress_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason ÷ена чахотки
			if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption"))
            {
				dialog.text = DLG_TEXT_BASE[55];
				link.l1 = DLG_TEXT_BASE[56];
				link.l1.go = "Consumption";
				break;
			}
			//<-- ÷ена чахотки
			
			// Addon-2016 Jason, французские миниквесты (ФМК) Порт Пренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				PlaySound("VOICE\Russian\Enc_RapersGirl_1.wav");
				dialog.text = DLG_TEXT_BASE[85];
				link.l1 = DLG_TEXT_BASE[86];
				link.l1.go = "FMQP";
				break;
			}
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = DLG_TEXT_BASE[0];
					link.l1 = DLG_TEXT_BASE[1];
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = DLG_TEXT_BASE[2];
					link.l1 = DLG_TEXT_BASE[3] + pchar.questTemp.different.FackWaitress.Name + DLG_TEXT_BASE[4];
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = DLG_TEXT_BASE[5];
					link.l1 = DLG_TEXT_BASE[6];
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = DLG_TEXT_BASE[7];
					link.l1 = DLG_TEXT_BASE[8];
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[57]+ GetSexPhrase("beau gosse","ma mignonne") +DLG_TEXT_BASE[9];
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[10];
					link.l1 = ""+ GetSexPhrase(DLG_TEXT_BASE[11],DLG_TEXT_BASE[58]) +"";
					link.l1.go = "exit";
				break;

				case 2:
					if (drand(1) == 0) // Addon-2016 Jason
					{
					dialog.text = ""+ GetSexPhrase(DLG_TEXT_BASE[12],DLG_TEXT_BASE[59]) +"";
					link.l1 = DLG_TEXT_BASE[13];
					link.l1.go = "exit";
					bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")); // 291112
					if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
					{
						link.l2 = DLG_TEXT_BASE[14];
						link.l2.go = "Love_1";
					}
					}
					else
					{
						dialog.text = DLG_TEXT_BASE[87];
						link.l1 = DLG_TEXT_BASE[88];
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[15];
					link.l1 = DLG_TEXT_BASE[16];
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[17];
					link.l1 = DLG_TEXT_BASE[18];
					link.l1.go = "exit";
				break;
			}			
			link.l9 = DLG_TEXT_BASE[20];
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = DLG_TEXT_BASE[22];
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Ўанс, что ограб€т, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = cRand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним им€ официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = DLG_TEXT_BASE[23];
			link.l1 = DLG_TEXT_BASE[24];
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = DLG_TEXT_BASE[27];
			link.l1 = DLG_TEXT_BASE[28];
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = DLG_TEXT_BASE[29];
			link.l1 = DLG_TEXT_BASE[30];
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = DLG_TEXT_BASE[33];
			link.l1 = DLG_TEXT_BASE[34];
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = DLG_TEXT_BASE[35];
			link.l2 = DLG_TEXT_BASE[36];
			link.l2.go = "exit";
		break;
		
		//--> Jason ÷ена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[66];
			link.l2.go = "Consumption_3_1";
			link.l3 = DLG_TEXT_BASE[67];
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = DLG_TEXT_BASE[68];
				link.l1 = DLG_TEXT_BASE[69];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[70];
				link.l1 = DLG_TEXT_BASE[71];
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = DLG_TEXT_BASE[74]
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77];
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = DLG_TEXT_BASE[80]+DLG_TEXT_BASE[81];
			link.l1 = DLG_TEXT_BASE[82];
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84];
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- ÷ена чахотки
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Порт Пренс
		case "FMQP":
			dialog.text = DLG_TEXT_BASE[89];
			link.l1 = DLG_TEXT_BASE[90];
			link.l1.go = "FMQP_1";
			link.l2 = DLG_TEXT_BASE[91];
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = DLG_TEXT_BASE[92];
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}