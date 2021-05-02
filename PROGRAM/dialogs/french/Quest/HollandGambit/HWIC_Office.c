#include "SD\TEXT\DIALOGS\Quest\HollandGambit\HWIC_Office.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = "Non.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = DLG_TEXT_Q[1];
				link.l1 = DLG_TEXT_Q[2];
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = DLG_TEXT_Q[3];
				link.l1 = DLG_TEXT_Q[4];
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = DLG_TEXT_Q[5];
				link.l1 = DLG_TEXT_Q[6];
				link.l1.go = "HWIC_officer_3";
				link.l2 = DLG_TEXT_Q[7];
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = DLG_TEXT_Q[8];
				link.l1 = DLG_TEXT_Q[9];
				link.l1.go = "HWIC_officer_exit";
				link.l2 = DLG_TEXT_Q[10];
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "HWIC_officer_3";
			link.l2 = DLG_TEXT_Q[13];
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "HWIC_officer_exit";
			LocatorReloadEnterDisable("Villemstad_houseS3", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Villemstad_houseS3", "reload", "reload3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = DLG_TEXT_Q[20];
				link.l1 = DLG_TEXT_Q[21];
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = DLG_TEXT_Q[22];
				link.l1 = DLG_TEXT_Q[23];
				link.l1.go = "fight";
				break;
			}
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = DLG_TEXT_Q[26];
				link.l1 = DLG_TEXT_Q[27];
				link.l1.go = "fight";
				break;
			}
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = DLG_TEXT_Q[29];
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = DLG_TEXT_Q[30];
				link.l1 = DLG_TEXT_Q[31];
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = DLG_TEXT_Q[32];
				link.l1 = DLG_TEXT_Q[33];
				link.l1.go = "fight";
				break;
			}
			dialog.text = DLG_TEXT_Q[34];
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = DLG_TEXT_Q[35];
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = DLG_TEXT_Q[36];
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = DLG_TEXT_Q[37];
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = DLG_TEXT_Q[38];
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = DLG_TEXT_Q[39];
				link.l4.go = "caleuche";	
			}
			link.l9 = DLG_TEXT_Q[40];
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = DLG_TEXT_Q[41];
				link.l1 = DLG_TEXT_Q[42];
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = DLG_TEXT_Q[43];
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = DLG_TEXT_Q[44];
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = DLG_TEXT_Q[45];	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = DLG_TEXT_Q[46];
				link.l1 = DLG_TEXT_Q[47];
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = DLG_TEXT_Q[48];
				link.l1 = DLG_TEXT_Q[49];
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = DLG_TEXT_Q[50];
				link.l1 = DLG_TEXT_Q[51];
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = DLG_TEXT_Q[52]+FindRussianDaysString(sti(fQty))+DLG_TEXT_Q[53]+FindRussianDublonString(sti(npchar.quest.lcc_summ))+DLG_TEXT_Q[54];
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = DLG_TEXT_Q[55];
				link.l1.go = "licence_2";
			}
			link.l2 = DLG_TEXT_Q[56];
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = DLG_TEXT_Q[57];	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "depeshe_dublon";
			link.l2 = DLG_TEXT_Q[66];
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info(DLG_TEXT_Q[67]);
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
			{
				dialog.text = DLG_TEXT_Q[78] + GetFullName(pchar) + DLG_TEXT_Q[79];
				link.l1 = DLG_TEXT_Q[80];
				link.l1.go = "silk_info";
				break;
			}
			dialog.text = DLG_TEXT_Q[81] + GetFullName(pchar) + DLG_TEXT_Q[82];
			if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
			{
				if (GetDataDay() == 1 || GetDataDay() == 15)
				{
					link.l1 = DLG_TEXT_Q[83];
					link.l1.go = "trade_silk";
				}
			}
			link.l2 = DLG_TEXT_Q[84];
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecord("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			dialog.text = DLG_TEXT_Q[91];
			if (GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = DLG_TEXT_Q[92];
				link.l1.go = "trade_silk_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[93];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveItems(pchar, "gold_dublon", 600);
			Log_Info(DLG_TEXT_Q[94]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}