#include "SD\TEXT\DIALOGS\Quest_Governor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = DLG_TEXT_GUB[436];
				link.l1 = DLG_TEXT_GUB[437];
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = DLG_TEXT_GUB[438];
				link.l1 = DLG_TEXT_GUB[439];
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = DLG_TEXT_GUB[469]+TimeGreeting()+" !";
				link.l1 = TimeGreeting()+DLG_TEXT_GUB[470];
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = DLG_TEXT_GUB[440];
			link.l1 = DLG_TEXT_GUB[441];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_GUB[442];
			link.l1 = DLG_TEXT_GUB[443];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_GUB[444];
			link.l1 = DLG_TEXT_GUB[445];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_GUB[446];
			link.l1 = DLG_TEXT_GUB[447];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_GUB[448];
			link.l1 = DLG_TEXT_GUB[449];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = DLG_TEXT_GUB[450];
			link.l1 = DLG_TEXT_GUB[451];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = DLG_TEXT_GUB[452];
			link.l1 = DLG_TEXT_GUB[453];
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = DLG_TEXT_GUB[454];
			link.l1 = DLG_TEXT_GUB[455];
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = DLG_TEXT_GUB[456];
			link.l1 = DLG_TEXT_GUB[457];
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info(DLG_TEXT_GUB[458]);
			Log_Info(DLG_TEXT_GUB[459]);
			Log_Info(DLG_TEXT_GUB[460]);
			Log_Info(DLG_TEXT_GUB[461]);
			Log_Info(DLG_TEXT_GUB[462]);
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_GUB[463];
			link.l1 = DLG_TEXT_GUB[464];
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = DLG_TEXT_GUB[465];
			link.l1 = DLG_TEXT_GUB[466];
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = DLG_TEXT_GUB[467];
			link.l1 = DLG_TEXT_GUB[468];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			dialog.text = DLG_TEXT_GUB[471];
			link.l1 = DLG_TEXT_GUB[472];
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = DLG_TEXT_GUB[473];
			link.l1 = DLG_TEXT_GUB[474];
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = DLG_TEXT_GUB[475];
			link.l1 = DLG_TEXT_GUB[476];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}