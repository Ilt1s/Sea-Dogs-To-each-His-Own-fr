#include "SD\TEXT\DIALOGS\Quest\Mangarosa.h"
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = DLG_TEXT_Q[2];
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[4];
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = DLG_TEXT_Q[5];
			link.l1 = DLG_TEXT_Q[6];
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = DLG_TEXT_Q[7];
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = DLG_TEXT_Q[8];
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = DLG_TEXT_Q[11];
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = DLG_TEXT_Q[12];
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = DLG_TEXT_Q[21];
			if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = DLG_TEXT_Q[22];
				link.l1.go = "amelia_8";
			}
			link.l2 = DLG_TEXT_Q[23];
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = DLG_TEXT_Q[24];
				link.l1 = DLG_TEXT_Q[25];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[26];
				if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
				{
					link.l1 = DLG_TEXT_Q[27];
					link.l1.go = "amelia_8";
				}
				link.l2 = DLG_TEXT_Q[28];
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = DLG_TEXT_Q[29];
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = DLG_TEXT_Q[30];
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = DLG_TEXT_Q[31];
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = DLG_TEXT_Q[32];
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveItems(pchar, "gold_dublon", 300);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info(DLG_TEXT_Q[39]);
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
	}
} 
