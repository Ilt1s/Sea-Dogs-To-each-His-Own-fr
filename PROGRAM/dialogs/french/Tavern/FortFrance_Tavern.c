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
			//--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = DLG_TEXT_STR[433];
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = DLG_TEXT_STR[434];
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = DLG_TEXT_STR[435];
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = DLG_TEXT_STR[436];
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = DLG_TEXT_STR[541];
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = DLG_TEXT_STR[542];
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			dialog.text =DLG_TEXT_STR[437]+DLG_TEXT_STR[438];
			link.l1 = DLG_TEXT_STR[439];
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = DLG_TEXT_STR[440];
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = DLG_TEXT_STR[441];
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = DLG_TEXT_STR[443];
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = DLG_TEXT_STR[443];
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = DLG_TEXT_STR[444];
				break;
			}
			dialog.text = DLG_TEXT_STR[445]+DLG_TEXT_STR[446]+DLG_TEXT_STR[447]+pchar.questTemp.Sharlie.Rum.Pass+"'\n"+DLG_TEXT_STR[448];
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = DLG_TEXT_STR[449]+DLG_TEXT_STR[450];
			link.l1 = DLG_TEXT_STR[451];
			link.l1.go = "Sharlie_rum_3";
			link.l2 = DLG_TEXT_STR[452];
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = DLG_TEXT_STR[453];
			link.l1 = DLG_TEXT_STR[454]+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = DLG_TEXT_STR[455];
			link.l1 = DLG_TEXT_STR[456]+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info(DLG_TEXT_STR[474]);
			PlaySound("interface\important_item.wav");
			pchar.quest.Sharlie_rum.win_condition.l1 = "locator";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l2 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l2.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
		break;
		
		case "Sharlie_rum_5":
			dialog.text = DLG_TEXT_STR[457];
			link.l1 = DLG_TEXT_STR[458];
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = DLG_TEXT_STR[459];
			link.l1 = DLG_TEXT_STR[460];
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = DLG_TEXT_STR[461];
			if (sti(pchar.money) >= 50)
			{
				link.l1 = DLG_TEXT_STR[462];
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = DLG_TEXT_STR[463];
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = DLG_TEXT_STR[464];
			link.l1 = DLG_TEXT_STR[465] + npchar.name + DLG_TEXT_STR[466];
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = DLG_TEXT_STR[467];
			if (pchar.money >= 1000)
			{
				link.l1 = DLG_TEXT_STR[468];
				link.l1.go = "Portugal_4";
			}
			link.l2 = DLG_TEXT_STR[469];
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = DLG_TEXT_STR[470];
			link.l1 = DLG_TEXT_STR[471];
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = DLG_TEXT_STR[472];
			link.l1 = DLG_TEXT_STR[473];
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = DLG_TEXT_STR[543];
			link.l1 = DLG_TEXT_STR[544];
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = DLG_TEXT_STR[545];
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = DLG_TEXT_STR[546];
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = DLG_TEXT_STR[547];
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = DLG_TEXT_STR[548];
			link.l1 = DLG_TEXT_STR[549];
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}