#include "SD\TEXT\DIALOGS\Quest\Saga\Dios.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+DLG_TEXT_Q[1];
				link.l3.go = "island";
			}
			link.l1 = DLG_TEXT_Q[2];
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = DLG_TEXT_Q[3];
			link.l1 = DLG_TEXT_Q[4]+GetFullName(pchar)+DLG_TEXT_Q[5];
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = DLG_TEXT_Q[24]+pchar.name+DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = DLG_TEXT_Q[31]+GetFullName(pchar)+DLG_TEXT_Q[32];
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+DLG_TEXT_Q[33];
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+DLG_TEXT_Q[34];
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+DLG_TEXT_Q[35];
				link.l4.go = "LSC";
			}
			link.l9 = DLG_TEXT_Q[36];
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			for(i=1; i<=24; i++)
			{
				sTemp = IdentifyAdmiralMapLast();
				if (sTemp != "") RemoveItems(pchar, sTemp, 1);
			}
			Log_Info(DLG_TEXT_Q[43]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info(DLG_TEXT_Q[48]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "amap_5";
		break;
		
		case "amap_5":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "amap_6";
		break;
		
		case "amap_6":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
		break;
		
		case "LSC":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam(DLG_TEXT_Q[61], "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = DLG_TEXT_Q[62]+pchar.name+" !";
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = DLG_TEXT_Q[64];
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = DLG_TEXT_Q[65];
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[66];
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info(DLG_TEXT_Q[67]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "LSC_10";
			link.l2 = DLG_TEXT_Q[70];
			link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info(DLG_TEXT_Q[71]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = DLG_TEXT_Q[76]+pchar.name+DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}