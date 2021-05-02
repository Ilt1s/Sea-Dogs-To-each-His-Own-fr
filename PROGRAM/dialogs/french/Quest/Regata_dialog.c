#include "SD\TEXT\DIALOGS\Quest\Regata_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = DLG_TEXT_Q[0] + GetFullName(pchar) + " ?";
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = DLG_TEXT_Q[6];
				link.l1 = DLG_TEXT_Q[7];
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = DLG_TEXT_Q[8];
				link.l1 = DLG_TEXT_Q[9];
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetFunctionTimerCondition("RegataToPortRoyalTimeOver", 0, 0, 31, false);
		break;
		
		//распор€дитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = DLG_TEXT_Q[10];
				link.l1 = DLG_TEXT_Q[11] + GetFullName(pchar) + DLG_TEXT_Q[12];
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[13];
				link.l1 = DLG_TEXT_Q[14];
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабл€ в порту
			{
				dialog.text = DLG_TEXT_Q[15] + GetFullName(pchar) + DLG_TEXT_Q[16];
				if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
				{
					link.l1 = DLG_TEXT_Q[17];
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = DLG_TEXT_Q[18];
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[19];
				link.l1 = DLG_TEXT_Q[20];
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабл€ в порту
				{
					dialog.text = DLG_TEXT_Q[21];
					if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
					{
						link.l1 = DLG_TEXT_Q[22];
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = DLG_TEXT_Q[23];
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = DLG_TEXT_Q[24];
					link.l1 = DLG_TEXT_Q[25];
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[26];
				link.l1 = DLG_TEXT_Q[27];
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Santa Catherina";
		break;
		
		case "Regata_Head_5":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Regata_rate";
			link.l2 = DLG_TEXT_Q[43];
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = DLG_TEXT_Q[44];
				link.l1 = DLG_TEXT_Q[45];
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[46];
				link.l1 = DLG_TEXT_Q[47];
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = DLG_TEXT_Q[48]+pchar.questTemp.Regata.AdversaryName.a+DLG_TEXT_Q[49]+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+DLG_TEXT_Q[49]+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+DLG_TEXT_Q[49]+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+DLG_TEXT_Q[49]+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+DLG_TEXT_Q[49]+pchar.questTemp.Regata.AdversaryShipName.e+DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//сн€ть таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
		break;
		
		case "Regata_Head_13":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = DLG_TEXT_Q[55];
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = DLG_TEXT_Q[56];
				link.l1 = DLG_TEXT_Q[57];
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = DLG_TEXT_Q[58];
				link.l1 = DLG_TEXT_Q[59];
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+DLG_TEXT_Q[60];
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = DLG_TEXT_Q[61];
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = DLG_TEXT_Q[62];
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = DLG_TEXT_Q[63];
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = DLG_TEXT_Q[64];
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[65];
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = DLG_TEXT_Q[66] + GetFullName(pchar) + DLG_TEXT_Q[67];
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = DLG_TEXT_Q[68];
				link.l1.go = "Regata_rate";
			}
			link.l2 = DLG_TEXT_Q[69];
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase(DLG_TEXT_Q[70],DLG_TEXT_Q[71],DLG_TEXT_Q[72]), LinkRandPhrase(DLG_TEXT_Q[73],DLG_TEXT_Q[74],DLG_TEXT_Q[75]));
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[77],DLG_TEXT_Q[78],DLG_TEXT_Q[79]);
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[80],DLG_TEXT_Q[81],DLG_TEXT_Q[82]);
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = DLG_TEXT_Q[84];
				link.l1 = DLG_TEXT_Q[85];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[86];
				link.l1 = DLG_TEXT_Q[87];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info(DLG_TEXT_Q[89]);
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельз€
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ѕ” ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = DLG_TEXT_Q[94]
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = DLG_TEXT_Q[96];
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = DLG_TEXT_Q[97];
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = DLG_TEXT_Q[98];
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = DLG_TEXT_Q[103] + GetFullName(pchar) + DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105]
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = DLG_TEXT_Q[108]+pchar.questTemp.Regata.AdversaryName.(sTemp)+DLG_TEXT_Q[109]+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+DLG_TEXT_Q[110];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[111]+pchar.questTemp.Regata.AdversaryName.b+DLG_TEXT_Q[112]+pchar.questTemp.Regata.AdversaryShipName.b+DLG_TEXT_Q[113];
			}
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = DLG_TEXT_Q[115];
			else sTemp = DLG_TEXT_Q[116];
			dialog.text = DLG_TEXT_Q[117]+sTemp+".";
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "Regata_Contra_4";
			link.l2 = DLG_TEXT_Q[119];
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "Contra_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = DLG_TEXT_Q[122]+iTemp+DLG_TEXT_Q[123];
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = DLG_TEXT_Q[124];
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = DLG_TEXT_Q[125];
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = DLG_TEXT_Q[130]
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "Regata_Padre_exit";
			link.l2 = DLG_TEXT_Q[132];
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = DLG_TEXT_Q[133];
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = DLG_TEXT_Q[134];
				link.l1 = DLG_TEXT_Q[135];
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = DLG_TEXT_Q[136];
				link.l1 = DLG_TEXT_Q[137];
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категори€ - намекнет
			{
				dialog.text = DLG_TEXT_Q[138];
				link.l1 = DLG_TEXT_Q[139];
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категори€ - скажет
			{
				dialog.text = DLG_TEXT_Q[140];
				link.l1 = DLG_TEXT_Q[141];
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 10000)//3 категори€ - расскажет полностью
			{
				dialog.text = DLG_TEXT_Q[142]+pchar.questTemp.Regata.BranderName+DLG_TEXT_Q[143];
				link.l1 = DLG_TEXT_Q[144];
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = DLG_TEXT_Q[145];
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = DLG_TEXT_Q[147] + npchar.name + DLG_TEXT_Q[148];
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(drand(11) > 10)//отлична€ труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(drand(11) < 6)//обычна€ труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хороша€ труба - как пригодитс€
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = DLG_TEXT_Q[152]+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+DLG_TEXT_Q[153];
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = DLG_TEXT_Q[154]+sTemp+DLG_TEXT_Q[155]+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+DLG_TEXT_Q[156];
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+DLG_TEXT_Q[157];
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159] + npchar.name + DLG_TEXT_Q[160];
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл врем€
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = DLG_TEXT_Q[161];
			link.l1 = DLG_TEXT_Q[162] + npchar.name + ".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл врем€
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = DLG_TEXT_Q[163];
			link.l1 = DLG_TEXT_Q[164];
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = DLG_TEXT_Q[165];
			link.l1 = DLG_TEXT_Q[166];
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = DLG_TEXT_Q[167];
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = DLG_TEXT_Q[170];
			link.l1 = DLG_TEXT_Q[171];
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = DLG_TEXT_Q[172]
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = DLG_TEXT_Q[174] + GetFullName(pchar) + DLG_TEXT_Q[175];
			link.l1 = DLG_TEXT_Q[176];
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = DLG_TEXT_Q[179] break;
				case FRANCE: sTemp = DLG_TEXT_Q[180] break;
				case SPAIN: sTemp = DLG_TEXT_Q[181] break;
				case HOLLAND: sTemp = DLG_TEXT_Q[182] break;
			}
			dialog.text = DLG_TEXT_Q[183]+sTemp+"";
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = DLG_TEXT_Q[185];
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = DLG_TEXT_Q[186];
			link.l1 = DLG_TEXT_Q[187];
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = DLG_TEXT_Q[188];
			link.l1 = DLG_TEXT_Q[189];
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//п€тый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удал€ем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
		break;
		
		case "Regata_BridgWom":
			dialog.text = DLG_TEXT_Q[192];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = DLG_TEXT_Q[197] + GetFullName(npchar) + DLG_TEXT_Q[198];
			link.l1 = DLG_TEXT_Q[199];
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = DLG_TEXT_Q[200];
			link.l1 = DLG_TEXT_Q[201];
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим ¬удро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = DLG_TEXT_Q[202];
			link.l1 = DLG_TEXT_Q[203];
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = DLG_TEXT_Q[204];
			link.l1 = DLG_TEXT_Q[205];
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = DLG_TEXT_Q[206];
			link.l1 = DLG_TEXT_Q[207]+pchar.questTemp.Regata.Name+DLG_TEXT_Q[208];
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(drand(2) != 2)
			{
				dialog.text = DLG_TEXT_Q[209]+pchar.questTemp.Regata.Name+DLG_TEXT_Q[210];
				link.l1 = DLG_TEXT_Q[211];
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+DLG_TEXT_Q[212];
				link.l1 = DLG_TEXT_Q[213];
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = DLG_TEXT_Q[214];
			link.l1 = DLG_TEXT_Q[215];
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = DLG_TEXT_Q[216];
			link.l1 = DLG_TEXT_Q[217];
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытатьс€ уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем врем€ п€того перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабл€ в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать врем€
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Santa Catherina")
			{
				dialog.text = DLG_TEXT_Q[218];
				link.l1 = DLG_TEXT_Q[219];
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = DLG_TEXT_Q[220]+GetFullName(pchar)+DLG_TEXT_Q[221]+sti(pchar.questTemp.Regata.FifthTransitionTime)+DLG_TEXT_Q[222];
					link.l1 = DLG_TEXT_Q[223];
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = DLG_TEXT_Q[224]+sti(pchar.questTemp.Regata.FifthTransitionTime)+DLG_TEXT_Q[225];
						link.l1 = DLG_TEXT_Q[226]
						link.l1.go = "Other_result";
					}
					else
					{
						dialog.text = DLG_TEXT_Q[227]+n+DLG_TEXT_Q[228]+sti(pchar.questTemp.Regata.FifthTransitionTime)+DLG_TEXT_Q[229];
						link.l1 = DLG_TEXT_Q[230];
						link.l1.go = "Other_result";
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удал€ем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //сн€ть таймер
		}
		else
		{
			dialog.text = DLG_TEXT_Q[231];
			link.l1 = DLG_TEXT_Q[232];
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = DLG_TEXT_Q[233];
			else sTemp = DLG_TEXT_Q[234];
			dialog.text = DLG_TEXT_Q[235]+sTemp+DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_SetStat(pchar, 9, 1);
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчиститс€ все автоматически
			// слухи
			AddSimpleRumour(DLG_TEXT_Q[238], ENGLAND, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[239], ENGLAND, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[240], ENGLAND, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[241], ENGLAND, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[242], FRANCE, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[243], FRANCE, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[244], FRANCE, 60, 10);
			AddSimpleRumour(DLG_TEXT_Q[245], FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Other_result":
			dialog.text = DLG_TEXT_Q[246];
			link.l1 = DLG_TEXT_Q[247];
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = DLG_TEXT_Q[248];
			link.l1 = DLG_TEXT_Q[249];
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = DLG_TEXT_Q[250]+GetFullName(pchar)+DLG_TEXT_Q[251];
			link.l1 = DLG_TEXT_Q[252];
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = DLG_TEXT_Q[253]+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+DLG_TEXT_Q[254];
			link.l1 = DLG_TEXT_Q[255];
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = DLG_TEXT_Q[258];
						link.l1 = DLG_TEXT_Q[259];
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = DLG_TEXT_Q[260];
						link.l1 = DLG_TEXT_Q[261];
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = DLG_TEXT_Q[262];
					link.l1 = DLG_TEXT_Q[263];
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[264];
				link.l1 = DLG_TEXT_Q[265];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = DLG_TEXT_Q[266];
						link.l1 = DLG_TEXT_Q[267];
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = DLG_TEXT_Q[268];
						link.l1 = DLG_TEXT_Q[269];
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = DLG_TEXT_Q[270];
					link.l1 = DLG_TEXT_Q[271];
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[272];
				link.l1 = DLG_TEXT_Q[273];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = DLG_TEXT_Q[274];
						link.l1 = DLG_TEXT_Q[275];
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = DLG_TEXT_Q[276];
						link.l1 = DLG_TEXT_Q[277];
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = DLG_TEXT_Q[278];
					link.l1 = DLG_TEXT_Q[279];
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[280];
				link.l1 = DLG_TEXT_Q[281];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}