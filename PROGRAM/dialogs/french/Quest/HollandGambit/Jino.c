#include "SD\TEXT\DIALOGS\Quest\HollandGambit\Jino.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = DLG_TEXT_Q[0];
				link.l1 = DLG_TEXT_Q[1]+GetFullName(pchar)+DLG_TEXT_Q[2];
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_Q[3];
				link.l1 = DLG_TEXT_Q[4];
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = DLG_TEXT_Q[5] + pchar.name + DLG_TEXT_Q[6];
					link.l1 = DLG_TEXT_Q[7];
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = DLG_TEXT_Q[8] + pchar.name + DLG_TEXT_Q[9];
					link.l1 = DLG_TEXT_Q[10];
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+DLG_TEXT_Q[11];
					link.l1 = DLG_TEXT_Q[12];
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = DLG_TEXT_Q[13] + pchar.name + " ?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = DLG_TEXT_Q[14];
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 4);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 4);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 4);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = DLG_TEXT_Q[15];
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = DLG_TEXT_Q[16] + pchar.name + DLG_TEXT_Q[17];
					link.l1 = DLG_TEXT_Q[18];
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = DLG_TEXT_Q[19] + pchar.name + DLG_TEXT_Q[20];
					link.l1 = DLG_TEXT_Q[21];
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = "" + pchar.name + DLG_TEXT_Q[22];
					link.l1 = DLG_TEXT_Q[23];
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = DLG_TEXT_Q[24] + pchar.name + DLG_TEXT_Q[25];
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = DLG_TEXT_Q[26];
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
					}
					else
					{
						link.l1 = DLG_TEXT_Q[27];
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесет через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = DLG_TEXT_Q[28] + pchar.name + DLG_TEXT_Q[29];
					link.l1 = DLG_TEXT_Q[30];
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = DLG_TEXT_Q[31] + pchar.name + DLG_TEXT_Q[32];
					link.l1 = DLG_TEXT_Q[33];
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = DLG_TEXT_Q[34];
					link.l1 = DLG_TEXT_Q[35];
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = DLG_TEXT_Q[36];
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = DLG_TEXT_Q[37];
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = DLG_TEXT_Q[38];
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = DLG_TEXT_Q[39];
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = DLG_TEXT_Q[40];
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = DLG_TEXT_Q[41];
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = DLG_TEXT_Q[42];
					link.l3.go = "mtraxx";
				}
				link.l9 = DLG_TEXT_Q[43];
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45]+GetFullName(pchar)+DLG_TEXT_Q[46];
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = DLG_TEXT_Q[52]+GetAddress_Form(NPChar)+DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info(DLG_TEXT_Q[59]);
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion3");
			Log_Info(DLG_TEXT_Q[64]);
			PlaySound("interface\notebook.wav");
			Log_Info(DLG_TEXT_Q[65]);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info(DLG_TEXT_Q[74]);
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = DLG_TEXT_Q[77]+pchar.name+DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = DLG_TEXT_Q[84];
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = DLG_TEXT_Q[87];
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = DLG_TEXT_Q[88];
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[89];
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info(DLG_TEXT_Q[90]);
			Log_Info(DLG_TEXT_Q[91]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = DLG_TEXT_Q[114];
			link.l1 = DLG_TEXT_Q[115];
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info(DLG_TEXT_Q[116]);
			Log_Info(DLG_TEXT_Q[117]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			pchar.questTemp.Portugal = "Portugal_wait";
			int iShipType = GetCharacterShipType(pchar);
			ref rShip = GetRealShip(iShipType);
			sTemp = "My_" + rShip.CabinType;
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_9";
			ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
			LAi_SetStayType(sld);
		break;
		
		case "Portugal_nomoney":
			dialog.text = DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = DLG_TEXT_Q[140];
			link.l1 = DLG_TEXT_Q[141];
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = DLG_TEXT_Q[142];
			link.l1 = DLG_TEXT_Q[143];
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = DLG_TEXT_Q[144];
			link.l1 = DLG_TEXT_Q[145];
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = DLG_TEXT_Q[146];
			link.l1 = DLG_TEXT_Q[147];
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = DLG_TEXT_Q[148];
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = DLG_TEXT_Q[152];
			link.l1 = DLG_TEXT_Q[153];
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_Q[156];
			link.l1 = DLG_TEXT_Q[157];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_Q[162];
			link.l1 = DLG_TEXT_Q[163];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = DLG_TEXT_Q[170];
			link.l1 = DLG_TEXT_Q[171];
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = DLG_TEXT_Q[172];
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = DLG_TEXT_Q[174]+pchar.name+DLG_TEXT_Q[175];
			link.l1 = DLG_TEXT_Q[176];
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = DLG_TEXT_Q[185];
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = DLG_TEXT_Q[186];
			else link.l1 = DLG_TEXT_Q[187];
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = DLG_TEXT_Q[188];
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = DLG_TEXT_Q[189];
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[190];
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = DLG_TEXT_Q[191];
			link.l1 = DLG_TEXT_Q[192];
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = DLG_TEXT_Q[209];
			link.l1 = DLG_TEXT_Q[210];
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214];
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = DLG_TEXT_Q[215];
			link.l1 = DLG_TEXT_Q[216];
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = DLG_TEXT_Q[217];
			link.l1 = DLG_TEXT_Q[218];
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = DLG_TEXT_Q[219];
			link.l1 = DLG_TEXT_Q[220];
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = DLG_TEXT_Q[225];
			link.l1 = DLG_TEXT_Q[226];
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info(DLG_TEXT_Q[227]);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = DLG_TEXT_Q[228];
			link.l1 = DLG_TEXT_Q[229];
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = DLG_TEXT_Q[232]+pchar.name+DLG_TEXT_Q[233];
			link.l1 = DLG_TEXT_Q[234];
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = DLG_TEXT_Q[235];
			link.l1 = DLG_TEXT_Q[236];
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = DLG_TEXT_Q[237];
			link.l1 = DLG_TEXT_Q[238];
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = DLG_TEXT_Q[239];
			link.l1 = DLG_TEXT_Q[240];
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = DLG_TEXT_Q[241];
			link.l1 = DLG_TEXT_Q[242];
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = DLG_TEXT_Q[243];
			link.l1 = DLG_TEXT_Q[244];
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = DLG_TEXT_Q[245];
			link.l1 = DLG_TEXT_Q[246];
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = DLG_TEXT_Q[247]+pchar.name+"...";
			link.l1 = DLG_TEXT_Q[248];
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[249];
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = DLG_TEXT_Q[250];
			link.l1 = DLG_TEXT_Q[251];
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = DLG_TEXT_Q[252];
			link.l1 = DLG_TEXT_Q[253];
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = DLG_TEXT_Q[254]+pchar.name+DLG_TEXT_Q[255];
			link.l1 = DLG_TEXT_Q[256];
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = DLG_TEXT_Q[257]+pchar.name+" ?";
			link.l1 = DLG_TEXT_Q[258];
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = DLG_TEXT_Q[259];
			link.l1 = DLG_TEXT_Q[260];
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = DLG_TEXT_Q[261];
			link.l1 = DLG_TEXT_Q[262];
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = DLG_TEXT_Q[263]+pchar.name+DLG_TEXT_Q[264];
			link.l1 = DLG_TEXT_Q[265];
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = DLG_TEXT_Q[266];
			link.l1 = DLG_TEXT_Q[267];
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = DLG_TEXT_Q[268];
			link.l1 = DLG_TEXT_Q[269];
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = DLG_TEXT_Q[270];
			link.l1 = DLG_TEXT_Q[271];
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+DLG_TEXT_Q[272];
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = DLG_TEXT_Q[273];
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = DLG_TEXT_Q[274];
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = DLG_TEXT_Q[275];
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = DLG_TEXT_Q[276];
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = DLG_TEXT_Q[277]+pchar.name+DLG_TEXT_Q[278];
			link.l1 = DLG_TEXT_Q[279];
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = DLG_TEXT_Q[280];
			link.l1 = DLG_TEXT_Q[281];
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = DLG_TEXT_Q[282]+pchar.name+DLG_TEXT_Q[283];
			link.l1 = DLG_TEXT_Q[284];
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = DLG_TEXT_Q[285]+pchar.name+" ?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = DLG_TEXT_Q[286];
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = DLG_TEXT_Q[287];
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = DLG_TEXT_Q[288]
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = DLG_TEXT_Q[289];
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[290];
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = DLG_TEXT_Q[291];
			link.l1 = DLG_TEXT_Q[292];
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = DLG_TEXT_Q[293]+pchar.name+DLG_TEXT_Q[294];
			link.l1 = DLG_TEXT_Q[295];
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = DLG_TEXT_Q[296];
			link.l1 = DLG_TEXT_Q[297];
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = DLG_TEXT_Q[298]+pchar.name+DLG_TEXT_Q[299];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = DLG_TEXT_Q[300]+pchar.name+DLG_TEXT_Q[301];
			link.l1 = DLG_TEXT_Q[302];
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = DLG_TEXT_Q[303];
			link.l1 = DLG_TEXT_Q[304];
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = DLG_TEXT_Q[305]+pchar.name+" ?";
			link.l1 = DLG_TEXT_Q[306];
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = DLG_TEXT_Q[307]+pchar.name+DLG_TEXT_Q[308];
			link.l1 = DLG_TEXT_Q[309];
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = DLG_TEXT_Q[310];
			link.l1 = DLG_TEXT_Q[311];
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = DLG_TEXT_Q[312]+pchar.name+DLG_TEXT_Q[313];
			link.l1 = DLG_TEXT_Q[314];
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = DLG_TEXT_Q[315];
			link.l1 = DLG_TEXT_Q[316];
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = DLG_TEXT_Q[317]+pchar.name+DLG_TEXT_Q[318];
			link.l1 = DLG_TEXT_Q[319];
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = DLG_TEXT_Q[320];
			link.l1 = DLG_TEXT_Q[321];
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = DLG_TEXT_Q[322]+pchar.name+DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = DLG_TEXT_Q[327]+pchar.name+DLG_TEXT_Q[328];
			link.l1 = DLG_TEXT_Q[329];
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = DLG_TEXT_Q[330];
			link.l1 = DLG_TEXT_Q[331];
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = DLG_TEXT_Q[332];
			link.l1 = DLG_TEXT_Q[333];
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = DLG_TEXT_Q[334];
			link.l1 = DLG_TEXT_Q[335];
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = DLG_TEXT_Q[336]+pchar.name+DLG_TEXT_Q[337];
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "aloc0", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = DLG_TEXT_Q[338]+pchar.name+DLG_TEXT_Q[339];
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = DLG_TEXT_Q[340];
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = DLG_TEXT_Q[341];
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = DLG_TEXT_Q[342];
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = DLG_TEXT_Q[343];
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = DLG_TEXT_Q[344];
				link.l1.go = "adversary_5";
			}
			link.l10 = DLG_TEXT_Q[345];
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = DLG_TEXT_Q[346];
			link.l1 = DLG_TEXT_Q[347];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = DLG_TEXT_Q[348];
			link.l1 = DLG_TEXT_Q[349];
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = DLG_TEXT_Q[350];
			link.l1 = DLG_TEXT_Q[351];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = DLG_TEXT_Q[352];
			link.l1 = DLG_TEXT_Q[353];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = DLG_TEXT_Q[354];
			link.l1 = DLG_TEXT_Q[355];
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = DLG_TEXT_Q[356];
			link.l1 = DLG_TEXT_Q[357];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = DLG_TEXT_Q[358];
			link.l1 = DLG_TEXT_Q[359];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[360];
			link.l1 = DLG_TEXT_Q[361];
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = DLG_TEXT_Q[362];
			link.l1 = DLG_TEXT_Q[363];
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = DLG_TEXT_Q[364]+pchar.name+"...";
			link.l1 = DLG_TEXT_Q[365];
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = DLG_TEXT_Q[366];
			link.l1 = DLG_TEXT_Q[367];
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[368];
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = DLG_TEXT_Q[369]+pchar.name+DLG_TEXT_Q[370];
			link.l1 = DLG_TEXT_Q[371];
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[372];
			link.l1 = DLG_TEXT_Q[373];
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = DLG_TEXT_Q[376]+pchar.name+DLG_TEXT_Q[377];
			link.l1 = DLG_TEXT_Q[378];
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = DLG_TEXT_Q[379]+pchar.name+DLG_TEXT_Q[380];
			link.l1 = DLG_TEXT_Q[381];
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = DLG_TEXT_Q[382];
			link.l1 = DLG_TEXT_Q[383];
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = DLG_TEXT_Q[384]+pchar.name+DLG_TEXT_Q[385];
			link.l1 = DLG_TEXT_Q[386];
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = DLG_TEXT_Q[387];
			link.l1 = DLG_TEXT_Q[388];
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = DLG_TEXT_Q[389];
			link.l1 = DLG_TEXT_Q[390];
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[391]+ GetSexPhrase(DLG_TEXT_Q[392],DLG_TEXT_Q[393]) +" !!!", DLG_TEXT_Q[394], DLG_TEXT_Q[395]);
			link.l1 = DLG_TEXT_Q[396];
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}