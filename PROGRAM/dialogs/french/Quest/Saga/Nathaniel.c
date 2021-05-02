#include "SD\TEXT\DIALOGS\Quest\Saga\Nathaniel.h"
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
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-02.wav");
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7]+GetFullName(pchar)+DLG_TEXT_Q[8];
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-01.wav");
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "story";
			link.l2 = DLG_TEXT_Q[41];
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = "Wow !";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошел ли игрок Калеуче
		case "story_7":
			dialog.text = DLG_TEXT_Q[52];
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = DLG_TEXT_Q[53];
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[54];
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = DLG_TEXT_Q[71];
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = DLG_TEXT_Q[72];
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[73];
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = DLG_TEXT_Q[76];
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = DLG_TEXT_Q[77];
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[78];
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = DLG_TEXT_Q[83];
			link.l1 = DLG_TEXT_Q[84];
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = DLG_TEXT_Q[98]+pchar.name+DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-03.wav");
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = DLG_TEXT_Q[104]+GetFullName(pchar)+DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = DLG_TEXT_Q[107]+pchar.name+DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = DLG_TEXT_Q[110]+pchar.name+DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info(DLG_TEXT_Q[113]);
			Log_Info(DLG_TEXT_Q[114]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[115]+pchar.name+DLG_TEXT_Q[116];
			link.l1 = DLG_TEXT_Q[117];
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = DLG_TEXT_Q[118]+GetFullName(pchar)+DLG_TEXT_Q[119];
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = DLG_TEXT_Q[120];
				link.l2.go = "caleuche";
			}
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = DLG_TEXT_Q[126]+pchar.name+DLG_TEXT_Q[127];
			link.l1 = DLG_TEXT_Q[128];
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = DLG_TEXT_Q[129];
			link.l1 = DLG_TEXT_Q[130];
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = DLG_TEXT_Q[135]+pchar.name+DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = DLG_TEXT_Q[138]+pchar.name+" !";
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}