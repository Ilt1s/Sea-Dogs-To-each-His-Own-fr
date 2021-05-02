#include "SD\TEXT\DIALOGS\Quest\Sharlie\Vicento.h"
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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = DLG_TEXT_Q[0];
				link.l1 = DLG_TEXT_Q[1];
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = DLG_TEXT_Q[2];
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = DLG_TEXT_Q[4];
				link.l1 = DLG_TEXT_Q[5];
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = DLG_TEXT_Q[6];
				link.l1 = TimeGreeting()+DLG_TEXT_Q[7];
				link.l1.go = "guardoftruth_17";
				break;
			}
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info(DLG_TEXT_Q[14]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[15]+pchar.name+DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = DLG_TEXT_Q[24];
			else sTemp = "Hm... ";
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = sTemp+DLG_TEXT_Q[26];
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = DLG_TEXT_Q[31]+pchar.name+DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", DLG_TEXT_Q[52]);
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", DLG_TEXT_Q[53]);
			}
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_Q[54]+pchar.name+DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info(DLG_TEXT_Q[62]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+DLG_TEXT_Q[83];
			link.l1 = DLG_TEXT_Q[84];
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = DLG_TEXT_Q[98]+pchar.name+DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = DLG_TEXT_Q[105]+pchar.name+DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = DLG_TEXT_Q[114];
			link.l1 = DLG_TEXT_Q[115];
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = DLG_TEXT_Q[116];
			link.l1 = DLG_TEXT_Q[117];
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info(DLG_TEXT_Q[124]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[125]+GetFullName(pchar)+DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}