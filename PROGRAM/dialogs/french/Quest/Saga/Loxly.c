#include "SD\TEXT\DIALOGS\Quest\Saga\Loxly.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_Q[0];
				link.l1 = DLG_TEXT_Q[1];
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = DLG_TEXT_Q[2];
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = DLG_TEXT_Q[3];
						link.l1 = DLG_TEXT_Q[4];
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = DLG_TEXT_Q[5];
						link.l1 = DLG_TEXT_Q[6];
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = DLG_TEXT_Q[7];
						link.l1 = DLG_TEXT_Q[8];
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = DLG_TEXT_Q[9];
							link.l1 = DLG_TEXT_Q[10];
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = DLG_TEXT_Q[11];
							if (GetCharacterItem(pchar, "gold_dublon") >= 450)
							{
								link.l1 = DLG_TEXT_Q[12];
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = DLG_TEXT_Q[13];
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = DLG_TEXT_Q[14];
							link.l1 = DLG_TEXT_Q[15];
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = DLG_TEXT_Q[16];
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = DLG_TEXT_Q[17];
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = DLG_TEXT_Q[18];
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						dialog.text = DLG_TEXT_Q[19];
						link.l1 = DLG_TEXT_Q[20];
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = DLG_TEXT_Q[21];
					link.l1 = DLG_TEXT_Q[22];
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = DLG_TEXT_Q[23];
					if (GetCharacterItem(pchar, "gold_dublon") >= 450)
					{
						link.l1 = DLG_TEXT_Q[24];
						link.l1.go = "saga_36";
					}
					link.l2 = DLG_TEXT_Q[25];
					link.l2.go = "saga_38";
					link.l3 = DLG_TEXT_Q[26];
					link.l3.go = "exit";
					break;
				}
				dialog.text = DLG_TEXT_Q[27];
				link.l1 = DLG_TEXT_Q[28];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = DLG_TEXT_Q[29];
				link.l1 = DLG_TEXT_Q[30];
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[31];
				link.l1 = DLG_TEXT_Q[32];
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
		break;
		
		case "saga_5":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info(DLG_TEXT_Q[39]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = DLG_TEXT_Q[59];
				link.l1 = DLG_TEXT_Q[60];
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[61];
				link.l1 = DLG_TEXT_Q[62];
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = DLG_TEXT_Q[71];
			if (GetCharacterItem(pchar, "gold_dublon") >= 450)
			{
				link.l1 = DLG_TEXT_Q[72];
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[73];
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = DLG_TEXT_Q[74];
				link.l1 = DLG_TEXT_Q[75];
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[76];
				if (GetCharacterItem(pchar, "gold_dublon") >= 450)
				{
					link.l1 = DLG_TEXT_Q[77];
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = DLG_TEXT_Q[78];
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info(DLG_TEXT_Q[81]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
			LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = DLG_TEXT_Q[87];
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = DLG_TEXT_Q[88];
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[89];
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info(DLG_TEXT_Q[100]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = DLG_TEXT_Q[107];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "loxly_1";
			link.l2 = DLG_TEXT_Q[112];
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = DLG_TEXT_Q[113];
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = DLG_TEXT_Q[114];
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = DLG_TEXT_Q[115];
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = DLG_TEXT_Q[116];
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = DLG_TEXT_Q[117];
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = DLG_TEXT_Q[118];
				Link.l5.go = "contraband";
            }
			Link.l7 = DLG_TEXT_Q[119];
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = DLG_TEXT_Q[120];
			Link.l1 = DLG_TEXT_Q[121];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = DLG_TEXT_Q[122];
			if (iRate > 10 && iRate <= 30) sTemp = DLG_TEXT_Q[123];
			if (iRate > 30 && iRate <= 60) sTemp = DLG_TEXT_Q[124];
			if (iRate > 60 && iRate <= 90) sTemp = DLG_TEXT_Q[125];
			if (iRate > 90) sTemp = DLG_TEXT_Q[126];
			dialog.text = ""+sTemp+DLG_TEXT_Q[127]+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+DLG_TEXT_Q[128]+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = DLG_TEXT_Q[129];
				link.l1.go = "relation";
			}
			link.l2 = DLG_TEXT_Q[130];
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = DLG_TEXT_Q[131]+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl") +DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = DLG_TEXT_Q[134]+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = DLG_TEXT_Q[135];
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = DLG_TEXT_Q[136];
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = DLG_TEXT_Q[137];
			Link.l1 = DLG_TEXT_Q[138];
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}