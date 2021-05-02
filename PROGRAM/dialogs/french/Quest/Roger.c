#include "SD\TEXT\DIALOGS\Quest\Roger.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
		break;ar.questTemp.Mtraxx == "jewelry_5")
			{
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pch
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = DLG_TEXT_Q[2];
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[4];
				link.l1 = DLG_TEXT_Q[5];
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "Mtr_officer_2";
		break;
		
		case "Mtr_officer_2":
            dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = DLG_TEXT_Q[12];
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "Mtr_officer_8";
		break;
		
		case "Mtr_officer_8":
            dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 5, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = DLG_TEXT_Q[25];
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = DLG_TEXT_Q[26];
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = DLG_TEXT_Q[27];
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveItems(pchar, "gold_dublon", 250);
			Log_Info(DLG_TEXT_Q[28]);
			PlaySound("interface\important_item.wav");
            dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "Mtr_rosario_8";
		break;
		
		case "Mtr_rosario_5":
            dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = DLG_TEXT_Q[33];
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = DLG_TEXT_Q[34];
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = DLG_TEXT_Q[35];
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = DLG_TEXT_Q[38];
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40]
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = DLG_TEXT_Q[79];
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			sld = characterFromId("Terrax");
		    sld.dialog.currentnode = "mtraxx_34";
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
		break;
		
		case "Jeffry_22":
            dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "Jeffry_23";
		break;
		
		case "Jeffry_23":
            dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = DLG_TEXT_Q[102];
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            dialog.text = RandSwear()+DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-10.wav");
            dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108];
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = DLG_TEXT_Q[109];
			link.l1 = DLG_TEXT_Q[110];
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = DLG_TEXT_Q[113];
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = DLG_TEXT_Q[117];
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
		break;
		
		case "Billy_8":
            dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-07.wav");
            dialog.text = DLG_TEXT_Q[120];
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 1)
			{
				link.l1 = DLG_TEXT_Q[121];
				link.l1.go = "Billy_11";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[122];
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = DLG_TEXT_Q[127]
			link.l1 = DLG_TEXT_Q[128];
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = DLG_TEXT_Q[129];
			link.l1 = DLG_TEXT_Q[130];
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			// ставим прерывание на 10-15 число
			int month = 0;
			pchar.questTemp.Mtraxx.month = 0;
			if (GetDataDay() > 12)
			{
				month = 1;
				pchar.questTemp.Mtraxx.month = 1;
			}
			int hour = 1+rand(2);
			int day = 13+rand(2);
			pchar.quest.mtr_silk_smuggler.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.hour  = hour;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l2 = "location";
			pchar.quest.mtr_silk_smuggler.win_condition.l2.location = "Jamaica";
			pchar.quest.mtr_silk_smuggler.function = "Mtraxx_SilkCreateSmuggler";
			// таймер
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.hour  = hour+2;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.function = "Mtraxx_SilkSmugglerOver";
		break;
		
		// мастеровой с верфи Порт-Рояля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = DLG_TEXT_Q[135];
			link.l1 = DLG_TEXT_Q[136];
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = DLG_TEXT_Q[137];
			link.l1 = DLG_TEXT_Q[138];
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = DLG_TEXT_Q[139];
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = DLG_TEXT_Q[140];
			link.l1 = DLG_TEXT_Q[141];
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = DLG_TEXT_Q[142];
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = DLG_TEXT_Q[143];
			link.l1 = DLG_TEXT_Q[144];
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = DLG_TEXT_Q[145];
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = DLG_TEXT_Q[147];
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = DLG_TEXT_Q[148];
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = DLG_TEXT_Q[149];
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = DLG_TEXT_Q[150];
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = DLG_TEXT_Q[151];
			link.l1 = DLG_TEXT_Q[152];
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = DLG_TEXT_Q[153];
			link.l1 = DLG_TEXT_Q[154];
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = DLG_TEXT_Q[155];
			link.l1 = DLG_TEXT_Q[156];
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = DLG_TEXT_Q[157];
			link.l1 = DLG_TEXT_Q[158];
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = DLG_TEXT_Q[159];
			link.l1 = DLG_TEXT_Q[160];
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = DLG_TEXT_Q[161];
			link.l1 = DLG_TEXT_Q[162]+FindRussianQtyString(i)+DLG_TEXT_Q[163];
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = DLG_TEXT_Q[164];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = DLG_TEXT_Q[165];
			link.l1 = DLG_TEXT_Q[166];
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = DLG_TEXT_Q[170];
			link.l1 = DLG_TEXT_Q[171];
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = DLG_TEXT_Q[172];
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = DLG_TEXT_Q[174];
			link.l1 = DLG_TEXT_Q[175];
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = DLG_TEXT_Q[176];
			link.l1 = DLG_TEXT_Q[177];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = DLG_TEXT_Q[178];
			link.l1 = DLG_TEXT_Q[179];
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = DLG_TEXT_Q[180];
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = DLG_TEXT_Q[185];
			link.l1 = DLG_TEXT_Q[186];
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = DLG_TEXT_Q[187];
			link.l1 = DLG_TEXT_Q[188];
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = DLG_TEXT_Q[189];
			link.l1 = DLG_TEXT_Q[190];
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = DLG_TEXT_Q[191];
			link.l1 = DLG_TEXT_Q[192];
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = DLG_TEXT_Q[209];
			link.l1 = DLG_TEXT_Q[210]+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = DLG_TEXT_Q[211]+GetFullName(pchar)+" ?";
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214];
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = DLG_TEXT_Q[215];
			link.l1 = DLG_TEXT_Q[216];
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = DLG_TEXT_Q[217];
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = DLG_TEXT_Q[218];
			link.l1 = DLG_TEXT_Q[219];
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = DLG_TEXT_Q[220];
				link.l1.go = "Pelly_8";
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = DLG_TEXT_Q[221];
				link.l1.go = "Pelly_11";
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_8":
            dialog.text = DLG_TEXT_Q[222];
			link.l1 = DLG_TEXT_Q[223];
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = DLG_TEXT_Q[224];
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = DLG_TEXT_Q[225];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = DLG_TEXT_Q[226];
			link.l1 = DLG_TEXT_Q[227];
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = DLG_TEXT_Q[228];
			link.l1 = DLG_TEXT_Q[229];
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = DLG_TEXT_Q[234];
			link.l1 = DLG_TEXT_Q[235];
			link.l1.go = "Pelly_18";
		break;
		
		case "Pelly_18":
            dialog.text = DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = DLG_TEXT_Q[238];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = DLG_TEXT_Q[239];
			link.l1 = DLG_TEXT_Q[240];
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = DLG_TEXT_Q[241];
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = DLG_TEXT_Q[242];
			link.l1 = DLG_TEXT_Q[243];
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = DLG_TEXT_Q[244];
			link.l1 = DLG_TEXT_Q[245];
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = DLG_TEXT_Q[246]+GetFullName(characterFromId("Tortuga_usurer"))+DLG_TEXT_Q[247];
			link.l1 = DLG_TEXT_Q[248];
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = DLG_TEXT_Q[249];
			link.l1 = DLG_TEXT_Q[250];
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_27":
            dialog.text = DLG_TEXT_Q[251];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_28":
            dialog.text = DLG_TEXT_Q[252];
			link.l1 = DLG_TEXT_Q[253];
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
            dialog.text = DLG_TEXT_Q[254];
			link.l1 = DLG_TEXT_Q[255];
			link.l1.go = "Pelly_31";
		break;
		
		case "Pelly_31":
            dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = DLG_TEXT_Q[258];
			link.l1 = DLG_TEXT_Q[259];
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = DLG_TEXT_Q[260];
			link.l1 = DLG_TEXT_Q[261];
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = DLG_TEXT_Q[262];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = DLG_TEXT_Q[263];
			link.l1 = DLG_TEXT_Q[264];
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = DLG_TEXT_Q[265];
			link.l1 = DLG_TEXT_Q[266];
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = DLG_TEXT_Q[267];
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = DLG_TEXT_Q[268];
			link.l1 = DLG_TEXT_Q[269]+GetFullName(pchar)+DLG_TEXT_Q[270];
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = DLG_TEXT_Q[271];
			link.l1 = DLG_TEXT_Q[272];
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = DLG_TEXT_Q[273];
			link.l1 = DLG_TEXT_Q[274];
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = DLG_TEXT_Q[275];
			link.l1 = DLG_TEXT_Q[276];
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = DLG_TEXT_Q[277];
			link.l1 = DLG_TEXT_Q[278];
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = DLG_TEXT_Q[279];
			link.l1 = DLG_TEXT_Q[280];
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hm...";
			link.l1 = DLG_TEXT_Q[281];
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = DLG_TEXT_Q[282];
			link.l1 = DLG_TEXT_Q[283];
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = DLG_TEXT_Q[284];
			link.l1 = DLG_TEXT_Q[285];
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = DLG_TEXT_Q[286];
			link.l1 = DLG_TEXT_Q[287];
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = DLG_TEXT_Q[288];
			link.l1 = DLG_TEXT_Q[289];
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = DLG_TEXT_Q[290];
			link.l1 = DLG_TEXT_Q[291];
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = DLG_TEXT_Q[292];
			link.l1 = DLG_TEXT_Q[293];
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = DLG_TEXT_Q[294];
			link.l1 = DLG_TEXT_Q[295];
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = DLG_TEXT_Q[296];
			link.l1 = DLG_TEXT_Q[297];
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = DLG_TEXT_Q[298];
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = DLG_TEXT_Q[299];
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[300];
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = DLG_TEXT_Q[301];
			link.l1 = DLG_TEXT_Q[302];
			link.l1.go = "rocur_21";
		break;
		
		case "rocur_21":
            dialog.text = DLG_TEXT_Q[303];
			link.l1 = DLG_TEXT_Q[304];
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = DLG_TEXT_Q[305];
			link.l1 = DLG_TEXT_Q[306];
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = DLG_TEXT_Q[307];
			link.l1 = DLG_TEXT_Q[308];
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
		break;
		
		case "rocur_wait_2":
            dialog.text = DLG_TEXT_Q[309];
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[310];
			link.l1.go = "rocur_25x";
		break;
		
		case "rocur_25x":
            dialog.text = DLG_TEXT_Q[311];
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = DLG_TEXT_Q[312];
			link.l1 = DLG_TEXT_Q[313];
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = DLG_TEXT_Q[314]+pchar.name+DLG_TEXT_Q[315];
			link.l1 = DLG_TEXT_Q[316];
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = DLG_TEXT_Q[317];
			link.l1 = DLG_TEXT_Q[318];
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = DLG_TEXT_Q[319];
			link.l1 = DLG_TEXT_Q[320];
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = DLG_TEXT_Q[321];
			link.l1 = DLG_TEXT_Q[322];
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = DLG_TEXT_Q[323];
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = DLG_TEXT_Q[324];
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = DLG_TEXT_Q[329];
			link.l1 = DLG_TEXT_Q[330];
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
		case "rocur_42":
            dialog.text = ""+pchar.name+DLG_TEXT_Q[331];
			link.l1 = DLG_TEXT_Q[332];
			link.l1.go = "rocur_43";
		break;
		
		case "rocur_43":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_success";
			AddQuestRecord("Roger_5", "12");
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "rocur_44":
            dialog.text = DLG_TEXT_Q[333]+pchar.name+DLG_TEXT_Q[334];
			link.l1 = DLG_TEXT_Q[335];
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 350);
			TakeNItems(pchar, "jewelry16", 244);
			TakeNItems(pchar, "jewelry14", 63);
            dialog.text = DLG_TEXT_Q[336];
			link.l1 = DLG_TEXT_Q[337];
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 116);
			TakeNItems(pchar, "jewelry16", 81);
			TakeNItems(pchar, "jewelry14", 21);
            dialog.text = DLG_TEXT_Q[338];
			link.l1 = DLG_TEXT_Q[339];
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = DLG_TEXT_Q[340]+pchar.name+DLG_TEXT_Q[341];
			link.l1 = DLG_TEXT_Q[342];
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = DLG_TEXT_Q[343];
			link.l1 = DLG_TEXT_Q[344];
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = DLG_TEXT_Q[345];
			link.l1 = DLG_TEXT_Q[346];
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = DLG_TEXT_Q[347];
			link.l1 = DLG_TEXT_Q[348];
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = DLG_TEXT_Q[349];
			link.l1 = DLG_TEXT_Q[350];
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = DLG_TEXT_Q[351];
			link.l1 = DLG_TEXT_Q[352];
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = DLG_TEXT_Q[353];
			link.l1 = DLG_TEXT_Q[354];
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = DLG_TEXT_Q[355];
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+DLG_TEXT_Q[356];
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = DLG_TEXT_Q[357]+pchar.name+DLG_TEXT_Q[358];
				link.l1 = DLG_TEXT_Q[359];
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[360]+pchar.name+DLG_TEXT_Q[361];
				link.l1 = DLG_TEXT_Q[362];
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = DLG_TEXT_Q[363];
				link.l1 = DLG_TEXT_Q[364];
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[365];
				link.l1 = DLG_TEXT_Q[366];
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = DLG_TEXT_Q[367];
			link.l1 = DLG_TEXT_Q[368];
			link.l1.go = "rocur_62";
		break;
		
		case "rocur_62":
            dialog.text = DLG_TEXT_Q[369];
			link.l1 = DLG_TEXT_Q[370];
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = DLG_TEXT_Q[371];
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = DLG_TEXT_Q[372];
			link.l1 = DLG_TEXT_Q[373];
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+DLG_TEXT_Q[376];
			link.l1 = DLG_TEXT_Q[377];
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = DLG_TEXT_Q[378];
			link.l1 = DLG_TEXT_Q[379];
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = DLG_TEXT_Q[380];
			link.l1 = DLG_TEXT_Q[381];
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = DLG_TEXT_Q[382];
			link.l1 = DLG_TEXT_Q[383];
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = DLG_TEXT_Q[384];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = DLG_TEXT_Q[385];
			link.l1 = DLG_TEXT_Q[386];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
		break;
		
		case "rocur_72":
            dialog.text = DLG_TEXT_Q[387];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = DLG_TEXT_Q[388];
			link.l1 = DLG_TEXT_Q[389];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+DLG_TEXT_Q[390];
			link.l1 = DLG_TEXT_Q[391];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = DLG_TEXT_Q[392];
			link.l1 = DLG_TEXT_Q[393];
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = DLG_TEXT_Q[394];
			link.l1 = DLG_TEXT_Q[395];
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = DLG_TEXT_Q[396];
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = DLG_TEXT_Q[397];
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = DLG_TEXT_Q[398];
			link.l1 = DLG_TEXT_Q[399];
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = DLG_TEXT_Q[400];
			link.l1 = DLG_TEXT_Q[401];
			link.l1.go = "rocur_82";
			link.l2 = DLG_TEXT_Q[402];
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = DLG_TEXT_Q[403];
			link.l1 = "Heh...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = DLG_TEXT_Q[404]+pchar.name+DLG_TEXT_Q[405];
			link.l1 = DLG_TEXT_Q[406];
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = DLG_TEXT_Q[407];
			else sTemp = DLG_TEXT_Q[408];
            dialog.text = DLG_TEXT_Q[409];
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info(DLG_TEXT_Q[410]);
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = DLG_TEXT_Q[411];
			link.l1 = DLG_TEXT_Q[412];
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = DLG_TEXT_Q[413];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
            dialog.text = DLG_TEXT_Q[414];
			link.l1 = DLG_TEXT_Q[415];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_90":
            dialog.text = DLG_TEXT_Q[416]+pchar.name+DLG_TEXT_Q[417];
			link.l1 = DLG_TEXT_Q[418];
			link.l1.go = "rocur_91";
		break;
		
		case "rocur_91":
            dialog.text = DLG_TEXT_Q[419];
			link.l1 = DLG_TEXT_Q[420];
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = DLG_TEXT_Q[421];
			link.l1 = DLG_TEXT_Q[422];
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = DLG_TEXT_Q[423];
			link.l1 = DLG_TEXT_Q[424];
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = DLG_TEXT_Q[425];
			link.l1 = DLG_TEXT_Q[426];
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = DLG_TEXT_Q[427];
			link.l1 = DLG_TEXT_Q[428];
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+DLG_TEXT_Q[429];
			link.l1 = DLG_TEXT_Q[430];
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = DLG_TEXT_Q[431];
			link.l1 = DLG_TEXT_Q[432];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+DLG_TEXT_Q[433];
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = DLG_TEXT_Q[434]+GetFullName(pchar)+DLG_TEXT_Q[435];
			link.l1 = DLG_TEXT_Q[436];
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = DLG_TEXT_Q[437];
			link.l1 = DLG_TEXT_Q[438];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = DLG_TEXT_Q[439];
			link.l1 = DLG_TEXT_Q[440];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = DLG_TEXT_Q[441];
			link.l1 = DLG_TEXT_Q[442];
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = DLG_TEXT_Q[443];
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = DLG_TEXT_Q[444];
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = DLG_TEXT_Q[445];
			link.l1 = DLG_TEXT_Q[446];
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = DLG_TEXT_Q[447];
			link.l1 = DLG_TEXT_Q[448];
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_hayamee";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = DLG_TEXT_Q[449];
			link.l1 = DLG_TEXT_Q[450];
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = DLG_TEXT_Q[451];
			link.l1 = DLG_TEXT_Q[452];
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = DLG_TEXT_Q[453];
			link.l1 = DLG_TEXT_Q[454];
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = DLG_TEXT_Q[455];
			link.l1 = DLG_TEXT_Q[456];
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = DLG_TEXT_Q[457];
			link.l1 = DLG_TEXT_Q[458];
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = DLG_TEXT_Q[459];
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
            dialog.text = DLG_TEXT_Q[460];
			link.l1 = DLG_TEXT_Q[461];
			link.l1.go = "lepricon_14";
		break;
		
		case "lepricon_14":
            dialog.text = DLG_TEXT_Q[462];
			link.l1 = DLG_TEXT_Q[463];
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = DLG_TEXT_Q[464];
			link.l1 = DLG_TEXT_Q[465];
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = DLG_TEXT_Q[466];
			link.l1 = DLG_TEXT_Q[467];
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
            dialog.text = DLG_TEXT_Q[468]
			link.l1 = DLG_TEXT_Q[469];
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = DLG_TEXT_Q[470];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = DLG_TEXT_Q[471];
			link.l1 = DLG_TEXT_Q[472];
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = DLG_TEXT_Q[473];
			link.l1 = DLG_TEXT_Q[474];
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = DLG_TEXT_Q[475];
			link.l1 = DLG_TEXT_Q[476];
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = DLG_TEXT_Q[477];
			link.l1 = DLG_TEXT_Q[478];
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = DLG_TEXT_Q[479];
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = DLG_TEXT_Q[480];
			link.l1 = DLG_TEXT_Q[481];
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = DLG_TEXT_Q[482];
			link.l1 = DLG_TEXT_Q[483];
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = DLG_TEXT_Q[484];
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = DLG_TEXT_Q[485];
			link.l1 = DLG_TEXT_Q[486];
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[487];
			link.l1.go = "tagofa_14";
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Serpentine2", "goto", "goto5");
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "Mtraxx_MeridaWarning", -1);
		break;
		
		case "tagofa_15":
            dialog.text = DLG_TEXT_Q[488];
			link.l1 = DLG_TEXT_Q[489];
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = DLG_TEXT_Q[490];
			link.l1 = DLG_TEXT_Q[491];
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = DLG_TEXT_Q[492];
			link.l1 = DLG_TEXT_Q[493];
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = DLG_TEXT_Q[494];
			link.l1 = DLG_TEXT_Q[495];
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = DLG_TEXT_Q[496];
			link.l1 = DLG_TEXT_Q[497];
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = DLG_TEXT_Q[498];
			link.l1 = DLG_TEXT_Q[499];
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = DLG_TEXT_Q[500];
			link.l1 = DLG_TEXT_Q[501];
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = DLG_TEXT_Q[502];
			link.l1 = DLG_TEXT_Q[503];
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = DLG_TEXT_Q[504];
			link.l1 = "...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":8=
            dialog.text = DLG_TEXT_Q[505];
			link.l1 = DLG_TEXT_Q[506];
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = DLG_TEXT_Q[507];
			link.l1 = DLG_TEXT_Q[508];
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = DLG_TEXT_Q[509];
			link.l1 = DLG_TEXT_Q[510];
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = DLG_TEXT_Q[511];
			link.l1 = DLG_TEXT_Q[512];
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[513];
			link.l1.go = "merida_head_5";
		break;
		
		case "merida_head_5":
            dialog.text = DLG_TEXT_Q[514];
			link.l1 = DLG_TEXT_Q[515];
			link.l1.go = "merida_head_6";
		break;
		
		case "merida_head_6":
            dialog.text = DLG_TEXT_Q[516];
			link.l1 = DLG_TEXT_Q[517];
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = DLG_TEXT_Q[518];
			link.l1 = DLG_TEXT_Q[519];
			link.l1.go = "merida_head_8";
		break;
		
		case "merida_head_8":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
		break;
		
		case "merida_head_9":
            dialog.text = DLG_TEXT_Q[520];
			link.l1 = DLG_TEXT_Q[521];
			link.l1.go = "merida_head_10";
		break;
		
		case "merida_head_10":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;
		
		case "merida_head_sleep":
            dialog.text = DLG_TEXT_Q[522];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+DLG_TEXT_Q[523];
			link.l1 = DLG_TEXT_Q[524];
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = DLG_TEXT_Q[525];
			link.l1 = DLG_TEXT_Q[526];
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = DLG_TEXT_Q[527];
			link.l1 = DLG_TEXT_Q[528];
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            dialog.text = DLG_TEXT_Q[529];
			link.l1 = TimeGreeting()+DLG_TEXT_Q[530]+GetFullName(pchar)+DLG_TEXT_Q[531];
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            dialog.text = DLG_TEXT_Q[532]+GetFullName(pchar)+DLG_TEXT_Q[533];
			link.l1 = DLG_TEXT_Q[534];
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = DLG_TEXT_Q[535];
			link.l1 = DLG_TEXT_Q[536];
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = DLG_TEXT_Q[537];
			link.l1 = DLG_TEXT_Q[538];
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = DLG_TEXT_Q[539];
			link.l1 = DLG_TEXT_Q[540];
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = DLG_TEXT_Q[541];
			link.l1 = DLG_TEXT_Q[542];
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            dialog.text = DLG_TEXT_Q[543];
			link.l1 = DLG_TEXT_Q[544];
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = DLG_TEXT_Q[545];
			link.l1 = DLG_TEXT_Q[546];
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = DLG_TEXT_Q[547];
			link.l1 = DLG_TEXT_Q[548];
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = DLG_TEXT_Q[549];
			link.l1 = DLG_TEXT_Q[550];
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = DLG_TEXT_Q[551];
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = DLG_TEXT_Q[552];
			else link.l1 = DLG_TEXT_Q[553];
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = DLG_TEXT_Q[554];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            dialog.text = DLG_TEXT_Q[555];
			link.l1 = DLG_TEXT_Q[556];
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = DLG_TEXT_Q[557];
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = DLG_TEXT_Q[558];
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = DLG_TEXT_Q[559];
				link.l1 = DLG_TEXT_Q[560];
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = DLG_TEXT_Q[561];
				link.l1 = DLG_TEXT_Q[562];
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = DLG_TEXT_Q[563];
			link.l1 = DLG_TEXT_Q[564];
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = DLG_TEXT_Q[565];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = DLG_TEXT_Q[566];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = DLG_TEXT_Q[567];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = DLG_TEXT_Q[568];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = DLG_TEXT_Q[569];
			link.l1 = DLG_TEXT_Q[570];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
            dialog.text = DLG_TEXT_Q[571];
			link.l1 = DLG_TEXT_Q[572]
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = DLG_TEXT_Q[573];
			link.l1 = DLG_TEXT_Q[574];
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+DLG_TEXT_Q[575];
			link.l1 = DLG_TEXT_Q[576];
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = DLG_TEXT_Q[577];
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = DLG_TEXT_Q[578];
			link.l1 = RandSwear()+DLG_TEXT_Q[579];
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = DLG_TEXT_Q[580];
			link.l1 = DLG_TEXT_Q[581];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = DLG_TEXT_Q[582];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = DLG_TEXT_Q[583];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = DLG_TEXT_Q[584]+RandSwear()+"";
			link.l1 = DLG_TEXT_Q[585];
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
            dialog.text = DLG_TEXT_Q[586];
			link.l1 = DLG_TEXT_Q[587]+GetFullName(pchar)+DLG_TEXT_Q[588];
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = DLG_TEXT_Q[589]+GetFullName(pchar)+DLG_TEXT_Q[590];
			link.l1 = DLG_TEXT_Q[591];
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = DLG_TEXT_Q[592];
			link.l1 = DLG_TEXT_Q[593];
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+DLG_TEXT_Q[594];
			link.l1 = DLG_TEXT_Q[595];
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = DLG_TEXT_Q[596];
			link.l1 = DLG_TEXT_Q[597];
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = DLG_TEXT_Q[598];
			link.l1 = DLG_TEXT_Q[599];
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = DLG_TEXT_Q[600];
			link.l1 = DLG_TEXT_Q[601];
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = DLG_TEXT_Q[602];
			link.l1 = DLG_TEXT_Q[603];
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = DLG_TEXT_Q[604];
			link.l1 = DLG_TEXT_Q[605];
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = DLG_TEXT_Q[606];
			link.l1 = DLG_TEXT_Q[607];
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = DLG_TEXT_Q[608];
			link.l1 = DLG_TEXT_Q[609];
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = DLG_TEXT_Q[610];
			link.l1 = DLG_TEXT_Q[611];
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = DLG_TEXT_Q[612];
			link.l1 = DLG_TEXT_Q[613];
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = DLG_TEXT_Q[614];
			link.l1 = DLG_TEXT_Q[615];
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
            dialog.text = DLG_TEXT_Q[616];
			link.l1 = DLG_TEXT_Q[617];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
/*		case "carpenter_17":
            dialog.text = DLG_TEXT_Q[618];
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = DLG_TEXT_Q[619];
				link.l1.go = "carpenter_18";
				break;
			}
			link.l2 = DLG_TEXT_Q[620];
			link.l2.go = "repair";
			link.l3 = DLG_TEXT_Q[621];
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (sti(npchar.portman > 0))
			{
				link.l4 = DLG_TEXT_Q[622];
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = DLG_TEXT_Q[623];
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = DLG_TEXT_Q[624];
				link.l5.go = "storadge_3";
			}
			link.l99 = DLG_TEXT_Q[625];
			link.l99.go = "carpenter_exit";
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = DLG_TEXT_Q[626];
			link.l1 = DLG_TEXT_Q[627];
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = DLG_TEXT_Q[628];
			link.l1 = DLG_TEXT_Q[629];
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = DLG_TEXT_Q[630];
			link.l1 = DLG_TEXT_Q[631];
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = DLG_TEXT_Q[632];
			link.l1 = DLG_TEXT_Q[633];
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = DLG_TEXT_Q[634];
			link.l1 = DLG_TEXT_Q[635];
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = DLG_TEXT_Q[636];
				link.l1 = DLG_TEXT_Q[637];
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[638];
				link.l1 = DLG_TEXT_Q[639];
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = DLG_TEXT_Q[640];
			link.l1 = DLG_TEXT_Q[641];
			link.l1.go = "shipstock";
			link.l2 = DLG_TEXT_Q[642];
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if (sti(npchar.portman) == 2)
			{
				dialog.text = DLG_TEXT_Q[643];
				link.l1 = DLG_TEXT_Q[644];
				link.l1.go = "carpenter_exit";
				break;
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = DLG_TEXT_Q[645];
				link.l1 = DLG_TEXT_Q[646];
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = DLG_TEXT_Q[647];
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = DLG_TEXT_Q[668];
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = DLG_TEXT_Q[669];
			Link.l1 = DLG_TEXT_Q[650];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_Q[651];
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = DLG_TEXT_Q[652];
			Link.l1 = DLG_TEXT_Q[653];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_Q[654];
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = DLG_TEXT_Q[655];
			Link.l1 = DLG_TEXT_Q[656];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_Q[657];
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = DLG_TEXT_Q[658];
			Link.l1 = DLG_TEXT_Q[659];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_Q[660];
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				dialog.text = DLG_TEXT_Q[661];
				Link.l1 = DLG_TEXT_Q[662];
				Link.l1.go = "carpenter_exit";
				break;
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = DLG_TEXT_Q[663];
				Link.l1 = DLG_TEXT_Q[664];
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = DLG_TEXT_Q[665]+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+DLG_TEXT_Q[666]+chref.Ship.Name+DLG_TEXT_Q[667];
			Link.l1 = DLG_TEXT_Q[668];
			Link.l1.go = "ShipStock_3";
			Link.l2 = DLG_TEXT_Q[669];
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = DLG_TEXT_Q[670];
			Link.l1 = DLG_TEXT_Q[671];
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = DLG_TEXT_Q[672];
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = DLG_TEXT_Q[673];
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[674];
				link.l1 = DLG_TEXT_Q[675];
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = DLG_TEXT_Q[676];
			link.l1 = DLG_TEXT_Q[677];
			link.l1.go = "ShipStockManBack2";
			link.l2 = DLG_TEXT_Q[678];
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = DLG_TEXT_Q[679];
			link.l1 = DLG_TEXT_Q[680];
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = DLG_TEXT_Q[681];
			link.l1 = DLG_TEXT_Q[682];
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = DLG_TEXT_Q[683];
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;*/
		
		// Мирабель
		case "mirabelle":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = DLG_TEXT_Q[684];
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("VOICE\Russian\other\RapersGirl-01.wav");
            dialog.text = DLG_TEXT_Q[685]+pchar.name+DLG_TEXT_Q[686];
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[687];
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = DLG_TEXT_Q[688];
			link.l1 = DLG_TEXT_Q[689];
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = DLG_TEXT_Q[690];
			link.l1 = DLG_TEXT_Q[691];
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = DLG_TEXT_Q[692];
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = DLG_TEXT_Q[693];
			link.l1 = DLG_TEXT_Q[694];
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = DLG_TEXT_Q[695];
			link.l1 = DLG_TEXT_Q[696];
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = DLG_TEXT_Q[697];
			link.l1 = DLG_TEXT_Q[698];
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = DLG_TEXT_Q[699];
			link.l1 = DLG_TEXT_Q[700];
			link.l1.go = "mirabelle_15";
		break;
		
		case "mirabelle_15":
            dialog.text = DLG_TEXT_Q[701]+pchar.name+DLG_TEXT_Q[702];
			link.l1 = DLG_TEXT_Q[703];
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = DLG_TEXT_Q[704];
			link.l1 = DLG_TEXT_Q[705];
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[706];
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = DLG_TEXT_Q[707];
			link.l1 = DLG_TEXT_Q[708];
			link.l1.go = "mirabelle_20";
		break;
		
		case "mirabelle_20":
            dialog.text = DLG_TEXT_Q[709]+pchar.name+DLG_TEXT_Q[710];
			link.l1 = DLG_TEXT_Q[711];
			link.l1.go = "mirabelle_21";
		break;
		
		case "mirabelle_21":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex10.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 5);
			LAi_SetCurHPMax(pchar);
			DoQuestFunctionDelay("Mtraxx_PasqualeMirabellaSex", 12.0);
			ChangeCharacterAddressGroup(pchar, "IslaMona_TwoFloorRoom", "goto", "goto2");
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
		break;
		
		case "mirabelle_22":
            dialog.text = DLG_TEXT_Q[712]+pchar.name+DLG_TEXT_Q[713];
			link.l1 = DLG_TEXT_Q[714];
			link.l1.go = "mirabelle_23";
		break;
		
		case "mirabelle_23":
            dialog.text = DLG_TEXT_Q[715];
			link.l1 = DLG_TEXT_Q[716];
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = DLG_TEXT_Q[717];
			link.l1 = "...";
			link.l1.go = "mirabelle_25";
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+DLG_TEXT_Q[718]+pchar.name+DLG_TEXT_Q[719];
			link.l1 = RandSwear()+""+RandPhraseSimple(DLG_TEXT_Q[720],DLG_TEXT_Q[721])+DLG_TEXT_Q[722];
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = DLG_TEXT_Q[723];
				link.l2.go = "mirabelle_sex";
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = DLG_TEXT_Q[724];
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[725],DLG_TEXT_Q[726]);
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_27";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_27":
            dialog.text = DLG_TEXT_Q[727];
			link.l1 = DLG_TEXT_Q[728];
			link.l1.go = "mirabelle_28";
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = DLG_TEXT_Q[729]+pchar.name+DLG_TEXT_Q[730]+pchar.name+" ?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+DLG_TEXT_Q[731]+pchar.name+DLG_TEXT_Q[732];
			link.l1 = DLG_TEXT_Q[733];
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = DLG_TEXT_Q[734];
			link.l1 = DLG_TEXT_Q[735];
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = DLG_TEXT_Q[736];
			link.l1 = DLG_TEXT_Q[737];
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = DLG_TEXT_Q[738];
			link.l1 = DLG_TEXT_Q[739];
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = DLG_TEXT_Q[740]+pchar.name+DLG_TEXT_Q[741];
			link.l1 = DLG_TEXT_Q[742];
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = DLG_TEXT_Q[743];
			link.l1 = DLG_TEXT_Q[744];
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = DLG_TEXT_Q[745];
			link.l1 = DLG_TEXT_Q[746];
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = DLG_TEXT_Q[747]+pchar.name+DLG_TEXT_Q[748];
			link.l1 = DLG_TEXT_Q[749];
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = DLG_TEXT_Q[750];
			link.l1 = DLG_TEXT_Q[751];
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = DLG_TEXT_Q[752];
			link.l1 = DLG_TEXT_Q[753];
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_40":
            dialog.text = DLG_TEXT_Q[754]+pchar.name+DLG_TEXT_Q[755];
			link.l1 = DLG_TEXT_Q[756];
			link.l1.go = "mirabelle_41";
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+DLG_TEXT_Q[757]+pchar.name+DLG_TEXT_Q[758];
			link.l1 = ""+LinkRandPhrase(DLG_TEXT_Q[759], DLG_TEXT_Q[760],DLG_TEXT_Q[761])+DLG_TEXT_Q[762];
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = DLG_TEXT_Q[763];
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = DLG_TEXT_Q[764];
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = DLG_TEXT_Q[765];
			link.l1 = TimeGreeting()+DLG_TEXT_Q[766];
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = DLG_TEXT_Q[767];
			link.l1 = DLG_TEXT_Q[768];
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = DLG_TEXT_Q[769];
			link.l1 = DLG_TEXT_Q[770];
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = DLG_TEXT_Q[771];
			link.l1 = DLG_TEXT_Q[772];
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = DLG_TEXT_Q[773];
			link.l1 = DLG_TEXT_Q[774];
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = DLG_TEXT_Q[775];
			link.l1 = DLG_TEXT_Q[776];
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = DLG_TEXT_Q[777];
			link.l1 = DLG_TEXT_Q[778];
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = DLG_TEXT_Q[779];
			link.l1 = DLG_TEXT_Q[780];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[781];
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[782];
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = DLG_TEXT_Q[783];
			link.l1 = DLG_TEXT_Q[784];
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[785];
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = DLG_TEXT_Q[786];
			link.l1 = DLG_TEXT_Q[787];
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = DLG_TEXT_Q[788];
			link.l1 = DLG_TEXT_Q[789];
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = DLG_TEXT_Q[790];
			link.l1 = RandSwear()+DLG_TEXT_Q[791];
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = DLG_TEXT_Q[792];
			link.l1 = DLG_TEXT_Q[793];
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = DLG_TEXT_Q[794];
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = DLG_TEXT_Q[795];
			link.l1 = DLG_TEXT_Q[796];
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = DLG_TEXT_Q[797];
			link.l1 = DLG_TEXT_Q[798];
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = DLG_TEXT_Q[799];
			link.l1 = RandSwear()+DLG_TEXT_Q[800];
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("VOICE\Russian\hambit\Gr_officiant_1.wav");
            dialog.text = DLG_TEXT_Q[801];
			link.l1 = DLG_TEXT_Q[802];
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = DLG_TEXT_Q[803];
			link.l1 = DLG_TEXT_Q[804];
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = DLG_TEXT_Q[805];
			link.l1 = DLG_TEXT_Q[806];
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = DLG_TEXT_Q[807];
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "M-m-m...";
			link.l1 = DLG_TEXT_Q[808];
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = DLG_TEXT_Q[809];
			link.l1 = DLG_TEXT_Q[810];
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = DLG_TEXT_Q[811];
			link.l1 = DLG_TEXT_Q[812];
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = DLG_TEXT_Q[813];
			link.l1 = DLG_TEXT_Q[814];
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = DLG_TEXT_Q[815];
			link.l1 = DLG_TEXT_Q[816];
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = DLG_TEXT_Q[817];
			link.l1 = DLG_TEXT_Q[818];
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm...";
			link.l1 = DLG_TEXT_Q[819];
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = DLG_TEXT_Q[820];
			link.l1 = DLG_TEXT_Q[821];
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = DLG_TEXT_Q[822];
			link.l1 = DLG_TEXT_Q[823];
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = DLG_TEXT_Q[824];
			link.l1 = DLG_TEXT_Q[825];
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = DLG_TEXT_Q[826];
			link.l1 = DLG_TEXT_Q[827];
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = DLG_TEXT_Q[828];
			link.l1 = DLG_TEXT_Q[829];
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = DLG_TEXT_Q[830];
			link.l1 = DLG_TEXT_Q[831];
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = DLG_TEXT_Q[832];
			link.l1 = DLG_TEXT_Q[833];
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = DLG_TEXT_Q[834];
			link.l1 = DLG_TEXT_Q[835];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = DLG_TEXT_Q[836];
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = DLG_TEXT_Q[837];
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[838];
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveItems(pchar, "gold_dublon", 200);
			Log_Info(DLG_TEXT_Q[839]);
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = DLG_TEXT_Q[840];
			link.l1 = DLG_TEXT_Q[841];
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = DLG_TEXT_Q[842];
			link.l1 = DLG_TEXT_Q[843];
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = DLG_TEXT_Q[844];
			link.l1 = DLG_TEXT_Q[845];
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = DLG_TEXT_Q[846];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("VOICE\Russian\OliverTrast01.wav");
            dialog.text = DLG_TEXT_Q[847];
			link.l1 = DLG_TEXT_Q[848];
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
            dialog.text = DLG_TEXT_Q[849]
			link.l1 = DLG_TEXT_Q[850];
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = DLG_TEXT_Q[851];
			link.l1 = DLG_TEXT_Q[852];
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = DLG_TEXT_Q[853];
			link.l1 = DLG_TEXT_Q[854];
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = DLG_TEXT_Q[855];
			link.l1 = DLG_TEXT_Q[856];
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            dialog.text = DLG_TEXT_Q[857];
			link.l1 = DLG_TEXT_Q[858];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "mishelle_sleep":
            dialog.text = DLG_TEXT_Q[859];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = DLG_TEXT_Q[860];
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = DLG_TEXT_Q[861];
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
		break;
		
		case "terrax_sleep_1":
            dialog.text = DLG_TEXT_Q[862];
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha !!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;
	}
} 
