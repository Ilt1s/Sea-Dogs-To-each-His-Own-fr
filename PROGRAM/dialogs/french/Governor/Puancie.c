#include "SD\TEXT\DIALOGS\Quest_Governor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = DLG_TEXT_GUB[367]+pchar.name+DLG_TEXT_GUB[368];
				link.l1 = DLG_TEXT_GUB[369];
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = DLG_TEXT_GUB[370]+pchar.name+DLG_TEXT_GUB[371];
				link.l1 = DLG_TEXT_GUB[372];
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 			
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = DLG_TEXT_GUB[477];
					link.l1 = DLG_TEXT_GUB[478];
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = DLG_TEXT_GUB[479];
					link.l1 = DLG_TEXT_GUB[480];
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text =DLG_TEXT_GUB[481];
					link.l1 = "Hum ...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = DLG_TEXT_GUB[482];
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = DLG_TEXT_GUB[483];
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = DLG_TEXT_GUB[484];
						link.l1.go = "patria_8";
					}
					break;
				}
				if (pchar.model != "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[485];
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[486];
					link.l1 = DLG_TEXT_GUB[487];
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+DLG_TEXT_GUB[488];
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = DLG_TEXT_GUB[489];
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = DLG_TEXT_GUB[490];
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+DLG_TEXT_GUB[491];
					link.l1 = DLG_TEXT_GUB[492];
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[493];
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[494];
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = DLG_TEXT_GUB[495];
					else link.l1 = DLG_TEXT_GUB[496];
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[497];
					link.l1 = DLG_TEXT_GUB[498];
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && pchar.model == "Sharle_6" && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = DLG_TEXT_GUB[499];
						link.l1 = DLG_TEXT_GUB[500];
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = DLG_TEXT_GUB[501];
						link.l1 = DLG_TEXT_GUB[502];
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[503];
					link.l1 = DLG_TEXT_GUB[504];
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && pchar.model == "Sharle_6" && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = DLG_TEXT_GUB[505];
					link.l1 = DLG_TEXT_GUB[506];
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = DLG_TEXT_GUB[507];
					link.l1 = DLG_TEXT_GUB[508];
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+DLG_TEXT_GUB[509];
					link.l1 = DLG_TEXT_GUB[510];
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[511];
					link.l1 = DLG_TEXT_GUB[512];
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && pchar.model == "Sharle_6")
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = DLG_TEXT_GUB[513]; // в зависимости от времени сколько добирался
					else sTemp = DLG_TEXT_GUB[514];
					dialog.text = DLG_TEXT_GUB[515];
					link.l1 = DLG_TEXT_GUB[516]+sTemp+DLG_TEXT_GUB[517];
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && pchar.model == "Sharle_6")
				{
					dialog.text = DLG_TEXT_GUB[518];
					link.l1 = DLG_TEXT_GUB[519];
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = DLG_TEXT_GUB[520];
					link.l1 = DLG_TEXT_GUB[521];
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = DLG_TEXT_GUB[522];
					link.l1 = DLG_TEXT_GUB[523];
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = DLG_TEXT_GUB[524];
					link.l1 = DLG_TEXT_GUB[525];
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = DLG_TEXT_GUB[526];
					link.l1 = DLG_TEXT_GUB[527];
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = DLG_TEXT_GUB[528];
					link.l1 = DLG_TEXT_GUB[529];
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = DLG_TEXT_GUB[530];
					link.l1 = DLG_TEXT_GUB[531];
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = DLG_TEXT_GUB[532];
				link.l1 = DLG_TEXT_GUB[533];
				link.l1.go = "exit";
				break;
			}			
			dialog.text = DLG_TEXT_GUB[373];
			link.l1 = DLG_TEXT_GUB[374];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Puancie_Jail":
			dialog.text = DLG_TEXT_GUB[375];
			link.l1 = DLG_TEXT_GUB[376];
			link.l1.go = "Puancie_Jail_1";			
		break;
		
		case "Puancie_Jail_1":
			dialog.text = DLG_TEXT_GUB[377];
			link.l1 = DLG_TEXT_GUB[378];
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = DLG_TEXT_GUB[379];
			link.l1 = DLG_TEXT_GUB[380];
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = DLG_TEXT_GUB[381];
			link.l1 = DLG_TEXT_GUB[382];
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = DLG_TEXT_GUB[383];
			link.l1 = DLG_TEXT_GUB[384];
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = DLG_TEXT_GUB[385];
			link.l1 = DLG_TEXT_GUB[386];
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = DLG_TEXT_GUB[387];
			link.l1 = DLG_TEXT_GUB[388];
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = DLG_TEXT_GUB[389];
			link.l1 = DLG_TEXT_GUB[390];
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = DLG_TEXT_GUB[391];
			link.l1 = DLG_TEXT_GUB[392];
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 5);
			NextDiag.CurrentNode = "First time";
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = DLG_TEXT_GUB[393];
			link.l1 = DLG_TEXT_GUB[394];
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = DLG_TEXT_GUB[395];
			link.l1 = DLG_TEXT_GUB[396];
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = DLG_TEXT_GUB[397];
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = DLG_TEXT_GUB[398];
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[399];
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = DLG_TEXT_GUB[400];
			link.l1 = DLG_TEXT_GUB[401];
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = DLG_TEXT_GUB[402];
			link.l1 = DLG_TEXT_GUB[403];
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = DLG_TEXT_GUB[404];
			link.l1 = DLG_TEXT_GUB[405];
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = DLG_TEXT_GUB[406];
			link.l1 = DLG_TEXT_GUB[407];
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "serve":
			dialog.text = DLG_TEXT_GUB[408]+pchar.name+DLG_TEXT_GUB[409];
			link.l1 = DLG_TEXT_GUB[410];
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = DLG_TEXT_GUB[411]+GetFullName(pchar)+DLG_TEXT_GUB[412];
			link.l1 = DLG_TEXT_GUB[413];
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = DLG_TEXT_GUB[414];
			link.l1 = DLG_TEXT_GUB[415];
			link.l1.go = "serve_3";
			link.l2 = DLG_TEXT_GUB[416];
			link.l2.go = "serve_no";
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = DLG_TEXT_GUB[417];
			link.l1 = DLG_TEXT_GUB[418];
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = DLG_TEXT_GUB[419]+GetFullName(pchar)+DLG_TEXT_GUB[420];
			link.l1 = DLG_TEXT_GUB[421];
			link.l1.go = "serve_4";			
		break;
		
		case "serve_4":
			dialog.text = DLG_TEXT_GUB[422];
			link.l1 = DLG_TEXT_GUB[423];
			link.l1.go = "serve_5";		
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit1");
			EquipCharacterbyItem(pchar, "suit1");
			GiveItem2Character(pchar, "patent_fra");
			EquipCharacterbyItem(pchar, "patent_fra");
			Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			Log_Info(DLG_TEXT_GUB[424]);
			ChangeCharacterNationReputation(pchar, FRANCE, 100);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = DLG_TEXT_GUB[425];
				link.l1 = DLG_TEXT_GUB[426];
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = DLG_TEXT_GUB[427];
				link.l1 = DLG_TEXT_GUB[428];
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = DLG_TEXT_GUB[429];
			link.l1 = DLG_TEXT_GUB[430];
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = DLG_TEXT_GUB[431];
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = DLG_TEXT_GUB[432];
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[433];
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = DLG_TEXT_GUB[434];
			link.l1 = DLG_TEXT_GUB[435];
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;

		// Jason НСО		
		case "patria":
			dialog.text = DLG_TEXT_GUB[534];
			link.l1 = DLG_TEXT_GUB[535];
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = DLG_TEXT_GUB[536];
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = DLG_TEXT_GUB[537];
			link.l1 = DLG_TEXT_GUB[538];
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text =DLG_TEXT_GUB[539];
			link.l1 = DLG_TEXT_GUB[540];
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = DLG_TEXT_GUB[541];
			link.l1 = DLG_TEXT_GUB[542];
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			if (pchar.model == "Sharle_6")
			{
				dialog.text = DLG_TEXT_GUB[543];
			}
			else
			{
				dialog.text = DLG_TEXT_GUB[544];
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = DLG_TEXT_GUB[545];
			link.l1 = DLG_TEXT_GUB[546];
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = DLG_TEXT_GUB[547];
				link.l1 = DLG_TEXT_GUB[548];
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = DLG_TEXT_GUB[549];
				link.l1 = DLG_TEXT_GUB[550];
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = DLG_TEXT_GUB[551];
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = DLG_TEXT_GUB[552];
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[553];
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = DLG_TEXT_GUB[554];
			link.l1 = DLG_TEXT_GUB[555];
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = DLG_TEXT_GUB[556];
			link.l1 = DLG_TEXT_GUB[557];
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = DLG_TEXT_GUB[558];
			link.l1 = DLG_TEXT_GUB[559];
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = DLG_TEXT_GUB[560];
			link.l1 = DLG_TEXT_GUB[561];
			if (pchar.model == "Sharle_6") link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = DLG_TEXT_GUB[562];
			link.l1 = DLG_TEXT_GUB[563];
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = DLG_TEXT_GUB[564];
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 =DLG_TEXT_GUB[565];
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = DLG_TEXT_GUB[566];
			link.l1 = DLG_TEXT_GUB[567];
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text =DLG_TEXT_GUB[568];
			link.l1 = DLG_TEXT_GUB[569];
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = DLG_TEXT_GUB[570];
			link.l1 = DLG_TEXT_GUB[571];
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = DLG_TEXT_GUB[572];
			link.l1 = DLG_TEXT_GUB[573];
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = DLG_TEXT_GUB[574];
			link.l1 = DLG_TEXT_GUB[575];
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = DLG_TEXT_GUB[576];
			link.l1 = DLG_TEXT_GUB[577];
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = DLG_TEXT_GUB[578];
			link.l1 = DLG_TEXT_GUB[579];
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = DLG_TEXT_GUB[580];
			link.l1 = DLG_TEXT_GUB[581];
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = DLG_TEXT_GUB[582];
			link.l1 = DLG_TEXT_GUB[583];
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = DLG_TEXT_GUB[584];
			link.l1 = DLG_TEXT_GUB[585];
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = DLG_TEXT_GUB[586];
			link.l1 = DLG_TEXT_GUB[587];
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = DLG_TEXT_GUB[588];
			link.l1 = DLG_TEXT_GUB[589];
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = DLG_TEXT_GUB[590];
			link.l1 = DLG_TEXT_GUB[591];
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = DLG_TEXT_GUB[592];
			link.l1 = DLG_TEXT_GUB[593];
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = DLG_TEXT_GUB[594];
			link.l1 = DLG_TEXT_GUB[595];
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = DLG_TEXT_GUB[596];
			link.l1 = DLG_TEXT_GUB[597];
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = DLG_TEXT_GUB[598];
			link.l1 = DLG_TEXT_GUB[599];
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = DLG_TEXT_GUB[600];
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = DLG_TEXT_GUB[601];
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = DLG_TEXT_GUB[602];
			link.l1 = DLG_TEXT_GUB[603];
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = DLG_TEXT_GUB[604];
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = DLG_TEXT_GUB[605];
			link.l1 = DLG_TEXT_GUB[606];
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = DLG_TEXT_GUB[607];
			link.l1 = DLG_TEXT_GUB[608];
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = DLG_TEXT_GUB[609];
			link.l1 = DLG_TEXT_GUB[610];
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = DLG_TEXT_GUB[611];
			link.l1 = DLG_TEXT_GUB[612];
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = DLG_TEXT_GUB[613];
			link.l1 = DLG_TEXT_GUB[614];
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = DLG_TEXT_GUB[615];
			link.l1 = DLG_TEXT_GUB[616];
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = DLG_TEXT_GUB[617];
			link.l1 = DLG_TEXT_GUB[618];
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = DLG_TEXT_GUB[619];
			link.l1 = DLG_TEXT_GUB[620];
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = DLG_TEXT_GUB[621];
			link.l1 = DLG_TEXT_GUB[622];
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = DLG_TEXT_GUB[623];
			link.l1 = DLG_TEXT_GUB[624];
			link.l1.go = "patria_53";
		break;
		
		case "patria_53":
			dialog.text = DLG_TEXT_GUB[625];
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = DLG_TEXT_GUB[626];
				link.l1 = DLG_TEXT_GUB[627];
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = DLG_TEXT_GUB[628]+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+DLG_TEXT_GUB[629];
				link.l1 = DLG_TEXT_GUB[630];
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = DLG_TEXT_GUB[631];
			link.l1 = DLG_TEXT_GUB[632];
			link.l1.go = "patria_58";
		break;
		
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = DLG_TEXT_GUB[633];
			link.l1 = DLG_TEXT_GUB[634];
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = DLG_TEXT_GUB[635];
			link.l1 = DLG_TEXT_GUB[636];
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = DLG_TEXT_GUB[637];
			link.l1 = DLG_TEXT_GUB[638];
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = DLG_TEXT_GUB[639];
			link.l1 = DLG_TEXT_GUB[640];
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = DLG_TEXT_GUB[641];
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = DLG_TEXT_GUB[642];
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[643];
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = DLG_TEXT_GUB[644];
			link.l1 = DLG_TEXT_GUB[645];
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = DLG_TEXT_GUB[646];
			link.l1 = DLG_TEXT_GUB[647];
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = DLG_TEXT_GUB[648];
			link.l1 = DLG_TEXT_GUB[649];
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = DLG_TEXT_GUB[650];
			link.l1 = DLG_TEXT_GUB[651];
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = DLG_TEXT_GUB[652];
			link.l1 = DLG_TEXT_GUB[653];
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = DLG_TEXT_GUB[654];
			link.l1 = DLG_TEXT_GUB[655];
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = DLG_TEXT_GUB[656];
			link.l1 = DLG_TEXT_GUB[657];
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = DLG_TEXT_GUB[658];
			link.l1 = DLG_TEXT_GUB[659];
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = DLG_TEXT_GUB[660];
			link.l1 = DLG_TEXT_GUB[661];
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info(DLG_TEXT_GUB[662]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_GUB[663];
			link.l1 = DLG_TEXT_GUB[664];
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = DLG_TEXT_GUB[665];
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = DLG_TEXT_GUB[666];
			link.l1 = DLG_TEXT_GUB[667];
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = DLG_TEXT_GUB[668];
			link.l1 = DLG_TEXT_GUB[669];
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = DLG_TEXT_GUB[670];
			link.l1 = DLG_TEXT_GUB[671];
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = DLG_TEXT_GUB[672];
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = DLG_TEXT_GUB[673];
			link.l1 = DLG_TEXT_GUB[674];
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = DLG_TEXT_GUB[675];
			link.l1 = DLG_TEXT_GUB[676];
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = DLG_TEXT_GUB[677];
			link.l1 = DLG_TEXT_GUB[678];
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = DLG_TEXT_GUB[679];
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			sld.dialog.currentnode = "noel_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = DLG_TEXT_GUB[680];
			link.l1 = DLG_TEXT_GUB[681];
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = DLG_TEXT_GUB[682];
			link.l1 = DLG_TEXT_GUB[683];
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = DLG_TEXT_GUB[684];
			link.l1 = DLG_TEXT_GUB[685];
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = DLG_TEXT_GUB[686];
			link.l1 = DLG_TEXT_GUB[687];
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = DLG_TEXT_GUB[688];
			link.l1 = DLG_TEXT_GUB[689];
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = DLG_TEXT_GUB[690];
			link.l1 = DLG_TEXT_GUB[691];
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = DLG_TEXT_GUB[692];
			link.l1 = DLG_TEXT_GUB[693];
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = DLG_TEXT_GUB[694];
			link.l1 = DLG_TEXT_GUB[695];
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = DLG_TEXT_GUB[696];
			link.l1 = "Hum...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = DLG_TEXT_GUB[697];
			link.l1 = DLG_TEXT_GUB[698];
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = DLG_TEXT_GUB[699];
			link.l1 = DLG_TEXT_GUB[700];
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = DLG_TEXT_GUB[701];
			link.l1 = DLG_TEXT_GUB[702];
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = DLG_TEXT_GUB[703];
			link.l1 = DLG_TEXT_GUB[704];
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = DLG_TEXT_GUB[705];
			link.l1 = DLG_TEXT_GUB[706];
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = DLG_TEXT_GUB[707];
			link.l1 = DLG_TEXT_GUB[708];
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = DLG_TEXT_GUB[709];
			link.l1 = DLG_TEXT_GUB[710];
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = DLG_TEXT_GUB[711];
			link.l1 = DLG_TEXT_GUB[712];
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = DLG_TEXT_GUB[713];
			link.l1 = DLG_TEXT_GUB[714];
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = DLG_TEXT_GUB[715];
			link.l1 = DLG_TEXT_GUB[716];
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info(DLG_TEXT_GUB[717]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_GUB[718];
			link.l1 = DLG_TEXT_GUB[719];
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = DLG_TEXT_GUB[720];
			link.l1 = DLG_TEXT_GUB[721];
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = DLG_TEXT_GUB[722];
			link.l1 = DLG_TEXT_GUB[723];
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = DLG_TEXT_GUB[724];
			link.l1 = DLG_TEXT_GUB[725];
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = DLG_TEXT_GUB[726];
			link.l1 = DLG_TEXT_GUB[727];
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = DLG_TEXT_GUB[728];
			link.l1 = DLG_TEXT_GUB[729];
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = DLG_TEXT_GUB[730];
			link.l1 = DLG_TEXT_GUB[731];
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = DLG_TEXT_GUB[732];
			link.l1 = DLG_TEXT_GUB[733];
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = DLG_TEXT_GUB[734];
			link.l1 = DLG_TEXT_GUB[735];
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = DLG_TEXT_GUB[736];
			link.l1 = DLG_TEXT_GUB[737];
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = DLG_TEXT_GUB[738];
			link.l1 = DLG_TEXT_GUB[739];
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = DLG_TEXT_GUB[740];
			link.l1 = DLG_TEXT_GUB[741];
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = DLG_TEXT_GUB[742];
			link.l1 = DLG_TEXT_GUB[743];
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = DLG_TEXT_GUB[744];
			link.l1 = DLG_TEXT_GUB[745];
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = DLG_TEXT_GUB[746];
			link.l1 = DLG_TEXT_GUB[747];
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = DLG_TEXT_GUB[748];
			link.l1 = DLG_TEXT_GUB[749];
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = DLG_TEXT_GUB[750];
			link.l1 = "...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = DLG_TEXT_GUB[751];
			link.l1 = DLG_TEXT_GUB[752];
			link.l1.go = "patria_prison_2";
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}